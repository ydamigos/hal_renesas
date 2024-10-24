/*
 * Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its
 * affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef R_ETHER_PHY_CFG_H_
#define R_ETHER_PHY_CFG_H_
#ifdef __cplusplus
extern "C" {
#endif

#define ETHER_PHY_LSI_TYPE_KIT_COMPONENT DT_PROP(DT_NODELABEL(eth), phy_type)
#define BOARD_PHY_REF_CLK (0)

#define ETHER_PHY_CFG_PARAM_CHECKING_ENABLE (BSP_CFG_PARAM_CHECKING_ENABLE)
#ifndef ETHER_PHY_CFG_TARGET_KSZ8091RNB_ENABLE
#define ETHER_PHY_CFG_TARGET_KSZ8091RNB_ENABLE (0)
#endif
#ifndef ETHER_PHY_CFG_TARGET_KSZ8041_ENABLE
#define ETHER_PHY_CFG_TARGET_KSZ8041_ENABLE (0)
#endif
#ifndef ETHER_PHY_CFG_TARGET_DP83620_ENABLE
#define ETHER_PHY_CFG_TARGET_DP83620_ENABLE (0)
#endif
#ifndef ETHER_PHY_CFG_TARGET_ICS1894_ENABLE
#define ETHER_PHY_CFG_TARGET_ICS1894_ENABLE (0)
#endif
#ifndef ETHER_PHY_CFG_USE_CUSTOM_PHY_LSI_ENABLE
#define ETHER_PHY_CFG_USE_CUSTOM_PHY_LSI_ENABLE (1)
#endif
#define ETHER_PHY_CFG_USE_REF_CLK (BOARD_PHY_REF_CLK)
#define ETHER_PHY_CFG_INIT_PHY_LSI_AUTOMATIC (0)

#ifdef __cplusplus
}
#endif
#endif /* R_ETHER_PHY_CFG_H_ */
