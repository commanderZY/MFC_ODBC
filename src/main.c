/************************************************************************************
 * @file    main.c
 * @brief   主函数，提供功能菜单
 * @version 1.0
 * @author  ZY
 * @date    2017.10.9
 *                   History
 *          Modified by :
 *          Date        :
 *          Modification:
 ***********************************************************************************/
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include"include/common.h"
#include"include/link_list.h"
#include"include/file_process.h"
#include"include/database_process.h"
#include<syslog.h>

int main(void)
{
    int logmask      = 0;
    char flag[3]     = {'\0'};
    int link_num     = 0;
    int num1         = 0;
    int num2         = 0;
    int ret          = 0;
    PSTU head        = NULL;
    PSTU add_node    = NULL;
    PSTU select_node = NULL;
    PSTU insert_node = NULL;
    PSTU update_node = NULL;

    head = (PSTU)malloc(sizeof(STU));
    head->next = NULL;
    
    /*打开并设置syslog*/
    openlog("logmask",LOG_PID | LOG_CONS,LOG_USER);
    logmask = setlogmask(LOG_UPTO(LOG_DEBUG));
    syslog(LOG_INFO,"syslog open");

    printf("=========================================\n");
    printf("欢迎使用学生成绩管理系统(链表练习版)     \n");
    printf("请输入如下指令实现相关操作：             \n");
    printf("a.创建指定大小的空白链表;                \n");
    printf("b.添加学生信息及成绩到空白链表;          \n");
    printf("c.增加链表;                              \n");
    printf("d.插入链表;                              \n");
    printf("e.删除链表中学生信息及成绩;              \n");
    printf("f.查询链表中学生信息及成绩;              \n");
    printf("g.修改链表中学生信息及成绩;              \n");
    printf("h.输出链表中学生信息及成绩;              \n");
    printf("i.保存链表中全部学生信息及成绩到文件;    \n");
    printf("j.下载文件中全部学生信息及成绩到链表;    \n");
    printf("k.保存链表中全部学生信息及成绩到数据库;  \n");
    printf("l.下载数据库中全部学生信息及成绩到链表;  \n");
    printf("m.显示指令菜单栏;                        \n");
    printf("n.释放并退出;                            \n");
    printf("=========================================\n");

    while(1)
    {
        memset(flag,'\0',sizeof(flag));
        printf("请输指令：\n");
        scanf("%s",flag);  //flag使用整形数时输入字符会使程序出现死循环

        /*释放空间并退出*/
        if((!strcmp(flag,"n")) || (!strcmp(flag,"N")))
        {
            destroy_link_list(head);
            free(head);
            head = NULL;
            add_node    = NULL;
            select_node = NULL;
            insert_node = NULL;
            update_node = NULL;
            break;
        }

        flag[0]|=0x20;  //实现大小写不敏感
        switch(flag[0])
        {
            case 'a':
                printf("请输入要创建的空数据的链表数量：\n");
                scanf("%d",&link_num);
                create_link_list(head,link_num);
                printf("创建完成\n");
                break;
            case 'b':
                printf("请输入：\n");
                printf("学号\t姓名\t性别\t数学成绩\t英语成绩\tc语言成绩\n");
                input_data(head);
                printf("输入完毕\n");
                break;
            case 'c':
                add_node = (PSTU)malloc(sizeof(STU));
                printf("请输入要添加的链表的内容：\n");
                printf("学号\t姓名\t性别\t数学成绩\t英语成绩\tc语言成绩\n");
                scanf("%d%s%s%d%d%d",&add_node->id,add_node->name,add_node->sex,&add_node->math,&add_node->english,&add_node->c_language);
                add_link_list(head,add_node);
                printf("增加完成\n");
                break;
            case 'd':
                insert_node = (PSTU)malloc(sizeof(STU));
                printf("请输入要插入的链表的内容：\n");
                printf("学号\t姓名\t性别\t数学成绩\t英语成绩\tc语言成绩\n");
                scanf("%d%s%s%d%d%d",&insert_node->id,insert_node->name,insert_node->sex,&insert_node->math,&insert_node->english,&insert_node->c_language);
                insert_link_list(head,insert_node);
                printf("插入完成\n");
                break;
            case 'e':
                printf("暂只支持按学号删除，且只删除第一个\n");
                printf("请输入学号：\n");
                scanf("%d",&num1);
                ret = delete_link_list(head,num1);
                if(ret < 0)
                    printf("该学号不存在\n");
                else
                    printf("删除完成\n");
                break;
            case 'f':
                printf("暂只支持按学号查找，请输入学号:\n");
                scanf("%u",&num2);
                select_node = select_link_list(head,num2);
                if(!select_node)
                    printf("该学号不存在\n");
                else
                {
                    printf("查询结果：\n");
                    printf("学号\t姓名\t性别\t数学成绩\t英语成绩\tc语言成绩\n");
                    printf("%d\t%s\t%s\t%d\t%d\t%d\n",select_node->id,select_node->name,select_node->sex,select_node->math,select_node->english,select_node->c_language);
                }
                printf("查找结束\n");
                break;
            case 'g':
                update_node = (PSTU)malloc(sizeof(STU));
                printf("请输入更新内容：\n");
                printf("学号\t姓名\t性别\t数学成绩\t英语成绩\tc语言成绩\n");
                scanf("%d%s%s%d%d%d",&update_node->id,update_node->name,update_node->sex,&update_node->math,&update_node->english,&update_node->c_language);
                ret = update_link_list(head,update_node);
                if(ret < 0)
                    printf("输入的更新内容中学号不存在,更新失败\n");
                else
                    printf("更新结束\n");
                free(update_node);
                break;
            case 'h':
                ret = output_data(head);
                if(ret < 0)
                    printf("链表内容为空\n");
                else
                    printf("输出完毕\n");
                break;
            case 'i':
                ret = save_data_to_file(head);
                if(ret < 0)
                    printf("链表为空\n");
                else
                    printf("保存完毕\n");
                break;
            case 'j':
                ret = load_data_from_file(head);
                if(ret < 0)
                    printf("打开文件失败或链表为空\n");
                else
                    printf("下载完毕，如需查看请输出链表\n");
                break;
            case 'k':
                ret = save_data_to_database(head);
                if(ret < 0)
                    printf("保存失败\n");
                else
                    printf("保存到数据库完毕\n");
                break;
            case 'l':
                ret = load_data_from_database(head);
                if(ret < 0)
                    printf("载入失败，如需查看具体信息请使用logread查看日志\n");
                else
                    printf("数据库数据下载完毕，如需查看请输出链表，然后也可将数据保存到文件\n");
                break;
            case 'm':
                printf("a.创建指定大小的空白链表;                \n");
                printf("b.添加学生信息及成绩到空白链表;          \n");
                printf("c.增加链表;                              \n");
                printf("d.插入链表;                              \n");
                printf("e.删除链表中学生信息及成绩;              \n");
                printf("f.查询链表中学生信息及成绩;              \n");
                printf("g.修改链表中学生信息及成绩;              \n");
                printf("h.输出链表中学生信息及成绩;              \n");
                printf("i.保存链表中全部学生信息及成绩到文件;    \n");
                printf("j.下载文件中全部学生信息及成绩到链表;    \n");
                printf("k.保存链表中全部学生信息及成绩到数据库;  \n");
                printf("l.下载数据库中全部学生信息及成绩到链表;  \n");
                printf("m.显示指令菜单栏;                        \n");
                printf("n.释放并退出;                            \n");
                break;
            default:
                syslog(LOG_ERR,"undefined commond");
                printf("请按指令重输：\n");
                break;
        }
        printf("=========================================\n");
    }

    return 0;
}
