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
 * @file      driver_em4100_card_test.c
 * @brief     driver em4100 card test source file
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

#include "driver_em4100_card_test.h"
#include <stdlib.h>

static em4100_handle_t gs_handle;        /**< em4100 handle */

/**
 * @brief  card test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t em4100_card_test(void)
{
    uint8_t res;
    uint8_t id[5];
    uint8_t times;
    em4100_info_t info;
    
    /* link function */
    DRIVER_EM4100_LINK_INIT(&gs_handle, em4100_handle_t);
    DRIVER_EM4100_LINK_CONTACTLESS_INIT(&gs_handle, em4100_interface_contactless_init);
    DRIVER_EM4100_LINK_CONTACTLESS_DEINIT(&gs_handle, em4100_interface_contactless_deinit);
    DRIVER_EM4100_LINK_CONTACTLESS_READ(&gs_handle, em4100_interface_contactless_read);
    DRIVER_EM4100_LINK_DELAY_MS(&gs_handle, em4100_interface_delay_ms);
    DRIVER_EM4100_LINK_DEBUG_PRINT(&gs_handle, em4100_interface_debug_print);
    
    /* get information */
    res = em4100_info(&info);
    if (res != 0)
    {
        em4100_interface_debug_print("em4100: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        em4100_interface_debug_print("em4100: chip is %s.\n", info.chip_name);
        em4100_interface_debug_print("em4100: manufacturer is %s.\n", info.manufacturer_name);
        em4100_interface_debug_print("em4100: interface is %s.\n", info.interface);
        em4100_interface_debug_print("em4100: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        em4100_interface_debug_print("em4100: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        em4100_interface_debug_print("em4100: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        em4100_interface_debug_print("em4100: max current is %0.2fmA.\n", info.max_current_ma);
        em4100_interface_debug_print("em4100: max temperature is %0.1fC.\n", info.temperature_max);
        em4100_interface_debug_print("em4100: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start card test */
    em4100_interface_debug_print("em4100: start card test.\n");
    
    /* init */
    res = em4100_init(&gs_handle);
    if (res != 0)
    {
        em4100_interface_debug_print("em4100: init failed.\n");
        
        return 1;
    }
    
    times = 3;
    while (times != 0)
    {
        /* try to read */
        res = em4100_read(&gs_handle, id);
        if (res == 0)
        {
            (void)em4100_print(&gs_handle, id);
            
            break;
        }
        
        em4100_interface_delay_ms(1000);
        times--;
    }
    
    /* finish card test */
    em4100_interface_debug_print("em4100: finish card test.\n");
    (void)em4100_deinit(&gs_handle);
    
    return 0;
}
