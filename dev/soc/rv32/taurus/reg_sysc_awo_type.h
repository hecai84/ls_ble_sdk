#ifndef REG_SYSC_AWO_TYPE_H_
#define REG_SYSC_AWO_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t LOCK;
    volatile uint32_t OE_DOT;
    volatile uint32_t PUPD;
    volatile uint32_t IE_OD;
    volatile uint32_t DS;
    volatile uint32_t AE;
    volatile uint32_t FIR;
    volatile uint32_t DIN;
}awo_io_reg_t;

typedef struct
{
    volatile uint32_t RESERVED0[2];
    volatile uint32_t CRYPT_WORD;
    volatile uint32_t AWO_CTRL;
    volatile uint32_t RESERVED1[2];
    volatile uint32_t PMU_CTRL;
    volatile uint32_t RESERVED2[3];
    volatile uint32_t PD_AWO_CLKG_SRST;
    volatile uint32_t PD_AWO_CLK_CTRL;
    volatile uint32_t PD_AWO_ANA2;
    volatile uint32_t PD_AWO_ANA0;
    volatile uint32_t PD_AWO_ANA1;
    volatile uint32_t RESERVED3[1];
    volatile uint32_t PIN_SEL0;
    volatile uint32_t PIN_SEL1;
    volatile uint32_t PIN_SEL2;
    volatile uint32_t PIN_SEL3;
    volatile uint32_t RESERVED5[4];
    awo_io_reg_t IO[2];                 // 0x60
    volatile uint32_t RESERVED8[9];	
    volatile uint32_t DBG_ACK;			// 0xc4
    volatile uint32_t ANA_STAT;
}reg_sysc_awo_t;

enum SYSC_AWO_REG_AWO_CTRL_FIELD
{
    SYSC_AWO_CRYPT_EN_MASK = (int)0x80000000,
    SYSC_AWO_CRYPT_EN_POS = 31,
};

enum SYSC_AWO_REG_PMU_CTRL_FIELD
{
    SYSC_AWO_PMU_HLD_DLY_MASK = (int)0x3f0,
    SYSC_AWO_PMU_HLD_DLY_POS = 4,
};

enum SYSC_AWO_REG_PD_AWO_CLKG_SRST_FIELD
{
    SYSC_AWO_CLKG_SET_DIV_HBUS_MASK = (int)0x1,
    SYSC_AWO_CLKG_SET_DIV_HBUS_POS = 0,
    SYSC_AWO_CLKG_CLR_DIV_HBUS_MASK = (int)0x2,
    SYSC_AWO_CLKG_CLR_DIV_HBUS_POS = 1,
};

enum SYSC_AWO_REG_PD_AWO_CLK_CTRL_FIELD
{
    SYSC_AWO_CLK_DIV_PARA_HBUS_M1_MASK = (int)0xf,
    SYSC_AWO_CLK_DIV_PARA_HBUS_M1_POS = 0,
    SYSC_AWO_CLK_SEL_HBUS_MASK = (int)0x70,
    SYSC_AWO_CLK_SEL_HBUS_POS = 4,
    SYSC_AWO_CLK_SEL_PBUS0_MASK = (int)0x100000,
    SYSC_AWO_CLK_SEL_PBUS0_POS = 20,
    SYSC_AWO_CLK_PBUS1_DIV4_MASK = (int)0x800000,
    SYSC_AWO_CLK_PBUS1_DIV4_POS = 23,
    SYSC_AWO_CLK_SEL_QSPI_MASK = (int)0xf000000,
    SYSC_AWO_CLK_SEL_QSPI_POS = 24,
    SYSC_AWO_CLK_FLT_SEL_MASK = (int)0x30000000,
    SYSC_AWO_CLK_FLT_SEL_POS = 28,
    SYSC_AWO_CLK_FLT_BYP_MASK = (int)0x40000000,
    SYSC_AWO_CLK_FLT_BYP_POS = 30,
};

