/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#include <../src/nrf_802154_peripherals.h>

#if defined(CONFIG_SOC_SERIES_NRF54LX) && defined(CONFIG_NRFX_DPPI)
#include <soc/interconnect/dppic_ppib/nrfx_interconnect_dppic_ppib.h>
#endif


static void mark_nrfx_used_resources(void)
{
#if defined(CONFIG_SOC_SERIES_NRF54LX) && defined(CONFIG_NRFX_DPPI)
	nrfx_interconnect_dppic_channels_mark_allocated(NRF_DPPIC10_S,
		NRF_802154_DPPI_CHANNELS_USED_MASK);
	
	// TODO: What about PPIB channels?
	// TODO: What about DPPIC20 related to GRTC channels?
#endif
}


static int pre_kernel_init(void)
{
        mark_nrfx_used_resources();

        return 0;
}

SYS_INIT(pre_kernel_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
