/* Copyright (c) 2018 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

/* fix an issue between POSIX and C99 */
#if __STDC_VERSION__ >= 199901L
    #define _XOPEN_SOURCE 600
#else
    #define _XOPEN_SOURCE 500
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "util.h"
#include "util_shell.h"

#define BUF_SIZE    1024

int util_shell_execute(const char *cmd, char *result)
{
    int rc = 0;
    size_t n = 0;
    FILE *fp = NULL;
    char *cmd_buf = NULL;
    char *rlt_buf = NULL;

    cmd_buf = (char *) malloc(BUF_SIZE);
    rlt_buf = (char *) malloc(BUF_SIZE);
    if ((cmd_buf == NULL) || (rlt_buf == NULL)) {
        if (rlt_buf != NULL)
            free(rlt_buf);

        if (cmd_buf != NULL)
            free(cmd_buf);

        return -1;
    } else {
        memset(cmd_buf, 0, BUF_SIZE);
        memset(rlt_buf, 0, BUF_SIZE);
    }

    if (!cmd || !result) {
        free(cmd_buf);
        free(rlt_buf);
        return -1;
    }

    if (strlen(cmd) <= BUF_SIZE) {
        strncpy(cmd_buf, cmd, strlen(cmd));
    } else {
        free(cmd_buf);
        free(rlt_buf);
        return -1;
    }

    fp = popen(cmd_buf, "r");
    if (fp == NULL) {
        free(cmd_buf);
        free(rlt_buf);
        return -1;
    }

    memset(rlt_buf, 0, BUF_SIZE);
    n = fread(rlt_buf, sizeof(char), BUF_SIZE, fp);
    UNUSED_VARIABLE(n);
    if (strlen(rlt_buf) <= BUF_SIZE) {
        memcpy(result, rlt_buf, strlen(rlt_buf));
    } else {
        pclose(fp);
        free(cmd_buf);
        free(rlt_buf);
        return -1;
    }

    rc = pclose(fp);
    if (rc == -1) {
        free(cmd_buf);
        free(rlt_buf);
        return -1;
    }

    free(cmd_buf);
    free(rlt_buf);

    return 0;
}

int util_shell_execute_with_no_results(const char *cmd)
{
    int rc = 0;
    FILE *fp = NULL;
    char *cmd_buf = NULL;

    cmd_buf = (char *) malloc(BUF_SIZE);
    if (cmd_buf == NULL) {
        return -1;
    } else {
        memset(cmd_buf, 0, BUF_SIZE);
    }

    if (!cmd) {
        free(cmd_buf);
        return -1;
    }

    if (strlen(cmd) <= BUF_SIZE) {
        strncpy(cmd_buf, cmd, strlen(cmd));
    } else {
        free(cmd_buf);
        return -1;
    }

    fp = popen(cmd_buf, "r");
    if (fp == NULL) {
        free(cmd_buf);
        return -1;
    }

    rc = pclose(fp);
    if (rc == -1) {
        free(cmd_buf);
        return -1;
    }

    free(cmd_buf);
    return 0;
}
