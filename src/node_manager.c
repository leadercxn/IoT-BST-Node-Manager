/* === Includes ====================================================== */
#include <stdint.h>		/* C99 types */
#include <stdbool.h>	/* bool type */
#include <stdio.h>		/* fopen, fputs */
#include <string.h>		/* memset, memcpy */
#include <signal.h>		/* sigaction */
#include <time.h>		/* time, clock_gettime, strftime, gmtime */
#include <sys/time.h>	/* timeval */
#include <sys/types.h>	/* timeval */
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>		/* getopt, access */
#include <stdlib.h>		/* atoi, exit */
#include <errno.h>		/* error messages */
#include <math.h>		/* modf */
#include <pthread.h>
#include <errno.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "util.h"
#include "queue.h"

#include "node_manager.h"

#define NODE_INFO_TABLE_FILE_PATH   "/root/node_table"                      //节点信息列表路径
#define NODE_INFO_TABLE_FILE        "/root/node_table/node_info_table"

#define NODE_INFO_TABLE_LOCK_FILE   "/var/run/node_info_table.pid"          //文件锁

static int m_node_info_table_fd = -1;           //节点信息列表的文件描述符
static int m_node_info_table_json_fd = -1;      //

static int m_node_info_table_lock_fd = -1;

static int m_node_cnt;          //终端节点总数

struct node_data_s
{
    node_info_t node_info;
    STAILQ_ENTRY(node_data_s) next;
};
typedef struct node_data_s node_data_t;

STAILQ_HEAD(, node_data_s) m_node_data_queue = STAILQ_HEAD_INITIALIZER(m_node_data_queue);  //定义一个单向尾队列

int main(int argc, char **argv)
{
    node_info_table_init();

    node_info_table_close();
    return 0;
}

/**
 * Function for creating pid lock file
 */
static int file_lock(const char *p_path, int *p_fd)
{
    int i;
    int fd;
    struct flock lock;
    int pid = 0;
    char buf[10] = {0};

    fd = open(p_path, O_RDWR | O_CREAT, 0444);
    if(fd == -1){
        return -1;
    }

    lock.l_type = F_WRLCK; 
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(fd, F_SETLK, &lock) < 0)
    {
        close(fd);
        return -1;
    } 

    pid = getpid();
    sprintf(buf, "%d", (int) pid); 
    if ((i = write (fd, buf, strlen(buf))) != (int)strlen(buf))
    {
        close(fd);
        return -1;
    }
    *p_fd = fd;
    return 0;
}

int node_info_table_lock(void)
{
    file_lock(NODE_INFO_TABLE_LOCK_FILE,&m_node_info_table_lock_fd);
}

int node_info_table_unlock(void)
{
    close(m_node_info_table_lock_fd);
}

/**
 * @brief 把节点信息链表中的数据更新到文件中
 */
int node_info_update(void)
{
    int ret = 0; 

    lseek(m_node_info_table_fd,0,SEEK_SET);

    ret = write(m_node_info_table_fd,&m_node_cnt,sizeof(m_node_cnt));
    if(ret < 0)
    {
        printf("write err\n");
        return -1;
    }

    lseek(m_node_info_table_fd,sizeof(m_node_cnt),SEEK_SET);

    node_data_t *p_w_node_data;
    STAILQ_FOREACH(p_w_node_data, &m_node_data_queue, next)           //遍历链表
    {
        ret = write(m_node_info_table_fd,&p_w_node_data->node_info,sizeof(node_info_t));
        if(ret < 0)
        {
            printf("write err\n");
            return -1;
        }

        lseek(m_node_info_table_fd,0,SEEK_CUR);
    }

    return 0;
}

/**
 * @brief 节点信息表初始化
 * 根据节点信息表文件，创建链表
 */
