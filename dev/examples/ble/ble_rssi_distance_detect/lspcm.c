#include <string.h>
#include "cpu.h"
#include "lstimer.h"
#include "io_config.h"
#include "platform.h"
#include "field_manipulate.h"
#include "lsdmac.h"
#include "spi_flash.h"
#include "lspcm.h"
#include "log.h"

#define TIM_PRESCALER (SDK_HCLK_MHZ / 2)
#define TIM_PERIOD (250 - 1) /* Period Value  */
#define TIM_PULSE1 256       /* Capture Compare 1 Value  */

#define FRAME_BUF_SIZE 256
#define PCM_SIZE 74240
#define PCM_DATA_LEN PCM_SIZE / FRAME_BUF_SIZE

volatile static uint16_t flash_os_num = 0;
static uint32_t tim_dma_config;
volatile static uint32_t pcm_source_image_base;
volatile static uint32_t pcm_size = 0;

struct PCM_PingPong_Bufptr
{
    uint8_t *Bufptr[2]; /**< Configure the pointer array to send PCM data */
};
struct PCM_PingPong_Bufptr pcm_data_receive;

TIM_HandleTypeDef TimHandle1;
TIM_HandleTypeDef TimHandle2;

DEF_DMA_CONTROLLER(dmac1_inst, DMAC1);
DMA_RAM_ATTR uint8_t Buf0[FRAME_BUF_SIZE];
DMA_RAM_ATTR uint8_t Buf1[FRAME_BUF_SIZE];

static void DMA_Channel_PingPong_Update(DMA_Controller_HandleTypeDef *hdma, uint8_t ch_idx, bool alt, uint32_t *ctrl_data)
{
    struct DMA_Channel_Config cfg;
    HAL_DMA_Channel_Config_Get(hdma, ch_idx, alt, &cfg);
    cfg.ctrl_data = *(struct ctrl_data_config *)ctrl_data;
    HAL_DMA_Channel_Config_Set(hdma, ch_idx, alt, &cfg);
}

uint8_t HAL_PCM_CH0_Handshake_Get(TIM_HandleTypeDef *hpcm)
{
    return CH_BSTIM1_UP;
}

void HAL_PCM_DMA_CpltCallback(TIM_HandleTypeDef *hpcm, uint8_t buf_idx)
{
    uint32_t offset_temp = (flash_os_num)*FRAME_BUF_SIZE;
    if (buf_idx)
    {
        spi_flash_quad_io_read(pcm_source_image_base + offset_temp, Buf1, FRAME_BUF_SIZE);
    }
    else
    {
        spi_flash_quad_io_read(pcm_source_image_base + offset_temp, Buf0, FRAME_BUF_SIZE);
    }
    flash_os_num++;
    if (flash_os_num > pcm_size / FRAME_BUF_SIZE)
    {
        flash_os_num = 0;
        LSADTIM->CCR1 = 0;
        HAL_TIM_Base_Stop_IT(&TimHandle1);
    }
}

void PCM_DMA_CH0_Callback(void *hdma, uint32_t param, uint8_t ch_idx, bool current_alt)
{
    TIM_HandleTypeDef *hpcm = (TIM_HandleTypeDef *)param;
    DMA_Channel_PingPong_Update(hdma, ch_idx, !current_alt, &tim_dma_config);
    HAL_PCM_DMA_CpltCallback(hpcm, current_alt ? 0 : 1);
}

HAL_StatusTypeDef HAL_PCM_PingPong_Transfer_Config_DMA(TIM_HandleTypeDef *hpcm, struct PCM_PingPong_Bufptr *CH0_Buf, struct PCM_PingPong_Bufptr *CH1_Buf, uint16_t FrameNum)
{
    struct ctrl_data_config *ctrl = (struct ctrl_data_config *)&tim_dma_config;
    ctrl->cycle_ctrl = DMA_Cycle_PingPong;
    ctrl->next_useburst = 0;
    ctrl->n_minus_1 = FrameNum - 1;
    ctrl->R_power = 0;
    ctrl->src_prot_ctrl = 0;
    ctrl->dst_prot_ctrl = 0;
    ctrl->src_size = 0;
    ctrl->src_inc = 0;
    ctrl->dst_size = 0;
    ctrl->dst_inc = 3;
    struct DMA_Channel_Config prim;
    prim.src_data_end_ptr = (uint32_t)&CH0_Buf->Bufptr[0][FrameNum - 1];
    prim.dst_data_end_ptr = (uint32_t)&LSADTIM->CCR1;
    prim.ctrl_data = *ctrl;
    prim.dummy = (uint32_t)PCM_DMA_CH0_Callback;
    struct DMA_Channel_Config alt;
    alt.src_data_end_ptr = (uint32_t)&CH0_Buf->Bufptr[1][FrameNum - 1];
    alt.dst_data_end_ptr = (uint32_t)&LSADTIM->CCR1;
    alt.ctrl_data = *ctrl;
    alt.dummy = (uint32_t)PCM_DMA_CH0_Callback;
    HAL_DMA_Channel_Config_Set(hpcm->DMAC_Instance, hpcm->Env.DMA.Channel, false, &prim);
    HAL_DMA_Channel_Config_Set(hpcm->DMAC_Instance, hpcm->Env.DMA.Channel, true, &alt);
    HAL_DMA_Channel_Start_IT(hpcm->DMAC_Instance, hpcm->Env.DMA.Channel, HAL_PCM_CH0_Handshake_Get(hpcm), (uint32_t)hpcm);
    REG_FIELD_WR(hpcm->Instance->DMAEN, TIMER_DMAEN_UDE, 1);
    return HAL_OK;
}

