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
 * @file      driver_em4100_basic.c
 * @brief     driver em4100 basic source file
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

#include "driver_em4100_basic.h"

static em4100_handle_t gs_handle;        /**< em4100 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t em4100_basic_init(void)
{
    uint8_t res;
    
    /* link function */
    DRIVER_EM4100_LINK_INIT(&gs_handle, em4100_handle_t);
    DRIVER_EM4100_LINK_CONTACTLESS_INIT(&gs_handle, em4100_interface_contactless_init);
    DRIVER_EM4100_LINK_CONTACTLESS_DEINIT(&gs_handle, em4100_interface_contactless_deinit);
    DRIVER_EM4100_LINK_CONTACTLESS_READ(&gs_handle, em4100_interface_contactless_read);
    DRIVER_EM4100_LINK_DELAY_MS(&gs_handle, em4100_interface_delay_ms);
    DRIVER_EM4100_LINK_DEBUG_PRINT(&gs_handle, em4100_interface_debug_print);
    
    /* init */
    res = em4100_init(&gs_handle);
    if (res != 0)
    {
        em4100_interface_debug_print("em4100: init failed.\n");
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t em4100_basic_deinit(void)
{
    uint8_t res;
    
    /* deinit */
    res = em4100_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example search
 * @param[out] *id points to an id buffer
 * @param[in]  timeout is the check times
 * @return     status code
 *             - 0 success
 *             - 1 timeout
 * @note       none
 */
uint8_t em4100_basic_search(uint8_t id[5], int32_t timeout)
{
    uint8_t res;
    
    /* loop */
    while (1)
    {
        /* request */
        res = em4100_read(&gs_handle, id);
        if (res == 0)
        {
            return 0;
        }
        
        /* delay */
        em4100_interface_delay_ms(EM4100_BASIC_DEFAULT_SEARCH_DELAY_MS);
        
        /* check the timeout */
        if (timeout < 0)
        {
            /* never timeout */
            continue;
        }
        else
        {
            /* timeout */
            if (timeout == 0)
            {
                return 1;
            }
            else
            {
                /* timout-- */
                timeout--;
            }
        }
    }
}

/**
 * @brief     basic example print
 * @param[in] *id points to an id buffer
 * @return    status code
 *            - 0 success
 *            - 1 print failed
 * @note      none
 */
uint8_t em4100_basic_print(uint8_t id[5])
{
    if (em4100_print(&gs_handle, id) != 0)
    {
        return 1;
    }
    
    return 0;
}
