/************************************************************************************
 * @file    database_process.c
 * @brief   数据库与链表交互的函数实现
 * @version 1.0
 * @author  ZY
 * @date    2017.10.9
 *                   History
 *          Modified by :
 *          Date        :
 *          Modification:
 ***********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql.h>
/*#include"mysql_include/mysql.h"*/
#include"include/common.h"
#include"include/mysql_fun.h"
#include<syslog.h>

/****************************************************
 * @brief    保存链表数据到mysql数据库
 * @param    head:链表头节点
 * @return   成功返回0,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
int save_data_to_database(PSTU head)
{
    MYSQL mysql;
    PSTU node = head->next;
    char sql[SQL_LEN] = {'\0'};
    int ret           = 0;

    /*连接数据库*/
    ret = mysql_fun_connect(&mysql);
    if(ret < 0)
    {
        syslog(LOG_ERR,"connect mysql failed");
        return -1;
    }
    syslog(LOG_INFO,"connect mysql success");

    /*将节点中的数据发送到数据库*/
    while(node)
    {
        memset(sql,'\0',sizeof(sql));
        ret = sprintf(sql,"insert into class value(%d,'%s','%s',%d,%d,%d,%d)",node->id,node->name,node->sex,node->math,node->english,node->c_language,DEFAULT_FLAG);
        syslog(LOG_DEBUG,"%d%s%s%d%d%d",node->id,node->name,node->sex,node->math,node->english,node->c_language);
        ret = mysql_fun_send(&mysql,sql);
        if(ret < 0)
        {
            syslog(LOG_ERR,"mysql send failed:%s",mysql_error(&mysql));
            return -1;
        }
        syslog(LOG_DEBUG,"send ok");
        node = node->next;
    }
    
    /*断开连接*/
    mysql_fun_close(&mysql);
    return 0;
}

