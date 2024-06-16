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
 * @file      driver_em4100_interface_template.c
 * @brief     driver em4100 interface template source file
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

/**
 * @brief  interface contactless init
 * @return status code
 *         - 0 success
 *         - 1 contactless init failed
 * @note   none
 */
uint8_t em4100_interface_contactless_init(void)
{
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
    return 0;
}

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void em4100_interface_delay_ms(uint32_t ms)
{

}

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void em4100_interface_debug_print(const char *const fmt, ...)
{

}
