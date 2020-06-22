#include "lsgpio.h"
#include "reg_lsgpio.h"
#include "io_config.h"
#include "reg_syscfg.h"
#include "sleep.h"
typedef struct
{
    uint8_t port:4,
            num:4;
}gpio_pin_t;

gpio_pin_t uart1_txd;
gpio_pin_t uart1_rxd;
gpio_pin_t uart2_txd;
gpio_pin_t uart2_rxd;
gpio_pin_t uart3_txd;
gpio_pin_t uart3_rxd;
reg_lsgpio_t* GPIO_GetPort(uint8_t Pin_port)
{
    uint8_t       PortID = Pin_port;
    reg_lsgpio_t* Port = {0};

   switch (PortID)
    {
    case 0:
        Port = LSGPIOA;
        break;
    case 1:
        Port = LSGPIOB;
        break;
    case 2:
        Port = LSGPIOC;
        break;
    default:
        break;
    }
    return Port;
}

static void uart_io_init(gpio_pin_t txd,gpio_pin_t rxd)
{
    reg_lsgpio_t* gpiox;
    uint8_t position = txd.num;
    gpiox = GPIO_GetPort(txd.port);
    MODIFY_REG(gpiox->MODE, (GPIO_MODE0_MASK << (position << 1u)), (SET_GPIO_MODE_AF << (position << 1u)));
    MODIFY_REG(gpiox->OD, (GPIO_OD0_MASK << (position << 1u)), (GPIO_OUTPUT_MAX_DRIVER << (position << 1u)));
    MODIFY_REG(gpiox->OE, (GPIO_OE0_MASK << position), (GPIO_OUTPUT_EN << position));
    MODIFY_REG(gpiox->IE, (GPIO_IE0_MASK << position), (0U << position));

    position = rxd.num;
    gpiox = GPIO_GetPort(rxd.port);
    MODIFY_REG(gpiox->MODE, (GPIO_MODE0_MASK << (position << 1u)), (SET_GPIO_MODE_AF << (position << 1u)));
    MODIFY_REG(gpiox->OD, (GPIO_OD0_MASK << (position << 1u)), (GPIO_OUTPUT_MAX_DRIVER << (position << 1u)));
    MODIFY_REG(gpiox->OE, (GPIO_OE0_MASK << position), (GPIO_OUTPUT_EN << position));
    MODIFY_REG(gpiox->IE, (GPIO_IE0_MASK << position), (0U << position));
}

static void uart_io_deinit(gpio_pin_t txd,gpio_pin_t rxd)
{
    reg_lsgpio_t* gpiox;
    uint8_t position = txd.num;
    gpiox = GPIO_GetPort(txd.port);
    MODIFY_REG(gpiox->MODE, (GPIO_MODE0_MASK << (position << 1u)), (SET_GPIO_MODE_GPIO << (position << 1u)));
    HAL_GPIO_WritePin(gpiox,0x01<<position,1);

    position = rxd.num;
    gpiox = GPIO_GetPort(rxd.port);
    MODIFY_REG(gpiox->MODE, (GPIO_MODE0_MASK << (position << 1u)), (SET_GPIO_MODE_GPIO << (position << 1u)));
    HAL_GPIO_WritePin(gpiox,0x01<<position,1);
}
void uart1_io_init(uint8_t txd,uint8_t rxd)
{
    uart1_rxd.port = rxd>>4;
    uart1_rxd.num = rxd;
    uart1_txd.port = txd>>4;
    uart1_txd.num = txd;
    uart_io_init(uart1_rxd,uart1_txd);
}

void uart1_io_deinit()
{
    uart_io_deinit(uart1_rxd,uart1_txd);
}

void uart2_io_init(uint8_t txd,uint8_t rxd)
{
    uart2_rxd.port = rxd>>4;
    uart2_rxd.num = rxd;
    uart2_txd.port = txd>>4;
    uart2_txd.num = txd;
    uart_io_init(uart2_rxd,uart2_txd);
}

void uart2_io_deinit()
{
    uart_io_deinit(uart2_rxd,uart2_txd);
}

