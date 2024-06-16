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
 * @file      driver_em4100.h
 * @brief     driver em4100 header file
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

#ifndef DRIVER_EM4100_H
#define DRIVER_EM4100_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup em4100_driver em4100 driver function
 * @brief    em4100 driver modules
 * @{
 */

/**
 * @addtogroup em4100_basic_driver
 * @{
 */

/**
 * @brief em4100 handle structure definition
 */
typedef struct em4100_handle_s
{
    uint8_t (*contactless_init)(void);                                            /**< point to a contactless_init function address */
    uint8_t (*contactless_deinit)(void);                                          /**< point to a contactless_deinit function address */
    uint8_t (*contactless_read)(uint32_t clock_div, uint8_t *buf, uint16_t len);  /**< point to a contactless_read function address */
    void (*delay_ms)(uint32_t ms);                                                /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                              /**< point to a debug_print function address */
    uint8_t buf[256];                                                             /**< inner buffer */
    uint8_t manchester_buf[128];                                                  /**< manchester buffer */
    uint8_t raw_buf[64];                                                          /**< raw buffer */
    uint8_t inited;                                                               /**< inited flag */
} em4100_handle_t;

/**
 * @brief em4100 information structure definition
 */
typedef struct em4100_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} em4100_info_t;

/**
 * @}
 */

/**
 * @defgroup em4100_link_driver em4100 link driver function
 * @brief    em4100 link driver modules
 * @ingroup  em4100_driver
 * @{
 */

/**
 * @brief     initialize em4100_handle_t structure
 * @param[in] HANDLE points to an em4100 handle structure
 * @param[in] STRUCTURE is em4100_handle_t
 * @note      none
 */
#define DRIVER_EM4100_LINK_INIT(HANDLE, STRUCTURE)             memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link contactless_init function
 * @param[in] HANDLE points to an em4100 handle structure
 * @param[in] FUC points to a contactless_init function address
 * @note      none
 */
#define DRIVER_EM4100_LINK_CONTACTLESS_INIT(HANDLE, FUC)       (HANDLE)->contactless_init = FUC

/**
 * @brief     link contactless_deinit function
 * @param[in] HANDLE points to an em4100 handle structure
 * @param[in] FUC points to a contactless_deinit function address
 * @note      none
 */
#define DRIVER_EM4100_LINK_CONTACTLESS_DEINIT(HANDLE, FUC)     (HANDLE)->contactless_deinit = FUC

/**
 * @brief     link contactless_read function
 * @param[in] HANDLE points to an em4100 handle structure
 * @param[in] FUC points to a contactless_read function address
 * @note      none
 */
#define DRIVER_EM4100_LINK_CONTACTLESS_READ(HANDLE, FUC)       (HANDLE)->contactless_read = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an em4100 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_EM4100_LINK_DELAY_MS(HANDLE, FUC)               (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an em4100 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_EM4100_LINK_DEBUG_PRINT(HANDLE, FUC)            (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup em4100_basic_driver em4100 basic driver function
 * @brief    em4100 basic driver modules
 * @ingroup  em4100_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an em4100 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t em4100_info(em4100_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an em4100 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 contactless initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t em4100_init(em4100_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an em4100 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t em4100_deinit(em4100_handle_t *handle);

/**
 * @brief      read data
 * @param[in]  *handle points to an em4100 handle structure
 * @param[out] *id points to an id buffer
 * @return     status code
 *             - 0 success
 *             - 1 manchester decode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 read failed
 *             - 5 raw decode failed
 *             - 6 frame decode failed
 * @note       none
 */
uint8_t em4100_read(em4100_handle_t *handle, uint8_t id[5]);

/**
 * @brief     print id
 * @param[in] *handle points to an em4100 handle structure
 * @param[in] *buf points to an id buffer
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t em4100_print(em4100_handle_t *handle, uint8_t buf[5]);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
