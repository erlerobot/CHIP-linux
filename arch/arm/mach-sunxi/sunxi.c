/*
 * Device Tree support for Allwinner A1X SoCs
 *
 * Copyright (C) 2012 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@free-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <linux/clk-provider.h>
#include <linux/clocksource.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/spi/spi.h>

#include <asm/mach/arch.h>

static struct spi_board_info sunxi_board_info[] = {
	// spi 2.0
	{
		.modalias	= "spidev",
		.max_speed_hz	= 48000000, //48 Mbps
		.bus_num	= 2,
		.chip_select	= 0,	
		.mode = SPI_MODE_1,
	},
};

static void __init sunxi_board_init(void)
{
	spi_register_board_info(sunxi_board_info,
			ARRAY_SIZE(sunxi_board_info));
}

static void __init sunxi_dt_cpufreq_init(void)
{
	platform_device_register_simple("cpufreq-dt", -1, NULL, 0);
}

static const char * const sunxi_board_dt_compat[] = {
	"allwinner,sun4i-a10",
	"allwinner,sun5i-a10s",
	"allwinner,sun5i-a13",
	"allwinner,sun5i-r8",
	NULL,
};

DT_MACHINE_START(SUNXI_DT, "Allwinner sun4i/sun5i Families")
	.init_machine   = sunxi_board_init,
	.dt_compat	= sunxi_board_dt_compat,
	.init_late	= sunxi_dt_cpufreq_init,
MACHINE_END

static const char * const sun6i_board_dt_compat[] = {
	"allwinner,sun6i-a31",
	"allwinner,sun6i-a31s",
	NULL,
};

extern void __init sun6i_reset_init(void);
static void __init sun6i_timer_init(void)
{
	of_clk_init(NULL);
	if (IS_ENABLED(CONFIG_RESET_CONTROLLER))
		sun6i_reset_init();
	clocksource_of_init();
}

DT_MACHINE_START(SUN6I_DT, "Allwinner sun6i (A31) Family")
	.init_time	= sun6i_timer_init,
	.dt_compat	= sun6i_board_dt_compat,
	.init_late	= sunxi_dt_cpufreq_init,
MACHINE_END

static const char * const sun7i_board_dt_compat[] = {
	"allwinner,sun7i-a20",
	NULL,
};

DT_MACHINE_START(SUN7I_DT, "Allwinner sun7i (A20) Family")
	.dt_compat	= sun7i_board_dt_compat,
	.init_late	= sunxi_dt_cpufreq_init,
MACHINE_END

static const char * const sun8i_board_dt_compat[] = {
	"allwinner,sun8i-a23",
	NULL,
};

DT_MACHINE_START(SUN8I_DT, "Allwinner sun8i (A23) Family")
	.dt_compat	= sun8i_board_dt_compat,
	.init_late	= sunxi_dt_cpufreq_init,
MACHINE_END

static const char * const sun9i_board_dt_compat[] = {
	"allwinner,sun9i-a80",
	NULL,
};

DT_MACHINE_START(SUN9I_DT, "Allwinner sun9i Family")
	.dt_compat	= sun9i_board_dt_compat,
MACHINE_END
