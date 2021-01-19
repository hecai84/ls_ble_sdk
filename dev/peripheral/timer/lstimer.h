/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LSTIMER_H_
#define LSTIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "HAL_def.h"
#include "reg_timer.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
#include "le501x.h"
#include "platform.h"

/** @addtogroup le501x_HAL_Driver
  * @{
  */

/** @addtogroup TIM
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup TIM_Exported_Types TIM Exported Types
  * @{
  */

/**
  * @brief  TIM Time base Configuration Structure definition
  */
typedef struct
{
  uint32_t Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                   This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

  uint32_t CounterMode;       /*!< Specifies the counter mode.
                                   This parameter can be a value of @ref TIM_Counter_Mode */

  uint32_t Period;            /*!< Specifies the period value to be loaded into the active
                                   Auto-Reload Register at the next update event.
                                   This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.  */

  uint32_t ClockDivision;     /*!< Specifies the clock division.
                                   This parameter can be a value of @ref TIM_ClockDivision */

  uint32_t RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                    reaches zero, an update event is generated and counting restarts
                                    from the RCR value (N).
                                    This means in PWM mode that (N+1) corresponds to:
                                        - the number of PWM periods in edge-aligned mode
                                        - the number of half PWM period in center-aligned mode
                                     GP timers: this parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
                                     Advanced timers: this parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

  uint32_t AutoReloadPreload;  /*!< Specifies the auto-reload preload.
                                   This parameter can be a value of @ref TIM_AutoReloadPreload */
} TIM_Base_InitTypeDef;

/**
  * @brief  TIM Output Compare Configuration Structure definition
  */
typedef struct
{
  uint32_t OCMode;        /*!< Specifies the TIM mode.
                               This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint32_t Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                               This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

  uint32_t OCPolarity;    /*!< Specifies the output polarity.
                               This parameter can be a value of @ref TIM_Output_Compare_Polarity */

  uint32_t OCNPolarity;   /*!< Specifies the complementary output polarity.
                               This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                               @note This parameter is valid only for timer instances supporting break feature. */

  uint32_t OCFastMode;    /*!< Specifies the Fast mode state.
                               This parameter can be a value of @ref TIM_Output_Fast_State
                               @note This parameter is valid only in PWM1 and PWM2 mode. */


  uint32_t OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                               This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                               @note This parameter is valid only for timer instances supporting break feature. */

  uint32_t OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                               This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                               @note This parameter is valid only for timer instances supporting break feature. */
} TIM_OC_InitTypeDef;

/**
  * @brief  TIM One Pulse Mode Configuration Structure definition
  */
