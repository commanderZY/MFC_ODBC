/************************************************************************************
 * @file    mysql_fun.h
 * @brief   提供封装后的mysql函数接口，便于实现复杂的逻辑功能
 * @version 1.0
 * @author  ZY
 * @date    2017.10.8
 *                   History
 *          Modified by :
 *          Date        :
 *          Modification:
 ***********************************************************************************/

#ifndef __MYSQL_FUN_H__
#define __MYSQL_FUN_H__

#include"../mysql_include/mysql.h"

/*************************************************
 * @brief   初始化并连接固定的数据库
 * @param   mysql：mysql数据库句柄
 * @retval  成功返回0，失败返回-1
 * @par     Usage：
 *          mysql_fun_connect(mysql);
 * @par     Tag: 
 *          该函数使用固定的用户名连接固定的数据库
**************************************************/
int mysql_fun_connect(MYSQL* mysql);

/****************************************
 * @brief   释放获取到的数据库的数据空间
 * @param   res:接收数据的特定类型的指针
 * @retval  无
 * @par     Usage：
 *          mysql_fun_free_res(res);
 * @par     Tag: 
 *          该函数和free函数作用等同
*****************************************/
void mysql_fun_free_res(MYSQL_RES* res);

/***********************************
 * @brief   关闭数据库连接
 * @param   mysql：mysql数据库句柄
 * @retval  无
 * @par     Usage：
 *          mysql_fun_close(mysql);
 * @par     Tag: 
************************************/
void mysql_fun_close(MYSQL* mysql);

/******************************************************
 * @brief   发送sql命令给数据库
 * @param   mysql：mysql数据库句柄
 *          command:要发送的命令字符串指针
 * @retval  成功返回0，失败返回-1
 * @par     Usage：
 *          mysql_fun_send(mysql,"select * from test");
 * @par     Tag: 
 *              该函数仅仅能判断命令是否发送成功，不保证
 *          一定能获取到结果。
*******************************************************/
int mysql_fun_send(MYSQL* mysql,char* command);

/***********************************************************************
 * @brief   发送sql命令并将结果转化为整形后返回
 * @param   mysql：mysql数据库句柄
 *          command:获取结果的sql命令
 * @retval  成功返回获取到的结果，失败返回-1
 * @par     Usage：
 *          mysql_fun_get_int_res(mysql,"select Flag from Device_list");
 * @par     Tag: 
 *          该函数用来获取数据库中存储的整形数据
************************************************************************/
int mysql_fun_get_int_res(MYSQL* mysql,char* command);

/************************************************************************************
 * @brief   发送sql命令并将结果复制给给定的空间
 * @param   mysql：mysql数据库句柄
 *          command:要发送的获取数据的指令
 *          str：存放获取到的字符串数据的空间的指针
 * @retval  成功返回存放数据的空间首地址，失败返回NULL
 * @par     Usage：
 *          mysql_fun_get_char_res(mysql,"select table_name from test where flag = 1",str);
 * @par     Tag: 
 *          该函数一般用于获取数据库中的字符串的数据
*************************************************************************************/
char* mysql_fun_get_char_res(MYSQL* mysql,char* command,char* str);

/*************************************************************************
 * @brief   获取结果集中结果的数量
 * @param   mysql：数据库句柄
 *          command：数据库指令
 * @retval  成功返回结果集中的数的量,失败返回-1
 * @par     Usage：
 *          mysql_fun_get_num(mysql,"select flag from knx where flag = 1")
 * @par     Tag: 
 *          该函数一般和获取结果集的函数配对使用
 *************************************************************************/
int mysql_fun_get_num(MYSQL* mysql,char* command);

#endif