void uart3_io_init(uint8_t txd,uint8_t rxd)
{
    uart3_rxd.port = rxd>>4;
    uart3_rxd.num = rxd;
    uart3_txd.port = txd>>4;
    uart3_txd.num = txd;
    uart_io_init(uart3_rxd,uart3_txd);
}

void uart3_io_deinit()
{
    uart_io_deinit(uart3_rxd,uart3_txd);
}


void io_init(void)
{
    RCC->AHBEN |= RCC_GPIOA_MASK | RCC_GPIOB_MASK | RCC_GPIOC_MASK;
    LSGPIOA->MODE = 0;
    LSGPIOA->IE = 0;
    LSGPIOA->OE = 0;
    LSGPIOA->PUPD = 0;
    LSGPIOB->MODE = 0x2800;
    LSGPIOB->IE = 0;
    LSGPIOB->OE = 0;
    LSGPIOB->PUPD = 0x2800;
}

void io_set_output(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    switch(x->port)
    {
    case 0:
        LSGPIOA->OE |= 1<< x->num;
    break;
    case 1:
        LSGPIOB->OE |= 1<< x->num;
    break;
    }

}

void io_set_input(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    switch(x->port)
    {
    case 0:
        LSGPIOA->OE &= ~(1<< x->num);
        LSGPIOA->IE |= 1<< x->num;
    break;
    case 1:
        LSGPIOB->OE &= ~(1<< x->num);
        LSGPIOB->IE |= 1<< x->num;
    break;
    }

}

void io_write_pin(uint8_t pin,uint8_t val)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    switch(x->port)
    {
    case 0:
        LSGPIOA->DOUT |= 1<< x->num;
    break;
    case 1:
        LSGPIOB->DOUT |= 1<< x->num;
    break;
    }

}

uint8_t io_read_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    uint8_t val = 0;
    switch(x->port)
    {
    case 0:
        val = (LSGPIOA->DIN >> x->num) & 0x1;
    break;
    case 1:
        val = (LSGPIOB->DIN >> x->num) & 0x1;
    break;
    }
    return val;
}

void io_toggle_pin(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    switch(x->port)
    {
    case 0:
        LSGPIOA->DOUT ^= 1<< x->num;
    break;
    case 1:
        LSGPIOB->DOUT ^= 1<< x->num;
    break;
    }
}

void io_pull_write(uint8_t pin,io_pull_type_t pull)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    switch(x->port)
    {
    case 0:
        LSGPIOA->PUPD = pull << 2 * x->num;
    break;
    case 1:
        LSGPIOB->PUPD = pull << 2 * x->num;
    break;
    }
}

io_pull_type_t io_pull_read(uint8_t pin)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    io_pull_type_t pull = IO_PULL_DISABLE;
    switch(x->port)
    {
    case 0:
        pull = (LSGPIOA->PUPD >> 2 * x->num ) & 0x3;
    break;
    case 1:
        pull = (LSGPIOB->PUPD >> 2 * x->num ) & 0x3;
    break;
    }
    return pull;
}

void io_exti_config(uint8_t pin,exti_edge_t edge)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    if(x->num <= 7)
    {
        MODIFY_REG(EXTI->EICFG0, 0xf<< 4 * x->num,x->port << 4 * x->num);
    }else
    {
        MODIFY_REG(EXTI->EICFG1, 0xf<< 4 * (x->num - 8),x->port << 4 * (x->num - 8));
    }
    if(edge == INT_EDGE_FALLING)
    {
        EXTI->ERTS &= ~(1 << x->num);
        EXTI->EFTS |= 1 << x->num;
        switch(pin)
        {
        case PA00:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PA00_IO_WKUP<<WKUP_EDGE_POS);
        break;
        case PA07:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PA07_IO_WKUP<<WKUP_EDGE_POS);
        break;
        case PB11:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PB11_IO_WKUP<<WKUP_EDGE_POS);
        break;
        case PB15:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PB15_IO_WKUP<<WKUP_EDGE_POS);
        break;
        }
    }else
    {
        EXTI->EFTS &= ~(1 << x->num);
        EXTI->ERTS |= 1 << x->num;
        switch(pin)
        {
        case PA00:
            SET_BIT(SYSCFG->PMU_WKUP,PA00_IO_WKUP<<WKUP_EDGE_POS);
        break;
        case PA07:
            SET_BIT(SYSCFG->PMU_WKUP,PA07_IO_WKUP<<WKUP_EDGE_POS);
        break;
        case PB11:
            SET_BIT(SYSCFG->PMU_WKUP,PB11_IO_WKUP<<WKUP_EDGE_POS);
        break;
        case PB15:
            SET_BIT(SYSCFG->PMU_WKUP,PB15_IO_WKUP<<WKUP_EDGE_POS);
        break;
        }
    }
}

