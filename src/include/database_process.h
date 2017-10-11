/************************************************************************************
 * @file    database_process.h
 * @brief   数据库与链表交互操作的函数头文件，提供函数接口
 * @version 1.0
 * @author  ZY
 * @date    2017.10.9
 *                   History
 *          Modified by :
 *          Date        :
 *          Modification:
 ***********************************************************************************/
#ifndef __DATABASE_PROCESS_H__
#define __DATABASE_PROCESS_H__

#include"common.h"

/*****************************************
 * @brief   保存数据到数据库
 * @param   head:链表头节点
 * @retval  成功返回0,失败返回-1
 * @par     Usage：
 *          save_data_to_database(head);
 * @par     Tag: 
 *****************************************/
int save_data_to_database(PSTU head);

/*****************************************
 * @brief   载入数据库数据到链表
 * @param   head:链表头节点
 * @retval  成功返回0,失败返回-1
 * @par     Usage：
 *          load_data_from_database(head);
 * @par     Tag: 
 *****************************************/
int load_data_from_database(PSTU head);

#endif