typedef struct
{
  uint32_t OCMode;        /*!< Specifies the TIM mode.
                               This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint32_t Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                               This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

  uint32_t OCPolarity;    /*!< Specifies the output polarity.
                               This parameter can be a value of @ref TIM_Output_Compare_Polarity */

  uint32_t OCNPolarity;   /*!< Specifies the complementary output polarity.
                               This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                               @note This parameter is valid only for timer instances supporting break feature. */

  uint32_t OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                               This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                               @note This parameter is valid only for timer instances supporting break feature. */

  uint32_t OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                               This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                               @note This parameter is valid only for timer instances supporting break feature. */

  uint32_t ICPolarity;    /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint32_t ICSelection;   /*!< Specifies the input.
                              This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint32_t ICFilter;      /*!< Specifies the input capture filter.
                              This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_OnePulse_InitTypeDef;

/**
  * @brief  TIM Input Capture Configuration Structure definition
  */
typedef struct
{
  uint32_t  ICPolarity;  /*!< Specifies the active edge of the input signal.
                              This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint32_t ICSelection;  /*!< Specifies the input.
                              This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint32_t ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                              This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint32_t ICFilter;     /*!< Specifies the input capture filter.
                              This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_IC_InitTypeDef;

/**
  * @brief  TIM Encoder Configuration Structure definition
  */
typedef struct
{
  uint32_t EncoderMode;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Encoder_Mode */

  uint32_t IC1Polarity;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint32_t IC1Selection;  /*!< Specifies the input.
                               This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint32_t IC1Prescaler;  /*!< Specifies the Input Capture Prescaler.
                               This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint32_t IC1Filter;     /*!< Specifies the input capture filter.
                               This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */

  uint32_t IC2Polarity;   /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint32_t IC2Selection;  /*!< Specifies the input.
                              This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint32_t IC2Prescaler;  /*!< Specifies the Input Capture Prescaler.
                               This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint32_t IC2Filter;     /*!< Specifies the input capture filter.
                               This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_Encoder_InitTypeDef;

/**
  * @brief  Clock Configuration Handle Structure definition
  */
typedef struct
{
  uint32_t ClockSource;     /*!< TIM clock sources
                                 This parameter can be a value of @ref TIM_Clock_Source */
  uint32_t ClockPolarity;   /*!< TIM clock polarity
                                 This parameter can be a value of @ref TIM_Clock_Polarity */
  uint32_t ClockPrescaler;  /*!< TIM clock prescaler
                                 This parameter can be a value of @ref TIM_Clock_Prescaler */
  uint32_t ClockFilter;     /*!< TIM clock filter
                                 This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_ClockConfigTypeDef;

/**
  * @brief  TIM Clear Input Configuration Handle Structure definition
  */
typedef struct
{
  uint32_t ClearInputState;      /*!< TIM clear Input state
                                      This parameter can be ENABLE or DISABLE */
  uint32_t ClearInputSource;     /*!< TIM clear Input sources
                                      This parameter can be a value of @ref TIM_ClearInput_Source */
  uint32_t ClearInputPolarity;   /*!< TIM Clear Input polarity
                                      This parameter can be a value of @ref TIM_ClearInput_Polarity */
  uint32_t ClearInputPrescaler;  /*!< TIM Clear Input prescaler
                                      This parameter must be 0: When OCRef clear feature is used with ETR source, ETR prescaler must be off */
  uint32_t ClearInputFilter;     /*!< TIM Clear Input filter
                                      This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_ClearInputConfigTypeDef;

/**
  * @brief  TIM Master configuration Structure definition
  */
typedef struct
{
  uint32_t  MasterOutputTrigger;   /*!< Trigger output (TRGO) selection
                                        This parameter can be a value of @ref TIM_Master_Mode_Selection */
  uint32_t  MasterSlaveMode;       /*!< Master/slave mode selection
                                        This parameter can be a value of @ref TIM_Master_Slave_Mode
                                        @note When the Master/slave mode is enabled, the effect of
                                        an event on the trigger input (TRGI) is delayed to allow a
                                        perfect synchronization between the current timer and its
                                        slaves (through TRGO). It is not mandatory in case of timer
                                        synchronization mode. */
} TIM_MasterConfigTypeDef;

/**
  * @brief  TIM Slave configuration Structure definition
  */
typedef struct
{
  uint32_t  SlaveMode;         /*!< Slave mode selection
                                    This parameter can be a value of @ref TIM_Slave_Mode */
  uint32_t  InputTrigger;      /*!< Input Trigger source
                                    This parameter can be a value of @ref TIM_Trigger_Selection */
  uint32_t  TriggerPolarity;   /*!< Input Trigger polarity
                                    This parameter can be a value of @ref TIM_Trigger_Polarity */
  uint32_t  TriggerPrescaler;  /*!< Input trigger prescaler
                                    This parameter can be a value of @ref TIM_Trigger_Prescaler */
  uint32_t  TriggerFilter;     /*!< Input trigger filter
                                    This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF  */

} TIM_SlaveConfigTypeDef;

/**
  * @brief  TIM Break input(s) and Dead time configuration Structure definition
  * @note   2 break inputs can be configured (BKIN and BKIN2) with configurable
  *        filter and polarity.
  */
typedef struct
{
  uint32_t OffStateRunMode;      /*!< TIM off state in run mode
                                      This parameter can be a value of @ref TIM_OSSR_Off_State_Selection_for_Run_mode_state */
  uint32_t OffStateIDLEMode;     /*!< TIM off state in IDLE mode
                                      This parameter can be a value of @ref TIM_OSSI_Off_State_Selection_for_Idle_mode_state */
  uint32_t LockLevel;            /*!< TIM Lock level
                                      This parameter can be a value of @ref TIM_Lock_level */
  uint32_t DeadTime;             /*!< TIM dead Time
                                      This parameter can be a number between Min_Data = 0x00 and Max_Data = 0xFF */
  uint32_t BreakState;           /*!< TIM Break State
                                      This parameter can be a value of @ref TIM_Break_Input_enable_disable */
  uint32_t BreakPolarity;        /*!< TIM Break input polarity
                                      This parameter can be a value of @ref TIM_Break_Polarity */
  uint32_t BreakFilter;          /*!< Specifies the break input filter.
                                      This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
  uint32_t AutomaticOutput;      /*!< TIM Automatic Output Enable state
                                      This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */
} TIM_BreakDeadTimeConfigTypeDef;

/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_TIM_STATE_RESET             = 0x00U,    /*!< Peripheral not yet initialized or disabled  */
  HAL_TIM_STATE_READY             = 0x01U,    /*!< Peripheral Initialized and ready for use    */
  HAL_TIM_STATE_BUSY              = 0x02U,    /*!< An internal process is ongoing              */
  HAL_TIM_STATE_TIMEOUT           = 0x03U,    /*!< Timeout state                               */
  HAL_TIM_STATE_ERROR             = 0x04U      /*!< Reception process is ongoing                */
} HAL_TIM_StateTypeDef;

/**
  * @brief  HAL Active channel structures definition
  */
typedef enum
{
  HAL_TIM_ACTIVE_CHANNEL_1        = 0x01U,    /*!< The active channel is 1     */
  HAL_TIM_ACTIVE_CHANNEL_2        = 0x02U,    /*!< The active channel is 2     */
  HAL_TIM_ACTIVE_CHANNEL_3        = 0x04U,    /*!< The active channel is 3     */
  HAL_TIM_ACTIVE_CHANNEL_4        = 0x08U,    /*!< The active channel is 4     */
  HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00U     /*!< All active channels cleared */
} HAL_TIM_ActiveChannel;

/**
  * @brief  TIM Time Base Handle Structure definition
  */
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
typedef struct __TIM_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
{
  reg_timer_t                 *Instance;     /*!< Register base address             */
  TIM_Base_InitTypeDef        Init;          /*!< TIM Time Base required parameters */
  HAL_TIM_ActiveChannel       Channel;       /*!< Active channel                    */
  //DMA_HandleTypeDef           *hdma[7];      /*!< DMA Handlers array. This array is accessed by a @ref DMA_Handle_index */
  HAL_LockTypeDef             Lock;          /*!< Locking object                    */
  volatile HAL_TIM_StateTypeDef   State;         /*!< TIM operation state               */

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  void (* Base_MspInitCallback)(struct __TIM_HandleTypeDef *htim);              /*!< TIM Base Msp Init Callback                              */
  void (* Base_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);            /*!< TIM Base Msp DeInit Callback                            */
  void (* IC_MspInitCallback)(struct __TIM_HandleTypeDef *htim);                /*!< TIM IC Msp Init Callback                                */
  void (* IC_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);              /*!< TIM IC Msp DeInit Callback                              */
  void (* OC_MspInitCallback)(struct __TIM_HandleTypeDef *htim);                /*!< TIM OC Msp Init Callback                                */
  void (* OC_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);              /*!< TIM OC Msp DeInit Callback                              */
  void (* PWM_MspInitCallback)(struct __TIM_HandleTypeDef *htim);               /*!< TIM PWM Msp Init Callback                               */
  void (* PWM_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);             /*!< TIM PWM Msp DeInit Callback                             */
  void (* OnePulse_MspInitCallback)(struct __TIM_HandleTypeDef *htim);          /*!< TIM One Pulse Msp Init Callback                         */
  void (* OnePulse_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);        /*!< TIM One Pulse Msp DeInit Callback                       */
  void (* Encoder_MspInitCallback)(struct __TIM_HandleTypeDef *htim);           /*!< TIM Encoder Msp Init Callback                           */
  void (* Encoder_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);         /*!< TIM Encoder Msp DeInit Callback                         */
  void (* HallSensor_MspInitCallback)(struct __TIM_HandleTypeDef *htim);        /*!< TIM Hall Sensor Msp Init Callback                       */
  void (* HallSensor_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);      /*!< TIM Hall Sensor Msp DeInit Callback                     */
  void (* PeriodElapsedCallback)(struct __TIM_HandleTypeDef *htim);             /*!< TIM Period Elapsed Callback                             */
  void (* PeriodElapsedHalfCpltCallback)(struct __TIM_HandleTypeDef *htim);     /*!< TIM Period Elapsed half complete Callback               */
  void (* TriggerCallback)(struct __TIM_HandleTypeDef *htim);                   /*!< TIM Trigger Callback                                    */
  void (* TriggerHalfCpltCallback)(struct __TIM_HandleTypeDef *htim);           /*!< TIM Trigger half complete Callback                      */
  void (* IC_CaptureCallback)(struct __TIM_HandleTypeDef *htim);                /*!< TIM Input Capture Callback                              */
  void (* IC_CaptureHalfCpltCallback)(struct __TIM_HandleTypeDef *htim);        /*!< TIM Input Capture half complete Callback                */
  void (* OC_DelayElapsedCallback)(struct __TIM_HandleTypeDef *htim);           /*!< TIM Output Compare Delay Elapsed Callback               */
  void (* PWM_PulseFinishedCallback)(struct __TIM_HandleTypeDef *htim);         /*!< TIM PWM Pulse Finished Callback                         */
  void (* PWM_PulseFinishedHalfCpltCallback)(struct __TIM_HandleTypeDef *htim); /*!< TIM PWM Pulse Finished half complete Callback           */
  void (* ErrorCallback)(struct __TIM_HandleTypeDef *htim);                     /*!< TIM Error Callback                                      */
  void (* CommutationCallback)(struct __TIM_HandleTypeDef *htim);               /*!< TIM Commutation Callback                                */
  void (* CommutationHalfCpltCallback)(struct __TIM_HandleTypeDef *htim);       /*!< TIM Commutation half complete Callback                  */
  void (* BreakCallback)(struct __TIM_HandleTypeDef *htim);                     /*!< TIM Break Callback                                      */
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
} TIM_HandleTypeDef;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL TIM Callback ID enumeration definition
  */
typedef enum
{
   HAL_TIM_BASE_MSPINIT_CB_ID            = 0x00U    /*!< TIM Base MspInit Callback ID                              */
  ,HAL_TIM_BASE_MSPDEINIT_CB_ID          = 0x01U    /*!< TIM Base MspDeInit Callback ID                            */
  ,HAL_TIM_IC_MSPINIT_CB_ID              = 0x02U    /*!< TIM IC MspInit Callback ID                                */
  ,HAL_TIM_IC_MSPDEINIT_CB_ID            = 0x03U    /*!< TIM IC MspDeInit Callback ID                              */
  ,HAL_TIM_OC_MSPINIT_CB_ID              = 0x04U    /*!< TIM OC MspInit Callback ID                                */
  ,HAL_TIM_OC_MSPDEINIT_CB_ID            = 0x05U    /*!< TIM OC MspDeInit Callback ID                              */
  ,HAL_TIM_PWM_MSPINIT_CB_ID             = 0x06U    /*!< TIM PWM MspInit Callback ID                               */
  ,HAL_TIM_PWM_MSPDEINIT_CB_ID           = 0x07U    /*!< TIM PWM MspDeInit Callback ID                             */
  ,HAL_TIM_ONE_PULSE_MSPINIT_CB_ID       = 0x08U    /*!< TIM One Pulse MspInit Callback ID                         */
  ,HAL_TIM_ONE_PULSE_MSPDEINIT_CB_ID     = 0x09U    /*!< TIM One Pulse MspDeInit Callback ID                       */
  ,HAL_TIM_ENCODER_MSPINIT_CB_ID         = 0x0AU    /*!< TIM Encoder MspInit Callback ID                           */
  ,HAL_TIM_ENCODER_MSPDEINIT_CB_ID       = 0x0BU    /*!< TIM Encoder MspDeInit Callback ID                         */
  ,HAL_TIM_HALL_SENSOR_MSPINIT_CB_ID     = 0x0CU    /*!< TIM Hall Sensor MspDeInit Callback ID                     */
  ,HAL_TIM_HALL_SENSOR_MSPDEINIT_CB_ID   = 0x0DU    /*!< TIM Hall Sensor MspDeInit Callback ID                     */
  ,HAL_TIM_PERIOD_ELAPSED_CB_ID          = 0x0EU    /*!< TIM Period Elapsed Callback ID                             */
  ,HAL_TIM_PERIOD_ELAPSED_HALF_CB_ID     = 0x0FU    /*!< TIM Period Elapsed half complete Callback ID               */
  ,HAL_TIM_TRIGGER_CB_ID                 = 0x10U    /*!< TIM Trigger Callback ID                                    */
  ,HAL_TIM_TRIGGER_HALF_CB_ID            = 0x11U    /*!< TIM Trigger half complete Callback ID                      */

  ,HAL_TIM_IC_CAPTURE_CB_ID              = 0x12U    /*!< TIM Input Capture Callback ID                              */
  ,HAL_TIM_IC_CAPTURE_HALF_CB_ID         = 0x13U    /*!< TIM Input Capture half complete Callback ID                */
  ,HAL_TIM_OC_DELAY_ELAPSED_CB_ID        = 0x14U    /*!< TIM Output Compare Delay Elapsed Callback ID               */
  ,HAL_TIM_PWM_PULSE_FINISHED_CB_ID      = 0x15U    /*!< TIM PWM Pulse Finished Callback ID           */
  ,HAL_TIM_PWM_PULSE_FINISHED_HALF_CB_ID = 0x16U    /*!< TIM PWM Pulse Finished half complete Callback ID           */
  ,HAL_TIM_ERROR_CB_ID                   = 0x17U    /*!< TIM Error Callback ID                                      */
  ,HAL_TIM_COMMUTATION_CB_ID             = 0x18U    /*!< TIM Commutation Callback ID                                */
  ,HAL_TIM_COMMUTATION_HALF_CB_ID        = 0x19U    /*!< TIM Commutation half complete Callback ID                  */
  ,HAL_TIM_BREAK_CB_ID                   = 0x1AU    /*!< TIM Break Callback ID                                      */
} HAL_TIM_CallbackIDTypeDef;

/**
  * @brief  HAL TIM Callback pointer definition
  */
typedef  void (*pTIM_CallbackTypeDef)(TIM_HandleTypeDef *htim);  /*!< pointer to the TIM callback function */

#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */

/**
  * @brief  TIM Hall sensor Configuration Structure definition
  */

typedef struct
{
  uint32_t IC1Polarity;         /*!< Specifies the active edge of the input signal.
                                     This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint32_t IC1Prescaler;        /*!< Specifies the Input Capture Prescaler.
                                     This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint32_t IC1Filter;           /*!< Specifies the input capture filter.
                                     This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */

  uint32_t Commutation_Delay;   /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                                     This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */
} TIM_HallSensor_InitTypeDef;

/**
  * @}
  */
/* End of exported types -----------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup TIM_Exported_Constants TIM Exported Constants
  * @{
  */

/** @defgroup TIM_ClearInput_Source TIM Clear Input Source
  * @{
  */
#define TIM_CLEARINPUTSOURCE_NONE           0x00000000U   /*!< OCREF_CLR is disabled */
#define TIM_CLEARINPUTSOURCE_ETR            0x00000001U   /*!< OCREF_CLR is connected to ETRF input */
/**
  * @}
  */

/** @defgroup TIM_DMA_Base_address TIM DMA Base Address
  * @{
  */
#define TIM_DMABASE_CR1                    0x00000000U
#define TIM_DMABASE_CR2                    0x00000001U
#define TIM_DMABASE_SMCR                   0x00000002U
#define TIM_DMABASE_DIER                   0x00000003U
#define TIM_DMABASE_SR                     0x00000004U
#define TIM_DMABASE_EGR                    0x00000005U
#define TIM_DMABASE_CCMR1                  0x00000006U
#define TIM_DMABASE_CCMR2                  0x00000007U
#define TIM_DMABASE_CCER                   0x00000008U
#define TIM_DMABASE_CNT                    0x00000009U
#define TIM_DMABASE_PSC                    0x0000000AU
#define TIM_DMABASE_ARR                    0x0000000BU
#define TIM_DMABASE_RCR                    0x0000000CU
#define TIM_DMABASE_CCR1                   0x0000000DU
#define TIM_DMABASE_CCR2                   0x0000000EU
#define TIM_DMABASE_CCR3                   0x0000000FU
#define TIM_DMABASE_CCR4                   0x00000010U
#define TIM_DMABASE_BDTR                   0x00000011U
#define TIM_DMABASE_DCR                    0x00000012U
#define TIM_DMABASE_DMAR                   0x00000013U
/**
  * @}
  */

/** @defgroup TIM_Event_Source TIM Event Source
  * @{
  */
#define TIM_EVENTSOURCE_UPDATE              TIMER_EGR_UG_MASK     /*!< Reinitialize the counter and generates an update of the registers */
#define TIM_EVENTSOURCE_CC1                 TIMER_EGR_CC1G_MASK   /*!< A capture/compare event is generated on channel 1 */
#define TIM_EVENTSOURCE_CC2                 TIMER_EGR_CC2G_MASK   /*!< A capture/compare event is generated on channel 2 */
#define TIM_EVENTSOURCE_CC3                 TIMER_EGR_CC3G_MASK   /*!< A capture/compare event is generated on channel 3 */
#define TIM_EVENTSOURCE_CC4                 TIMER_EGR_CC4G_MASK   /*!< A capture/compare event is generated on channel 4 */
#define TIM_EVENTSOURCE_COM                 TIMER_EGR_COMG_MASK   /*!< A commutation event is generated */
#define TIM_EVENTSOURCE_TRIGGER             TIMER_EGR_TG_MASK     /*!< A trigger event is generated */
#define TIM_EVENTSOURCE_BREAK               TIMER_EGR_BG_MASK     /*!< A break event is generated */
/**
  * @}
  */

/** @defgroup TIM_Input_Channel_Polarity TIM Input Channel polarity
  * @{
  */
#define  TIM_INPUTCHANNELPOLARITY_RISING      0x00000000U                              /*!< Polarity for TIx source */
#define  TIM_INPUTCHANNELPOLARITY_FALLING     TIMER_CCER_CC1P_MASK                     /*!< Polarity for TIx source */
#define  TIM_INPUTCHANNELPOLARITY_BOTHEDGE    (TIMER_CCER_CC1P_MASK | TIMER_CCER_CC1NP_MASK)  /*!< Polarity for TIx source */
/**
  * @}
  */

/** @defgroup TIM_ETR_Polarity TIM ETR Polarity
  * @{
  */
#define TIM_ETRPOLARITY_INVERTED              TIMER_SMCR_ETP_MASK               /*!< Polarity for ETR source */
#define TIM_ETRPOLARITY_NONINVERTED           0x00000000U                       /*!< Polarity for ETR source */
/**
  * @}
  */

/** @defgroup TIM_ETR_Prescaler TIM ETR Prescaler
  * @{
  */
#define TIM_ETRPRESCALER_DIV1                 0x00000000U                       /*!< No prescaler is used */
#define TIM_ETRPRESCALER_DIV2                 TIMER_SMCR_ETPS_0                       /*!< ETR input source is divided by 2 */
#define TIM_ETRPRESCALER_DIV4                 TIMER_SMCR_ETPS_1                       /*!< ETR input source is divided by 4 */
#define TIM_ETRPRESCALER_DIV8                 TIMER_SMCR_ETPS                       /*!< ETR input source is divided by 8 */
/**
  * @}
  */

/** @defgroup TIM_Counter_Mode TIM Counter Mode
  * @{
  */
#define TIM_COUNTERMODE_UP                 0x00000000U                          /*!< Counter used as up-counter   */
#define TIM_COUNTERMODE_DOWN               TIMER_CR1_DIR_MASK                       /*!< Counter used as down-counter */
#define TIM_COUNTERMODE_CENTERALIGNED1     TIMER_CR1_CMS_0                          /*!< Center-aligned mode 1        */
#define TIM_COUNTERMODE_CENTERALIGNED2     TIMER_CR1_CMS_1                          /*!< Center-aligned mode 2        */
#define TIM_COUNTERMODE_CENTERALIGNED3     TIMER_CR1_CMS                       /*!< Center-aligned mode 3        */
/**
  * @}
  */

/** @defgroup TIM_ClockDivision TIM Clock Division
  * @{
  */
#define TIM_CLOCKDIVISION_DIV1             0x00000000U                        /*!< Clock division: tDTS=tCK_INT   */
#define TIM_CLOCKDIVISION_DIV2             TIMER_CR1_CKD_0                        /*!< Clock division: tDTS=2*tCK_INT */
#define TIM_CLOCKDIVISION_DIV4             TIMER_CR1_CKD_1                        /*!< Clock division: tDTS=4*tCK_INT */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_State TIM Output Compare State
  * @{
  */
#define TIM_OUTPUTSTATE_DISABLE            0x00000000U                          /*!< Capture/Compare 1 output disabled */
#define TIM_OUTPUTSTATE_ENABLE             TIMER_CCER_CC1E_MASK                 /*!< Capture/Compare 1 output enabled */
/**
  * @}
  */

/** @defgroup TIM_AutoReloadPreload TIM Auto-Reload Preload
  * @{
  */
#define TIM_AUTORELOAD_PRELOAD_DISABLE                0x00000000U               /*!< TIMx_ARR register is not buffered */
#define TIM_AUTORELOAD_PRELOAD_ENABLE                 TIMER_CR1_ARPE_MASK           /*!< TIMx_ARR register is buffered */

/**
  * @}
  */

/** @defgroup TIM_Output_Fast_State TIM Output Fast State
  * @{
  */
#define TIM_OCFAST_DISABLE                 0x00000000U                          /*!< Output Compare fast disable */
#define TIM_OCFAST_ENABLE                  TIMER_CCMR1_OC1FE_MASK              /*!< Output Compare fast enable  */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_State TIM Complementary Output Compare State
  * @{
  */
#define TIM_OUTPUTNSTATE_DISABLE           0x00000000U                          /*!< OCxN is disabled  */
#define TIM_OUTPUTNSTATE_ENABLE            TIMER_CCER_CC1NE_MASK                /*!< OCxN is enabled   */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Polarity TIM Output Compare Polarity
  * @{
  */
#define TIM_OCPOLARITY_HIGH                0x00000000U                          /*!< Capture/Compare output polarity  */
#define TIM_OCPOLARITY_LOW                 TIMER_CCER_CC1P_MASK                 /*!< Capture/Compare output polarity  */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Polarity TIM Complementary Output Compare Polarity
  * @{
  */
#define TIM_OCNPOLARITY_HIGH               0x00000000U                          /*!< Capture/Compare complementary output polarity */
#define TIM_OCNPOLARITY_LOW                TIMER_CCER_CC1NP_MASK                /*!< Capture/Compare complementary output polarity */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Idle_State TIM Output Compare Idle State
  * @{
  */
#define TIM_OCIDLESTATE_SET                TIMER_CR2_OIS1_MASK                      /*!< Output Idle state: OCx=1 when MOE=0 */
#define TIM_OCIDLESTATE_RESET              0x00000000U                          /*!< Output Idle state: OCx=0 when MOE=0 */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Idle_State TIM Complementary Output Compare Idle State
  * @{
  */
#define TIM_OCNIDLESTATE_SET               TIMER_CR2_OIS1N_MASK                     /*!< Complementary output Idle state: OCxN=1 when MOE=0 */
#define TIM_OCNIDLESTATE_RESET             0x00000000U                          /*!< Complementary output Idle state: OCxN=0 when MOE=0 */
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Polarity TIM Input Capture Polarity
  * @{
  */
#define  TIM_ICPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING      /*!< Capture triggered by rising edge on timer input                  */
#define  TIM_ICPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING     /*!< Capture triggered by falling edge on timer input                 */
#define  TIM_ICPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE    /*!< Capture triggered by both rising and falling edges on timer input*/
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Selection TIM Input Capture Selection
  * @{  
  */
#define TIM_ICSELECTION_DIRECTTI           TIMER_CCMR1_CC1S_0                     /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                                     connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSELECTION_INDIRECTTI         TIMER_CCMR1_CC1S_1                     /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                                     connected to IC2, IC1, IC4 or IC3, respectively */
#define TIM_ICSELECTION_TRC                TIMER_CCMR1_CC1S_MASK                       /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC */
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Prescaler TIM Input Capture Prescaler
  * @{
  */
#define TIM_ICPSC_DIV1                     0x00000000U                          /*!< Capture performed each time an edge is detected on the capture input */
#define TIM_ICPSC_DIV2                     TIMER_CCMR1_IC1PSC_0                   /*!< Capture performed once every 2 events                                */
#define TIM_ICPSC_DIV4                     TIMER_CCMR1_IC1PSC_1                   /*!< Capture performed once every 4 events                                */
#define TIM_ICPSC_DIV8                     TIMER_CCMR1_IC1PSC                     /*!< Capture performed once every 8 events                                */
/**
  * @}
  */

/** @defgroup TIM_One_Pulse_Mode TIM One Pulse Mode
  * @{
  */
#define TIM_OPMODE_SINGLE                  TIMER_CR1_OPM_MASK                          /*!< Counter stops counting at the next update event */
#define TIM_OPMODE_REPETITIVE              0x00000000U                          /*!< Counter is not stopped at update event          */
/**
  * @}
  */

/** @defgroup TIM_Encoder_Mode TIM Encoder Mode
  * @{
  */
#define TIM_ENCODERMODE_TI1                      0x00000001U                                                       /*!< Quadrature encoder mode 1, x2 mode, counts up/down on TI1FP1 edge depending on TI2FP2 level  */
#define TIM_ENCODERMODE_TI2                      0x00000002U                                                       /*!< Quadrature encoder mode 2, x2 mode, counts up/down on TI2FP2 edge depending on TI1FP1 level. */
#define TIM_ENCODERMODE_TI12                     0x00000003U                                                       /*!< Quadrature encoder mode 3, x4 mode, counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input. */
/**
  * @}
  */

/** @defgroup TIM_Interrupt_definition TIM interrupt Definition
  * @{
  */
#define TIM_IT_UPDATE                      TIMER_IDR_UIE_MASK                         /*!< Update interrupt            */
#define TIM_IT_CC1                         TIMER_IDR_CC1IE_MASK                       /*!< Capture/Compare 1 interrupt */
#define TIM_IT_CC2                         TIMER_IDR_CC2IE_MASK                       /*!< Capture/Compare 2 interrupt */
#define TIM_IT_CC3                         TIMER_IDR_CC3IE_MASK                       /*!< Capture/Compare 3 interrupt */
#define TIM_IT_CC4                         TIMER_IDR_CC4IE_MASK                       /*!< Capture/Compare 4 interrupt */
#define TIM_IT_COM                         TIMER_IDR_COMIE_MASK                       /*!< Commutation interrupt       */
#define TIM_IT_TRIGGER                     TIMER_IDR_TIE_MASK                         /*!< Trigger interrupt           */
#define TIM_IT_BREAK                       TIMER_IDR_BIE_MASK                         /*!< Break interrupt             */
#define TIM_IT_CC1O                        TIMER_IDR_CC1OIE_MASK                      /*!< Capture/compare 1 overcap interrupt */
#define TIM_IT_CC2O                        TIMER_IDR_CC2OIE_MASK                      /*!< Break interrupt 2 overcap interrupt */
#define TIM_IT_CC3O                        TIMER_IDR_CC3OIE_MASK                      /*!< Break interrupt 3 overcap interrupt */
#define TIM_IT_CC4O                        TIMER_IDR_CC4OIE_MASK                      /*!< Break interrupt 4 overcap interrupt */
/**
  * @}
  */

/** @defgroup TIM_Commutation_Source  TIM Commutation Source
  * @{
  */
#define TIM_COMMUTATION_TRGI              TIMER_CR2_CCUS                          /*!< When Capture/compare control bits are preloaded, they are updated by setting the COMG bit or when an rising edge occurs on trigger input */
#define TIM_COMMUTATION_SOFTWARE          0x00000000U                           /*!< When Capture/compare control bits are preloaded, they are updated by setting the COMG bit */
/**
  * @}
  */

/** @defgroup TIM_DMA_sources TIM DMA Sources
  * @{
  */
#define TIM_DMA_UPDATE                     TIMER_DMAEN_UDE_MASK                         /*!< DMA request is triggered by the update event */
#define TIM_DMA_CC1                        TIMER_DMAEN_CC1DE_MASK                       /*!< DMA request is triggered by the capture/compare macth 1 event */
#define TIM_DMA_CC2                        TIMER_DMAEN_CC2DE_MASK                       /*!< DMA request is triggered by the capture/compare macth 2 event event */
#define TIM_DMA_CC3                        TIMER_DMAEN_CC3DE_MASK                       /*!< DMA request is triggered by the capture/compare macth 3 event event */
#define TIM_DMA_CC4                        TIMER_DMAEN_CC4DE_MASK                       /*!< DMA request is triggered by the capture/compare macth 4 event event */
#define TIM_DMA_COM                        TIMER_DMAEN_COMDE_MASK                       /*!< DMA request is triggered by the commutation event */
#define TIM_DMA_TRIGGER                    TIMER_DMAEN_TDE_MASK                         /*!< DMA request is triggered by the trigger event */
/**
  * @}
  */

/** @defgroup TIM_Flag_definition TIM Flag Definition
  * @{
  */
#define TIM_FLAG_UPDATE                    TIMER_RIF_UIF                           /*!< Update interrupt flag         */
#define TIM_FLAG_CC1                       TIMER_RIF_CC1IF                         /*!< Capture/Compare 1 interrupt flag */
#define TIM_FLAG_CC2                       TIMER_RIF_CC2IF                         /*!< Capture/Compare 2 interrupt flag */
#define TIM_FLAG_CC3                       TIMER_RIF_CC3IF                         /*!< Capture/Compare 3 interrupt flag */
#define TIM_FLAG_CC4                       TIMER_RIF_CC4IF                         /*!< Capture/Compare 4 interrupt flag */
#define TIM_FLAG_COM                       TIMER_RIF_COMIF                         /*!< Commutation interrupt flag    */
#define TIM_FLAG_TRIGGER                   TIMER_RIF_TIF                           /*!< Trigger interrupt flag        */
#define TIM_FLAG_BREAK                     TIMER_RIF_BIF                           /*!< Break interrupt flag          */
#define TIM_FLAG_CC1OF                     TIMER_RIF_CC1OIF                         /*!< Capture 1 overcapture flag    */
#define TIM_FLAG_CC2OF                     TIMER_RIF_CC2OIF                         /*!< Capture 2 overcapture flag    */
#define TIM_FLAG_CC3OF                     TIMER_RIF_CC3OIF                         /*!< Capture 3 overcapture flag    */
#define TIM_FLAG_CC4OF                     TIMER_RIF_CC4OIF                         /*!< Capture 4 overcapture flag    */
/**
  * @}
  */

/** @defgroup TIM_Channel TIM Channel
  * @{
  */
#define TIM_CHANNEL_1                      0x00000000U                          /*!< Capture/compare channel 1 identifier      */
#define TIM_CHANNEL_2                      0x00000004U                          /*!< Capture/compare channel 2 identifier      */
#define TIM_CHANNEL_3                      0x00000008U                          /*!< Capture/compare channel 3 identifier      */
#define TIM_CHANNEL_4                      0x0000000CU                          /*!< Capture/compare channel 4 identifier      */
#define TIM_CHANNEL_ALL                    0x0000003CU                          /*!< Global Capture/compare channel identifier  */
/**
  * @}
  */

/** @defgroup TIM_Clock_Source TIM Clock Source
  * @{
  */
#define TIM_CLOCKSOURCE_ETRMODE2    TIMER_SMCR_ETPS_1      /*!< External clock source mode 2                          */
#define TIM_CLOCKSOURCE_INTERNAL    TIMER_SMCR_ETPS_0      /*!< Internal clock source                                 */
#define TIM_CLOCKSOURCE_ITR0        TIM_TS_ITR0          /*!< External clock source mode 1 (ITR0)                   */
#define TIM_CLOCKSOURCE_ITR1        TIM_TS_ITR1          /*!< External clock source mode 1 (ITR1)                   */
#define TIM_CLOCKSOURCE_ITR2        TIM_TS_ITR2          /*!< External clock source mode 1 (ITR2)                   */
#define TIM_CLOCKSOURCE_ITR3        TIM_TS_ITR3          /*!< External clock source mode 1 (ITR3)                   */
#define TIM_CLOCKSOURCE_TI1ED       TIM_TS_TI1F_ED       /*!< External clock source mode 1 (TTI1FP1 + edge detect.) */
#define TIM_CLOCKSOURCE_TI1         TIM_TS_TI1FP1        /*!< External clock source mode 1 (TTI1FP1)                */
#define TIM_CLOCKSOURCE_TI2         TIM_TS_TI2FP2        /*!< External clock source mode 1 (TTI2FP2)                */
#define TIM_CLOCKSOURCE_ETRMODE1    TIM_TS_ETRF          /*!< External clock source mode 1 (ETRF)                   */
/**
  * @}
  */

/** @defgroup TIM_Clock_Polarity TIM Clock Polarity
  * @{
  */
#define TIM_CLOCKPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED           /*!< Polarity for ETRx clock sources */
#define TIM_CLOCKPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED        /*!< Polarity for ETRx clock sources */
#define TIM_CLOCKPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING    /*!< Polarity for TIx clock sources */
#define TIM_CLOCKPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING   /*!< Polarity for TIx clock sources */
#define TIM_CLOCKPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE  /*!< Polarity for TIx clock sources */
/**
  * @}
  */

/** @defgroup TIM_Clock_Prescaler TIM Clock Prescaler
  * @{
  */
#define TIM_CLOCKPRESCALER_DIV1                 TIM_ETRPRESCALER_DIV1           /*!< No prescaler is used                                                     */
#define TIM_CLOCKPRESCALER_DIV2                 TIM_ETRPRESCALER_DIV2           /*!< Prescaler for External ETR Clock: Capture performed once every 2 events. */
#define TIM_CLOCKPRESCALER_DIV4                 TIM_ETRPRESCALER_DIV4           /*!< Prescaler for External ETR Clock: Capture performed once every 4 events. */
#define TIM_CLOCKPRESCALER_DIV8                 TIM_ETRPRESCALER_DIV8           /*!< Prescaler for External ETR Clock: Capture performed once every 8 events. */
/**
  * @}
  */

/** @defgroup TIM_ClearInput_Polarity TIM Clear Input Polarity
  * @{
  */
#define TIM_CLEARINPUTPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED      /*!< Polarity for ETRx pin */
#define TIM_CLEARINPUTPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED   /*!< Polarity for ETRx pin */
/**
  * @}
  */

/** @defgroup TIM_ClearInput_Prescaler TIM Clear Input Prescaler
  * @{
  */
#define TIM_CLEARINPUTPRESCALER_DIV1              TIM_ETRPRESCALER_DIV1         /*!< No prescaler is used                                                   */
#define TIM_CLEARINPUTPRESCALER_DIV2              TIM_ETRPRESCALER_DIV2         /*!< Prescaler for External ETR pin: Capture performed once every 2 events. */
#define TIM_CLEARINPUTPRESCALER_DIV4              TIM_ETRPRESCALER_DIV4         /*!< Prescaler for External ETR pin: Capture performed once every 4 events. */
#define TIM_CLEARINPUTPRESCALER_DIV8              TIM_ETRPRESCALER_DIV8         /*!< Prescaler for External ETR pin: Capture performed once every 8 events. */
/**
  * @}
  */

/** @defgroup TIM_OSSR_Off_State_Selection_for_Run_mode_state TIM OSSR OffState Selection for Run mode state
  * @{
  */
#define TIM_OSSR_ENABLE                          TIMER_BDTR_OSSR                  /*!< When inactive, OC/OCN outputs are enabled (still controlled by the timer)           */
#define TIM_OSSR_DISABLE                         0x00000000U                    /*!< When inactive, OC/OCN outputs are disabled (not controlled any longer by the timer) */
/**
  * @}
  */

/** @defgroup TIM_OSSI_Off_State_Selection_for_Idle_mode_state TIM OSSI OffState Selection for Idle mode state
  * @{
  */
#define TIM_OSSI_ENABLE                          TIMER_BDTR_OSSI                  /*!< When inactive, OC/OCN outputs are enabled (still controlled by the timer)           */
#define TIM_OSSI_DISABLE                         0x00000000U                    /*!< When inactive, OC/OCN outputs are disabled (not controlled any longer by the timer) */
/**
  * @}
  */
/** @defgroup TIM_Lock_level  TIM Lock level
  * @{
  */
#define TIM_LOCKLEVEL_OFF                  0x00000000U                          /*!< LOCK OFF     */
#define TIM_LOCKLEVEL_1                    TIMER_BDTR_LOCK_0                      /*!< LOCK Level 1 */
#define TIM_LOCKLEVEL_2                    TIMER_BDTR_LOCK_1                      /*!< LOCK Level 2 */
#define TIM_LOCKLEVEL_3                    TIMER_BDTR_LOCK                        /*!< LOCK Level 3 */
/**
  * @}
  */

/** @defgroup TIM_Break_Input_enable_disable TIM Break Input Enable
  * @{
  */
#define TIM_BREAK_ENABLE                   TIMER_BDTR_BKE                         /*!< Break input BRK is enabled  */
#define TIM_BREAK_DISABLE                  0x00000000U                          /*!< Break input BRK is disabled */
/**
  * @}
  */

/** @defgroup TIM_Break_Polarity TIM Break Input Polarity
  * @{
  */
#define TIM_BREAKPOLARITY_LOW              0x00000000U                          /*!< Break input BRK is active low  */
#define TIM_BREAKPOLARITY_HIGH             TIMER_BDTR_BKP                         /*!< Break input BRK is active high */
/**
  * @}
  */

/** @defgroup TIM_AOE_Bit_Set_Reset TIM Automatic Output Enable
  * @{
  */
#define TIM_AUTOMATICOUTPUT_DISABLE        0x00000000U                          /*!< MOE can be set only by software */
#define TIM_AUTOMATICOUTPUT_ENABLE         TIMER_BDTR_AOE                         /*!< MOE can be set by software or automatically at the next update event 
                                                                                    (if none of the break inputs BRK and BRK2 is active) */
/**
  * @}
  */

/** @defgroup TIM_Master_Mode_Selection TIM Master Mode Selection
  * @{
  */
#define TIM_TRGO_RESET            0x00000000U                                      /*!< TIMx_EGR.UG bit is used as trigger output (TRGO)              */
#define TIM_TRGO_ENABLE           TIMER_CR2_MMS_0                                    /*!< TIMx_CR1.CEN bit is used as trigger output (TRGO)             */
#define TIM_TRGO_UPDATE           TIMER_CR2_MMS_1                                    /*!< Update event is used as trigger output (TRGO)                 */
#define TIM_TRGO_OC1              (TIMER_CR2_MMS_1 | TIMER_CR2_MMS_0)                  /*!< Capture or a compare match 1 is used as trigger output (TRGO) */
#define TIM_TRGO_OC1REF           TIMER_CR2_MMS_2                                    /*!< OC1REF signal is used as trigger output (TRGO)                */
#define TIM_TRGO_OC2REF           (TIMER_CR2_MMS_2 | TIMER_CR2_MMS_0)                  /*!< OC2REF signal is used as trigger output(TRGO)                 */
#define TIM_TRGO_OC3REF           (TIMER_CR2_MMS_2 | TIMER_CR2_MMS_1)                  /*!< OC3REF signal is used as trigger output(TRGO)                 */
#define TIM_TRGO_OC4REF           (TIMER_CR2_MMS_2 | TIMER_CR2_MMS_1 | TIMER_CR2_MMS_0)  /*!< OC4REF signal is used as trigger output(TRGO)                 */
/**
  * @}
  */

/** @defgroup TIM_Master_Slave_Mode TIM Master/Slave Mode
  * @{
  */
#define TIM_MASTERSLAVEMODE_ENABLE         TIMER_SMCR_MSM                         /*!< No action */
#define TIM_MASTERSLAVEMODE_DISABLE        0x00000000U                          /*!< Master/slave mode is selected */
/**
  * @}
  */

/** @defgroup TIM_Slave_Mode TIM Slave mode
  * @{
  */
#define TIM_SLAVEMODE_DISABLE                0x00000000U                                        /*!< Slave mode disabled           */
#define TIM_SLAVEMODE_RESET                  TIMER_SMCR_SMS_2                                     /*!< Reset Mode                    */
#define TIM_SLAVEMODE_GATED                  (TIMER_SMCR_SMS_2 | TIMER_SMCR_SMS_0)                  /*!< Gated Mode                    */
#define TIM_SLAVEMODE_TRIGGER                (TIMER_SMCR_SMS_2 | TIMER_SMCR_SMS_1)                  /*!< Trigger Mode                  */
#define TIM_SLAVEMODE_EXTERNAL1              (TIMER_SMCR_SMS_2 | TIMER_SMCR_SMS_1 | TIMER_SMCR_SMS_0) /*!< External Clock Mode 1         */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_and_PWM_modes TIM Output Compare and PWM Modes
  * @{
  */
#define TIM_OCMODE_TIMING                   0x00000000U                                              /*!< Frozen                                 */
#define TIM_OCMODE_ACTIVE                   TIMER_CCMR1_OC1M_0                                         /*!< Set channel to active level on match   */
#define TIM_OCMODE_INACTIVE                 TIMER_CCMR1_OC1M_1                                         /*!< Set channel to inactive level on match */
#define TIM_OCMODE_TOGGLE                   (TIMER_CCMR1_OC1M_1 | TIMER_CCMR1_OC1M_0)                    /*!< Toggle                                 */
#define TIM_OCMODE_PWM1                     (TIMER_CCMR1_OC1M_2 | TIMER_CCMR1_OC1M_1)                    /*!< PWM mode 1                             */
#define TIM_OCMODE_PWM2                     (TIMER_CCMR1_OC1M_2 | TIMER_CCMR1_OC1M_1 | TIMER_CCMR1_OC1M_0) /*!< PWM mode 2                             */
#define TIM_OCMODE_FORCED_ACTIVE            (TIMER_CCMR1_OC1M_2 | TIMER_CCMR1_OC1M_0)                    /*!< Force active level                     */
#define TIM_OCMODE_FORCED_INACTIVE          TIMER_CCMR1_OC1M_2                                         /*!< Force inactive level                   */
/**
  * @}
  */

/** @defgroup TIM_Trigger_Selection TIM Trigger Selection
  * @{
  */
#define TIM_TS_ITR0          0x00000000U                /*!< Internal Trigger 0 (ITR0)              */
#define TIM_TS_ITR1          0x00000001U                /*!< Internal Trigger 1 (ITR1)              */
#define TIM_TS_ITR2          0x00000002U                /*!< Internal Trigger 2 (ITR2)              */
#define TIM_TS_ITR3          0x00000003U                /*!< Internal Trigger 3 (ITR3)              */
#define TIM_TS_TI1F_ED       0x00000004U                /*!< TI1 Edge Detector (TI1F_ED)            */
#define TIM_TS_TI1FP1        0x00000005U                /*!< Filtered Timer Input 1 (TI1FP1)        */
#define TIM_TS_TI2FP2        0x00000006U                /*!< Filtered Timer Input 2 (TI2FP2)        */
#define TIM_TS_ETRF          0x00000007U                /*!< Filtered External Trigger input (ETRF) */
#define TIM_TS_NONE          0x0000FFFFU                /*!< No trigger selected                    */
/**
  * @}
  */

/** @defgroup TIM_Trigger_Polarity TIM Trigger Polarity
  * @{
  */
#define TIM_TRIGGERPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED               /*!< Polarity for ETRx trigger sources             */
#define TIM_TRIGGERPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED            /*!< Polarity for ETRx trigger sources             */
#define TIM_TRIGGERPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING        /*!< Polarity for TIxFPx or TI1_ED trigger sources */
#define TIM_TRIGGERPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING       /*!< Polarity for TIxFPx or TI1_ED trigger sources */
#define TIM_TRIGGERPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE      /*!< Polarity for TIxFPx or TI1_ED trigger sources */
/**
  * @}
  */

/** @defgroup TIM_Trigger_Prescaler TIM Trigger Prescaler
  * @{
  */
#define TIM_TRIGGERPRESCALER_DIV1             TIM_ETRPRESCALER_DIV1             /*!< No prescaler is used                                                       */
#define TIM_TRIGGERPRESCALER_DIV2             TIM_ETRPRESCALER_DIV2             /*!< Prescaler for External ETR Trigger: Capture performed once every 2 events. */
#define TIM_TRIGGERPRESCALER_DIV4             TIM_ETRPRESCALER_DIV4             /*!< Prescaler for External ETR Trigger: Capture performed once every 4 events. */
#define TIM_TRIGGERPRESCALER_DIV8             TIM_ETRPRESCALER_DIV8             /*!< Prescaler for External ETR Trigger: Capture performed once every 8 events. */
/**
  * @}
  */

/** @defgroup TIM_TI1_Selection TIM TI1 Input Selection
  * @{
  */
#define TIM_TI1SELECTION_CH1               0x00000000U                          /*!< The TIMx_CH1 pin is connected to TI1 input */
#define TIM_TI1SELECTION_XORCOMBINATION    TIMER_CR2_TI1S                      /*!< The TIMx_CH1, CH2 and CH3 pins are connected to the TI1 input (XOR combination) */
/**
  * @}
  */

/** @defgroup TIM_DMA_Burst_Length TIM DMA Burst Length
  * @{
  */
#define TIM_DMABURSTLENGTH_1TRANSFER       0x00000000U                          /*!< The transfer is done to 1 register starting trom TIMx_CR1 + TIMx_DCR.DBA   */
#define TIM_DMABURSTLENGTH_2TRANSFERS      0x00000100U                          /*!< The transfer is done to 2 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABURSTLENGTH_3TRANSFERS      0x00000200U                          /*!< The transfer is done to 3 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABURSTLENGTH_4TRANSFERS      0x00000300U                          /*!< The transfer is done to 4 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABURSTLENGTH_5TRANSFERS      0x00000400U                          /*!< The transfer is done to 5 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABURSTLENGTH_6TRANSFERS      0x00000500U                          /*!< The transfer is done to 6 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABURSTLENGTH_7TRANSFERS      0x00000600U                          /*!< The transfer is done to 7 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABURSTLENGTH_8TRANSFERS      0x00000700U                          /*!< The transfer is done to 8 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABURSTLENGTH_9TRANSFERS      0x00000800U                          /*!< The transfer is done to 9 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABURSTLENGTH_10TRANSFERS     0x00000900U                          /*!< The transfer is done to 10 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABURSTLENGTH_11TRANSFERS     0x00000A00U                          /*!< The transfer is done to 11 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABURSTLENGTH_12TRANSFERS     0x00000B00U                          /*!< The transfer is done to 12 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABURSTLENGTH_13TRANSFERS     0x00000C00U                          /*!< The transfer is done to 13 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABURSTLENGTH_14TRANSFERS     0x00000D00U                          /*!< The transfer is done to 14 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABURSTLENGTH_15TRANSFERS     0x00000E00U                          /*!< The transfer is done to 15 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABURSTLENGTH_16TRANSFERS     0x00000F00U                          /*!< The transfer is done to 16 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABURSTLENGTH_17TRANSFERS     0x00001000U                          /*!< The transfer is done to 17 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABURSTLENGTH_18TRANSFERS     0x00001100U                          /*!< The transfer is done to 18 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
/**
  * @}
  */

/** @defgroup DMA_Handle_index TIM DMA Handle Index
  * @{
  */
#define TIM_DMA_ID_UPDATE                ((uint16_t) 0x0000)       /*!< Index of the DMA handle used for Update DMA requests */
#define TIM_DMA_ID_CC1                   ((uint16_t) 0x0001)       /*!< Index of the DMA handle used for Capture/Compare 1 DMA requests */
#define TIM_DMA_ID_CC2                   ((uint16_t) 0x0002)       /*!< Index of the DMA handle used for Capture/Compare 2 DMA requests */
#define TIM_DMA_ID_CC3                   ((uint16_t) 0x0003)       /*!< Index of the DMA handle used for Capture/Compare 3 DMA requests */
#define TIM_DMA_ID_CC4                   ((uint16_t) 0x0004)       /*!< Index of the DMA handle used for Capture/Compare 4 DMA requests */
#define TIM_DMA_ID_COMMUTATION           ((uint16_t) 0x0005)       /*!< Index of the DMA handle used for Commutation DMA requests */
#define TIM_DMA_ID_TRIGGER               ((uint16_t) 0x0006)       /*!< Index of the DMA handle used for Trigger DMA requests */
/**
  * @}
  */

/** @defgroup Channel_CC_State TIM Capture/Compare Channel State
  * @{
  */
#define TIM_CCx_ENABLE                   0x00000001U                            /*!< Input or output channel is enabled */
#define TIM_CCx_DISABLE                  0x00000000U                            /*!< Input or output channel is disabled */
#define TIM_CCxN_ENABLE                  0x00000004U                            /*!< Complementary output channel is enabled */
#define TIM_CCxN_DISABLE                 0x00000000U                            /*!< Complementary output channel is enabled */
/**
  * @}
  */

/**
  * @}
  */
/* End of exported constants -------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/
/** @defgroup TIM_Exported_Macros TIM Exported Macros
  * @{
  */

/** @brief  Reset TIM handle state.
  * @param  __HANDLE__ TIM handle.
  * @retval None
  */
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
#define __HAL_TIM_RESET_HANDLE_STATE(__HANDLE__) do {                                                        \
                                                      (__HANDLE__)->State             = HAL_TIM_STATE_RESET; \
                                                      (__HANDLE__)->Base_MspInitCallback         = NULL;     \
                                                      (__HANDLE__)->Base_MspDeInitCallback       = NULL;     \
                                                      (__HANDLE__)->IC_MspInitCallback           = NULL;     \
                                                      (__HANDLE__)->IC_MspDeInitCallback         = NULL;     \
                                                      (__HANDLE__)->OC_MspInitCallback           = NULL;     \
                                                      (__HANDLE__)->OC_MspDeInitCallback         = NULL;     \
                                                      (__HANDLE__)->PWM_MspInitCallback          = NULL;     \
                                                      (__HANDLE__)->PWM_MspDeInitCallback        = NULL;     \
                                                      (__HANDLE__)->OnePulse_MspInitCallback     = NULL;     \
                                                      (__HANDLE__)->OnePulse_MspDeInitCallback   = NULL;     \
                                                      (__HANDLE__)->Encoder_MspInitCallback      = NULL;     \
                                                      (__HANDLE__)->Encoder_MspDeInitCallback    = NULL;     \
                                                      (__HANDLE__)->HallSensor_MspInitCallback   = NULL;     \
                                                      (__HANDLE__)->HallSensor_MspDeInitCallback = NULL;     \
                                                     } while(0)
#else
#define __HAL_TIM_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_TIM_STATE_RESET)
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */

/**
  * @brief  Enable the TIM peripheral.
  * @param  __HANDLE__ TIM handle
  * @retval None
  */
#define __HAL_TIM_ENABLE(__HANDLE__)                 ((__HANDLE__)->Instance->CR1|=(TIMER_CR1_CEN))

/**
  * @brief  Enable the TIM main Output.
  * @param  __HANDLE__ TIM handle
  * @retval None
  */
#define __HAL_TIM_MOE_ENABLE(__HANDLE__)             ((__HANDLE__)->Instance->BDTR|=(TIMER_BDTR_MOE))

/**
  * @brief  Disable the TIM peripheral.
  * @param  __HANDLE__ TIM handle
  * @retval None
  */
#define __HAL_TIM_DISABLE(__HANDLE__) \
  do { \
    if (((__HANDLE__)->Instance->CCER & TIM_CCER_CCxE_MASK) == 0UL) \
    { \
      if(((__HANDLE__)->Instance->CCER & TIM_CCER_CCxNE_MASK) == 0UL) \
      { \
        (__HANDLE__)->Instance->CR1 &= ~(TIMER_CR1_CEN); \
      } \
    } \
  } while(0)

/**
  * @brief  Disable the TIM main Output.
  * @param  __HANDLE__ TIM handle
  * @retval None
  * @note The Main Output Enable of a timer instance is disabled only if all the CCx and CCxN channels have been disabled
  */
#define __HAL_TIM_MOE_DISABLE(__HANDLE__) \
  do { \
    if (((__HANDLE__)->Instance->CCER & TIM_CCER_CCxE_MASK) == 0UL) \
    { \
      if(((__HANDLE__)->Instance->CCER & TIM_CCER_CCxNE_MASK) == 0UL) \
      { \
        (__HANDLE__)->Instance->BDTR &= ~(TIMER_BDTR_MOE); \
      } \
    } \
  } while(0)

/**
  * @brief  Disable the TIM main Output.
  * @param  __HANDLE__ TIM handle
  * @retval None
  * @note The Main Output Enable of a timer instance is disabled unconditionally
  */
#define __HAL_TIM_MOE_DISABLE_UNCONDITIONALLY(__HANDLE__)  (__HANDLE__)->Instance->BDTR &= ~(TIMER_BDTR_MOE)

/** @brief  Enable the specified TIM interrupt.
  * @param  __HANDLE__ specifies the TIM Handle.
  * @param  __INTERRUPT__ specifies the TIM interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg TIM_IT_UPDATE: Update interrupt
  *            @arg TIM_IT_CC1:   Capture/Compare 1 interrupt
  *            @arg TIM_IT_CC2:  Capture/Compare 2 interrupt
  *            @arg TIM_IT_CC3:  Capture/Compare 3 interrupt
  *            @arg TIM_IT_CC4:  Capture/Compare 4 interrupt
  *            @arg TIM_IT_COM:   Commutation interrupt
  *            @arg TIM_IT_TRIGGER: Trigger interrupt
  *            @arg TIM_IT_BREAK: Break interrupt
  * @retval None
  */
#define __HAL_TIM_ENABLE_IT(__HANDLE__, __INTERRUPT__)    ((__HANDLE__)->Instance->IER |= (__INTERRUPT__))

/** @brief  Disable the specified TIM interrupt.
  * @param  __HANDLE__ specifies the TIM Handle.
  * @param  __INTERRUPT__ specifies the TIM interrupt source to disable.
  *          This parameter can be one of the following values:
  *            @arg TIM_IT_UPDATE: Update interrupt
  *            @arg TIM_IT_CC1:   Capture/Compare 1 interrupt
  *            @arg TIM_IT_CC2:  Capture/Compare 2 interrupt
  *            @arg TIM_IT_CC3:  Capture/Compare 3 interrupt
  *            @arg TIM_IT_CC4:  Capture/Compare 4 interrupt
  *            @arg TIM_IT_COM:   Commutation interrupt
  *            @arg TIM_IT_TRIGGER: Trigger interrupt
  *            @arg TIM_IT_BREAK: Break interrupt
  * @retval None
  */
#define __HAL_TIM_DISABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->IDR &= ~(__INTERRUPT__))

/** @brief  Enable the specified DMA request.
  * @param  __HANDLE__ specifies the TIM Handle.
  * @param  __DMA__ specifies the TIM DMA request to enable.
  *          This parameter can be one of the following values:
  *            @arg TIM_DMA_UPDATE: Update DMA request
  *            @arg TIM_DMA_CC1:   Capture/Compare 1 DMA request
  *            @arg TIM_DMA_CC2:  Capture/Compare 2 DMA request
  *            @arg TIM_DMA_CC3:  Capture/Compare 3 DMA request
  *            @arg TIM_DMA_CC4:  Capture/Compare 4 DMA request
  *            @arg TIM_DMA_COM:   Commutation DMA request
  *            @arg TIM_DMA_TRIGGER: Trigger DMA request
  * @retval None
  */
#define __HAL_TIM_ENABLE_DMA(__HANDLE__, __DMA__)         ((__HANDLE__)->Instance->DMAEN |= (__DMA__))

/** @brief  Disable the specified DMA request.
  * @param  __HANDLE__ specifies the TIM Handle.
  * @param  __DMA__ specifies the TIM DMA request to disable.
  *          This parameter can be one of the following values:
  *            @arg TIM_DMA_UPDATE: Update DMA request
  *            @arg TIM_DMA_CC1:   Capture/Compare 1 DMA request
  *            @arg TIM_DMA_CC2:  Capture/Compare 2 DMA request
  *            @arg TIM_DMA_CC3:  Capture/Compare 3 DMA request
  *            @arg TIM_DMA_CC4:  Capture/Compare 4 DMA request
  *            @arg TIM_DMA_COM:   Commutation DMA request
  *            @arg TIM_DMA_TRIGGER: Trigger DMA request
  * @retval None
  */
#define __HAL_TIM_DISABLE_DMA(__HANDLE__, __DMA__)        ((__HANDLE__)->Instance->DMAEN &= ~(__DMA__))

/** @brief  Check whether the specified TIM interrupt flag is set or not.
  * @param  __HANDLE__ specifies the TIM Handle.
  * @param  __FLAG__ specifies the TIM interrupt flag to check.
  *        This parameter can be one of the following values:
  *            @arg TIM_FLAG_UPDATE: Update interrupt flag
  *            @arg TIM_FLAG_CC1: Capture/Compare 1 interrupt flag
  *            @arg TIM_FLAG_CC2: Capture/Compare 2 interrupt flag
  *            @arg TIM_FLAG_CC3: Capture/Compare 3 interrupt flag
  *            @arg TIM_FLAG_CC4: Capture/Compare 4 interrupt flag
  *            @arg TIM_FLAG_COM:  Commutation interrupt flag
  *            @arg TIM_FLAG_TRIGGER: Trigger interrupt flag
  *            @arg TIM_FLAG_BREAK: Break interrupt flag
  *            @arg TIM_FLAG_CC1OF: Capture/Compare 1 overcapture flag
  *            @arg TIM_FLAG_CC2OF: Capture/Compare 2 overcapture flag
  *            @arg TIM_FLAG_CC3OF: Capture/Compare 3 overcapture flag
  *            @arg TIM_FLAG_CC4OF: Capture/Compare 4 overcapture flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_TIM_GET_FLAG(__HANDLE__, __FLAG__)          (((__HANDLE__)->Instance->RIF &(__FLAG__)) == (__FLAG__))

/** @brief  Clear the specified TIM interrupt flag.
  * @param  __HANDLE__ specifies the TIM Handle.
  * @param  __FLAG__ specifies the TIM interrupt flag to clear.
  *        This parameter can be one of the following values:
  *            @arg TIM_FLAG_UPDATE: Update interrupt flag
  *            @arg TIM_FLAG_CC1: Capture/Compare 1 interrupt flag
  *            @arg TIM_FLAG_CC2: Capture/Compare 2 interrupt flag
  *            @arg TIM_FLAG_CC3: Capture/Compare 3 interrupt flag
  *            @arg TIM_FLAG_CC4: Capture/Compare 4 interrupt flag
  *            @arg TIM_FLAG_COM:  Commutation interrupt flag
  *            @arg TIM_FLAG_TRIGGER: Trigger interrupt flag
  *            @arg TIM_FLAG_BREAK: Break interrupt flag
  *            @arg TIM_FLAG_CC1OF: Capture/Compare 1 overcapture flag
  *            @arg TIM_FLAG_CC2OF: Capture/Compare 2 overcapture flag
  *            @arg TIM_FLAG_CC3OF: Capture/Compare 3 overcapture flag
  *            @arg TIM_FLAG_CC4OF: Capture/Compare 4 overcapture flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_TIM_CLEAR_FLAG(__HANDLE__, __FLAG__)        ((__HANDLE__)->Instance->ICR |= (__FLAG__))

/**
  * @brief  Check whether the specified TIM interrupt source is enabled or not.
  * @param  __HANDLE__ TIM handle
  * @param  __INTERRUPT__ specifies the TIM interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg TIM_IT_UPDATE: Update interrupt
  *            @arg TIM_IT_CC1:   Capture/Compare 1 interrupt
  *            @arg TIM_IT_CC2:  Capture/Compare 2 interrupt
  *            @arg TIM_IT_CC3:  Capture/Compare 3 interrupt
  *            @arg TIM_IT_CC4:  Capture/Compare 4 interrupt
  *            @arg TIM_IT_COM:   Commutation interrupt
  *            @arg TIM_IT_TRIGGER: Trigger interrupt
  *            @arg TIM_IT_BREAK: Break interrupt
  * @retval The state of TIM_IT (SET or RESET).
  */
#define __HAL_TIM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->IVS & (__INTERRUPT__)) \
                                                             == (__INTERRUPT__)) ? SET : RESET)

/** @brief Clear the TIM interrupt pending bits.
  * @param  __HANDLE__ TIM handle
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *          This parameter can be one of the following values:
  *            @arg TIM_IT_UPDATE: Update interrupt
  *            @arg TIM_IT_CC1:   Capture/Compare 1 interrupt
  *            @arg TIM_IT_CC2:  Capture/Compare 2 interrupt
  *            @arg TIM_IT_CC3:  Capture/Compare 3 interrupt
  *            @arg TIM_IT_CC4:  Capture/Compare 4 interrupt
  *            @arg TIM_IT_COM:   Commutation interrupt
  *            @arg TIM_IT_TRIGGER: Trigger interrupt
  *            @arg TIM_IT_BREAK: Break interrupt
  * @retval None
  */
#define __HAL_TIM_CLEAR_IT(__HANDLE__, __INTERRUPT__)      ((__HANDLE__)->Instance->ICR |= (__INTERRUPT__))

/**
  * @brief  Indicates whether or not the TIM Counter is used as downcounter.
  * @param  __HANDLE__ TIM handle.
  * @retval False (Counter used as upcounter) or True (Counter used as downcounter)
  * @note This macro is particularly useful to get the counting mode when the timer operates in Center-aligned mode or Encoder
mode.
  */
#define __HAL_TIM_IS_TIM_COUNTING_DOWN(__HANDLE__)    (((__HANDLE__)->Instance->CR1 &(TIMER_CR1_DIR)) == (TIMER_CR1_DIR))

/**
  * @brief  Set the TIM Prescaler on runtime.
  * @param  __HANDLE__ TIM handle.
  * @param  __PRESC__ specifies the Prescaler new value.
  * @retval None
  */
#define __HAL_TIM_SET_PRESCALER(__HANDLE__, __PRESC__)       ((__HANDLE__)->Instance->PSC = (__PRESC__))

/**
  * @brief  Set the TIM Counter Register value on runtime.
  * @param  __HANDLE__ TIM handle.
  * @param  __COUNTER__ specifies the Counter register new value.
  * @retval None
  */
#define __HAL_TIM_SET_COUNTER(__HANDLE__, __COUNTER__)  ((__HANDLE__)->Instance->CNT = (__COUNTER__))

/**
  * @brief  Get the TIM Counter Register value on runtime.
  * @param  __HANDLE__ TIM handle.
  * @retval 16-bit or 32-bit value of the timer counter register (TIMx_CNT)
  */
#define __HAL_TIM_GET_COUNTER(__HANDLE__)  ((__HANDLE__)->Instance->CNT)

/**
  * @brief  Set the TIM Autoreload Register value on runtime without calling another time any Init function.
  * @param  __HANDLE__ TIM handle.
  * @param  __AUTORELOAD__ specifies the Counter register new value.
  * @retval None
  */
#define __HAL_TIM_SET_AUTORELOAD(__HANDLE__, __AUTORELOAD__) \
  do{                                                    \
    (__HANDLE__)->Instance->ARR = (__AUTORELOAD__);  \
    (__HANDLE__)->Init.Period = (__AUTORELOAD__);    \
  } while(0)

/**
  * @brief  Get the TIM Autoreload Register value on runtime.
  * @param  __HANDLE__ TIM handle.
  * @retval 16-bit or 32-bit value of the timer auto-reload register(TIMx_ARR)
  */
#define __HAL_TIM_GET_AUTORELOAD(__HANDLE__)  ((__HANDLE__)->Instance->ARR)

/**
  * @brief  Set the TIM Clock Division value on runtime without calling another time any Init function.
  * @param  __HANDLE__ TIM handle.
  * @param  __CKD__ specifies the clock division value.
  *          This parameter can be one of the following value:
  *            @arg TIM_CLOCKDIVISION_DIV1: tDTS=tCK_INT
  *            @arg TIM_CLOCKDIVISION_DIV2: tDTS=2*tCK_INT
  *            @arg TIM_CLOCKDIVISION_DIV4: tDTS=4*tCK_INT
  * @retval None
  */
#define __HAL_TIM_SET_CLOCKDIVISION(__HANDLE__, __CKD__) \
  do{                                                   \
    (__HANDLE__)->Instance->CR1 &= (~TIMER_CR1_CKD);  \
    (__HANDLE__)->Instance->CR1 |= (__CKD__);       \
    (__HANDLE__)->Init.ClockDivision = (__CKD__);   \
  } while(0)

/**
  * @brief  Get the TIM Clock Division value on runtime.
  * @param  __HANDLE__ TIM handle.
  * @retval The clock division can be one of the following values:
  *            @arg TIM_CLOCKDIVISION_DIV1: tDTS=tCK_INT
  *            @arg TIM_CLOCKDIVISION_DIV2: tDTS=2*tCK_INT
  *            @arg TIM_CLOCKDIVISION_DIV4: tDTS=4*tCK_INT
  */
#define __HAL_TIM_GET_CLOCKDIVISION(__HANDLE__)  ((__HANDLE__)->Instance->CR1 & TIMER_CR1_CKD)

/**
  * @brief  Set the TIM Input Capture prescaler on runtime without calling another time HAL_TIM_IC_ConfigChannel() function.
  * @param  __HANDLE__ TIM handle.
  * @param  __CHANNEL__ TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @param  __ICPSC__ specifies the Input Capture4 prescaler new value.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPSC_DIV1: no prescaler
  *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
#define __HAL_TIM_SET_ICPRESCALER(__HANDLE__, __CHANNEL__, __ICPSC__) \
  do{                                                    \
    TIM_RESET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__));  \
    TIM_SET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__), (__ICPSC__)); \
  } while(0)

/**
  * @brief  Get the TIM Input Capture prescaler on runtime.
  * @param  __HANDLE__ TIM handle.
  * @param  __CHANNEL__ TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: get input capture 1 prescaler value
  *            @arg TIM_CHANNEL_2: get input capture 2 prescaler value
  *            @arg TIM_CHANNEL_3: get input capture 3 prescaler value
  *            @arg TIM_CHANNEL_4: get input capture 4 prescaler value
  * @retval The input capture prescaler can be one of the following values:
  *            @arg TIM_ICPSC_DIV1: no prescaler
  *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  */
#define __HAL_TIM_GET_ICPRESCALER(__HANDLE__, __CHANNEL__)  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 & TIMER_CCMR1_IC1PSC) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? (((__HANDLE__)->Instance->CCMR1 & TIMER_CCMR1_IC2PSC) >> 8U) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 & TIMER_CCMR2_IC3PSC) :\
   (((__HANDLE__)->Instance->CCMR2 & TIM_CCMR2_IC4PSC)) >> 8U)

/**
  * @brief  Set the TIM Capture Compare Register value on runtime without calling another time ConfigChannel function.
  * @param  __HANDLE__ TIM handle.
  * @param  __CHANNEL__ TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @param  __COMPARE__ specifies the Capture Compare register new value.
  * @retval None
  */
#define __HAL_TIM_SET_COMPARE(__HANDLE__, __CHANNEL__, __COMPARE__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCR1 = (__COMPARE__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCR2 = (__COMPARE__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCR3 = (__COMPARE__)) :\
   ((__HANDLE__)->Instance->CCR4 = (__COMPARE__)))

/**
  * @brief  Get the TIM Capture Compare Register value on runtime.
  * @param  __HANDLE__ TIM handle.
  * @param  __CHANNEL__ TIM Channel associated with the capture compare register
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: get capture/compare 1 register value
  *            @arg TIM_CHANNEL_2: get capture/compare 2 register value
  *            @arg TIM_CHANNEL_3: get capture/compare 3 register value
  *            @arg TIM_CHANNEL_4: get capture/compare 4 register value
  * @retval 16-bit or 32-bit value of the capture/compare register (TIMx_CCRy)
  */
#define __HAL_TIM_GET_COMPARE(__HANDLE__, __CHANNEL__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCR1) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCR2) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCR3) :\
   ((__HANDLE__)->Instance->CCR4))

/**
  * @brief  Set the TIM Output compare preload.
  * @param  __HANDLE__ TIM handle.
  * @param  __CHANNEL__ TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @retval None
  */
#define __HAL_TIM_ENABLE_OCxPRELOAD(__HANDLE__, __CHANNEL__)    \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= TIMER_CCMR1_OC1PE) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= TIMER_CCMR1_OC2PE) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 |= TIMER_CCMR2_OC3PE) :\
   ((__HANDLE__)->Instance->CCMR2 |= TIMER_CCMR2_OC4PE))

/**
  * @brief  Reset the TIM Output compare preload.
  * @param  __HANDLE__ TIM handle.
  * @param  __CHANNEL__ TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @retval None
  */
#define __HAL_TIM_DISABLE_OCxPRELOAD(__HANDLE__, __CHANNEL__)    \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_OC1PE) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_OC2PE) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 &= ~TIMER_CCMR2_OC3PE) :\
   ((__HANDLE__)->Instance->CCMR2 &= ~TIMER_CCMR2_OC4PE))

/**
  * @brief  Enable fast mode for a given channel.
  * @param  __HANDLE__ TIM handle.
  * @param  __CHANNEL__ TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @note  When fast mode is enabled an active edge on the trigger input acts
  *        like a compare match on CCx output. Delay to sample the trigger
  *        input and to activate CCx output is reduced to 3 clock cycles.
  * @note  Fast mode acts only if the channel is configured in PWM1 or PWM2 mode.
  * @retval None
  */
#define __HAL_TIM_ENABLE_OCxFAST(__HANDLE__, __CHANNEL__)    \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= TIMER_CCMR1_OC1FE) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= TIMER_CCMR1_OC2FE) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 |= TIMER_CCMR2_OC3FE) :\
   ((__HANDLE__)->Instance->CCMR2 |= TIMER_CCMR2_OC4FE))

/**
  * @brief  Disable fast mode for a given channel.
  * @param  __HANDLE__ TIM handle.
  * @param  __CHANNEL__ TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @note  When fast mode is disabled CCx output behaves normally depending
  *        on counter and CCRx values even when the trigger is ON. The minimum
  *        delay to activate CCx output when an active edge occurs on the
  *        trigger input is 5 clock cycles.
  * @retval None
  */
#define __HAL_TIM_DISABLE_OCxFAST(__HANDLE__, __CHANNEL__)    \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_OC1FE) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_OC2FE) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 &= ~TIMER_CCMR2_OC3FE) :\
   ((__HANDLE__)->Instance->CCMR2 &= ~TIMER_CCMR2_OC4FE))

/**
  * @brief  Set the Update Request Source (URS) bit of the TIMx_CR1 register.
  * @param  __HANDLE__ TIM handle.
  * @note  When the URS bit of the TIMx_CR1 register is set, only counter
  *        overflow/underflow generates an update interrupt or DMA request (if
  *        enabled)
  * @retval None
  */
#define __HAL_TIM_URS_ENABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR1|= TIMER_CR1_URS)

/**
  * @brief  Reset the Update Request Source (URS) bit of the TIMx_CR1 register.
  * @param  __HANDLE__ TIM handle.
  * @note  When the URS bit of the TIMx_CR1 register is reset, any of the
  *        following events generate an update interrupt or DMA request (if
  *        enabled):
  *           _ Counter overflow underflow
  *           _ Setting the UG bit
  *           _ Update generation through the slave mode controller
  * @retval None
  */
#define __HAL_TIM_URS_DISABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR1&=~TIMER_CR1_URS)

/**
  * @brief  Set the TIM Capture x input polarity on runtime.
  * @param  __HANDLE__ TIM handle.
  * @param  __CHANNEL__ TIM Channels to be configured.
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  * @param  __POLARITY__ Polarity for TIx source
  *            @arg TIM_INPUTCHANNELPOLARITY_RISING: Rising Edge
  *            @arg TIM_INPUTCHANNELPOLARITY_FALLING: Falling Edge
  *            @arg TIM_INPUTCHANNELPOLARITY_BOTHEDGE: Rising and Falling Edge
  * @retval None
  */
#define __HAL_TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__)    \
  do{                                                                     \
    TIM_RESET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__));               \
    TIM_SET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__), (__POLARITY__)); \
  }while(0)

