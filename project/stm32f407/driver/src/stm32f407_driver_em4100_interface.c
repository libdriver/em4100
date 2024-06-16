/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      stm32f407_driver_em4100_interface.c
 * @brief     stm32f407 driver em4100 interface source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-06-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/06/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_em4100_interface.h"
#include "driver_em4095_basic.h"
#include "delay.h"
#include "gpio.h"
#include "uart.h"
#include <stdarg.h>

/**
 * @brief exti 0 irq
 * @note  none
 */
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
 * @brief     gpio exti callback
 * @param[in] pin is the gpio pin
 * @note      none
 */
void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
    if (pin == GPIO_PIN_0)
    {
#ifdef USE_DRIVER_EM4095
        em4095_basic_irq_handler();
#else
        #error "em4100 no driver"
#endif
    }
}

#ifdef USE_DRIVER_EM4095
/**
 * @brief     interface receive callback
 * @param[in] mode is the running mode
 * @param[in] *buf points to a decode buffer
 * @param[in] len is the data length
 * @note      none
 */
static void a_em4095_receive_callback(em4095_mode_t mode, em4095_decode_t *buf, uint16_t len)
{
    switch (mode)
    {
        case EM4095_MODE_READ :
        {
            break;
        }
        case EM4095_MODE_WRITE :
        {
            break;
        }
        default :
        {
            em4095_interface_debug_print("em4095: irq unknown mode.\n");
            
            break;
        }
    }
}
#else
    #error "em4100 no driver"
#endif

/**
 * @brief  interface contactless init
 * @return status code
 *         - 0 success
 *         - 1 contactless init failed
 * @note   none
 */
uint8_t em4100_interface_contactless_init(void)
{
    if (gpio_interrupt_init() != 0)
    {
        return 1;
    }
#ifdef USE_DRIVER_EM4095
    if (em4095_basic_init(a_em4095_receive_callback) != 0)
    {
        return 1;
    }
#else
    #error "em4100 no driver"
#endif
    
    return 0;
}

/**
 * @brief  interface contactless deinit
 * @return status code
 *         - 0 success
 *         - 1 contactless deinit failed
 * @note   none
 */
uint8_t em4100_interface_contactless_deinit(void)
{
    if (gpio_interrupt_deinit() != 0)
    {
        return 1;
    }
#ifdef USE_DRIVER_EM4095
    if (em4095_basic_deinit() != 0)
    {
        return 1;
    }
#else
    #error "em4100 no driver"
#endif
    
    return 0;
}

/**
 * @brief      interface contactless read
 * @param[in]  clock_div is the set clock div
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the read length
 * @return     status code
 *             - 0 success
 *             - 1 contactless read failed
 * @note       none
 */
uint8_t em4100_interface_contactless_read(uint32_t clock_div, uint8_t *buf, uint16_t len)
{
    if (em4095_basic_set_div(clock_div) != 0)
    {
        return 1;
    }
#ifdef USE_DRIVER_EM4095
    return em4095_basic_read(buf, len);
#else
    #error "em4100 no driver"
#endif
}

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void em4100_interface_delay_ms(uint32_t ms)
{
    delay_ms(ms);
}

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void em4100_interface_debug_print(const char *const fmt, ...)
{
    char str[256];
    uint16_t len;
    va_list args;
    
    memset((char *)str, 0, sizeof(char) * 256); 
    va_start(args, fmt);
    vsnprintf((char *)str, 255, (char const *)fmt, args);
    va_end(args);
    
    len = strlen((char *)str);
    (void)uart_write((uint8_t *)str, len);
}
