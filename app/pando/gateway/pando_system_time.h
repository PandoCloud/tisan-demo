/*******************************************************
 * File name: pando_system_time.h
 * Author:  Chongguang Li
 * Versions: 1.0
 * Description:This module is the interface of system time, generate by time interrupt.
 * History:
 *   1.Date:  
 *     Author:
 *     Modification:    
 *********************************************************/

#ifndef PANDO_SYSTEM_TIME_H
#define PANDO_SYSTEM_TIME_H

#include "c_types.h"

struct calendar
{
    uint8_t sec;    // �� �C ȡֵ����Ϊ[0,59]
    uint8_t min;    // �� - ȡֵ����Ϊ[0,59]
    uint8_t hour;   // ʱ - ȡֵ����Ϊ[0,23]
    uint8_t mday;   // һ�����е����� - ȡֵ����Ϊ[1,31]
    uint8_t mon;    // �·�1-12
    uint16_t year;  // ���
    uint8_t wday;   // ���� �C ȡֵ����Ϊ[0,6]������0���������죬1��������һ���Դ�����
    uint16_t yday;  // ��ÿ���1��1�տ�ʼ������ �C ȡֵ����Ϊ[0,365]������0����1��1�գ�1����1��2�գ��Դ�����
};

/******************************************************************************
 * FunctionName : pando_set_system_time
 * Description  : configure the system time.
 * Parameters   : the set value.
 * Returns      : none
*******************************************************************************/

void pando_set_system_time(uint64 time);

/******************************************************************************
 * FunctionName : pando_get_system_time
 * Description  : geit the system time.
 * Parameters   : none.
 * Returns      : the system time.
*******************************************************************************/

uint64 pando_get_system_time(void);

/******************************************************************************
 * FunctionName : pando_system_time_init
 * Description  : initialize system time.
 * Parameters   : none.
 * Returns      : none.
*******************************************************************************/


void pando_system_time_init(void);

/******************************************************************************
 * FunctionName : pando_get_local_time
 * Description  : get local time.
 * Parameters   : the calendar pointer.
 * Returns      : none.
*******************************************************************************/

void pando_get_calendar(struct calendar * c);

/******************************************************************************
 * FunctionName : pando_set_timezone
 * Description  : set time zone.
 * Parameters   : the time zone value.
 * Returns      : none.
*******************************************************************************/
void pando_set_timezone(sint8_t tz);


#endif