int node_info_table_init(void)
{
    int     ret = 0; 

    ret = access(NODE_INFO_TABLE_FILE_PATH, F_OK);
    if(ret < 0)
    {
        printf("there have no %s dir\n",NODE_INFO_TABLE_FILE_PATH);

        ret = mkdir(NODE_INFO_TABLE_FILE_PATH, 0755);
        if(ret < 0)
        {
            printf("mkdir dir %s err\n",NODE_INFO_TABLE_FILE_PATH);
            return -1;
        }
        printf("mkdir dir %s done\n",NODE_INFO_TABLE_FILE_PATH);
    }

    m_node_info_table_fd = open(NODE_INFO_TABLE_FILE, O_CREAT | O_RDWR , 0755);
    if(m_node_info_table_fd < 0)
    {
        printf("open %s err\n",NODE_INFO_TABLE_FILE);

        return -1;
    }

    ret = read(m_node_info_table_fd,&m_node_cnt,sizeof(m_node_cnt));
    if(ret < 0)
    {
        printf("read err\n");
        return -1;
    }

    lseek(m_node_info_table_fd,sizeof(m_node_cnt),SEEK_SET);

    for(int i = 0;i < m_node_cnt; i++)
    {
        node_data_t *p_r_node_data = (node_data_t *)malloc(sizeof(node_data_t));

        ret = read(m_node_info_table_fd,&p_r_node_data->node_info,sizeof(node_info_t));
        if(ret < 0)
        {
            printf("write err\n");
            return -1;
        }
        lseek(m_node_info_table_fd,0,SEEK_CUR);

        STAILQ_INSERT_TAIL(&m_node_data_queue, p_r_node_data, next);  //往后添加节点
    }

    return 0;
}

/**
 * @brief 根据设备sn，遍历链表中节点,搜索节点
 * @param sn[8]  [in]   要搜索的sn
 * @param p_node_info  [out]   拷贝搜索到的节点信息放到该指针指向的内存，可为NULL    
 * @return 0    找到sn相同的节点
 *         -1   找不到相同sn的节点
 */
int node_info_find(uint8_t sn[8],node_info_t *p_node_info)
{
    if(m_node_cnt == 0)
    {
        return -1;
    }

    node_data_t *p_node_data ;

    STAILQ_FOREACH(p_node_data, &m_node_data_queue, next)           //遍历链表
    {
        if(memcmp(p_node_data->node_info.sn, sn, 8) == 0 )
        {
            if(p_node_info)
            {
                memcpy(p_node_info,&p_node_data->node_info,sizeof(node_info_t));
            }

            return 0;
        }
    }

    return -1;
}

/**
 * @brief 增加节点到链表中
 * @param p_node_info [in]  指向节点信息，不能为NULL
 * @return  0 添加成功
 *          -1 添加失败
 */
int node_info_add(node_info_t *p_node_info)
{
    if(p_node_info == NULL)
    {
        return -1;
    }

    int ret = 0;

    ret = node_info_find(p_node_info->sn,NULL);

    if(ret == 0)    //节点已存在,无需添加
    {
        return 0;
    }

    node_data_t *p_node_data = (node_data_t *)malloc(sizeof(node_data_t));

    memcpy(&p_node_data->node_info,p_node_info,sizeof(node_info_t));

    STAILQ_INSERT_TAIL(&m_node_data_queue, p_node_data, next);  //往后添加节点

    m_node_cnt++;
    return 0;
}

/**
 * @brief 根据设备sn，遍历链表中节点,删除节点信息
 * @param sn[8]  [in]   要删除的节点sn
 * @return  0  删除成功
 *          -1 删除失败
 */
int node_info_del(uint8_t sn[8])
{
    if(m_node_cnt == 0)
    {
        return -1;
    }

    node_data_t *p_node_data ;

    STAILQ_FOREACH(p_node_data, &m_node_data_queue, next)           //遍历链表
    {
        if(memcmp(p_node_data->node_info.sn, sn, 8) == 0 )
        {
            STAILQ_REMOVE(&m_node_data_queue, p_node_data, node_data_s, next);

            free(p_node_data);

            m_node_cnt--;
            return 0;
        }
    }

    return -1;
}

/**
 * @brief 增加节点到链表中，并更新保存到文件中
 */
int node_info_add_with_updte(node_info_t *p_node_info)
{
    int ret = 0;
    ret = node_info_add(p_node_info);
    if(ret < 0)
    {
        return ret;
    }
    ret = node_info_update();

    return ret;
}

/**
 * @brief 删除节点信息，并更新保存到文件中
 */
int node_info_del_with_updte(uint8_t sn[8])
{
    int ret = 0;
    ret = node_info_del(sn);
    if(ret < 0)
    {
        return ret;
    }
    ret = node_info_update();

    return ret;
}

/**
 * 关闭节点信息表文件
 */
int node_info_table_close(void)
{
    return close(m_node_info_table_fd);
}

/**
 * @brief 获取节点总数
 */
int node_cnt_get(void)
{
    return m_node_cnt;
}
