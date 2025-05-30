/***********************************************************************************************************************
* Copyright (c) 2013 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_gpio_rx_if.h
* Description  : General Purpose I/O driver for RX MCUs. This interface file has everything the user needs to use this
*                module.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*         : 17.07.2013 1.00    First Release
*         : 23.04.2014 1.20    Add support for RX63N, and RX110
*         : 28.05.2014 1.30    Add support for RX64M
*         : 28.11.2014 1.40    Add support for RX113
*         : 02.09.2015 1.50    Add support for RX71M, increased the minor version number to 50.
*         :                    Added GPIO_CMD_DSCR_DISABLE and GPIO_CMD_DSCR_ENABLE commands in gpio_cmd_t
*         : 06.04.2015 1.60    Add support for RX231
*         : 30.09.2015 1.70    Add support for RX23T
*         : 01.10.2015 1.80    Add support for RX130
*         : 01.12.2015 1.90    Add support for RX24T
*         : 01.02.2016 2.00    Add support for RX230
*         : 15.06.2016 2.01    Added the demo of the RX64M group.
*         : 01.10.2016 2.10    Add support for RX65N
*         : 19.12.2016 2.20    Add support for RX24U, RX24T(512KB)
*         : 21.07.2017 2.30    Add support for RX65N-2M, RX130-512KB
*         : 31.10.2017 2.31    Added the demo for RX65N, RX65N-2M
*         : 28.09.2018 2.40    Add support for RX66T
*         : 16.11.2018 2.41    Added XML document number
*         : 01.02.2019 2.50    Add support for RX72T, RX65N-64pin
*         : 20.05.2019 3.00    Added support for GNUC and ICCRX.
*         : 28.06.2019 3.10    Added support RX23W
*         : 15.08.2019 3.20    Added support RX72M
*         : 25.11.2019 3.30    Added support RX13T
*                              Removed support for Generation 1 devices.
*         : 30.12.2019 3.40    Added support RX72N, RX66N
*         : 31.03.2020 3.50    Added support for RX23E-A
*         : 30.06.2020 3.60    Changed revision to reflect demo upgrade.
*         : 15.01.2021 3.70    Removed PH7 for RX111, RX113.
*         : 01.04.2021 3.80    Added support for RX23W 83pins
*         : 01.04.2021 3.90    Added support for RX72M 144pins, 100pins 
*         : 07.04.2021 4.00    Added support for RX671.
*         : 15.04.2021 4.10    Added support for RX140.
*         : 13.09.2021 4.20    Added the demo for RX671.
*         : 11.11.2021 4.30    Added support for RX140-256KB.
*         : 14.03.2022 4.40    Added support for RX66T 48pins.
*         : 31.03.2022 4.50    Added support for RX660.
*         : 28.06.2022 4.60    Updated demo projects
*         : 15.12.2022 4.70    Added P50 and P51 for RX66T and RX72T.
*                              Added PORTJ for RX110.
*                              Added PH7 for RX110 and RX111.
*                              Removed 112pins, 80pins, and 64pins package for RX72T.
*         : 28.02.2023 4.80    Corrected PIN MASK value of PORTF and PORTJ for RX72N 145-pin and 144-pin.
*         : 07.04.2023 4.90    Added support for RX26T.
*                              Fixed to comply with GSCE Coding Standards Rev.6.5.0.
*                              Updated P05 for RX671 64-pin and RX65N 64-pin.
*                              Updated P71 and P72 for RX671 145-pin and 144-pin.
*                              Updated PORT2, PORTB, and PORTD for RX66T 100-pin and RX72T 100-pin.
*                              Corrected PIN MASK value of PORT4 for RX110 40-pin.
*                              Corrected PIN MASK value of PORT4 for RX24T 64-pin.
*                              Corrected PIN MASK value of PORTF and PORTJ for RX66N 145-pin and 144-pin.
*                              Corrected PIN MASK value of PORT5 for RX66T 64-pin.
*                              Corrected the values of PORRT7, PORRT8, PORRT9, and PORRTJ 
*                                 in the g_gpio_open_drain_n_support structure for RX231.
*                              Corrected the values of PORRT5 in the g_gpio_pull_up_support and 
*                                 g_gpio_dscr_support structures for RX231.
*                              Corrected the value of PORRT3 in the g_gpio_open_drain_n_support, 
*                                 g_gpio_pull_up_support, and g_gpio_dscr_support structures for RX23T.
*                              Added P36 and P37 for RX23T 64-pin, 52-pin, and 48-pin.
*                              Corrected the value of GPIO_PORT_H_PIN_3 for RX660 144-pin, 100-pin, 80-pin, 
*                                 64-pin, and 48-pin.
*                              Corrected the "Total of pins" for RX23T, RX24T, RX65N, and RX66T.
*                              Updated for RX65N (with products with 1 Mbyte of code flash memory or less) 
*                                 for the g_gpio_dscr_support and g_gpio_dscr2_support structures.
*                              Removed define PIN MASK is not provided for RX110, RX111, RX113, 
*                                 RX64M, RX65N, and RX71M.
*                              Removed common "gpio_port_t" structure and added "gpio_port_t" structure for RX110 
*                                 64-Pin, 48-Pin, 40-Pin, and 36-Pin.
*         : 29.05.2023 5.00    Added support for RX23E-B.
*         : 28.06.2024 5.10    Added support for RX260, RX261.
*         : 15.03.2025 5.11    Updated disclaimer.
***********************************************************************************************************************/