enum SYSC_AWO_REG_PD_AWO_ANA2_FIELD
{
    SYSC_AWO_AWO_BG_RBIAS_TRIM_MASK = (int)0xf,
    SYSC_AWO_AWO_BG_RBIAS_TRIM_POS = 0,
};

enum SYSC_AWO_REG_PD_AWO_ANA0_FIELD
{
    SYSC_AWO_AWO_EN_DPLL_48M_EXT_MASK = (int)0x1,
    SYSC_AWO_AWO_EN_DPLL_48M_EXT_POS = 0,
    SYSC_AWO_AWO_EN_QCLK_MASK = (int)0x2,
    SYSC_AWO_AWO_EN_QCLK_POS = 1,
    SYSC_AWO_AWO_EN_DPLL_LOCK_BYPS_MASK = (int)0x4,
    SYSC_AWO_AWO_EN_DPLL_LOCK_BYPS_POS = 2,
    SYSC_AWO_AWO_EN_DPLL_128M_EXT_MASK = (int)0x8,
    SYSC_AWO_AWO_EN_DPLL_128M_EXT_POS = 3,
    SYSC_AWO_AWO_EN_DPLL_128M_RF_MASK = (int)0x10,
    SYSC_AWO_AWO_EN_DPLL_128M_RF_POS = 4,
    SYSC_AWO_AWO_EN_DPLL_16M_RF_MASK = (int)0x20,
    SYSC_AWO_AWO_EN_DPLL_16M_RF_POS = 5,
    SYSC_AWO_AWO_EN_DPLL_MASK = (int)0x40,
    SYSC_AWO_AWO_EN_DPLL_POS = 6,
    SYSC_AWO_AWO_ENB_DPLL_64M_EXT_MASK = (int)0x80,
    SYSC_AWO_AWO_ENB_DPLL_64M_EXT_POS = 7,
    SYSC_AWO_AWO_LVD_EN_MASK = (int)0x100,
    SYSC_AWO_AWO_LVD_EN_POS = 8,
    SYSC_AWO_AWO_LVD_REF_MASK = (int)0xe00,
    SYSC_AWO_AWO_LVD_REF_POS = 9,
    SYSC_AWO_AWO_LVD_CTL_MASK = (int)0x7000,
    SYSC_AWO_AWO_LVD_CTL_POS = 12,
    SYSC_AWO_AWO_LDO_DG_TRIM_MASK = (int)0x30000,
    SYSC_AWO_AWO_LDO_DG_TRIM_POS = 16,
    SYSC_AWO_AWO_DPLL_SEL_REF_24M_MASK = (int)0x40000,
    SYSC_AWO_AWO_DPLL_SEL_REF_24M_POS = 18,
    SYSC_AWO_AWO_BG_VREF_FINE_MASK = (int)0xc00000,
    SYSC_AWO_AWO_BG_VREF_FINE_POS = 22,
    SYSC_AWO_AWO_BG_RES_TRIM_MASK = (int)0x3f000000,
    SYSC_AWO_AWO_BG_RES_TRIM_POS = 24,
    SYSC_AWO_AWO_DPLL_VCO_ADJ_MASK = (int)0xc0000000,
    SYSC_AWO_AWO_DPLL_VCO_ADJ_POS = 30,
};