/**
  * @}
  */
/* End of exported macros ----------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup TIM_Private_Constants TIM Private Constants
  * @{
  */
/* The counter of a timer instance is disabled only if all the CCx and CCxN
   channels have been disabled */
#define TIM_CCER_CCxE_MASK  ((uint32_t)(TIMER_CCER_CC1E | TIMER_CCER_CC2E | TIMER_CCER_CC3E | TIMER_CCER_CC4E))
#define TIM_CCER_CCxNE_MASK ((uint32_t)(TIMER_CCER_CC1NE | TIMER_CCER_CC2NE | TIMER_CCER_CC3NE))
/**
  * @}
  */
/* End of private constants --------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
/** @defgroup TIM_Private_Macros TIM Private Macros
  * @{
  */
#define IS_TIM_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB)    || \
   ((INSTANCE) == LSBSTIM))

#define IS_TIM_ADVANCED_INSTANCE(INSTANCE) ((INSTANCE) == LSADTIM)

#define IS_TIM_CC1_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CC2_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CC3_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CC4_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define  IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CLOCKSOURCE_TIX_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CLOCKSOURCE_ITRX_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_OCXREF_CLEAR_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_ENCODER_INTERFACE_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_XOR_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_MASTER_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB)    || \
   ((INSTANCE) == LSBSTIM))

