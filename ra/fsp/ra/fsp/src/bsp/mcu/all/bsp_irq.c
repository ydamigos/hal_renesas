/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/** ELC event definitions. */

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_IRQ_UINT32_MAX       (0xFFFFFFFFU)
#define BSP_PRV_BITS_PER_WORD    (32)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/* This table is used to store the context in the ISR. */
void * gp_renesas_isr_context[BSP_ICU_VECTOR_MAX_ENTRIES];

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_WEAK_REFERENCE =
{
    (bsp_interrupt_event_t) 0
};

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 *
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU) */

/*******************************************************************************************************************//**
 *        Using the vector table information section that has been built by the linker and placed into ROM in the
 * .vector_info. section, this function will initialize the ICU so that configured ELC events will trigger interrupts
 * in the NVIC.
 *
 **********************************************************************************************************************/
void bsp_irq_cfg (void)
{
#if FSP_PRIV_TZ_USE_SECURE_REGS
 #if (BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_SECURE_BUILD == 0)

    /* On MCUs with this implementation of TrustZone, IRQ security attribution is set to secure by default.
     * This means that flat projects do not need to set security attribution to secure. */
 #else

    /* Unprotect security registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

  #if !BSP_TZ_SECURE_BUILD

    /* Set the DMAC channels to secure access. */
   #ifdef BSP_TZ_CFG_ICUSARC
    R_CPSCU->ICUSARC = ~R_CPSCU_ICUSARC_SADMACn_Msk;
   #endif
  #endif

    /* Place all vectors in non-secure state unless they are used in the secure project. */
    uint32_t interrupt_security_state[BSP_ICU_VECTOR_MAX_ENTRIES / BSP_PRV_BITS_PER_WORD];
    memset(&interrupt_security_state, UINT8_MAX, sizeof(interrupt_security_state));

    for (uint32_t i = 0U; i < BSP_ICU_VECTOR_MAX_ENTRIES; i++)
    {
        if (0U != g_interrupt_event_link_select[i])
        {
            /* This is a secure vector. Clear the associated bit. */
            uint32_t index = i / BSP_PRV_BITS_PER_WORD;
            uint32_t bit   = i % BSP_PRV_BITS_PER_WORD;
            interrupt_security_state[index] &= ~(1U << bit);
        }
    }

    /* The Secure Attribute managed within the ARM CPU NVIC must match the security attribution of IELSEn
     * (Reference section 13.2.9 in the RA6M4 manual R01UH0890EJ0050). */
    uint32_t volatile * p_icusarg = &R_CPSCU->ICUSARG;
    for (uint32_t i = 0U; i < BSP_ICU_VECTOR_MAX_ENTRIES / BSP_PRV_BITS_PER_WORD; i++)
    {
        p_icusarg[i]  = interrupt_security_state[i];
        NVIC->ITNS[i] = interrupt_security_state[i];
    }

    /* Protect security registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);
 #endif
#endif

    for (uint32_t i = 0U; i < (BSP_ICU_VECTOR_MAX_ENTRIES - BSP_FEATURE_ICU_FIXED_IELSR_COUNT); i++)
    {
        if (0U != g_interrupt_event_link_select[i])
        {
            R_ICU->IELSR[i] = (uint32_t) g_interrupt_event_link_select[i];
        }
    }
}