enum SYSC_AWO_REG_PD_AWO_ANA1_FIELD
{
    SYSC_AWO_AWO_RCO_MODE_SEL_MASK = (int)0x2000,
    SYSC_AWO_AWO_RCO_MODE_SEL_POS = 13,
    SYSC_AWO_AWO_RCO_CAL_START_MASK = (int)0x8000,
    SYSC_AWO_AWO_RCO_CAL_START_POS = 15,
    SYSC_AWO_AWO_EN_RCO_DIG_PWR_MASK = (int)0x10000,
    SYSC_AWO_AWO_EN_RCO_DIG_PWR_POS = 16,
    SYSC_AWO_AWO_ADC12B_DIG_PWR_EN_MASK = (int)0x20000,
    SYSC_AWO_AWO_ADC12B_DIG_PWR_EN_POS = 17,
    SYSC_AWO_AWO_OSCRC_DIG_PWR_EN_MASK = (int)0x40000,
    SYSC_AWO_AWO_OSCRC_DIG_PWR_EN_POS = 18,
    SYSC_AWO_AWO_XO32K_OE_BYPS_MASK = (int)0x100000,
    SYSC_AWO_AWO_XO32K_OE_BYPS_POS = 20,
    SYSC_AWO_AWO_XO32K_CODE_MASK = (int)0x200000,
    SYSC_AWO_AWO_XO32K_CODE_POS = 21,
    SYSC_AWO_AWO_XO16M_SEL_MASK = (int)0x400000,
    SYSC_AWO_AWO_XO16M_SEL_POS = 22,
    SYSC_AWO_AWO_XO16M_LP_MASK = (int)0x800000,
    SYSC_AWO_AWO_XO16M_LP_POS = 23,
    SYSC_AWO_AWO_XO16M_CAP_TRIM_MASK = (int)0x3f000000,
    SYSC_AWO_AWO_XO16M_CAP_TRIM_POS = 24,
    SYSC_AWO_AWO_XO16M_ADJ_MASK = (int)0xc0000000,
    SYSC_AWO_AWO_XO16M_ADJ_POS = 30,
};

enum SYSC_AWO_REG_PIN_SEL0_FIELD
{
    SYSC_AWO_SWD_EN_MASK = (int)0x1,
    SYSC_AWO_SWD_EN_POS = 0,
    SYSC_AWO_MDM_IO_EN_MASK = (int)0x4,
    SYSC_AWO_MDM_IO_EN_POS = 2,
    SYSC_AWO_CLK_HBUS_OUT_EN_MASK = (int)0x8,
    SYSC_AWO_CLK_HBUS_OUT_EN_POS = 3,
    SYSC_AWO_HSE_OUT_EN_MASK = (int)0x20,
    SYSC_AWO_HSE_OUT_EN_POS = 5,
    SYSC_AWO_RF_IO_EN_MASK = (int)0x40,
    SYSC_AWO_RF_IO_EN_POS = 6,
    SYSC_AWO_BLE_SPI_EN_MASK = (int)0x80,
    SYSC_AWO_BLE_SPI_EN_POS = 7,
    SYSC_AWO_QSPI_EN_MASK = (int)0x3f00,
    SYSC_AWO_QSPI_EN_POS = 8,
    SYSC_AWO_MISC_DBG_EN_MASK = (int)0xff0000,
    SYSC_AWO_MISC_DBG_EN_POS = 16,
    SYSC_AWO_CLK_OUT_SEL_MASK = (int)0x30000000,
    SYSC_AWO_CLK_OUT_SEL_POS = 28,
};

enum SYSC_AWO_REG_PIN_SEL1_FIELD
{
    SYSC_AWO_FUNC_IO_EN_MASK = (int)0x3ffffff,
    SYSC_AWO_FUNC_IO_EN_POS = 0,
};

enum SYSC_AWO_REG_PIN_SEL3_FIELD
{
    SYSC_AWO_MAC_DBG_EN_MASK = (int)0xffff,
    SYSC_AWO_MAC_DBG_EN_POS = 0,
    SYSC_AWO_MDM_DBG_EN_MASK = (int)0xffff0000,
    SYSC_AWO_MDM_DBG_EN_POS = 16,
};

enum SYSC_AWO_REG_IOA_LOCK_FIELD
{
    SYSC_AWO_GPIOA_LOCK_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_LOCK_POS = 0,
};

enum SYSC_AWO_REG_IOA_OE_DOT_FIELD
{
    SYSC_AWO_GPIOA_DOT_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_DOT_POS = 0,
    SYSC_AWO_GPIOA_OE_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOA_OE_POS = 16,
};

enum SYSC_AWO_REG_IOA_PD_PU_FIELD
{
    SYSC_AWO_GPIOA_PU_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_PU_POS = 0,
    SYSC_AWO_GPIOA_PD_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOA_PD_POS = 16,
};