#define IS_TIM_SLAVE_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_SYNCHRO_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_DMABURST_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB)    || \
   ((INSTANCE) == LSBSTIM))

#define IS_TIM_BREAK_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC))

#define IS_TIM_CCX_INSTANCE(INSTANCE, CHANNEL) \
   ((((INSTANCE) == LSADTIM) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
    ||                                         \
    (((INSTANCE) == LSGPTIMC) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2)))           \
    ||                                         \
    (((INSTANCE) == LSGPTIMA) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
    ||                                         \
    (((INSTANCE) == LSGPTIMB) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4))))

#define IS_TIM_CCXN_INSTANCE(INSTANCE, CHANNEL) \
   ((((INSTANCE) == LSADTIM) &&                    \
     (((CHANNEL) == TIM_CHANNEL_1) ||           \
      ((CHANNEL) == TIM_CHANNEL_2) ||           \
      ((CHANNEL) == TIM_CHANNEL_3)))            \
    ||                                          \
    (((INSTANCE) == LSGPTIMC) &&                   \
      ((CHANNEL) == TIM_CHANNEL_1)))

#define IS_TIM_COUNTER_MODE_SELECT_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_REPETITION_COUNTER_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC))

#define IS_TIM_CLOCK_DIVISION_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_DMA_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))
    