/****************************************************
 * @brief    更新数据库中的flag字段为标志flag
 * @param    mysql：数据库句柄
 *           num:需要更新的flag数量
 * @return   成功返回0,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
int update_flag(MYSQL* mysql,int num)
{
    char sql[SQL_LEN] = {'\0'};
    int ret           = 0;

    while(num)
    {
        memset(sql,'\0',sizeof(sql));
        sprintf(sql,"update %s set flag = %d",TABLE_NAME,LOAD_FLAG);
        ret = mysql_fun_send(mysql,sql);
        if(ret < 0)
        {
            syslog(LOG_ERR,"update load_flag failed");
            return -1;
        }
        num--;
    }
    return 0;
}

/****************************************************
 * @brief    置flag字段值为默认值
 * @param    mysql：数据库句柄
 *           id：需要置flag的学号即id字段值
 * @return   成功返回0,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
int set_flag(MYSQL* mysql,int id)
{
    char sql[SQL_LEN] = {'\0'};
    int ret           = 0;

    sprintf(sql,"update %s set flag = %d where id = %d",TABLE_NAME,DEFAULT_FLAG,id);
    ret = mysql_fun_send(mysql,sql);
    if(ret < 0)
        return -1;
    return 0;
}

/****************************************************
 * @brief    载入数据库信息到链表
 * @param    head:链表头节点
 * @return   成功返回0,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
int load_data_from_database(PSTU head)
{
    MYSQL mysql;
    char sql[SQL_LEN]   = {'\0'};
    char name[NAME]     = {'\0'};
    char* name_point    = NULL;
    char sex[SEX_LEN]   = {'\0'};
    char* sex_point     = NULL;
    int id              = 0;
    int math            = 0;
    int english         = 0;
    int c_language      = 0;
    int num             = 0;
    int ret             = 0;
    PSTU node_tmp1      = head;
    PSTU node_tmp2      = head;

    /*连接数据库*/
    ret = mysql_fun_connect(&mysql);
    if(ret < 0)
    {
        syslog(LOG_ERR,"connect mysql failed");
        return -1;
    }
    syslog(LOG_INFO,"connect mysql success");

    /*获取flag数量*/
    sprintf(sql,"select flag from %s where flag = %d",TABLE_NAME,DEFAULT_FLAG);
    num = mysql_fun_get_num(&mysql,sql);
    if(num < 0)
    {
        syslog(LOG_ERR,"get num failed");
        return -1;
    }
    syslog(LOG_DEBUG,"get num is %d",num);

    /*更新flag，准备载入数据*/
    ret = update_flag(&mysql,num);
    if(ret < 0)
        return -1;
    syslog(LOG_DEBUG,"update_flag ok");
    
    while(num)
    {
        /*获取更新了flag的对应id值*/
        memset(sql,'\0',sizeof(sql));
        sprintf(sql,"select id from %s where flag!= %d",TABLE_NAME,DEFAULT_FLAG);
        id = mysql_fun_get_int_res(&mysql,sql);
        if(ret < 0)
        {
            syslog(LOG_ERR,"get id failed");
            return -1;
        }
        
        /*获取姓名*/
        memset(sql,'\0',sizeof(sql));
        sprintf(sql,"select name from %s where flag!= %d",TABLE_NAME,DEFAULT_FLAG);
        name_point = mysql_fun_get_char_res(&mysql,sql,name);
        if(!name)
        {
            syslog(LOG_ERR,"get name failed");
            return -1;
        }

        /*获取性别*/
        memset(sql,'\0',sizeof(sql));
        sprintf(sql,"select sex from %s where flag!= %d",TABLE_NAME,DEFAULT_FLAG);
        sex_point = mysql_fun_get_char_res(&mysql,sql,sex);
        if(!sex)
        {
            syslog(LOG_ERR,"get sex failed");
            return -1;
        }

        /*获取数学成绩*/
        memset(sql,'\0',sizeof(sql));
        sprintf(sql,"select math from %s where flag!= %d",TABLE_NAME,DEFAULT_FLAG);
        math = mysql_fun_get_int_res(&mysql,sql);
        if(ret < 0)
        {
            syslog(LOG_ERR,"get math failed");
            return -1;
        }
        
        /*获取英语成绩*/
        memset(sql,'\0',sizeof(sql));
        sprintf(sql,"select english from %s where flag!= %d",TABLE_NAME,DEFAULT_FLAG);
        english = mysql_fun_get_int_res(&mysql,sql);
        if(ret < 0)
        {
            syslog(LOG_ERR,"get english failed");
            return -1;
        }

        /*获取c语言成绩*/
        memset(sql,'\0',sizeof(sql));
        sprintf(sql,"select c_language from %s where flag!= %d",TABLE_NAME,DEFAULT_FLAG);
        c_language = mysql_fun_get_int_res(&mysql,sql);
        if(ret < 0)
        {
            syslog(LOG_ERR,"get c_language failed");
            return -1;
        }
        syslog(LOG_DEBUG,"id=%d,name=%s,sex=%s,math=%d,english=%d,c_language=%d",id,name,sex,math,english,c_language);

        /*将获取到的数据存入链表节点并形成链表*/
        node_tmp1 = (PSTU)malloc(sizeof(STU));
        node_tmp1->id = id;
        strcpy(node_tmp1->name,name);
        strcpy(node_tmp1->sex,sex);
        node_tmp1->math = math;
        node_tmp1->english = english;
        node_tmp1->c_language = c_language;

        node_tmp1->next = NULL;
        node_tmp2->next = node_tmp1;
        node_tmp2 = node_tmp1;

        /*置载入过数据的行的flag字段为默认值*/
        ret = set_flag(&mysql,id);
        if(ret < 0)
        {
            syslog(LOG_ERR,"set flag failed");
            return -1;
        }
        num--;
    }

    /*断开数据库连接*/
    mysql_fun_close(&mysql);
    return 0;
}
