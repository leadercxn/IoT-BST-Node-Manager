/* Copyright (c) 2021 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

#ifndef _NODE_MANAGER_H
#define _NODE_MANAGER_H

typedef struct
{
    uint8_t  sn[8];
    uint8_t  nwkskey[16];
    uint8_t  appskey[16];

    uint32_t devaddr;

    uint32_t priority;
    uint32_t up_fcnt;
    uint32_t down_fcnt;

    uint16_t rnti;
} node_info_t;

int node_info_table_lock(void);

int node_info_table_unlock(void);
/**
 * @brief 把节点信息链表中的数据更新到文件中
 */
int node_info_update(void);

/**
 * @brief 节点信息表初始化
 * 根据节点信息表文件，创建链表
 */
int node_info_table_init(void);

/**
 * @brief 根据设备sn，遍历链表中节点,搜索节点
 * @param sn[8]  [in]   要搜索的sn
 * @param p_node_info  [out]   拷贝搜索到的节点信息放到该指针指向的内存，可为NULL    
 * @return 0    找到sn相同的节点
 *         -1   找不到相同sn的节点
 */
int node_info_find(uint8_t sn[8],node_info_t *p_node_info);

/**
 * @brief 增加节点到链表中
 * @param p_node_info [in]  指向节点信息，不能为NULL
 * @return  0 添加成功
 *          -1 添加失败
 */
int node_info_add(node_info_t *p_node_info);

/**
 * @brief 根据设备sn，遍历链表中节点,删除节点信息
 * @param sn[8]  [in]   要删除的节点sn
 * @return  0  删除成功
 *          -1 删除失败
 */
int node_info_del(uint8_t sn[8]);

/**
 * @brief 增加节点到链表中，并更新保存到文件中
 */
int node_info_add_with_updte(node_info_t *p_node_info);

/**
 * @brief 删除节点信息，并更新保存到文件中
 */
int node_info_del_with_updte(uint8_t sn[8]);

/**
 * 关闭节点信息表文件
 */
int node_info_table_close(void);

/**
 * @brief 获取节点总数
 */
int node_cnt_get(void);
#endif
