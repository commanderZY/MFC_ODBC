/************************************************************************************
 * @file    link_list.h
 * @brief   链表操作函数头文件，提供链表操作的函数接口
 * @version 1.0
 * @author  ZY
 * @date    2017.10.6
 *                   History
 *          Modified by :
 *          Date        :
 *          Modification:
 ***********************************************************************************/
#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#include"common.h"

/***************************************************
 * @brief   创建空白链表
 * @param   head：链表头节点
 *          num：节点数量
 * @retval  无
 * @par     Usage：
 *          create_link_list(head,3);
 * @par     Tag: 
 *          该函数需要和input_data()函数配套使用
 ***************************************************/
void create_link_list(PSTU head,int num);

/***************************************************
 * @brief   释放初头节点外的链表其它节点空间
 * @param   head：链表头节点
 * @retval  无
 * @par     Usage：
 *          destroy_link_list(head);
 * @par     Tag: 
 ***************************************************/
void destroy_link_list(PSTU head);

/***************************************************
 * @brief   向链表中输入数据
 * @param   head:链表头节点
 * @retval  无
 * @par     Usage：
 *          input_data(head);
 * @par     Tag: 
 *          该函数和create_link_list()函数配套使用
 ***************************************************/
void input_data(PSTU head);

/***************************************************
 * @brief   输出链表中的数据
 * @param   head：链表头节点
 * @retval  成功返回0,失败返回-1
 * @par     Usage：
 *          output_data(head);
 * @par     Tag: 
 ***************************************************/
int output_data(PSTU head);

/***************************************************
 * @brief   按学号查找节点
 * @param   head:链表头节点
 *          num：要查找的学号
 * @retval  成功返回查到的节点地址,失败返回NULL
 * @par     Usage：
 *          select_link_list(head,4);
 * @par     Tag: 
 ***************************************************/
PSTU select_link_list(PSTU head,int num);

/***************************************************
 * @brief   添加含有数据的节点
 * @param   head:链表头节点
 *          node：要添加的节点
 * @retval  无
 * @par     Usage：
 *          add_link_list(head,node);
 * @par     Tag: 
 ***************************************************/
void add_link_list(PSTU head,PSTU node);

/***************************************************
 * @brief   删除节点
 * @param   head:链表头节点
 *          num：要删除的节点的学号
 * @retval  成功返回0,失败返回-1
 * @par     Usage：
 *          destroy_link_list(head,3);
 * @par     Tag: 
 ***************************************************/
int delete_link_list(PSTU head,int num);

/***************************************************
 * @brief   按学号大小插入节点
 * @param   head:链表头节点
 *          node:要插入的节点
 * @retval  无
 * @par     Usage：
 *          insert_link_list(head,node);
 * @par     Tag: 
 ***************************************************/
void insert_link_list(PSTU head,PSTU node);

/***************************************************
 * @brief   按学号更新节点
 * @param   head:链表头节点
 *          node:要更新的信息
 * @retval  成功返回0,失败返回-1
 * @par     Usage：
 *          update_link_list(head,node);
 * @par     Tag: 
 ***************************************************/
int update_link_list(PSTU head,PSTU node);

#endif