#define IS_TIM_DMA_CC_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))
    
#define IS_TIM_COMMUTATION_EVENT_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC))

#define IS_TIM_ETR_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_32B_COUNTER_INSTANCE(INSTANCE)    ((INSTANCE) == LSGPTIMA)




#define IS_TIM_CLEARINPUT_SOURCE(__MODE__)  (((__MODE__) == TIM_CLEARINPUTSOURCE_NONE)      || \
                                             ((__MODE__) == TIM_CLEARINPUTSOURCE_ETR))

#define IS_TIM_DMA_BASE(__BASE__) (((__BASE__) == TIM_DMABASE_CR1)   || \
                                   ((__BASE__) == TIM_DMABASE_CR2)   || \
                                   ((__BASE__) == TIM_DMABASE_SMCR)  || \
                                   ((__BASE__) == TIM_DMABASE_DIER)  || \
                                   ((__BASE__) == TIM_DMABASE_SR)    || \
                                   ((__BASE__) == TIM_DMABASE_EGR)   || \
                                   ((__BASE__) == TIM_DMABASE_CCMR1) || \
                                   ((__BASE__) == TIM_DMABASE_CCMR2) || \
                                   ((__BASE__) == TIM_DMABASE_CCER)  || \
                                   ((__BASE__) == TIM_DMABASE_CNT)   || \
                                   ((__BASE__) == TIM_DMABASE_PSC)   || \
                                   ((__BASE__) == TIM_DMABASE_ARR)   || \
                                   ((__BASE__) == TIM_DMABASE_RCR)   || \
                                   ((__BASE__) == TIM_DMABASE_CCR1)  || \
                                   ((__BASE__) == TIM_DMABASE_CCR2)  || \
                                   ((__BASE__) == TIM_DMABASE_CCR3)  || \
                                   ((__BASE__) == TIM_DMABASE_CCR4)  || \
                                   ((__BASE__) == TIM_DMABASE_BDTR))

