/* Copyright (c) 2018 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/file.h>
#include <errno.h>      /* error messages */

#include "util.h"

static int m_pid_fd = 0;

int util_singleton_process(const char *path)
{
    int n = 0;
    char pid_str[16] = {0};
    struct flock lock;

    m_pid_fd = open(path, O_RDWR | O_CREAT, 0444);
    if (-1 == m_pid_fd) {
        return -1;
    }

    /* lock file */
    lock.l_type   = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start  = 0;
    lock.l_len    = 0;

    if (fcntl(m_pid_fd, F_SETLK, &lock) < 0) {
        close(m_pid_fd);
        return -1;
    }

    sprintf(pid_str, "%d", (int)getpid());

    /* write pid into file */
    n = write (m_pid_fd, pid_str, strlen(pid_str));
    if ( n != (int)strlen(pid_str)) {
        close(m_pid_fd);
        return -1;
    }

    return 0;
}

int util_singleton_close(void)
{
    return close(m_pid_fd);
}

bool hexstr_verify(const char *in)
{
    size_t len = strlen(in);

    if(len%2 != 0){
        return false;
    }

    for(size_t i = 0; i < len; i++){
        if(!isxdigit(in[i])){
            return false;
        }
    }
    return true;
}

size_t hexstr_decode(const char *in, uint8_t *out)
{
    size_t in_len = strlen(in);
    size_t index = 0;
    uint8_t *p = out;
    char tmp[3] = {0};
    unsigned char c;

    if(!hexstr_verify(in)){
        return 0;
    }

    for(size_t i = 0; i < in_len;) {
        tmp[0] = in[i++];
        tmp[1] = in[i++];
        sscanf((const char *)tmp, "%hhx", (unsigned char *)&c);
        p[index++] = c;
    }

    return index;
}

int util_strsplit(char *str, char separator, char **pp_array, int *p_num, int max_num)
{
    int num = 0;

    if(pp_array == NULL || p_num == NULL || max_num == 0){
        return -1;
    }

    pp_array[num++] = str;

    while ((str = strchr(str, separator)) != NULL){
        *str = '\0';
        str++;
        pp_array[num++] = str;

        if (num >= max_num){
            break;
        }
    }

    *p_num = num;

    return 0;
}

