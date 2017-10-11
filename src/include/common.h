/************************************************************************************
 * @file    common.h
 * @brief   通用或常用内容放置文件
 * @version 1.0
 * @author  ZY
 * @date    2017.10.9
 *                   History
 *          Modified by :
 *          Date        :
 *          Modification:
 ***********************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

typedef struct stu
{
    int id;
    char name[30];
    char sex[10];
    int math;
    int english;
    int c_language;
    struct stu* next;
}STU,*PSTU;  //链表结构体

#define FILE_MAX_LEN 12004    //存储链表数据的文件大小
#define SQL_LEN      200      //存放数据库命令的空间长度
#define TABLE_NAME   "class"  //数据库信息存放表名
#define NAME         30       //名字长度
#define SEX_LEN      10       //性别存放长度
#define LOAD_FLAG    1        //载入数据库信息到链表时的数据库表的flag字段值
#define DEFAULT_FLAG 0        //默认的flag字段值

#endif