#define IS_TIM_EVENT_SOURCE(__SOURCE__) ((((__SOURCE__) & 0xFFFFFF00U) == 0x00000000U) && ((__SOURCE__) != 0x00000000U))

#define IS_TIM_COUNTER_MODE(__MODE__)      (((__MODE__) == TIM_COUNTERMODE_UP)              || \
                                            ((__MODE__) == TIM_COUNTERMODE_DOWN)            || \
                                            ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED1)  || \
                                            ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED2)  || \
                                            ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED3))

#define IS_TIM_CLOCKDIVISION_DIV(__DIV__)  (((__DIV__) == TIM_CLOCKDIVISION_DIV1) || \
                                            ((__DIV__) == TIM_CLOCKDIVISION_DIV2) || \
                                            ((__DIV__) == TIM_CLOCKDIVISION_DIV4))

#define IS_TIM_AUTORELOAD_PRELOAD(PRELOAD) (((PRELOAD) == TIM_AUTORELOAD_PRELOAD_DISABLE) || \
                                            ((PRELOAD) == TIM_AUTORELOAD_PRELOAD_ENABLE))

#define IS_TIM_FAST_STATE(__STATE__)       (((__STATE__) == TIM_OCFAST_DISABLE) || \
                                            ((__STATE__) == TIM_OCFAST_ENABLE))

