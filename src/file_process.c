/************************************************************************************
 * @file    file_process.c
 * @brief   文件操作函数实现
 * @version 1.0
 * @author  ZY
 * @date    2017.10.7
 *                   History
 *          Modified by :
 *          Date        :
 *          Modification:
 ***********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"include/common.h"
#include<syslog.h>

/****************************************************
 * @brief    将链表数据保存到文件
 * @param    head:链表头节点
 * @return   成功返回0,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
int save_data_to_file(PSTU head)
{
    int n     = 0;
    PSTU node = head->next;
    FILE* fp  = NULL;

    /*打开文件,如果文件不存在创建文件*/
    fp = fopen("../doc/stu","r+");
    if(!fp)
        fp = fopen("../doc/stu","w+");

    /*计算文件长度,并将文件大小存入文件头4个字节*/
    fseek(fp,0,2);
    n = ftell(fp);
    if(!n)
    {
        n = 4;
        fwrite(&n,4,1,fp);
        rewind(fp);
    }
    else
    {
        rewind(fp);
        fread(&n,4,1,fp);
    }

    /*判断链表中是否有数据*/
    if(!node)
    {
        fclose(fp);
        syslog(LOG_ERR,"node is NULL");
        return -1;
    }

    /*跳过文件头前4个字节，开始将链表数据写入文件*/
    fseek(fp,n,0);
    while(node)
    {
        fwrite(node,sizeof(STU),1,fp);
        node = node->next;
    }

    /*计算文件长度，如果超过大小限制重新开始，否则继续*/
    n = ftell(fp);
    if(n == FILE_MAX_LEN)
    {
        rewind(fp);
        n = 4;
    }
    else
        rewind(fp);
    
    /*将文件大小写入头4个字节后关闭文件*/
    fwrite(&n,4,1,fp);
    fclose(fp);
}

/****************************************************
 * @brief    载入文件数据到链表
 * @param    head：链表头节点
 * @return   成功返回0,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
int load_data_from_file(PSTU head)
{
    FILE* fp = NULL;
    int num  = 0;
    PSTU node_tmp1 = head;
    PSTU node_tmp2 = head;

    /*以只读方式打开文件*/
    fp = fopen("../doc/stu","r");
    if(!fp)
    {
        syslog(LOG_ERR,"open file error");
        return -1;
    }

    /*找到尾节点然后跳过文件头4个字节*/
    while(node_tmp1->next)
    {
        node_tmp1 = node_tmp1->next;
        node_tmp2 = node_tmp1;
    }
    fseek(fp,4,SEEK_SET);

    /*将数据读到节点中并添加到链表末尾*/
    while(1)
    {
        node_tmp1 = (PSTU)malloc(sizeof(STU));
        num = fread(node_tmp1,sizeof(STU),1,fp);
        if(!num)
        {
            free(node_tmp1);
            break;
        }

        node_tmp1->next = NULL;
        node_tmp2->next = node_tmp1;
        node_tmp2 = node_tmp1;
    }

    /*关闭文件*/
    fclose(fp);
    return 0;
}