#ifndef GPIO_RX_INTERFACE_HEADER_FILE
#define GPIO_RX_INTERFACE_HEADER_FILE

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"
/* Module configuration. */
#include "r_gpio_rx_config.h"

/* Include specifics for chosen MCU. Go to the header file for your MCU to see available ports and pins. */
#if defined(BSP_MCU_RX113)
    #include "./src/targets/rx113/r_gpio_rx113.h"
#elif   defined(BSP_MCU_RX110)
    #include "./src/targets/rx110/r_gpio_rx110.h"
#elif   defined(BSP_MCU_RX111)
    #include "./src/targets/rx111/r_gpio_rx111.h"
#elif   defined(BSP_MCU_RX130)
    #include "./src/targets/rx130/r_gpio_rx130.h"
#elif   defined(BSP_MCU_RX13T)
    #include "./src/targets/rx13t/r_gpio_rx13t.h"
#elif   defined(BSP_MCU_RX140)
    #include "./src/targets/rx140/r_gpio_rx140.h"
#elif defined(BSP_MCU_RX230)
    #include "./src/targets/rx230/r_gpio_rx230.h"
#elif defined(BSP_MCU_RX231)
    #include "./src/targets/rx231/r_gpio_rx231.h"
#elif defined(BSP_MCU_RX23T)
    #include "./src/targets/rx23t/r_gpio_rx23t.h"
#elif defined(BSP_MCU_RX23W)
    #include "./src/targets/rx23w/r_gpio_rx23w.h"
#elif defined(BSP_MCU_RX23E_A)
    #include "./src/targets/rx23e-a/r_gpio_rx23e-a.h"
#elif defined(BSP_MCU_RX23E_B)
    #include "./src/targets/rx23e-b/r_gpio_rx23e-b.h"
#elif defined(BSP_MCU_RX24T)
    #include "./src/targets/rx24t/r_gpio_rx24t.h"
#elif defined(BSP_MCU_RX260)
    #include "./src/targets/rx260/r_gpio_rx260.h"
#elif defined(BSP_MCU_RX261)
    #include "./src/targets/rx261/r_gpio_rx261.h"
#elif defined(BSP_MCU_RX26T)
    #include "./src/targets/rx26t/r_gpio_rx26t.h"
#elif defined(BSP_MCU_RX24U)
    #include "./src/targets/rx24u/r_gpio_rx24u.h"
#elif defined(BSP_MCU_RX64M)
    #include "./src/targets/rx64m/r_gpio_rx64m.h"
#elif defined(BSP_MCU_RX65N)
    #include "./src/targets/rx65n/r_gpio_rx65n.h"
#elif defined(BSP_MCU_RX66T)
    #include "./src/targets/rx66t/r_gpio_rx66t.h"
#elif defined(BSP_MCU_RX66N)
    #include "./src/targets/rx66n/r_gpio_rx66n.h"
#elif defined(BSP_MCU_RX671)
    #include "./src/targets/rx671/r_gpio_rx671.h"
#elif defined(BSP_MCU_RX660)
    #include "./src/targets/rx660/r_gpio_rx660.h"
#elif defined(BSP_MCU_RX71M)
    #include "./src/targets/rx71m/r_gpio_rx71m.h"
#elif defined(BSP_MCU_RX72T)
    #include "./src/targets/rx72t/r_gpio_rx72t.h"
#elif defined(BSP_MCU_RX72M)
    #include "./src/targets/rx72m/r_gpio_rx72m.h"
