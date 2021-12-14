/*
 * @Description: 
 * @Author: hecai
 * @Date: 2021-09-16 10:44:14
 * @LastEditTime: 2021-12-15 01:52:41
 * @FilePath: \ls_ble_sdk\dev\project\ble\ble_uart_server\Tools.c
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

#define BT PB09
#define LED_RED PB15
#define LED_BLUE PA14
#define TWINK_TIME 500
#define LONGPRESS_TIME 3000

static struct builtin_timer *led_timer_blue = NULL;
static struct builtin_timer *led_timer_red = NULL;
static struct builtin_timer *click_timer = NULL;
static u8 twinkTimes;
volatile uint8_t recv_flag = 0;
ADC_HandleTypeDef hadc;
u16 battery=0;

void Error_Handler(void);

void initLed(void)
{
    io_cfg_output(LED_RED); //LEDR
    io_write_pin(LED_RED, 1);
    io_cfg_output(LED_BLUE); //LEDB
    io_write_pin(LED_BLUE, 1);
}
void initBt(void)
{
    io_cfg_input(BT);                     //PB11 config input
    io_pull_write(BT, IO_PULL_UP);        //PB11 config pullup
    io_exti_config(BT, INT_EDGE_FALLING); //PB11 interrupt falling edge
    io_exti_enable(BT, true);             //PB11 interrupt enable
}

void toggleRed(void *param)
{
    twinkTimes=(*(u8*)param) -1;
    LOG_I("toggleRed %d",twinkTimes);
    io_toggle_pin(LED_RED);
    if (led_timer_red != NULL && twinkTimes>0)
    {
        builtin_timer_start(led_timer_red, TWINK_TIME, &twinkTimes);
    }
}
void toggleBlue(void *param)
{
    twinkTimes=(*(u8*)param) -1;
    LOG_I("toggleBlue %d",twinkTimes);
    io_toggle_pin(LED_BLUE);
    if (led_timer_blue != NULL && twinkTimes>0)
    {
        builtin_timer_start(led_timer_blue, TWINK_TIME, &twinkTimes);
    }
}
void longPress(void *param)
{
    if(io_read_pin(BT)==0)
    {
        LOG_I("longPress");
        SetLedBlue(LED_TWINK);
        memcpy(pw,DEFAULT_PW,16);
        LOG_I("new pw:%s",pw);
        writeFlash(RECODE_PW,pw,16);
    }
}

void lsadc_init(void)
{
    /** Common config  */
    hadc.Instance = LSADC;
    hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode          = ADC_SCAN_DISABLE;              /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
    hadc.Init.NbrOfConversion       = 1;                            /* Parameter discarded because sequencer is disabled */
    hadc.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
    hadc.Init.NbrOfDiscConversion   = 1;                             /* Parameter discarded because sequencer is disabled */

    hadc.Init.ContinuousConvMode    = ENABLE;                        /* Continuous mode to have maximum conversion speed (no delay between conversions) */
    hadc.Init.TrigType      = ADC_REGULAR_SOFTWARE_TRIGT;            /* Trig of conversion start done by which event */
    hadc.Init.Vref          = ADC_VREF_INSIDE; 

    if (HAL_ADC_Init(&hadc) != HAL_OK)
    {
        Error_Handler();
    }


    ADC_ChannelConfTypeDef sConfig = {0};
    /** 
     * Configure Regular Channel 
    */
    sConfig.Channel      = ADC_CHANNEL_6;
    sConfig.Rank         = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

    //打开AD
    //adc12b_in0_io_init();
    adc12b_in6_io_init();
    recv_flag=0;
    HAL_ADC_Start_IT(&hadc);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    u16 value;
    value = HAL_ADC_GetValue(hadc)*4200/4095;
    LOG_I("battery:%d",value);
    //3*1400*adc_value/4095
    if(value>3950)
        battery=5;
    else if(value>3800)
        battery=4;
    else if(value>3600)
        battery=3;
    else if(value>3300)
        battery=2;
    else
        battery=1;

    recv_flag=1;
    // HAL_ADC_Stop_IT(hadc);   //close adc per
}

void CheckBattery()
{
    if(recv_flag==1)
    {
        recv_flag=0;
        HAL_ADC_Start_IT(&hadc);
    }
}

void SetLedRed(LED_STATE state)
{
    twinkTimes=6;
    if (state == LED_TWINK)
    {
        if (led_timer_red != NULL)
        {          
            builtin_timer_stop(led_timer_red);
            builtin_timer_delete(led_timer_red);
            io_write_pin(LED_RED, 0);
        }
        led_timer_red = builtin_timer_create(toggleRed);
        builtin_timer_start(led_timer_red, TWINK_TIME, &twinkTimes);
    }
    else
    {
        if (led_timer_red != NULL)
        {
            builtin_timer_stop(led_timer_red);
            builtin_timer_delete(led_timer_red);
        }
        if (state == LED_OPEN)
            io_write_pin(LED_RED, 0);
        if (state == LED_CLOSE)
            io_write_pin(LED_RED, 1);
    }
}

void SetLedBlue(LED_STATE state)
{
    twinkTimes=6;
    if (state == LED_TWINK)
    {
        if (led_timer_blue != NULL)
        {
            builtin_timer_stop(led_timer_blue);
            builtin_timer_delete(led_timer_blue);
            io_write_pin(LED_BLUE, 0);
        }
        led_timer_blue = builtin_timer_create(toggleBlue);
        builtin_timer_start(led_timer_blue, TWINK_TIME, &twinkTimes);
    }
    else
    {
        if (led_timer_blue != NULL)
        {
            builtin_timer_stop(led_timer_blue);
            builtin_timer_delete(led_timer_blue);
        }
        if (state == LED_OPEN)
            io_write_pin(LED_BLUE, 0);
        if (state == LED_CLOSE)
            io_write_pin(LED_BLUE, 1);
    }
}

void io_exti_callback(uint8_t pin)
{
    switch (pin)
    {
    case BT:
        // do something

        LOG_I("click");
        if (click_timer != NULL)
        {
            builtin_timer_stop(click_timer);
            builtin_timer_delete(click_timer);
        }
        click_timer = builtin_timer_create(longPress);
        builtin_timer_start(click_timer, LONGPRESS_TIME, NULL);
        break;
    default:
        break;
    }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}
