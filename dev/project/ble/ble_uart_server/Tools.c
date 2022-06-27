/*
 * @Description:
 * @Author: hecai
 * @Date: 2021-09-16 10:44:14
 * @LastEditTime: 2022-06-24 17:38:58
 * @FilePath: \battery\dev\project\ble\ble_uart_server\Tools.c
 */
#include "Tools.h"
#include "lscrypt.h"
#include "lsadc.h"
#include <string.h>
#include "flash.h"
/**buff**/
uint8_t ciphertext_buff[64];
uint8_t plaintext_buff[64];
extern u8 pw[];
extern u8 lastTime[];

#define BT PB15
#define CHRG PA00
#define LED_RED PA14
#define LED_BLUE PA13
#define TWINK_BLUE_TIME 500
#define TWINK_RED_TIME1 500
#define TWINK_RED_TIME2 1500
#define LONGPRESS_TIME 3000
#define CHRG_OVERTIME 500
#define REFRESH_VBAT_TIME 60000



#include "main.h"