static void Basic_PWM_Output_Cfg(uint8_t pcm_in, uint8_t pcm_out)
{
    TIM_OC_InitTypeDef sConfig = {0};
    TIM_BreakDeadTimeConfigTypeDef BDT_Config = {0};
    adtim1_ch1_io_init(pcm_in, true, 0);
    adtim1_ch1n_io_init(pcm_out);
    /*##-1- Configure the TIM peripheral #######################################*/
    TimHandle2.Instance = LSADTIM;
    TimHandle2.Init.Prescaler = 7;
    TimHandle2.Init.Period = TIM_PULSE1;
    TimHandle2.Init.ClockDivision = 0;
    TimHandle2.Init.CounterMode = TIM_COUNTERMODE_UP;
    TimHandle2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Init(&TimHandle2);
    BDT_Config.OffStateRunMode = TIM_OSSR_DISABLE;
    BDT_Config.OffStateIDLEMode = TIM_OSSI_DISABLE;
    BDT_Config.LockLevel = TIM_LOCKLEVEL_OFF;
    BDT_Config.DeadTime = 0x3f; //0~0xFF
    BDT_Config.BreakState = TIM_BREAK_DISABLE;
    BDT_Config.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    BDT_Config.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    HAL_TIMEx_ConfigBreakDeadTime(&TimHandle2, &BDT_Config);
    /*##-2- Configure the PWM channels #########################################*/
    sConfig.OCMode = TIM_OCMODE_PWM1;
    sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfig.OCFastMode = TIM_OCFAST_DISABLE;

    sConfig.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&TimHandle2, &sConfig, TIM_CHANNEL_1);
    /*##-3- Start PWM signals generation #######################################*/
    HAL_TIM_PWM_Start(&TimHandle2, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&TimHandle2, TIM_CHANNEL_1);
}

static void Basic_Timer_Cfg(void)
{
    TimHandle1.Instance = LSBSTIM;
    TimHandle1.Init.Prescaler = TIM_PRESCALER;
    TimHandle1.Init.Period = TIM_PERIOD;
    TimHandle1.Init.ClockDivision = 0;
    TimHandle1.Init.CounterMode = TIM_COUNTERMODE_UP;
    TimHandle1.DMAC_Instance = &dmac1_inst;
    TimHandle1.Env.DMA.Channel = 1; ///Configure the DMA channel to Send PCM data
    pcm_data_receive.Bufptr[0] = Buf0;
    pcm_data_receive.Bufptr[1] = Buf1;
    HAL_TIM_Init(&TimHandle1);
    HAL_PCM_PingPong_Transfer_Config_DMA(&TimHandle1, &pcm_data_receive, NULL, 0x100); ///DMA send PCM data streams in Ping-Pong mode
}
void PCM_update_config(uint32_t offset, uint32_t size)
{
    uint32_t cpu_stat = enter_critical();
    pcm_source_image_base = offset;
    pcm_size = size;
    flash_os_num = 0;
    exit_critical(cpu_stat);
}
void PCM_init(uint8_t pcm_out_pin1, uint8_t pcm_out_pin2, uint32_t pcm_image_base)
{
    flash_os_num = 0;
    pcm_source_image_base = pcm_image_base;
    memset(Buf0, 0, sizeof(Buf0));
    memset(Buf1, 0, sizeof(Buf1));
    DMA_CONTROLLER_INIT(dmac1_inst);
    Basic_PWM_Output_Cfg(pcm_out_pin1, pcm_out_pin2);
    Basic_Timer_Cfg();
}
void PCM_DeInit(void)
{
    adtim1_ch1_io_deinit();
    adtim1_ch1n_io_deinit();
    HAL_TIM_DeInit(&TimHandle1);
    HAL_TIM_DeInit(&TimHandle2);
}
void PCM_Out_Start(void)
{
    HAL_TIM_Base_Start_IT(&TimHandle1);
}
void PCM_Out_Stop(void)
{
    HAL_TIM_Base_Stop_IT(&TimHandle1);
}