#define IS_TIM_OC_POLARITY(__POLARITY__)   (((__POLARITY__) == TIM_OCPOLARITY_HIGH) || \
                                            ((__POLARITY__) == TIM_OCPOLARITY_LOW))

#define IS_TIM_OCN_POLARITY(__POLARITY__)  (((__POLARITY__) == TIM_OCNPOLARITY_HIGH) || \
                                            ((__POLARITY__) == TIM_OCNPOLARITY_LOW))

#define IS_TIM_OCIDLE_STATE(__STATE__)     (((__STATE__) == TIM_OCIDLESTATE_SET) || \
                                            ((__STATE__) == TIM_OCIDLESTATE_RESET))

#define IS_TIM_OCNIDLE_STATE(__STATE__)    (((__STATE__) == TIM_OCNIDLESTATE_SET) || \
                                            ((__STATE__) == TIM_OCNIDLESTATE_RESET))

#define IS_TIM_IC_POLARITY(__POLARITY__)   (((__POLARITY__) == TIM_ICPOLARITY_RISING)   || \
                                            ((__POLARITY__) == TIM_ICPOLARITY_FALLING)  || \
                                            ((__POLARITY__) == TIM_ICPOLARITY_BOTHEDGE))

#define IS_TIM_IC_SELECTION(__SELECTION__) (((__SELECTION__) == TIM_ICSELECTION_DIRECTTI) || \
                                            ((__SELECTION__) == TIM_ICSELECTION_INDIRECTTI) || \
                                            ((__SELECTION__) == TIM_ICSELECTION_TRC))

#define IS_TIM_IC_PRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_ICPSC_DIV1) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV2) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV4) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV8))

#define IS_TIM_OPM_MODE(__MODE__)          (((__MODE__) == TIM_OPMODE_SINGLE) || \
                                            ((__MODE__) == TIM_OPMODE_REPETITIVE))

#define IS_TIM_ENCODER_MODE(__MODE__)      (((__MODE__) == TIM_ENCODERMODE_TI1) || \
                                            ((__MODE__) == TIM_ENCODERMODE_TI2) || \
                                            ((__MODE__) == TIM_ENCODERMODE_TI12))

#define IS_TIM_DMA_SOURCE(__SOURCE__) ((((__SOURCE__) & 0xFFFF80FFU) == 0x00000000U) && ((__SOURCE__) != 0x00000000U))

#define IS_TIM_CHANNELS(__CHANNEL__)       (((__CHANNEL__) == TIM_CHANNEL_1) || \
                                            ((__CHANNEL__) == TIM_CHANNEL_2) || \
                                            ((__CHANNEL__) == TIM_CHANNEL_3) || \
                                            ((__CHANNEL__) == TIM_CHANNEL_4) || \
                                            ((__CHANNEL__) == TIM_CHANNEL_ALL))

#define IS_TIM_OPM_CHANNELS(__CHANNEL__)   (((__CHANNEL__) == TIM_CHANNEL_1) || \
                                            ((__CHANNEL__) == TIM_CHANNEL_2))

#define IS_TIM_COMPLEMENTARY_CHANNELS(__CHANNEL__) (((__CHANNEL__) == TIM_CHANNEL_1) || \
                                                    ((__CHANNEL__) == TIM_CHANNEL_2) || \
                                                    ((__CHANNEL__) == TIM_CHANNEL_3))

#define IS_TIM_CLOCKSOURCE(__CLOCK__) (((__CLOCK__) == TIM_CLOCKSOURCE_INTERNAL) || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ETRMODE2) || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR0)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR1)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR2)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR3)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI1ED)    || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI1)      || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI2)      || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ETRMODE1))

#define IS_TIM_CLOCKPOLARITY(__POLARITY__) (((__POLARITY__) == TIM_CLOCKPOLARITY_INVERTED)    || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_NONINVERTED) || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_RISING)      || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_FALLING)     || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_BOTHEDGE))

#define IS_TIM_CLOCKPRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV1) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV2) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV4) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV8))

#define IS_TIM_CLOCKFILTER(__ICFILTER__)      ((__ICFILTER__) <= 0xFU)

#define IS_TIM_CLEARINPUT_POLARITY(__POLARITY__) (((__POLARITY__) == TIM_CLEARINPUTPOLARITY_INVERTED) || \
                                                  ((__POLARITY__) == TIM_CLEARINPUTPOLARITY_NONINVERTED))

#define IS_TIM_CLEARINPUT_PRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV1) || \
                                                    ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV2) || \
                                                    ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV4) || \
                                                    ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV8))

#define IS_TIM_CLEARINPUT_FILTER(__ICFILTER__) ((__ICFILTER__) <= 0xFU)

#define IS_TIM_OSSR_STATE(__STATE__)       (((__STATE__) == TIM_OSSR_ENABLE) || \
                                            ((__STATE__) == TIM_OSSR_DISABLE))

#define IS_TIM_OSSI_STATE(__STATE__)       (((__STATE__) == TIM_OSSI_ENABLE) || \
                                            ((__STATE__) == TIM_OSSI_DISABLE))

#define IS_TIM_LOCK_LEVEL(__LEVEL__)       (((__LEVEL__) == TIM_LOCKLEVEL_OFF) || \
                                            ((__LEVEL__) == TIM_LOCKLEVEL_1)   || \
                                            ((__LEVEL__) == TIM_LOCKLEVEL_2)   || \
                                            ((__LEVEL__) == TIM_LOCKLEVEL_3))

#define IS_TIM_BREAK_FILTER(__BRKFILTER__) ((__BRKFILTER__) <= 0xFUL)


#define IS_TIM_BREAK_STATE(__STATE__)      (((__STATE__) == TIM_BREAK_ENABLE) || \
                                            ((__STATE__) == TIM_BREAK_DISABLE))

#define IS_TIM_BREAK_POLARITY(__POLARITY__) (((__POLARITY__) == TIM_BREAKPOLARITY_LOW) || \
                                             ((__POLARITY__) == TIM_BREAKPOLARITY_HIGH))

#define IS_TIM_AUTOMATIC_OUTPUT_STATE(__STATE__) (((__STATE__) == TIM_AUTOMATICOUTPUT_ENABLE) || \
                                                  ((__STATE__) == TIM_AUTOMATICOUTPUT_DISABLE))

#define IS_TIM_TRGO_SOURCE(__SOURCE__) (((__SOURCE__) == TIM_TRGO_RESET)  || \
                                        ((__SOURCE__) == TIM_TRGO_ENABLE) || \
                                        ((__SOURCE__) == TIM_TRGO_UPDATE) || \
                                        ((__SOURCE__) == TIM_TRGO_OC1)    || \
                                        ((__SOURCE__) == TIM_TRGO_OC1REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC2REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC3REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC4REF))

#define IS_TIM_MSM_STATE(__STATE__)      (((__STATE__) == TIM_MASTERSLAVEMODE_ENABLE) || \
                                          ((__STATE__) == TIM_MASTERSLAVEMODE_DISABLE))

#define IS_TIM_SLAVE_MODE(__MODE__) (((__MODE__) == TIM_SLAVEMODE_DISABLE)   || \
                                     ((__MODE__) == TIM_SLAVEMODE_RESET)     || \
                                     ((__MODE__) == TIM_SLAVEMODE_GATED)     || \
                                     ((__MODE__) == TIM_SLAVEMODE_TRIGGER)   || \
                                     ((__MODE__) == TIM_SLAVEMODE_EXTERNAL1))

#define IS_TIM_PWM_MODE(__MODE__) (((__MODE__) == TIM_OCMODE_PWM1)               || \
                                   ((__MODE__) == TIM_OCMODE_PWM2))

#define IS_TIM_OC_MODE(__MODE__)  (((__MODE__) == TIM_OCMODE_TIMING)             || \
                                   ((__MODE__) == TIM_OCMODE_ACTIVE)             || \
                                   ((__MODE__) == TIM_OCMODE_INACTIVE)           || \
                                   ((__MODE__) == TIM_OCMODE_TOGGLE)             || \
                                   ((__MODE__) == TIM_OCMODE_FORCED_ACTIVE)      || \
                                   ((__MODE__) == TIM_OCMODE_FORCED_INACTIVE))

#define IS_TIM_TRIGGER_SELECTION(__SELECTION__) (((__SELECTION__) == TIM_TS_ITR0) || \
                                                 ((__SELECTION__) == TIM_TS_ITR1) || \
                                                 ((__SELECTION__) == TIM_TS_ITR2) || \
                                                 ((__SELECTION__) == TIM_TS_ITR3) || \
                                                 ((__SELECTION__) == TIM_TS_TI1F_ED) || \
                                                 ((__SELECTION__) == TIM_TS_TI1FP1) || \
                                                 ((__SELECTION__) == TIM_TS_TI2FP2) || \
                                                 ((__SELECTION__) == TIM_TS_ETRF))

#define IS_TIM_INTERNAL_TRIGGEREVENT_SELECTION(__SELECTION__) (((__SELECTION__) == TIM_TS_ITR0) || \
                                                               ((__SELECTION__) == TIM_TS_ITR1) || \
                                                               ((__SELECTION__) == TIM_TS_ITR2) || \
                                                               ((__SELECTION__) == TIM_TS_ITR3) || \
                                                               ((__SELECTION__) == TIM_TS_NONE))

#define IS_TIM_TRIGGERPOLARITY(__POLARITY__)   (((__POLARITY__) == TIM_TRIGGERPOLARITY_INVERTED   ) || \
                                                ((__POLARITY__) == TIM_TRIGGERPOLARITY_NONINVERTED) || \
                                                ((__POLARITY__) == TIM_TRIGGERPOLARITY_RISING     ) || \
                                                ((__POLARITY__) == TIM_TRIGGERPOLARITY_FALLING    ) || \
                                                ((__POLARITY__) == TIM_TRIGGERPOLARITY_BOTHEDGE   ))

#define IS_TIM_TRIGGERPRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV1) || \
                                                ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV2) || \
                                                ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV4) || \
                                                ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV8))

#define IS_TIM_TRIGGERFILTER(__ICFILTER__) ((__ICFILTER__) <= 0xFU)

#define IS_TIM_TI1SELECTION(__TI1SELECTION__)  (((__TI1SELECTION__) == TIM_TI1SELECTION_CH1) || \
                                                ((__TI1SELECTION__) == TIM_TI1SELECTION_XORCOMBINATION))

#define IS_TIM_DMA_LENGTH(__LENGTH__)      (((__LENGTH__) == TIM_DMABURSTLENGTH_1TRANSFER) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_2TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_3TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_4TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_5TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_6TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_7TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_8TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_9TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_10TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_11TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_12TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_13TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_14TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_15TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_16TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_17TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_18TRANSFERS))

#define IS_TIM_IC_FILTER(__ICFILTER__)   ((__ICFILTER__) <= 0xFU)

#define IS_TIM_DEADTIME(__DEADTIME__)    ((__DEADTIME__) <= 0xFFU)

#define IS_TIM_SLAVEMODE_TRIGGER_ENABLED(__TRIGGER__) ((__TRIGGER__) == TIM_SLAVEMODE_TRIGGER)

#define TIM_SET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__, __ICPSC__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= (__ICPSC__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= ((__ICPSC__) << 8U)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 |= (__ICPSC__)) :\
   ((__HANDLE__)->Instance->CCMR2 |= ((__ICPSC__) << 8U)))

