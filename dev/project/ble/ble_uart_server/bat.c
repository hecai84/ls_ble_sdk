/*
 * @Description:
 * @Author: hecai
 * @Date: 2021-09-14 15:27:57
 * @LastEditTime: 2022-06-29 21:16:07
 * @FilePath: \battery\dev\project\ble\ble_uart_server\bat.c
 */
#include "bat.h"
#include "lsadc.h"

#define CHECK_TIME 50
#define BAT_EN PB14
ADC_HandleTypeDef hadc;
// 0x55+ack+0xaa+ack+电量+ack+stop
/* I2C handler declaration */
static struct builtin_timer *bat_timer_inst_stop = NULL;

u8 battery = 50;
u8 saled = false;
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

void lsadc_init(void)
{
    /** Common config  */
    hadc.Instance = LSADC;
    hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode = ADC_SCAN_DISABLE; /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
    hadc.Init.NbrOfConversion = 1;             /* Parameter discarded because sequencer is disabled */
    hadc.Init.DiscontinuousConvMode = DISABLE; /* Parameter discarded because sequencer is disabled */
    hadc.Init.NbrOfDiscConversion = 1;         /* Parameter discarded because sequencer is disabled */

    hadc.Init.ContinuousConvMode = ENABLE;           /* Continuous mode to have maximum conversion speed (no delay between conversions) */
    hadc.Init.TrigType = ADC_REGULAR_SOFTWARE_TRIGT; /* Trig of conversion start done by which event */
    hadc.Init.Vref = ADC_VREF_INSIDE;
}
void initBattery(void)
{
    io_cfg_output(BAT_EN);
    io_write_pin(BAT_EN, 0);
    lsadc_init();
}

void UpdateBattery(void)
{
    //如果已经售卖了电量显示0xff
    if (saled)
        battery = 0xff;
    else
    {
        if (HAL_ADC_Init(&hadc) != HAL_OK)
        {
            LOG_I("HAL_ADC_Init error");
            Error_Handler();
        }

        ADC_ChannelConfTypeDef sConfig = {0};
        /**
         * Configure Regular Channel
         */
        sConfig.Channel = ADC_CHANNEL_5;
        sConfig.Rank = ADC_REGULAR_RANK_1;
        sConfig.SamplingTime = 0x00000002U;
        if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
        {
            Error_Handler();
        }
        adc12b_in5_io_init();
        LOG_I("HAL_ADC_Start_IT");
        HAL_ADC_Start_IT(&hadc);

        // if (recv_flag == 1)
        // {
        //     recv_flag = 0;
        //     HAL_ADC_Start_IT(&hadc);
        // }
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *h)
{
    u16 value;
    // 1400/4095*11
    value = HAL_ADC_GetValue(h) * 3.76;
    LOG_I("battery volt:%d", value);
    // 3*1400*adc_value/4095
    if (value > 4100)
        battery = 100;
    else if (value > 3950)
        battery = 90;
    else if (value > 3850)
        battery = 80;
    else if (value > 3800)
        battery = 70;
    else if (value > 3750)
        battery = 60;
    else if (value > 3700)
        battery = 50;
    else if (value > 3650)
        battery = 40;
    else if (value > 3550)
        battery = 30;
    else if (value > 3450)
        battery = 20;
    else if (value > 3250)
        battery = 10;
    else
        battery = 0;
    adc12b_in5_io_deinit();
    HAL_ADC_Stop_IT(h); // close adc per
    HAL_ADC_DeInit(h);
    //如果电量有变化，重新检查是否有变化
}

void StopBattery(void *param)
{
    LOG_I("StopBattery");
    io_write_pin(BAT_EN, 0);
    UpdateBattery();
}

void CloseBattery(void)
{
    LOG_I("CloseBattery");
    StopBattery(NULL);
    UpdateBattery();
}
/**
 * @description: 销售电池
 * @return {*}
 */
void SaleBattery(void)
{
    LOG_I("SaleBattery");
    io_write_pin(BAT_EN, 1);
    saled = true;
    //关闭定时器
    if (bat_timer_inst_stop != NULL)
        builtin_timer_stop(bat_timer_inst_stop);
    UpdateBattery();
}
/**
 * @description:
 * @param {int} procTime  打开的时间,如果为-1则不主动关闭
 * @return {*}
 */
void DisCharge(int procTime)
{
    LOG_I("procTime:%d ", procTime);

    LOG_I("DisCharge");
    io_write_pin(BAT_EN, 1);

    if (procTime != -1)
    {
        if (bat_timer_inst_stop == NULL)
            bat_timer_inst_stop = builtin_timer_create(StopBattery);

        //定时关闭
        builtin_timer_stop(bat_timer_inst_stop);
        builtin_timer_start(bat_timer_inst_stop, procTime * 60000, NULL);
    }

    return;
}

void io_exti_callback(uint8_t pin)
{
    LOG_I("exti");
    switch (pin)
    {
    default:
        break;
    }
}
