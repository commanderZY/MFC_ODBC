/************************************************************************************
 * @file    mysql_fun.c
 * @brief   进行mysql数据库操作，将mysql提供的api函数再次进行封装，实现某些特定的功能
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
#include<string.h>
#include<mysql.h>
/*#include"mysql_include/mysql.h"*/
#include<syslog.h>

/************************************************
 * @brief    用固定的用户名和密码连接固定的数据库
 * @param    mysql:数据库句柄
 * @return   成功返回0,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ************************************************/
int mysql_fun_connect(MYSQL* mysql)
{
    if(!mysql_init(mysql))
    {
        syslog(LOG_ERR,"mysql_init error");
        return -1;
    }

    if(!mysql_real_connect(mysql,"127.0.0.1","root","123","MFC_ODBC",0,NULL,0))
    {
        syslog(LOG_ERR,"connecte mysql error");
        return -1;
    }

    return 0;
}

/*对mysql原释放空间的api进行封装，便于函数名统一*/
void mysql_fun_free_res(MYSQL_RES* res)
{
    mysql_free_result(res);
}

/*对mysql原关闭数据库连接的api进行封装，便于函数名统一*/
void mysql_fun_close(MYSQL* mysql)
{
    syslog(LOG_DEBUG,"in the mysql_my_close");
    mysql_close(mysql);
}

/***********************************************
 * @brief    发送mysql客户端指令
 * @param    mysql：mysql句柄
 *           command：数据库客户端指令
 * @return   成功返回0,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 **********************************************/
int mysql_fun_send(MYSQL* mysql,char* command)
{
    int ret = 0;

    ret = mysql_query(mysql,command);
    if(ret)
    {
        syslog(LOG_ERR,"mysql_query error:%s",mysql_error(mysql));
        return -1;
    }

    return 0;
}

/***********************************************************
 * @brief    从数据库中获取结果并将其转化为整数
 * @param    mysql：数据库句柄
 *           command：发送给数据库的sql命令
 * @return   成功返回整数结果,错误返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***********************************************************/
int mysql_fun_get_int_res(MYSQL* mysql,const char* command)
{
    MYSQL_RES* res = NULL;
    MYSQL_ROW row;
    int ret = 0;

    ret = mysql_query(mysql,command);
    if(ret)
        syslog(LOG_ERR,"mysql query error:%s",mysql_error(mysql));
    else
    {
        res = mysql_store_result(mysql);
        if(res)
        {
            row = mysql_fetch_row(res);
            if(row && (*row))
            {
                mysql_fun_free_res(res);
                res = NULL;
                return ((int)atoi(*row));
            }
            
            mysql_fun_free_res(res);
            res = NULL;
        }
        if(mysql_errno(mysql))
            syslog(LOG_ERR,"Retrive error:%s",mysql_error(mysql));
    }

    return -1;
}

/*****************************************************************
 * @brief    从数据库中获取字符串结果
 * @param    mysql:数据库句柄
 *           command:符合要求的mysql客户端指令
 *           str:接收结果的字符串空间指针
 * @return   成功返回空间首地址,失败返回空
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 *****************************************************************/
char* mysql_fun_get_char_res(MYSQL* mysql,char* command,char* str)
{
    MYSQL_RES* res = NULL;
    MYSQL_ROW row;
    int ret = 0;

    ret = mysql_query(mysql,command);
    if(ret)
        syslog(LOG_ERR,"mysql_query error");
    else
    {
        res = mysql_store_result(mysql);
        if(res)
        {
            row = mysql_fetch_row(res);
            if(row && (*row))  //必须有内容且内容不为空，缺少内容不为空的判断可能会造成段错误
            {
                strcpy(str,*row);
                mysql_fun_free_res(res);
                res = NULL;
                return str;
            }
        
            mysql_fun_free_res(res);  //缺少该处可能会造成内存泄漏
            res = NULL;
        }
        if(mysql_errno(mysql))
            syslog(LOG_ERR,"Retrive error:%s",mysql_error(mysql));
    }

    return NULL;
}

/****************************************************
 * @brief    获取结果集中结果的数量
 * @param    mysql：数据库句柄
 *           command：数据库指令
 * @return   成功返回结果集数量,失败返回-1
 *                       History
 *           Modified by：
 *           Date：
 *           Modification:
 ***************************************************/
int mysql_fun_get_num(MYSQL* mysql,char* command)
{
    MYSQL_RES* res = NULL;
    int ret        = 0;
    int num        = 0;

    ret = mysql_query(mysql,command);
    if(ret)
    {
        syslog(LOG_ERR,"selected error:%s",mysql_error(mysql));
        return -1;
    }
    res = mysql_store_result(mysql);
    if(res)
    {
        num = (int)mysql_num_rows(res);
        mysql_fun_free_res(res);
        res = NULL;
    }

    return num;
}