#elif defined(BSP_MCU_RX72N)
    #include "./src/targets/rx72n/r_gpio_rx72n.h"
#else
    #error "This MCU is not supported by the current r_gpio_rx module."
#endif

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif

/* Version Number of API. */
#define GPIO_RX_VERSION_MAJOR           (5)
#define GPIO_RX_VERSION_MINOR           (11)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* The gpio_port_t and gpio_port_pin_t enums are located in the 'targets' folder for each MCU. For example, to see
 * these enums for a RX111 look at the following file: r_gpio_rx/src/targets/rx111/r_gpio_rx111.h
 */

/* Levels that can be set and read for individual pins. */
typedef enum
{
    GPIO_LEVEL_LOW = 0,
    GPIO_LEVEL_HIGH
} gpio_level_t;

/* Options that can be used with the R_GPIO_PortDirectionSet() and R_GPIO_PinDirectionSet() functions. */
typedef enum
{
    GPIO_DIRECTION_INPUT = 0,
    GPIO_DIRECTION_OUTPUT
} gpio_dir_t;

/* Commands that can be used with the R_GPIO_PinControl() function. This list will vary depending on the MCU chosen. */
typedef enum
{
    GPIO_CMD_OUT_CMOS = 0,
    GPIO_CMD_OUT_OPEN_DRAIN_N_CHAN,
    GPIO_CMD_OUT_OPEN_DRAIN_P_CHAN,
    GPIO_CMD_IN_PULL_UP_DISABLE,
    GPIO_CMD_IN_PULL_UP_ENABLE,
    GPIO_CMD_ASSIGN_TO_PERIPHERAL,
    GPIO_CMD_ASSIGN_TO_GPIO,
    GPIO_CMD_DSCR_DISABLE,
    GPIO_CMD_DSCR_ENABLE,
    GPIO_CMD_DSCR2_DISABLE,
    GPIO_CMD_DSCR2_ENABLE
} gpio_cmd_t;

/* Function return type. */
typedef enum
{
    GPIO_SUCCESS = 0,
    GPIO_ERR_INVALID_MODE,  // The mode specified cannot be applied to this pin
    GPIO_ERR_INVALID_CMD    // The input command is not supported
} gpio_err_t;

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
/******************************************************************************
 * Function Name: R_GPIO_PortWrite
 * Description  : .
 * Arguments    : port
 *              : value
 * Return Value : .
 *****************************************************************************/
void            R_GPIO_PortWrite (gpio_port_t port, uint8_t value);

/******************************************************************************
 * Function Name: R_GPIO_PortRead
 * Description  : .
 * Argument     : port
 * Return Value : .
 *****************************************************************************/
uint8_t         R_GPIO_PortRead (gpio_port_t port);

/******************************************************************************
 * Function Name: R_GPIO_PortDirectionSet
 * Description  : .
 * Arguments    : port
 *              : dir
 *              : mask
 * Return Value : .
 *****************************************************************************/
void            R_GPIO_PortDirectionSet (gpio_port_t port, gpio_dir_t dir, uint8_t mask);

/******************************************************************************
 * Function Name: R_GPIO_PinWrite
 * Description  : .
 * Arguments    : pin
 *              : level
 * Return Value : .
 *****************************************************************************/
void            R_GPIO_PinWrite (gpio_port_pin_t pin, gpio_level_t level);

/******************************************************************************
 * Function Name: R_GPIO_PinRead
 * Description  : .
 * Argument     : pin
 * Return Value : .
 *****************************************************************************/
gpio_level_t    R_GPIO_PinRead (gpio_port_pin_t pin);

/******************************************************************************
 * Function Name: R_GPIO_PinDirectionSet
 * Description  : .
 * Arguments    : pin
 *              : dir
 * Return Value : .
 *****************************************************************************/
void            R_GPIO_PinDirectionSet (gpio_port_pin_t pin, gpio_dir_t dir);

/******************************************************************************
 * Function Name: R_GPIO_PinControl
 * Description  : .
 * Arguments    : pin
 *              : cmd
 * Return Value : .
 *****************************************************************************/
gpio_err_t      R_GPIO_PinControl (gpio_port_pin_t pin, gpio_cmd_t cmd);

/******************************************************************************
 * Function Name: R_GPIO_GetVersion
 * Description  : .
 * Return Value : .
 *****************************************************************************/
uint32_t        R_GPIO_GetVersion (void);

#endif /* GPIO_RX_INTERFACE_HEADER_FILE */


