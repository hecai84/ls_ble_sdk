/*
 * @Description: 
 * @Author: hecai
 * @Date: 2021-09-14 15:27:57
 * @LastEditTime: 2021-09-26 15:47:36
 * @FilePath: \ls_ble_sdk\dev\project\ble\ble_uart_server\Motor.c
 */
#include "Motor.h"
#include "Tools.h"


static struct builtin_timer *motor_timer_inst1 = NULL;
static struct builtin_timer *motor_timer_inst2 = NULL;
static struct builtin_timer *motor_timer_inst3 = NULL;
//static struct builtin_timer *motor_timer_inst4 = NULL;

void initMotor(void)
{
    io_cfg_output(PA00);  
    io_write_pin(PA00,0);  
    io_cfg_output(PB13);  
    io_write_pin(PB13,0);  
    io_cfg_output(PB14);  
    io_write_pin(PB14,0);  
    io_cfg_output(PB15);  
    io_write_pin(PB15,0);  

    
    io_cfg_output(PB08);  
    io_write_pin(PB08,0);  
}

void stopMotor(void *param)
{
    LOG_I("stopMotor");
    io_write_pin(PA00,0);
    io_write_pin(PB13,0);
    io_write_pin(PB14,0);
    io_write_pin(PB15,0);
    io_write_pin(PB08,0);  
}

void closeDoor(void *param)
{
    LOG_I("closeDoor");    
    stopMotor(NULL);
    io_write_pin(PB08,1);  
    io_write_pin(PA00,1);
    io_write_pin(PB14,1);
    return;
}

void openDoor(void *param)
{
    uint16_t delayT=0;
    if(motor_timer_inst1!=NULL)
        builtin_timer_delete(motor_timer_inst1);
    if(motor_timer_inst2!=NULL)
        builtin_timer_delete(motor_timer_inst2);
    if(motor_timer_inst3!=NULL)
        builtin_timer_delete(motor_timer_inst3);
    stopMotor(NULL);
    LOG_I("openDoor");
    io_write_pin(PB08,1);  
    io_write_pin(PB13,1);
    io_write_pin(PB15,1);

    delayT+=500;
    motor_timer_inst1=builtin_timer_create(stopMotor);
    builtin_timer_start(motor_timer_inst1, delayT, NULL);
    
    delayT+=3000;
    motor_timer_inst2=builtin_timer_create(closeDoor);
    builtin_timer_start(motor_timer_inst2, delayT, NULL);
    
    delayT+=500;
    motor_timer_inst3=builtin_timer_create(stopMotor);
    builtin_timer_start(motor_timer_inst3, delayT, NULL);
    return;
}