void io_exti_enable(uint8_t pin,bool enable)
{
    gpio_pin_t *x = (gpio_pin_t *)&pin;
    if(enable==false)
    {
        EXTI->EIDR =  1 << x->num;
        switch(pin)
        {
        case PA00:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PA00_IO_WKUP<<WKUP_EN_POS);
        break;
        case PA07:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PA07_IO_WKUP<<WKUP_EN_POS);
        break;
        case PB11:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PB11_IO_WKUP<<WKUP_EN_POS);
        break;
        case PB15:
            CLEAR_BIT(SYSCFG->PMU_WKUP,PB15_IO_WKUP<<WKUP_EN_POS);
        break;
        }
    }else
    {
        switch(pin)
        {
        case PA00:
            SET_BIT(SYSCFG->PMU_WKUP,PA00_IO_WKUP<<WKUP_EN_POS);
        break;
        case PA07:
            SET_BIT(SYSCFG->PMU_WKUP,PA07_IO_WKUP<<WKUP_EN_POS);
        break;
        case PB11:
            SET_BIT(SYSCFG->PMU_WKUP,PB11_IO_WKUP<<WKUP_EN_POS);
        break;
        case PB15:
            SET_BIT(SYSCFG->PMU_WKUP,PB15_IO_WKUP<<WKUP_EN_POS);
        break;
        }
        EXTI->EIER =  1 << x->num;
    }
}

void io_wkup_en_clr_set(uint8_t pin)
{
    switch(pin)
    {
    case PA00:
        CLEAR_BIT(SYSCFG->PMU_WKUP,PA00_IO_WKUP<<WKUP_EN_POS);
        SET_BIT(SYSCFG->PMU_WKUP,PA00_IO_WKUP<<WKUP_EN_POS);
    break;
    case PA07:
        CLEAR_BIT(SYSCFG->PMU_WKUP,PA07_IO_WKUP<<WKUP_EN_POS);
        SET_BIT(SYSCFG->PMU_WKUP,PA07_IO_WKUP<<WKUP_EN_POS);
    break;
    case PB11:
        CLEAR_BIT(SYSCFG->PMU_WKUP,PB11_IO_WKUP<<WKUP_EN_POS);
        SET_BIT(SYSCFG->PMU_WKUP,PB11_IO_WKUP<<WKUP_EN_POS);
    break;
    case PB15:
        CLEAR_BIT(SYSCFG->PMU_WKUP,PB15_IO_WKUP<<WKUP_EN_POS);
        SET_BIT(SYSCFG->PMU_WKUP,PB15_IO_WKUP<<WKUP_EN_POS);
    break;
    }
}

__attribute__((weak)) void io_exti_callback(uint8_t pin){}

static void exti_io_handler(uint8_t port,uint8_t num)
{
    uint8_t pin = port<<4 | num;
    EXTI->EICR = 1<<num;
    io_wkup_en_clr_set(pin);
    io_exti_callback(pin);
}

void EXTI_Handler()
{
    uint16_t int_stat = EXTI->EEIFM;
    uint8_t i;
    uint8_t port;
    for(i=0;i<8;++i)
    {
        if(1<<i & int_stat)
        {
            port = EXTI->EICFG0 >> (4*i);
            exti_io_handler(port,i);
        }
    }
    for(i=8;i<16;++i)
    {
        if(1<<i & int_stat)
        {
            port = EXTI->EICFG1 >> (4*(i-8));
            exti_io_handler(port,i);
        }
    }
}
