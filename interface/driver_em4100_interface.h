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
 * @file      driver_em4100_interface.h
 * @brief     driver em4100 interface header file
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

#ifndef DRIVER_EM4100_INTERFACE_H
#define DRIVER_EM4100_INTERFACE_H

#include "driver_em4100.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup em4100_interface_driver em4100 interface driver function
 * @brief    em4100 interface driver modules
 * @ingroup  em4100_driver
 * @{
 */

/**
 * @brief  interface contactless init
 * @return status code
 *         - 0 success
 *         - 1 contactless init failed
 * @note   none
 */
uint8_t em4100_interface_contactless_init(void);

/**
 * @brief  interface contactless deinit
 * @return status code
 *         - 0 success
 *         - 1 contactless deinit failed
 * @note   none
 */
uint8_t em4100_interface_contactless_deinit(void);

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
uint8_t em4100_interface_contactless_read(uint32_t clock_div, uint8_t *buf, uint16_t len);

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void em4100_interface_delay_ms(uint32_t ms);

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void em4100_interface_debug_print(const char *const fmt, ...);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
