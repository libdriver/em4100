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
 * @file      driver_em4100.c
 * @brief     driver em4100 source file
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

#include "driver_em4100.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "EM Microelectronic EM4100"        /**< chip name */
#define MANUFACTURER_NAME         "EM Microelectronic"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        1.5f                               /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        7.5f                               /**< chip max supply voltage */
#define MAX_CURRENT               10.0f                              /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                             /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                              /**< chip max operating temperature */
#define DRIVER_VERSION            1000                               /**< driver version */

/**
 * @brief         manchester decode
 * @param[in]     *handle points to an em4095 handle structure
 * @param[in]     *input points to an input buffer
 * @param[in]     input_len is the input length
 * @param[out]    *output points to an output buffer
 * @param[in,out] *output_len points to an output length buffer
 * @return        status code
 *                - 0 success
 *                - 1 can't find header
 *                - 2 invalid manchester code
 * @note          none
 */
static uint8_t a_em4100_manchester_decode(uint8_t *input, uint16_t input_len, uint8_t *output, uint16_t *output_len)
{
    uint16_t i;
    uint16_t start;
    uint16_t l;
    uint16_t cnt;
    
    l = input_len;                                                    /* set input length */
    for (i = 0; i < (l - 1); i++)                                     /* check all */
    {
        if ((input[i] == 0x01) && (input[i + 1] == 0x01))             /* find header */
        {
            break;                                                    /* break */
        }
    }
    if (i == (l - 1))                                                 /* check length */
    {
        return 1;                                                     /* return error */
    }
    start = i + 1;                                                    /* set start point */
    cnt = 0;                                                          /* init 0 */
    for (i = start; i < (l - 1); i += 2)                              /* loop all */
    {
        if (cnt >= (*output_len))                                     /* check output length */
        {
            break;                                                    /* break */
        }
        if ((input[i] == 0x01) && (input[i + 1] == 0x00))             /* 1 */
        {
            output[cnt] = 1;                                          /* set 1*/
            cnt++;                                                    /* cnt++ */
        }
        else if ((input[i] == 0x00) && (input[i + 1] == 0x01))        /* 0 */
        {
            output[cnt] = 0;                                          /* set 0 */
            cnt++;                                                    /* cnt++ */
        }
        else
        {
            return 2;                                                 /* return error */
        }
    }
    *output_len = cnt;                                                /* copy to output length */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief         raw decode
 * @param[in]     *handle points to an em4095 handle structure
 * @param[in]     *input points to an input buffer
 * @param[in]     input_len is the input length
 * @param[out]    *output points to an output buffer
 * @param[in,out] *output_len points to an output length buffer
 * @return        status code
 *                - 0 success
 *                - 1 can't find header
 * @note          none
 */
static uint8_t a_em4100_raw_decode(uint8_t *input, uint16_t input_len, uint8_t *output, uint16_t *output_len)
{
    uint16_t i;
    uint16_t start;
    uint16_t l;
    uint16_t cnt;
    
    l = input_len;                                                                               /* set input length */
    for (i = 0; i < (l - 9); i++)                                                                /* check all */
    {
        if ((input[i + 0] == 0x01) && (input[i + 1] == 0x01) && (input[i + 2] == 0x01) &&
            (input[i + 3] == 0x01) && (input[i + 4] == 0x01) && (input[i + 5] == 0x01) &&
            (input[i + 6] == 0x01) && (input[i + 7] == 0x01) && (input[i + 8] == 0x01))          /* find header */
        {
            break;                                                                               /* break */
        }
    }
    if (i == (l - 9))                                                                            /* check length */
    {
        return 1;                                                                                /* return error */
    }
    start = i;                                                                                   /* set start point */
    cnt = 0;                                                                                     /* init 0 */
    for (i = start; i < (l - 9); i++)                                                            /* loop all */
    {
        if (cnt >= (*output_len))                                                                /* check output length */
        {
            break;                                                                               /* break */
        }
        output[cnt] = input[i];                                                                  /* set data */
        cnt++;                                                                                   /* cnt++ */
    }
    *output_len = cnt;                                                                           /* copy to output length */
    
    return 0;                                                                                    /* success return 0 */
}

/**
 * @brief      frame decode
 * @param[in]  *handle points to an em4095 handle structure
 * @param[in]  *input points to an input buffer
 * @param[out] *output points to an output buffer
 * @return     status code
 *             - 0 success
 *             - 1 header is invalid
 *             - 2 trail is invalid
 *             - 3 check error
 * @note       none
 */
static uint8_t a_em4100_frame_decode(uint8_t input[64], uint8_t output[5])
{
    uint16_t i;
    uint16_t cnt;
    uint8_t buf[10];
    
    if ((input[0] != 0x01) || (input[1] != 0x01) || (input[2] != 0x01) ||
        (input[3] != 0x01) || (input[4] != 0x01) || (input[5] != 0x01) ||
        (input[6] != 0x01) || (input[7] != 0x01) || (input[8] != 0x01))          /* find header */
    {
        return 1;                                                                /* return error */
    }
    if (input[63] != 0)                                                          /* check stop bit */
    {
        return 2;                                                                /* return error */
    }
    
    cnt = 0;                                                                     /* init 0 */
    for (i = 9; i < 59; i += 5)                                                  /* loop all */
    {
        uint8_t t;
        uint8_t check;
        
        t = 0;                                                                   /* init 0 */
        check = 0;                                                               /* init 0 */
        t |= input[i + 0] << 3;                                                  /* copy bit */
        t |= input[i + 1] << 2;                                                  /* copy bit */
        t |= input[i + 2] << 1;                                                  /* copy bit */
        t |= input[i + 3] << 0;                                                  /* copy bit */
        check = input[i + 0] ^ input[i + 1] ^ input[i + 2] ^ 
                input[i + 3] ^ input[i + 4];                                     /* get check bit */
        if (check != 0)                                                          /* check bit */
        {
           return 3;                                                             /* return error */
        }
        buf[cnt] = t;                                                            /* savt one group */
        cnt++;                                                                   /* cnt++ */
    }
    for (i = 0; i < 4; i++)                                                      /* loop all */
    {
        uint8_t check;
        
        check = 0;                                                               /* init 0 */
        check = input[9 + 0 * 5 + i] ^ input[9 + 1 * 5 + i] ^ 
                input[9 + 2 * 5 + i] ^ input[9 + 3 * 5 + i] ^ 
                input[9 + 4 * 5 + i] ^ input[9 + 5 * 5 + i] ^ 
                input[9 + 6 * 5 + i] ^ input[9 + 7 * 5 + i] ^
                input[9 + 8 * 5 + i] ^ input[9 + 9 * 5 + i] ^
                input[9 + 10 * 5 + i];                                           /* get check */
        if (check != 0)                                                          /* check bit */
        {
           return 3;                                                             /* return error */
        }
    }
    for (i = 0; i < 5; i++)                                                      /* loop all */
    {
       output[i] = (buf[i * 2 + 0] << 4) | buf[i * 2 + 1];                       /* copy data */
    }
    
    return 0;                                                                    /* success return 0 */
}

/**
 * @brief      read data
 * @param[in]  *handle points to an em4100 handle structure
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the read length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_em4100_read(em4100_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle->contactless_read(64, buf, len) != 0)        /* contactless read */
    {
        return 1;                                           /* return error */
    }
    
    return 0;                                               /* success return 0 */
}

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
uint8_t em4100_init(em4100_handle_t *handle)
{
    uint8_t res;

    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->debug_print == NULL)                                       /* check debug_print */
    {
        return 3;                                                          /* return error */
    }
    if (handle->contactless_init == NULL)                                  /* check contactless_init */
    {
        handle->debug_print("em4100: contactless_init is null.\n");        /* contactless_init is null */

        return 3;                                                          /* return error */
    }
    if (handle->contactless_deinit == NULL)                                /* check contactless_deinit */
    {
        handle->debug_print("em4100: contactless_deinit is null.\n");      /* contactless_deinit is null */

        return 3;                                                          /* return error */
    }
    if (handle->contactless_read == NULL)                                  /* check contactless_read */
    {
        handle->debug_print("em4100: contactless_read is null.\n");        /* contactless_read is null */

        return 3;                                                          /* return error */
    }
    if (handle->delay_ms == NULL)                                          /* check delay_ms */
    {
        handle->debug_print("em4100: delay_ms is null.\n");                /* delay_ms is null */

        return 3;                                                          /* return error */
    }

    res = handle->contactless_init();                                      /* contactless init */
    if (res != 0)                                                          /* check the result */
    {
        handle->debug_print("em4100: contactless init failed.\n");         /* contactless init failed */

        return 1;                                                          /* return error */
    }
    handle->inited = 1;                                                    /* flag inited */

    return 0;                                                              /* success return 0 */
}

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
uint8_t em4100_deinit(em4100_handle_t *handle)
{
    uint8_t res;

    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }

    res = handle->contactless_deinit();                                  /* contactless deinit */
    if (res != 0)                                                        /* check the result */
    {
        handle->debug_print("em4100: contactless deinit failed.\n");     /* contactless deinit failed */

        return 1;                                                        /* return error */
    }
    handle->inited = 0;                                                  /* flag close */

    return 0;                                                            /* success return 0 */
}

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
uint8_t em4100_read(em4100_handle_t *handle, uint8_t id[5])
{
    uint8_t res;
    uint16_t manchester_len;
    uint16_t raw_len;

    if (handle == NULL)                                                                               /* check handle */
    {
        return 2;                                                                                     /* return error */
    }
    if (handle->inited != 1)                                                                          /* check handle initialization */
    {
        return 3;                                                                                     /* return error */
    }
    
    res = a_em4100_read(handle, handle->buf, 256);                                                    /* read data */
    if (res != 0)                                                                                     /* check result */
    {
        return 4;                                                                                     /* return error */
    }
    manchester_len = 128;                                                                             /* read 128 bytes */
    res = a_em4100_manchester_decode(handle->buf, 256, handle->manchester_buf, &manchester_len);      /* manchester decode */
    if (res != 0)                                                                                     /* check result */
    {
        return 1;                                                                                     /* return error */
    }
    raw_len = 64;                                                                                     /* read 64 bytes */
    res = a_em4100_raw_decode(handle->manchester_buf, manchester_len, handle->raw_buf, &raw_len);     /* raw decode */
    if (res != 0)                                                                                     /* check result */
    {
        return 5;                                                                                     /* return error */
    }
    if (raw_len != 64)                                                                                /* check output length */
    {
        return 5;                                                                                     /* return error */
    }
    res = a_em4100_frame_decode(handle->raw_buf, id);                                                 /* frame decode */
    if (res != 0)                                                                                     /* check result */
    {
        return 6;                                                                                     /* return error */
    }
    
    return 0;                                                                                         /* success return 0 */
}

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
uint8_t em4100_print(em4100_handle_t *handle, uint8_t buf[5])
{
    uint32_t id;
    uint16_t wiegand26;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    handle->debug_print("id: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X.\n", 
                        buf[0], buf[1], buf[2], buf[3], buf[4]);                    /* output */
    id = ((uint32_t)buf[1] << 24) | ((uint32_t)buf[2] << 16) |
         ((uint32_t)buf[3] << 8) | ((uint32_t)buf[4] << 0);                         /* make id */
    wiegand26 = ((uint16_t)buf[3] << 8) | ((uint16_t)buf[4] << 0);                  /* make wiegand26 */
    handle->debug_print("%010d %03d, %05d.\n", id, buf[2], wiegand26);              /* output */
    
    return 0;                                                                       /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an em4100 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t em4100_info(em4100_info_t *info)
{
    if (info == NULL)                                             /* check handle */
    {
        return 2;                                                 /* return error */
    }

    memset(info, 0, sizeof(em4100_info_t));                       /* initialize em4100 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                      /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);      /* copy manufacturer name */
    strncpy(info->interface, "RF", 8);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;              /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;              /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                           /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                      /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                      /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                        /* set driver version */

    return 0;                                                     /* success return 0 */
}
