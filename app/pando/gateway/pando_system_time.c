/*******************************************************
 * File name: pando_system_time.h
 * Author:  Chongguang Li
 * Versions: 1.0
 * Description:This module is the interface of system time.
 * History:
 *   1.Date:  
 *     Author:
 *     Modification:    
 *********************************************************/

#include "pando_system_time.h"
#include "osapi.h"
#include "os_type.h"
#include "user_interface.h"

static uint64 system_time = 0;

static os_timer_t  system_timer;
 
static sint8_t time_zone;	// Ê±Çø

/******************************************************************************
 * FunctionName : pando_set_system_time
 * Description  : configure the system time.
 * Parameters   : the set value.
 * Returns      : none
*******************************************************************************/

void ICACHE_FLASH_ATTR
pando_set_system_time(uint64 time)
{
    system_time = time;

    int i = 0;
    for(i = 0; i<sizeof(system_time); i++)
    {
    	PRINTF("%02x ", *((unsigned char*)(&system_time) +i));
    }

    struct calendar c;
    const char *str_wday[]={"Sun","Mon","Tue","Wen","Thu","Fri","Sat"};
    pando_get_calendar(&c);
    //PRINTF("time:%d-%d-%d %d:%d:%d yday=%d,wday=%d\n",c.year,c.mon,c.mday,c.hour,c.min,c.sec,c.yday,c.wday);
    PRINTF("\nlocal time:%d-%d-%d %d:%d:%d %s\n",c.year,c.mon,c.mday,c.hour,c.min,c.sec,str_wday[c.wday]);
}

/******************************************************************************
 * FunctionName : pando_get_system_time
 * Description  : geit the system time.
 * Parameters   : none.
 * Returns      : the system time.
*******************************************************************************/

uint64 ICACHE_FLASH_ATTR
pando_get_system_time(void)
{
    return system_time;
}

/******************************************************************************
 * FunctionName : add_time.
 * Description  : add the system time at fixed time.
 * Parameters   : the time callback parameter.
 * Returns      : none.
*******************************************************************************/

static void ICACHE_FLASH_ATTR
add_time(void *arg)
{
    system_time = system_time + 60000;
    int i = 0;
    for(i = 0; i<sizeof(system_time); i++)
    {
    	PRINTF("%02x ", *((unsigned char*)(&system_time) +i));
    }

    PRINTF("\n");

#ifdef DEBUG_MSG
    system_print_meminfo();
    PRINTF("available heap size:%d\n", system_get_free_heap_size());
#endif

}


//W = [Y-1] + [(Y-1)/4] - [(Y-1)/100] + [(Y-1)/400] + D
static uint8_t ICACHE_FLASH_ATTR
pando_get_week_day(uint16_t year, uint16_t yday)
{
	uint8_t wday;

    wday = ((year-1) + ((year-1)/4) - ((year-1)/100) + ((year-1)/400) + yday) % 7;
    return wday;
}

#define YEAR_IS_LEAP(y)     (((y)%4 == 0 && y%100 != 0)||((y)%400 == 0))
void ICACHE_FLASH_ATTR
pando_get_calendar(struct calendar * c)
{
	uint32_t temp;
	uint16_t i;
	const uint8_t mon_days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

	temp = (uint32_t)(system_time/1000);
	c->sec = temp%60;
	temp = temp/60;
	c->min = temp%60;
	temp /= 60;
	temp += time_zone;
	c->hour = temp%24;
	temp /= 24;
	i = 1970;
	while(temp >= 365)
	{
	    if(YEAR_IS_LEAP(i))
	    {
	        if(temp >= 366)
	        {
	            temp -= 366;
	        }
	        else
	        {
	            break;
	        }
	    }
	    else
	    {
	        temp -= 365;
	    }
	    i++;
	}
	c->year = i;
	c->yday = temp;
	i = 0;
	while(temp >= 28)
	{
	    if(YEAR_IS_LEAP(c->year) && (i == 1))
	    {
	        if(temp >= 29)
	        {
	            temp -= 29;
	        }
	        else
	        {
	            break;
	        }
	    }
	    else
	    {
	        if(temp >= mon_days[i])
	        {
	            temp -= mon_days[i];
	        }
	        else
	        {
	            break;
	        }
	    }
	    i++;
	}
	c->mon = i+1;
	c->mday = temp+1;
	c->wday = pando_get_week_day(c->year, c->yday+1);
}

void ICACHE_FLASH_ATTR
pando_set_timezone(sint8_t tz)
{
	time_zone = tz;
}

/******************************************************************************
 * FunctionName : pando_system_time_init
 * Description  : initialize system time.
 * Parameters   : none.
 * Returns      : none.
*******************************************************************************/

void ICACHE_FLASH_ATTR
pando_system_time_init(void)
{
    os_timer_disarm(&system_timer);
    os_timer_setfn(&system_timer, (os_timer_func_t *)add_time, NULL);
    os_timer_arm(&system_timer, 60000, 1);

    pando_set_timezone(8);	//+8Çø
}


