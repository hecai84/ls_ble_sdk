#include "platform.h"
#include "ARMCM3.h"
#include "reg_sysc_awo.h"
#include "field_manipulate.h"
#include "io_config.h"
#include "swint_call_asm.h"
#include "reg_sysc_ble.h"
void modem_rf_init(void);
#define ISR_VECTOR_ADDR ((uint32_t *)(0x400000))

void ble_pkt_isr(void);
void ble_util_isr(void);
void SWINT_Handler_ASM(void);
void swint2_process(void);

__attribute__((weak)) void SystemInit(){
    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
    SCB->VTOR = (uint32_t)ISR_VECTOR_ADDR;
}

static void irq_priority()
{
    __NVIC_SetPriority(SVCall_IRQn,1);
    __NVIC_SetPriority(PendSV_IRQn,7);

    __NVIC_SetPriority(RTC1_IRQn,7);
    __NVIC_SetPriority(IWDT_IRQn,7);
    __NVIC_SetPriority(RTC2_IRQn,7);
    __NVIC_SetPriority(EXT_IRQn,7);
    __NVIC_SetPriority(LVD33_IRQn,7);
    __NVIC_SetPriority(MAC_LP_IRQn,0);
    __NVIC_SetPriority(MAC1_IRQn,0);
    __NVIC_SetPriority(DMA_IRQn,7);
    __NVIC_SetPriority(QSPI_IRQn,7);
    __NVIC_SetPriority(SWINT1_IRQn,1);
    __NVIC_SetPriority(CACHE_IRQn,7);
    __NVIC_SetPriority(I8080_IRQn,7);
    __NVIC_SetPriority(TRNG_IRQn,7);
    __NVIC_SetPriority(ECC_IRQn,7);
    __NVIC_SetPriority(CRYPT_IRQn,7);
    __NVIC_SetPriority(BSTIM1_IRQn,7);
    __NVIC_SetPriority(GPTIMA1_IRQn,7);
    __NVIC_SetPriority(GPTIMB1_IRQn,7);
    __NVIC_SetPriority(GPTIMC1_IRQn,7);
    __NVIC_SetPriority(ADTIM1_IRQn,7);
    __NVIC_SetPriority(I2C1_IRQn,7);
    __NVIC_SetPriority(I2C2_IRQn,7);
    __NVIC_SetPriority(I2C3_IRQn,7);
    __NVIC_SetPriority(UART1_IRQn,7);
    __NVIC_SetPriority(UART2_IRQn,7);
    __NVIC_SetPriority(UART3_IRQn,7);
    __NVIC_SetPriority(SPI1_IRQn,7);
    __NVIC_SetPriority(SPI2_IRQn,7);
    __NVIC_SetPriority(PDM_IRQn,7);
    __NVIC_SetPriority(GPIO_IRQn,7);
    __NVIC_SetPriority(WWDT_IRQn,7);
    __NVIC_SetPriority(SWINT2_IRQn,1);
    __NVIC_SetPriority(LCD_IRQn,7);
    __NVIC_SetPriority(ADC_IRQn,7);
    __NVIC_SetPriority(DAC_IRQn,7);
    __NVIC_SetPriority(MAC2_IRQn,2);
    __NVIC_SetPriority(ADC24_IRQn,7);

}

void iob_output_enable(uint8_t i)
{
    SYSC_AWO->IO[1].OE_DOT |= 1<<(i+16);
}

void arm_cm_set_int_isr(uint8_t type,void (*isr)())
{
    ISR_VECTOR_ADDR[type + 16] = (uint32_t)isr;
}

void pll_enable()
{
    SYSC_AWO->PD_AWO_ANA0 |= SYSC_AWO_AWO_EN_DPLL_MASK | SYSC_AWO_AWO_EN_DPLL_16M_RF_MASK | SYSC_AWO_AWO_EN_DPLL_128M_RF_MASK | SYSC_AWO_AWO_EN_DPLL_128M_EXT_MASK;
}

void sys_init_itf()
{
    pll_enable();
    REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL,SYSC_AWO_CLK_SEL_HBUS_L0,2);//16M
    REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0,SYSC_AWO_AWO_BG_RES_TRIM,0x33);
    REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA2,SYSC_AWO_AWO_BG_RBIAS_TRIM,0xf);
    MODIFY_REG(SYSC_AWO->PD_AWO_ANA1,SYSC_AWO_AWO_XO16M_LP_MASK|SYSC_AWO_AWO_XO16M_CAP_TRIM_MASK,1<<SYSC_AWO_AWO_XO16M_LP_POS | 7<<SYSC_AWO_AWO_XO16M_CAP_TRIM_POS);
    SYSC_AWO->PIN_SEL3 = FIELD_BUILD(SYSC_AWO_MAC_DBG_EN, 0xFFFF);
    //SYSC_AWO->PIN_SEL3 = FIELD_BUILD(SYSC_AWO_MDM_DBG_EN, 0xFFFF);

    SYSC_BLE->PD_BLE_CLKG = SYSC_BLE_CLKG_SET_MAC_MASK | SYSC_BLE_CLKG_SET_MDM_MASK | SYSC_BLE_CLKG_SET_RF_MASK;
    irq_priority();
    arm_cm_set_int_isr(MAC1_IRQn,ble_pkt_isr);
    arm_cm_set_int_isr(MAC2_IRQn,ble_util_isr);
    arm_cm_set_int_isr(SWINT1_IRQn,SWINT_Handler_ASM);
    arm_cm_set_int_isr(SWINT2_IRQn,swint2_process);
    __NVIC_EnableIRQ(MAC1_IRQn);
    __NVIC_EnableIRQ(MAC2_IRQn);
    __NVIC_EnableIRQ(SWINT1_IRQn);
    __NVIC_EnableIRQ(SWINT2_IRQn);
    modem_rf_init();
    io_cfg_output(PB02);
    io_cfg_output(PB03);
    io_cfg_output(PB04);
    iob_output_enable(2);
    iob_output_enable(3);
    iob_output_enable(4);
}

void ble_pkt_irq_mask()
{
    __NVIC_DisableIRQ(MAC1_IRQn);
}

void ble_pkt_irq_unmask()
{
    __NVIC_EnableIRQ(MAC1_IRQn);
}

void ble_pkt_irq_clr()
{
    __NVIC_ClearPendingIRQ(MAC1_IRQn);
}

void swint2_set()
{
    __NVIC_SetPendingIRQ(SWINT2_IRQn);
}

void ll_swint_set()
{
    SWINT_SET_INLINE_ASM(SWINT1_IRQn);
}

void iob_output_set(uint8_t i)
{
    SYSC_AWO->IO[1].OE_DOT |= 1<<i;
}

void iob_output_clr(uint8_t i)
{
    SYSC_AWO->IO[1].OE_DOT &= ~(1<<i);
}
