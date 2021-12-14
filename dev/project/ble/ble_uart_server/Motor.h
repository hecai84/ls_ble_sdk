/*
 * @Description: 
 * @Author: hecai
 * @Date: 2021-09-14 15:28:12
 * @LastEditTime: 2021-12-14 23:41:56
 * @FilePath: \ls_ble_sdk\dev\project\ble\ble_uart_server\Motor.h
 */
#ifndef __MOTOR_H__
#define __MOTOR_H__
void initMotor(void);
void openDoor(int time);
void closeDoor(void *param);
void stopMotor(void *param);



#endif