enum SYSC_AWO_REG_IOA_IE_OD_FIELD
{
    SYSC_AWO_GPIOA_OD_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_OD_POS = 0,
    SYSC_AWO_GPIOA_IE_N_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOA_IE_N_POS = 16,
};

enum SYSC_AWO_REG_IOA_DS_FIELD
{
    SYSC_AWO_GPIOA_DS2_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_DS2_POS = 0,
    SYSC_AWO_GPIOA_DS1_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOA_DS1_POS = 16,
};

enum SYSC_AWO_REG_IOA_AE_FIELD
{
    SYSC_AWO_GPIOA_AE2_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_AE2_POS = 0,
    SYSC_AWO_GPIOA_AE1_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOA_AE1_POS = 16,
};

enum SYSC_AWO_REG_IOA_DIN_FIELD
{
    SYSC_AWO_GPIOA_DIN_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_DIN_POS = 0,
};

enum SYSC_AWO_REG_IOB_LOCK_FIELD
{
    SYSC_AWO_GPIOB_LOCK_MASK = (int)0x3ff,
    SYSC_AWO_GPIOB_LOCK_POS = 0,
};

enum SYSC_AWO_REG_IOB_OE_DOT_FIELD
{
    SYSC_AWO_GPIOB_DOT_MASK = (int)0x3ff,
    SYSC_AWO_GPIOB_DOT_POS = 0,
    SYSC_AWO_GPIOB_OE_MASK = (int)0x3ff0000,
    SYSC_AWO_GPIOB_OE_POS = 16,
};

enum SYSC_AWO_REG_IOB_PD_PU_FIELD
{
    SYSC_AWO_GPIOB_PU_MASK = (int)0x3ff,
    SYSC_AWO_GPIOB_PU_POS = 0,
    SYSC_AWO_GPIOB_PD_MASK = (int)0x3ff0000,
    SYSC_AWO_GPIOB_PD_POS = 16,
};

enum SYSC_AWO_REG_IOB_IE_OD_FIELD
{
    SYSC_AWO_GPIOB_OD_MASK = (int)0x3ff,
    SYSC_AWO_GPIOB_OD_POS = 0,
    SYSC_AWO_GPIOB_IE_N_MASK = (int)0x3ff0000,
    SYSC_AWO_GPIOB_IE_N_POS = 16,
};

enum SYSC_AWO_REG_IOB_DS_FIELD
{
    SYSC_AWO_GPIOB_DS2_MASK = (int)0x3ff,
    SYSC_AWO_GPIOB_DS2_POS = 0,
    SYSC_AWO_GPIOB_DS1_MASK = (int)0x3ff0000,
    SYSC_AWO_GPIOB_DS1_POS = 16,
};

enum SYSC_AWO_REG_IOB_AE_FIELD
{
    SYSC_AWO_GPIOB_AE2_MASK = (int)0x3ff,
    SYSC_AWO_GPIOB_AE2_POS = 0,
    SYSC_AWO_GPIOB_AE1_MASK = (int)0x3ff0000,
    SYSC_AWO_GPIOB_AE1_POS = 16,
};

enum SYSC_AWO_REG_IOB_DIN_FIELD
{
    SYSC_AWO_GPIOB_DIN_MASK = (int)0x3ff,
    SYSC_AWO_GPIOB_DIN_POS = 0,
};

enum SYSC_AWO_REG_DBG_ACK_FIELD
{
    SYSC_AWO_CPU_CDBGPWRUPACK_MASK = (int)0x1,
    SYSC_AWO_CPU_CDBGPWRUPACK_POS = 0,
};

enum SYSC_AWO_REG_ANA_STAT_FIELD
{
    SYSC_AWO_BG_VREF_OK12_MASK = (int)0x1,
    SYSC_AWO_BG_VREF_OK12_POS = 0,
    SYSC_AWO_DPLL_LOCK_MASK = (int)0x2,
    SYSC_AWO_DPLL_LOCK_POS = 1,
};

#endif


