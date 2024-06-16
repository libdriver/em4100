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
 * @file      main.c
 * @brief     main source file
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
#include "driver_em4100_card_test.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "gpio.h"
#include "getopt.h"
#include <math.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                                      /**< uart buffer */
volatile uint16_t g_len;                                 /**< uart buffer length */
extern uint8_t em4095_interface_timer_init(void);        /**< timer init function */

/**
 * @brief     em4100 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t em4100(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_card", type) == 0)
    {
        uint8_t res;
        
        /* run the card test */
        res = em4100_card_test();
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint8_t id[5];
        
        /* basic init */
        res = em4100_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* search */
        res = em4100_basic_search(id, 100);
        if (res != 0)
        {
            (void)em4100_basic_deinit();
            em4100_interface_debug_print("timeout.\n");
            
            return 1;
        }
        
        /* print */
        (void)em4100_basic_print(id);
        
        /* basic deinit */
        (void)em4100_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        em4100_interface_debug_print("Usage:\n");
        em4100_interface_debug_print("  em4100 (-i | --information)\n");
        em4100_interface_debug_print("  em4100 (-h | --help)\n");
        em4100_interface_debug_print("  em4100 (-p | --port)\n");
        em4100_interface_debug_print("  em4100 (-t card | --test=card)\n");
        em4100_interface_debug_print("  em4100 (-e read | --example=read)\n");
        em4100_interface_debug_print("\n");
        em4100_interface_debug_print("Options:\n");
        em4100_interface_debug_print("  -e <read>, --example=<read>   Run the driver example.\n");
        em4100_interface_debug_print("  -h, --help                    Show the help.\n");
        em4100_interface_debug_print("  -i, --information             Show the chip information.\n");
        em4100_interface_debug_print("  -p, --port                    Display the pin connections of the current board.\n");
        em4100_interface_debug_print("  -t <card>, --test=<card>      Run the driver test.\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        em4100_info_t info;
        
        /* print em4100 info */
        em4100_info(&info);
        em4100_interface_debug_print("em4100: chip is %s.\n", info.chip_name);
        em4100_interface_debug_print("em4100: manufacturer is %s.\n", info.manufacturer_name);
        em4100_interface_debug_print("em4100: interface is %s.\n", info.interface);
        em4100_interface_debug_print("em4100: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        em4100_interface_debug_print("em4100: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        em4100_interface_debug_print("em4100: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        em4100_interface_debug_print("em4100: max current is %0.2fmA.\n", info.max_current_ma);
        em4100_interface_debug_print("em4100: max temperature is %0.1fC.\n", info.temperature_max);
        em4100_interface_debug_print("em4100: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        em4100_interface_debug_print("em4100: CLK connected to GPIOB PIN0.\n");
        em4100_interface_debug_print("em4100: SHD connected to GPIOB PIN2.\n");
        em4100_interface_debug_print("em4100: DEMOD_OUT connected to GPIOA PIN8.\n");
        em4100_interface_debug_print("em4100: MOD connected to GPIOB PIN1.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* timer init */
    em4095_interface_timer_init();
    
    /* shell init && register em4100 function */
    shell_init();
    shell_register("em4100", em4100);
    uart_print("em4100: welcome to libdriver em4100.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("em4100: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("em4100: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("em4100: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("em4100: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("em4100: param is invalid.\n");
            }
            else
            {
                uart_print("em4100: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
