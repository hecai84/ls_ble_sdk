#ifndef LSUART_H_
#define LSUART_H_
#include <stdbool.h>
#include "reg_uart_type.h"
#include "HAL_def.h"
#include "sdk_config.h"
#include "reg_base_addr.h"

#ifdef UART1_BASE_ADDR
#define UART1 ((reg_uart_t *)UART1_BASE_ADDR)
#endif
#ifdef UART2_BASE_ADDR
#define UART2 ((reg_uart_t *)UART2_BASE_ADDR)
#endif
#ifdef UART3_BASE_ADDR
#define UART3 ((reg_uart_t *)UART3_BASE_ADDR)
#endif

#if FPGA 
#define UART_CLOCK   16000000
#else 
#define UART_CLOCK   (SDK_PCLK_MHZ*1000000)

#endif 

#define UART_BUADRATE_ENUM_GEN(BAUD)  ((((UART_CLOCK<<4)/BAUD) +8)>>4)

typedef enum
{
    UART_BAUDRATE_1200   = UART_BUADRATE_ENUM_GEN(1200),
    UART_BAUDRATE_2400   = UART_BUADRATE_ENUM_GEN(2400),
    UART_BAUDRATE_4800   = UART_BUADRATE_ENUM_GEN(4800),
    UART_BAUDRATE_9600   = UART_BUADRATE_ENUM_GEN(9600),
    UART_BAUDRATE_14400 = UART_BUADRATE_ENUM_GEN(14400),
    UART_BAUDRATE_19200 = UART_BUADRATE_ENUM_GEN(19200),
    UART_BAUDRATE_28800 = UART_BUADRATE_ENUM_GEN(28800),
    UART_BAUDRATE_38400  = UART_BUADRATE_ENUM_GEN(38400),
    UART_BAUDRATE_57600 = UART_BUADRATE_ENUM_GEN(57600),
    UART_BAUDRATE_76800  = UART_BUADRATE_ENUM_GEN(76800),
    UART_BAUDRATE_115200 = UART_BUADRATE_ENUM_GEN(115200),
    UART_BAUDRATE_230400 = UART_BUADRATE_ENUM_GEN(230400),
    UART_BAUDRATE_250000 = UART_BUADRATE_ENUM_GEN(250000),
    UART_BAUDRATE_500000 = UART_BUADRATE_ENUM_GEN(500000),
    UART_BAUDRATE_460800 = UART_BUADRATE_ENUM_GEN(460800),
    UART_BAUDRATE_750000=  UART_BUADRATE_ENUM_GEN(750000),
    UART_BAUDRATE_921600 = UART_BUADRATE_ENUM_GEN(921600),
    UART_BAUDRATE_1000000= UART_BUADRATE_ENUM_GEN(1000000),
    UART_BAUDRATE_2000000= UART_BUADRATE_ENUM_GEN(2000000),
}app_uart_baudrate_t;


/** @defgroup UART_Exported_Types UART Exported Types
  * @{
  */

/**
  * @brief UART Init Structure definition
  */
typedef struct
{
    app_uart_baudrate_t BaudRate;                  /*!< This member configures the UART communication baud rate.*/

    uint8_t     WordLength:2,                /*!< Specifies the number of data bits transmitted or received in a frame.
                                                  This parameter can be a value of @ref UART_Word_Length */

               StopBits:1,                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_Stop_Bits */

               Parity:2,                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
               MSBEN:1,
               HwFlowCtl:1;                 /*!< Specifies whether the hardware flow control mode is enabled or disabled.
                                                 This parameter can be a value of @ref UART_Hardware_Flow_Control */
} UART_InitTypeDef;

/**
  * @brief HAL UART State structures definition
  * @note  HAL UART State value is a combination of 2 different substates: gState and RxState.
  *        - gState contains UART state information related to global Handle management
  *          and also information related to Tx operations.
  *          gState value coding follow below described bitmap :
  *          b7-b6  Error information
  *             00 : No Error
  *             01 : (Not Used)
  *             10 : Timeout
  *             11 : Error
  *          b5     Peripheral initialization status
  *             0  : Reset (Peripheral not initialized)
  *             1  : Init done (Peripheral not initialized. HAL UART Init function already called)
  *          b4-b3  (not used)
  *             xx : Should be set to 00
  *          b2     Intrinsic process state
  *             0  : Ready
  *             1  : Busy (Peripheral busy with some configuration or internal operations)
  *          b1     (not used)
  *             x  : Should be set to 0
  *          b0     Tx state
  *             0  : Ready (no Tx operation ongoing)
  *             1  : Busy (Tx operation ongoing)
  *        - RxState contains information related to Rx operations.
  *          RxState value coding follow below described bitmap :
  *          b7-b6  (not used)
  *             xx : Should be set to 00
  *          b5     Peripheral initialization status
  *             0  : Reset (Peripheral not initialized)
  *             1  : Init done (Peripheral not initialized)
  *          b4-b2  (not used)
  *            xxx : Should be set to 000
  *          b1     Rx state
  *             0  : Ready (no Rx operation ongoing)
  *             1  : Busy (Rx operation ongoing)
  *          b0     (not used)
  *             x  : Should be set to 0.
  */
