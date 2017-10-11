/************************************************************************************
 * @file    link_list.c
 * @brief   链表操作函数
 * @version 1.0
 * @author  ZY
 * @date    2017.10.4
 *                   History
 *          Modified by :
 *          Date        :
 *          Modification:
 ***********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"include/common.h"
#include<syslog.h>

/****************************************************
 * @brief    创建一定数量的空链表
 * @param    head：链表头节点
 *           num：空节点数量
 * @return   无
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
void create_link_list(PSTU head,int num)
{
    int i = 0;
    PSTU node1 = head;
    PSTU node2 = head;

    for(i = 0;i < num;i++)
    {
        node1 = (PSTU)malloc(sizeof(STU));
        node1->next = NULL;
        node2->next = node1;
        node2 = node1;
    }
}

/****************************************************
 * @brief    释放头节点外的其它节点空间
 * @param    head:链表头节点
 * @return   无
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
void destroy_link_list(PSTU head)
{
    PSTU node_tmp = head->next;

    while(node_tmp)
    {
        head->next = node_tmp->next;
        free(node_tmp);
        node_tmp = head->next;
    }
    syslog(LOG_DEBUG,"free ok");
}

/****************************************************
 * @brief    向空节点输入数据
 * @param    head:链表头节点
 * @return   无
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
void input_data(PSTU head)
{
    PSTU node = head->next;

    while(node)
    {
        scanf("%d%s%s%d%d%d",&node->id,node->name,node->sex,&node->math,&node->english,&node->c_language);
        node = node->next;
    }
}

/****************************************************
 * @brief    输出链表中的数据
 * @param    head:链表头节点
 * @return   成功返回0,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
int output_data(PSTU head)
{
    PSTU node = head->next;

    if(!node)
        return -1;

    printf("学号\t姓名\t性别\t数学成绩\t英语成绩\tc语言成绩\n");
    while(node)
    {
        printf("%d\t%s\t%s\t%d\t%d\t%d\n",node->id,node->name,node->sex,node->math,node->english,node->c_language);
        node = node->next;
    }
    return 0;
}

/****************************************************
 * @brief    查询满足学号条件的节点
 * @param    head:链表头节点
 *           num:学号
 * @return   成功返回查到的节点地址,失败返回NULL
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
PSTU select_link_list(PSTU head,int num)
{
    PSTU node = head->next;

    while(node)
    {
        if(num == node->id)
            return node;

        node = node->next;
    }
    return NULL;
}

/****************************************************
 * @brief    在链表末尾添加节点
 * @param    head：链表头节点
 *           node:要添加的节点
 * @return   无
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
void add_link_list(PSTU head,PSTU node)
{
    PSTU node_tmp = head;

    while(node_tmp->next)
    {
        node_tmp = node_tmp->next;
    }

    node->next = NULL;
    node_tmp->next = node;
}

/****************************************************
 * @brief    按学号删除节点
 * @param    head:链表头节点
 *           num：学号
 * @return   成功返回0,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
int delete_link_list(PSTU head,int num)
{
    PSTU node_tmp1 = head;
    PSTU node_tmp2 = head->next;
    int flag = 0;

    while(node_tmp2)
    {
        if(num == node_tmp2->id)
        {
            flag = 1;
            break;
        }
        node_tmp1 = node_tmp2;
        node_tmp2 = node_tmp2->next;
    }
    if(!flag)
        return -1;
    else
    {
        node_tmp1->next = node_tmp2->next;
        free(node_tmp2);
    }
    return 0;
}

/****************************************************
 * @brief    按学号顺序插入节点
 * @param    head:链表头节点
 *           node:要插入的节点
 * @return   无
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
void insert_link_list(PSTU head,PSTU node)
{
    PSTU node_tmp1 = head;
    PSTU node_tmp2 = head->next;

    while(node_tmp2)
    {
        if(node_tmp2->id > node->id)
        {
            node_tmp1->next = node;
            node->next = node_tmp2;
            return ;
        }
        node_tmp1 = node_tmp2;
        node_tmp2 = node_tmp2->next;
    }
    node_tmp1->next = node;
}

/****************************************************
 * @brief    更新节点中的数据
 * @param    head:链表头节点
 *           node:要更新的节点内容
 * @return   成功返回0,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
int update_link_list(PSTU head,PSTU node)
{
    PSTU node_tmp = head->next;
    int flag      = 0;

    while(node_tmp)
    {
        if(node->id == node_tmp->id)
        {
            strcpy(node_tmp->name,node->name);
            strcpy(node_tmp->sex,node->sex);
            node_tmp->math = node->math;
            node_tmp->english = node->english;
            node_tmp->c_language = node->c_language;
            flag = 1;
        }
        node_tmp = node_tmp->next;
    }

    if(!flag)
        return -1;
    return 0;
}
