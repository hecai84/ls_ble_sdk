
/**
  ******************************************************************************
  * @file    dev\examples\peripheral\ssi\ssi_it\main.c
  * @author  LinkedSemi Software
  * @brief   This sample code shows how to use LE501x SSI HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          DMA transfer.
  *          The communication is done using 1 LE5010 board and a SPI Flash module(W25Q128JV).
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#define LOG_TAG "MAIN"
#include "ls_ble.h"
#include "platform.h"
#include "prf_diss.h"
#include "log.h"
#include "ls_dbg.h"
#include "cpu.h"
#include "builtin_timer.h"
#include <string.h>
#include "co_math.h"
#include "io_config.h"
#include "SEGGER_RTT.h"
#include "lsspi.h"
#include "lsssi.h"
#include "lsdmac.h"

#define SSI_TEST_BUF_SIZE 4
#define SSI_TEST_LED_IO PA01
/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);

/* Private variables ---------------------------------------------------------*/
/* SPI handler declaration */
SSI_HandleTypeDef SsiHandle;

/* SSI TxRx flag */
volatile static uint8_t ssi_txrx_flag = 1;

DMA_RAM_ATTR uint8_t ssi_dma_tx_buf[SSI_TEST_BUF_SIZE];
DMA_RAM_ATTR uint8_t ssi_dma_rx_buf[SSI_TEST_BUF_SIZE];

DEF_DMA_CONTROLLER(dmac1_SSI_inst,DMAC1);

void HAL_SSI_TxRxDMACpltCallback(SSI_HandleTypeDef *hssi)
{
    LOG_I("DMA TXRX CMPLT: 0x%x, 0x%x, 0x%x, 0x%x", ssi_dma_rx_buf[0],ssi_dma_rx_buf[1],ssi_dma_rx_buf[2],ssi_dma_rx_buf[3]);
    if (0 == memcmp(&ssi_dma_tx_buf[0], &ssi_dma_rx_buf[0], SSI_TEST_BUF_SIZE))
    {
        ssi_txrx_flag = 1;
        io_toggle_pin(SSI_TEST_LED_IO);
    }
    else
    {
        LOG_I("Data unmatched!!!");
        LS_ASSERT(0);
    }
}

static void ssi_test_init(void)
{
    ssi_clk_io_init(PB09);        /* CLK-------------PB09 */    
    ssi_nss0_io_init(PB08);    /* SSN-------------PB08 */    
    ssi_dq0_io_init(PA07);        /* MOSI------------PA07 */    
    ssi_dq1_io_init(PA00);        /* MISO------------PA00 */    
    
    SsiHandle.REG = LSSSI;
    SsiHandle.Init.clk_div = 64;
    SsiHandle.Init.rxsample_dly = 0;
    SsiHandle.Init.ctrl.cph = SCLK_Toggle_In_Middle;
    SsiHandle.Init.ctrl.cpol = Inactive_Low;
    SsiHandle.Init.ctrl.data_frame_size = DFS_32_8_bits;

    DMA_CONTROLLER_INIT(dmac1_SSI_inst);
    SsiHandle.DMAC_Instance = &dmac1_SSI_inst;
    SsiHandle.Tx_Env.DMA.DMA_Channel = 0;
    SsiHandle.Rx_Env.DMA.DMA_Channel = 1;

    if(HAL_SSI_Init(&SsiHandle) != HAL_OK)
    {
        /* Initialization Error */
        Error_Handler();
    }
}

static void ssi_test_data_vary(void)
{
    for (uint16_t i = 0; i < SSI_TEST_BUF_SIZE; i++)
    {
        ssi_dma_tx_buf[i] += rand() % 256;
    }
}

int main(void)
{
    sys_init_none();
    ssi_test_init();

    io_cfg_output(SSI_TEST_LED_IO);

    while(1)
    {
        if(ssi_txrx_flag == 1)
        {
            DELAY_US(50000);
            ssi_txrx_flag = 0;
            ssi_test_data_vary();
            if(HAL_SSI_TransmitReceive_DMA(&SsiHandle, ssi_dma_tx_buf,ssi_dma_rx_buf, SSI_TEST_BUF_SIZE)!= HAL_OK)
            {
                /* Transfer error in transmission process */
                Error_Handler();
            }
        }
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}