#define TIM_RESET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_IC1PSC) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_IC2PSC) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 &= ~TIMER_CCMR2_IC3PSC) :\
   ((__HANDLE__)->Instance->CCMR2 &= ~TIM_CCMR2_IC4PSC))

#define TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER |= (__POLARITY__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 4U)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 8U)) :\
   ((__HANDLE__)->Instance->CCER |= (((__POLARITY__) << 12U))))

#define TIM_RESET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER &= ~(TIMER_CCER_CC1P | TIMER_CCER_CC1NP))) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER &= ~(TIMER_CCER_CC2P | TIMER_CCER_CC2NP)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER &= ~(TIMER_CCER_CC3P)) :\
   ((__HANDLE__)->Instance->CCER &= ~(TIM_CCER_CC4P)))


#define __HAL_RCC_ADTIM_CLK_ENABLE()   do { \
                                        REG_FIELD_WR(RCC->APB2RST, RCC_ADTIM1, 1);\
                                        REG_FIELD_WR(RCC->APB2RST, RCC_ADTIM1, 0);\
                                        REG_FIELD_WR(RCC->APB2EN, RCC_ADTIM1, 1);\
                                      } while(0U)
#define __HAL_RCC_ADTIM_CLK_DISABLE()   do { \
                                        REG_FIELD_WR(RCC->APB2EN, RCC_ADTIM1, 0);\
                                      } while(0U)                                      

#define __HAL_RCC_GPTIMC_CLK_ENABLE()   do { \
                                        REG_FIELD_WR(RCC->APB2RST, RCC_GPTIMC1, 1);\
                                        REG_FIELD_WR(RCC->APB2RST, RCC_GPTIMC1, 0);\
                                        REG_FIELD_WR(RCC->APB2EN, RCC_GPTIMC1, 1);\
                                      } while(0U)
#define __HAL_RCC_GPTIMC_CLK_DISABLE()   do { \
                                        REG_FIELD_WR(RCC->APB2EN, RCC_GPTIMC1, 0);\
                                      } while(0U)

#define __HAL_RCC_GPTIMA_CLK_ENABLE()   do { \
                                        REG_FIELD_WR(RCC->APB1RST, RCC_GPTIMA1, 1);\
                                        REG_FIELD_WR(RCC->APB1RST, RCC_GPTIMA1, 0);\
                                        REG_FIELD_WR(RCC->APB1EN, RCC_GPTIMA1, 1);\
                                      } while(0U)   
#define __HAL_RCC_GPTIMA_CLK_DISABLE()   do { \
                                        REG_FIELD_WR(RCC->APB1EN, RCC_GPTIMA1, 0);\
                                      } while(0U) 

#define __HAL_RCC_GPTIMB_CLK_ENABLE()   do { \
                                        REG_FIELD_WR(RCC->APB1RST, RCC_GPTIMB1, 1);\
                                        REG_FIELD_WR(RCC->APB1RST, RCC_GPTIMB1, 0);\
                                        REG_FIELD_WR(RCC->APB1EN, RCC_GPTIMB1, 1);\
                                      } while(0U)
#define __HAL_RCC_GPTIMB_CLK_DISABLE()   do { \
                                        REG_FIELD_WR(RCC->APB1EN, RCC_GPTIMB1, 0);\
                                      } while(0U)

#define __HAL_RCC_BTIM_CLK_ENABLE()   do { \
                                        REG_FIELD_WR(RCC->APB1RST, RCC_BSTIM1, 1);\
                                        REG_FIELD_WR(RCC->APB1RST, RCC_BSTIM1, 0);\
                                        REG_FIELD_WR(RCC->APB1EN, RCC_BSTIM1, 1);\
                                      } while(0U)
#define __HAL_RCC_BTIM_CLK_DISABLE()   do { \
                                        REG_FIELD_WR(RCC->APB1EN, RCC_BSTIM1, 0);\
                                      } while(0U)                                                                            
/**
  * @}
  */
/* End of private macros -----------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
/** @addtogroup TIM_Exported_Functions TIM Exported Functions
  * @{
  */

/** @addtogroup TIM_Exported_Functions_Group1 TIM Time Base functions
  *  @brief   Time Base functions
  * @{
  */
/* Time Base functions ********************************************************/
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIM_Base_Start_DMA(TIM_HandleTypeDef *htim, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Base_Stop_DMA(TIM_HandleTypeDef *htim);
/**
  * @}
  */

/** @addtogroup TIM_Exported_Functions_Group2 TIM Output Compare functions
  *  @brief   TIM Output Compare functions
  * @{
  */
/* Timer Output Compare functions *********************************************/
HAL_StatusTypeDef HAL_TIM_OC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_OC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_OC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_OC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIM_OC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_OC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */

/** @addtogroup TIM_Exported_Functions_Group3 TIM PWM functions
  *  @brief   TIM PWM functions
  * @{
  */
/* Timer PWM functions ********************************************************/
HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_PWM_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */

/** @addtogroup TIM_Exported_Functions_Group4 TIM Input Capture functions
  *  @brief   TIM Input Capture functions
  * @{
  */
/* Timer Input Capture functions **********************************************/
HAL_StatusTypeDef HAL_TIM_IC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_IC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIM_IC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_IC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */

/** @addtogroup TIM_Exported_Functions_Group5 TIM One Pulse functions
  *  @brief   TIM One Pulse functions
  * @{
  */
/* Timer One Pulse functions **************************************************/
HAL_StatusTypeDef HAL_TIM_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t OnePulseMode);
HAL_StatusTypeDef HAL_TIM_OnePulse_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_OnePulse_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_OnePulse_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
/**
  * @}
  */

/** @addtogroup TIM_Exported_Functions_Group6 TIM Encoder functions
  *  @brief   TIM Encoder functions
  * @{
  */
/* Timer Encoder functions ****************************************************/
HAL_StatusTypeDef HAL_TIM_Encoder_Init(TIM_HandleTypeDef *htim,  TIM_Encoder_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIM_Encoder_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *htim);
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIM_Encoder_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIM_Encoder_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIM_Encoder_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData1,
                                            uint32_t *pData2, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */

/** @addtogroup TIM_Exported_Functions_Group7 TIM IRQ handler management
  *  @brief   IRQ handler management
  * @{
  */
/* Interrupt Handler functions  ***********************************************/
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);
/**
  * @}
  */

/** @defgroup TIM_Exported_Functions_Group8 TIM Peripheral Control functions
  *  @brief   Peripheral Control functions
  * @{
  */
/* Control functions  *********************************************************/
HAL_StatusTypeDef HAL_TIM_OC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_IC_InitTypeDef *sConfig, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OnePulse_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OnePulse_InitTypeDef *sConfig,
                                                 uint32_t OutputChannel,  uint32_t InputChannel);
HAL_StatusTypeDef HAL_TIM_ConfigOCrefClear(TIM_HandleTypeDef *htim, TIM_ClearInputConfigTypeDef *sClearInputConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef *sClockSourceConfig);
HAL_StatusTypeDef HAL_TIM_ConfigTI1Input(TIM_HandleTypeDef *htim, uint32_t TI1_Selection);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro_IT(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                              uint32_t BurstRequestSrc, uint32_t  *BurstBuffer, uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                             uint32_t BurstRequestSrc, uint32_t  *BurstBuffer, uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource);
uint32_t HAL_TIM_ReadCapturedValue(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */

/** @defgroup TIM_Exported_Functions_Group9 TIM Callbacks functions
  *  @brief   TIM Callbacks functions
  * @{
  */
/* Callback in non blocking modes (Interrupt and DMA) *************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim);

/* Callbacks Register/UnRegister functions  ***********************************/
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_TIM_RegisterCallback(TIM_HandleTypeDef *htim, HAL_TIM_CallbackIDTypeDef CallbackID,
                                           pTIM_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_TIM_UnRegisterCallback(TIM_HandleTypeDef *htim, HAL_TIM_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup TIM_Exported_Functions_Group10 TIM Peripheral State functions
  *  @brief  Peripheral State functions
  * @{
  */
/* Peripheral State functions  ************************************************/
HAL_TIM_StateTypeDef HAL_TIM_Base_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OC_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_PWM_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_IC_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OnePulse_GetState(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_Encoder_GetState(TIM_HandleTypeDef *htim);
/**
  * @}
  */

/**
  * @}
  */
/* End of exported functions -------------------------------------------------*/

/* Private functions----------------------------------------------------------*/
/** @defgroup TIM_Private_Functions TIM Private Functions
  * @{
  */
void TIM_Base_SetConfig(reg_timer_t *TIMx, TIM_Base_InitTypeDef *Structure);
void TIM_TI1_SetConfig(reg_timer_t *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t TIM_ICFilter);
void TIM_OC2_SetConfig(reg_timer_t *TIMx, TIM_OC_InitTypeDef *OC_Config);
void TIM_ETR_SetConfig(reg_timer_t *TIMx, uint32_t TIM_ExtTRGPrescaler,
                       uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter);

// void TIM_DMADelayPulseCplt(DMA_HandleTypeDef *hdma);
// void TIM_DMADelayPulseHalfCplt(DMA_HandleTypeDef *hdma);
// void TIM_DMAError(DMA_HandleTypeDef *hdma);
// void TIM_DMACaptureCplt(DMA_HandleTypeDef *hdma);
// void TIM_DMACaptureHalfCplt(DMA_HandleTypeDef *hdma);
void TIM_CCxChannelCmd(reg_timer_t *TIMx, uint32_t Channel, uint32_t ChannelState);

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
void TIM_ResetCallback(TIM_HandleTypeDef *htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
/** @addtogroup TIMEx_Exported_Functions_Group1 Extended Timer Hall Sensor functions
  *  @brief    Timer Hall Sensor functions
  * @{
  */
/*  Timer Hall Sensor functions  **********************************************/
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Init(TIM_HandleTypeDef *htim, TIM_HallSensor_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_DeInit(TIM_HandleTypeDef *htim);

void HAL_TIMEx_HallSensor_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIMEx_HallSensor_MspDeInit(TIM_HandleTypeDef *htim);

/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop(TIM_HandleTypeDef *htim);
/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_IT(TIM_HandleTypeDef *htim);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_DMA(TIM_HandleTypeDef *htim, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_DMA(TIM_HandleTypeDef *htim);
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group2 Extended Timer Complementary Output Compare functions
  *  @brief   Timer Complementary Output Compare functions
  * @{
  */
/*  Timer Complementary Output Compare functions  *****************************/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIMEx_OCN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group3 Extended Timer Complementary PWM functions
  *  @brief    Timer Complementary PWM functions
  * @{
  */
/*  Timer Complementary PWM functions  ****************************************/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
/* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group4 Extended Timer Complementary One Pulse functions
  *  @brief    Timer Complementary One Pulse functions
  * @{
  */
/*  Timer Complementary One Pulse functions  **********************************/
/* Blocking mode: Polling */
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

/* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group5 Extended Peripheral Control functions
  *  @brief    Peripheral Control functions
  * @{
  */
/* Extended Control functions  ************************************************/
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                              uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_IT(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                 uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_DMA(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                  uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim,
                                                        TIM_MasterConfigTypeDef *sMasterConfig);
HAL_StatusTypeDef HAL_TIMEx_ConfigBreakDeadTime(TIM_HandleTypeDef *htim,
                                                TIM_BreakDeadTimeConfigTypeDef *sBreakDeadTimeConfig);
HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap);
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group6 Extended Callbacks functions
  * @brief    Extended Callbacks functions
  * @{
  */
/* Extended Callback **********************************************************/
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_CommutHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_BreakCallback(TIM_HandleTypeDef *htim);
/**
  * @}
  */

/** @addtogroup TIMEx_Exported_Functions_Group7 Extended Peripheral State functions
  * @brief    Extended Peripheral State functions
  * @{
  */
/* Extended Peripheral State functions  ***************************************/
HAL_TIM_StateTypeDef HAL_TIMEx_HallSensor_GetState(TIM_HandleTypeDef *htim);
/**
  * @}
  */
void TIM_SetCounter(reg_timer_t* TIMx, uint16_t Counter);
void TIM_SetAutoreload(reg_timer_t* TIMx, uint16_t Autoreload);
void TIM_SetCompare1(reg_timer_t* TIMx, uint16_t Compare1);
void TIM_SetCompare2(reg_timer_t* TIMx, uint16_t Compare2);
void TIM_SetCompare3(reg_timer_t* TIMx, uint16_t Compare3);
void TIM_SetCompare4(reg_timer_t* TIMx, uint16_t Compare4);
uint16_t TIM_GetCapture1(reg_timer_t* TIMx);
uint16_t TIM_GetCapture2(reg_timer_t* TIMx);
uint16_t TIM_GetCapture3(reg_timer_t* TIMx);
uint16_t TIM_GetCapture4(reg_timer_t* TIMx);
uint16_t TIM_GetCounter(reg_timer_t* TIMx);
uint16_t TIM_GetPrescaler(reg_timer_t* TIMx);
/**
  * @}
  */
/* End of exported functions -------------------------------------------------*/

/* Private functions----------------------------------------------------------*/
/** @addtogroup TIMEx_Private_Functions TIMEx Private Functions
  * @{
  */
#ifdef DMA_READY
void TIMEx_DMACommutationCplt(DMA_HandleTypeDef *hdma);
void TIMEx_DMACommutationHalfCplt(DMA_HandleTypeDef *hdma);
#endif //DMA_READY
/**
  * @}
  */
/* End of private functions --------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* LSTIMER_H_ */

/*****************************END OF FILE****************************/
