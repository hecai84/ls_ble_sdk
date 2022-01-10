/*
 * @Description:
 * @Author: hecai
 * @Date: 2021-09-14 15:27:57
 * @LastEditTime: 2022-01-10 22:09:09
 * @FilePath: \ls_ble_sdk\dev\project\ble\ble_uart_server\Motor.c
 */
#include "Motor.h"
#include "Tools.h"
#include "io_config.h"

#define H1 PA01
#define H2 PB12
#define L1 PB13
#define L2 PB14
#define POWEN PB08
#define CHECK_TIME 50
#define OVER_CURRENT
#define STOP_TIME 500;

static struct builtin_timer *motor_timer_inst_stop = NULL;
static struct builtin_timer *motor_timer_inst_close = NULL;
static struct builtin_timer *motor_timer_inst_finish = NULL;
static bool foward = true;
bool isWorking = false;
u16 processTime=0;


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
    
    //定时关闭
    builtin_timer_stop(motor_timer_inst_stop);
    builtin_timer_start(motor_timer_inst_stop, processTime, NULL);
    return;
}

void powFinish(void *param)
{
    isWorking = false;
    UpdateBattery();
}

void openDoor(int procTime,int waitTime)
{
    LOG_I("procTime:%d waitTime:%d",procTime,waitTime);
    if (procTime > 0)
    {
        foward = true;
        processTime = procTime;
    }
    else
    {
        foward = false;
        processTime = -procTime;
    }
    if(isWorking)
        return;
    isWorking = true;
    if (motor_timer_inst_stop == NULL)
        motor_timer_inst_stop = builtin_timer_create(stopMotor);
    if (motor_timer_inst_close == NULL)
        motor_timer_inst_close = builtin_timer_create(closeDoor);
    if (motor_timer_inst_finish == NULL)
        motor_timer_inst_finish = builtin_timer_create(powFinish);

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
    //定时关闭
    builtin_timer_stop(motor_timer_inst_stop);
    builtin_timer_start(motor_timer_inst_stop, processTime, NULL);
    //定时反转
    builtin_timer_stop(motor_timer_inst_close);
    builtin_timer_start(motor_timer_inst_close, waitTime+processTime, NULL);
    //定时结束
    builtin_timer_stop(motor_timer_inst_finish);
    builtin_timer_start(motor_timer_inst_finish, waitTime+processTime*3, NULL);

    //    adc_timer_inst=builtin_timer_create(checkCurrent);
    //    recv_flag=0;
    //    HAL_ADC_Start_IT(&hadc);
    //    builtin_timer_start(adc_timer_inst, CHECK_TIME, NULL);

    return;
}
