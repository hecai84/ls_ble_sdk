/*
 * @Description:
 * @Author: hecai
 * @Date: 2021-09-14 15:27:57
 * @LastEditTime: 2021-12-31 00:19:36
 * @FilePath: \ls_ble_sdk\dev\project\ble\ble_uart_server\Motor.c
 */
#include "Motor.h"
#include "Tools.h"
#include "io_config.h"

#define H1 PA01
#define H2 PA00
#define L1 PB13
#define L2 PB14
#define POWEN PB08
#define CHECK_TIME 50
#define OVER_CURRENT
#define STOP_TIME 500;

static struct builtin_timer *motor_timer_inst1 = NULL;
static struct builtin_timer *motor_timer_inst2 = NULL;
static struct builtin_timer *motor_timer_inst3 = NULL;
static struct builtin_timer *motor_timer_inst4 = NULL;
static struct builtin_timer *adc_timer_inst = NULL;
static bool foward = true;
bool isWorking = false;

// void checkCurrent(void *param)
//{
//         LOG_I("checkCurrent:%d",recv_flag);
//     if(recv_flag>=2)
//     {
//         LOG_I("motor current:%d",aRxBuffer[0]);
//         LOG_I("battery:%d",aRxBuffer[1]);
//         recv_flag=0;
//		HAL_ADC_Start_IT(&hadc);
//
//     }
//     if(adc_timer_inst && isWorking)
//     {
//         builtin_timer_start(adc_timer_inst, CHECK_TIME, NULL);
//     }
// }

void initMotor(void)
{
    io_cfg_output(H1);
    io_write_pin(H1, 0);
    io_cfg_output(H2);
    io_write_pin(H2, 0);
    io_cfg_output(L1);
    io_write_pin(L1, 0);
    io_cfg_output(L2);
    io_write_pin(L2, 0);

    io_cfg_output(POWEN);
    io_write_pin(POWEN, 0);
}

void stopMotor(void *param)
{
    LOG_I("stopMotor");
    io_write_pin(POWEN, 0);
    io_write_pin(H1, 0);
    io_write_pin(H2, 0);
    io_write_pin(L1, 0);
    io_write_pin(L2, 0);
}

void closeDoor(void *param)
{
    LOG_I("closeDoor");
    io_write_pin(H1, 0);
    io_write_pin(H2, 0);
    io_write_pin(L1, 0);
    io_write_pin(L2, 0);
    if (foward)
    {
        io_write_pin(H2, 1);
        io_write_pin(L2, 1);
    }
    else
    {
        io_write_pin(H1, 1);
        io_write_pin(L1, 1);
    }
    io_write_pin(POWEN, 1);
    return;
}

void powFinish(void *param)
{
    isWorking = false;
    UpdateBattery();
}

void openDoor(int procTime,int waitTime)
{
    uint16_t delayT = 0;
    LOG_I("procTime:%d waitTime:%d",procTime,waitTime);
    if (procTime > 0)
        foward = true;
    else
    {
        foward = false;
        procTime = -procTime;
    }
    isWorking = true;
    if (motor_timer_inst1 == NULL)
        motor_timer_inst1 = builtin_timer_create(stopMotor);
    if (motor_timer_inst2 == NULL)
        motor_timer_inst2 = builtin_timer_create(closeDoor);
    if (motor_timer_inst3 == NULL)
        motor_timer_inst3 = builtin_timer_create(stopMotor);
    if (motor_timer_inst4 == NULL)
        motor_timer_inst4 = builtin_timer_create(powFinish);

    LOG_I("openDoor");
    io_write_pin(H1, 0);
    io_write_pin(H2, 0);
    io_write_pin(L1, 0);
    io_write_pin(L2, 0);
    if (foward)
    {
        io_write_pin(H1, 1);
        io_write_pin(L1, 1);
    }
    else
    {
        io_write_pin(H2, 1);
        io_write_pin(L2, 1);
    }
    io_write_pin(POWEN, 1);

    delayT += procTime;
    builtin_timer_stop(motor_timer_inst1);
    builtin_timer_start(motor_timer_inst1, delayT, NULL);

    delayT += waitTime;
    builtin_timer_stop(motor_timer_inst2);
    builtin_timer_start(motor_timer_inst2, delayT, NULL);

    delayT += procTime;
    builtin_timer_stop(motor_timer_inst3);
    builtin_timer_start(motor_timer_inst3, delayT, NULL);

    delayT += procTime;
    builtin_timer_stop(motor_timer_inst4);
    builtin_timer_start(motor_timer_inst4, delayT, NULL);

    //    adc_timer_inst=builtin_timer_create(checkCurrent);
    //    recv_flag=0;
    //    HAL_ADC_Start_IT(&hadc);
    //    builtin_timer_start(adc_timer_inst, CHECK_TIME, NULL);

    return;
}
