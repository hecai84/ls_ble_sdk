/*
 * @Description: 
 * @Author: hecai
 * @Date: 2021-09-14 15:28:12
 * @LastEditTime: 2021-09-16 10:56:11
 * @FilePath: \ls_ble_sdk\dev\project\ble\ble_uart_server\Motor.h
 */
#ifndef __MOTOR_H__
#define __MOTOR_H__
void initMotor(void);
void openDoor(void *param);
void closeDoor(void *param);
void stopMotor(void *param);



#endif

