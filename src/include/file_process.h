/************************************************************************************
 * @file    file_process.h
 * @brief   文件操作的头文件，提供文件操作函数接口
 * @version 1.0
 * @author  ZY
 * @date    2017.10.7
 *                   History
 *          Modified by :
 *          Date        :
 *          Modification:
 ***********************************************************************************/
#ifndef __FILE_PROCESS_H__
#define __FILE_PROCESS_H__

#include"common.h"

/************************************
 * @brief   保存链表数据到文件
 * @param   head：链表头节点
 * @retval  成功返回0,失败返回-1
 * @par     Usage：
 *          save_data_to_file(head);
 * @par     Tag: 
 ************************************/
int save_data_to_file(PSTU head);

/**************************************
 * @brief   载入文件数据到链表
 * @param   head:链表头节点
 * @retval  成功返回0,失败返回-1
 * @par     Usage：
 *          load_data_from_file(head);
 * @par     Tag: 
 **************************************/
int load_data_from_file(PSTU head);

#endif