typedef enum
{
    HAL_UART_STATE_RESET             = 0x00U,    /*!< Peripheral is not yet Initialized
                                                    Value is allowed for gState and RxState */
    HAL_UART_STATE_READY             = 0x20U,    /*!< Peripheral Initialized and ready for use
                                                    Value is allowed for gState and RxState */
    HAL_UART_STATE_BUSY              = 0x24U,    /*!< an internal process is ongoing
                                                    // Value is allowed for gState only */
    HAL_UART_STATE_BUSY_TX           = 0x21U,    /*!< Data Transmission process is ongoing
                                                    Value is allowed for gState only */
    HAL_UART_STATE_BUSY_RX           = 0x22U,    /*!< Data Reception process is ongoing
                                                    Value is allowed for RxState only */
    HAL_UART_STATE_BUSY_TX_RX        = 0x23U,    /*!< Data Transmission and Reception process is ongoing
                                                    Not to be used for neither gState nor RxState.
                                                    Value is result of combination (Or) between gState and RxState values */
    HAL_UART_STATE_TIMEOUT           = 0xA0U,    /*!< Timeout state
                                                    Value is allowed for gState only */
    HAL_UART_STATE_ERROR             = 0xE0U     /*!< Error
                                                    Value is allowed for gState only */
} HAL_UART_StateTypeDef;

struct UartDMAEnv
{
    uint8_t                       DMA_Channel;
};

struct UartInterruptEnv
{
    uint8_t                       *pBuffPtr;      /*!< Pointer to UART Tx transfer Buffer */
    uint16_t                      XferCount;      /*!< UART Tx Transfer Counter           */
};

/**
  * @brief  UART handle Structure definition
  */

typedef struct __UART_HandleTypeDef
{
    reg_uart_t                    *UARTX;           /*!< UART registers base address        */
    UART_InitTypeDef              Init;             /*!< UART communication parameters      */
    void                          *DMAC_Instance;
    union{
        struct UartDMAEnv DMA;
        struct UartInterruptEnv Interrupt;
    }Tx_Env,Rx_Env;

    HAL_UART_StateTypeDef         gState;           /*!< UART state information related to global Handle management
                                                                and also related to Tx operations.
                                                                This parameter can be a value of @ref HAL_UART_StateTypeDef */

    HAL_UART_StateTypeDef         RxState;          /*!< UART state information related to Rx operations.*/
        
    uint32_t                 ErrorCode;        /*!< UART Error code                    */

} UART_HandleTypeDef;

#define UART_NOPARITY       0x0     // Parity diable
#define UART_ODDPARITY      0x1     // Parity Odd
#define UART_EVENPARITY     0x3     // Parity Even

#define UART_BYTESIZE5      0X0     // Byte size 5 bits
#define UART_BYTESIZE6      0X1     // Byte size 6 bits
#define UART_BYTESIZE7      0X2     // Byte size 7 bits
#define UART_BYTESIZE8      0X3     // Byte size 8 bits

#define UART_STOPBITS1      0x0     // Stop 1 bits
#define UART_STOPBITS2      0x1     // Stop 2 bits


HAL_StatusTypeDef HAL_UART_AutoBaudRate_Detect(UART_HandleTypeDef *huart,uint8_t mode);
HAL_StatusTypeDef HAL_UART_AutoBaudRate_Detect_IT(UART_HandleTypeDef * huart,uint8_t mode);

/* operation functions *******************************************************/
/**
  * @brief  Sends an amount of data in blocking mode.
  * @note   
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (uint8_t data elements).
  * @param  Size  Amount of data elements (uint8_t) to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  Receives an amount of data in blocking mode.
  * @note   
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (uint8_t data elements).
  * @param  Size  Amount of data elements (uint8_t) to be received.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size,uint32_t Timeout);

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.int_t
  * @param  pData Pointer to data buffer (uint8_t  data elements).
  * @param  Size  Amount of data elements (uint8_t) to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Receives an amount of data in non blocking mode.
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (uint8_t data elements).
  * @param  Size  Amount of data elements (uint8_t) to be received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Sends an amount of data in DMA mode.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (uint_8 data elements).
  * @param  Size  Amount of data elements (uint_8) to be sent.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Receives an amount of data in DMA mode.
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (uint_8  data elements).
  * @param  Size  Amount of data elements (uint_8 ) to be received.
  * @note   When the UART parity is enabled (PCE = 1) the received data contains the parity bit.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Initializes the UART mode according to the specified parameters in
  *         the UART_InitTypeDef and create the associated handle.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);

/**
  * @brief  DeInitializes the UART peripheral.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart);

/**
  * @brief  This function handles UARTx interrupt request.
  * @param  huart  Pointer to a UARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UARTx_IRQHandler(UART_HandleTypeDef *huart);

/**
  * @brief  Tx Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file     
  * @param  huart  Pointer to a UARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

/**
  * @brief  Rx Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
  * @param  huart  Pointer to a UARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

/**
  * @brief  DMA UART Tx Transfer completed callbacks.
  * @note   This function needs to be implemented when the callback is needed,
           the HAL_UART_DMA_TxCpltCallback could be implemented in the user file
  * @param  huart  Pointer to a UARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_DMA_TxCpltCallback(UART_HandleTypeDef *huart);

/**
  * @brief  DMA UART Rx Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_DMA_RxCpltCallback could be implemented in the user file
  * @param  huart  Pointer to a UARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_DMA_RxCpltCallback(UART_HandleTypeDef *huart);


#endif // _LSUART_H_

