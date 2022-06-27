/*
 * @Description: 
 * @Author: hecai
 * @Date: 2021-09-14 15:28:12
 * @LastEditTime: 2022-06-27 21:38:20
 * @FilePath: \battery\dev\project\ble\ble_uart_server\bat.h
 */
#ifndef __BAT_H__
#define __BAT_H__
#include "Tools.h"
void initBattery(void);
void DisCharge(int procTime);
void UpdateBattery(void);
void CloseBattery(void);
void SaleBattery(void);
#endif
