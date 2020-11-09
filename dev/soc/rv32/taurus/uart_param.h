#ifndef UART_PARAM_H_
#define UART_PARAM_H_

#include <stddef.h>
#include "lsuart.h"
#include "reg_uart.h"
#include "field_manipulate.h"

void uart_sw_reset(UART_HandleTypeDef *inst);
void uart_clock_enable(UART_HandleTypeDef *inst,uint8_t status);

void uart_int_op(void (*isr)(UART_HandleTypeDef *),UART_HandleTypeDef *inst,uint8_t states);
void uart_status_set(UART_HandleTypeDef *inst, uint8_t status);

#endif
