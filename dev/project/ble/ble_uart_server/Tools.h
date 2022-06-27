/*
 * @Description: 
 * @Author: hecai
 * @Date: 2021-09-15 12:26:42
 * @LastEditTime: 2022-06-23 00:32:02
 * @FilePath: \battery\dev\project\ble\ble_uart_server\Tools.h
 */
#ifndef __TOOLS_H__
#define __TOOLS_H__
#include "builtin_timer.h"
#include "io_config.h"
#include <stddef.h>
#define LOG_TAG "BLE"
#include "log.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
//默认密码 123456  md5 16位小写
#define DEFAULT_PW "49ba59abbe56e057"


typedef enum 
{
    LED_OPEN = 0,
    LED_CLOSE,
    LED_TWINK,
}LED_STATE;



#endif
