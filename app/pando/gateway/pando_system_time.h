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
    uint8_t sec;    // 秒 – 取值区间为[0,59]
    uint8_t min;    // 分 - 取值区间为[0,59]
    uint8_t hour;   // 时 - 取值区间为[0,23]
    uint8_t mday;   // 一个月中的日期 - 取值区间为[1,31]
    uint8_t mon;    // 月份1-12
    uint16_t year;  // 年份
    uint8_t wday;   // 星期 – 取值区间为[0,6]，其中0代表星期天，1代表星期一，以此类推
    uint16_t yday;  // 从每年的1月1日开始的天数 – 取值区间为[0,365]，其中0代表1月1日，1代表1月2日，以此类推
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
