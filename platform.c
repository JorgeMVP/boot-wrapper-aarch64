/*
 * platform.c - code to initialise everything required when first booting.
 *
 * Copyright (C) 2015 ARM Limited. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE.txt file.
 */

#include <stdint.h>

#include <asm/io.h>

#define PL011_UARTDR		0x00
#define PL011_UARTFR		0x18
#define PL011_UARTIBRD		0x24
#define PL011_UARTFBRD		0x28
#define PL011_UART_LCR_H	0x2c
#define PL011_UARTCR		0x30

#define PL011_UARTFR_BUSY	(1 << 3)
#define PL011_UARTFR_FIFO_FULL	(1 << 5)

#define PL011(reg)	((void *)UART_BASE + PL011_##reg)
#define UART8250(reg)	((void *)UART_BASE + (UART8250_##reg * 4))

#define UART8250_TX	0
#define UART8250_LSR	5

#define V2M_SYS(reg)	((void *)SYSREGS_BASE + V2M_SYS_##reg)

static void print_char(char x)
{
	uint32_t flags;

	raw_writel(x, UART8250(TX));

	do
		flags = raw_readl(UART8250(LSR));
	while ((flags & 0x60) != 0x60);
}

static void print_string(const char *str)
{
	while (*str)
		print_char(*str++);
}

void init_platform(void)
{
	/*
	 * UART initialisation (38400 8N1)
	 */
#if 0
	raw_writel(0x10,	PL011(UARTIBRD));
	raw_writel(0x0,		PL011(UARTFBRD));
	/* Set parameters to 8N1 and enable the FIFOs */
	raw_writel(0x70,	PL011(UART_LCR_H));
	/* Enable the UART, TXen and RXen */
	raw_writel(0x301,	PL011(UARTCR));
#endif

	print_string("Boot-wrapper v0.2\r\n\r\n");

#if 0
	/*
	 * CLCD output site MB
	 */
	raw_writel(0x0,		V2M_SYS(CFGDATA));
	/* START | WRITE | MUXFPGA | SITE_MB */
	raw_writel((1 << 31) | (1 << 30) | (7 << 20) | (0 << 16),
				V2M_SYS(CFGCTRL));
#endif
}

void printhex(unsigned long long val)
{
	int i;

	for (i = 60; i >= 0; i -= 4) {
		char x = ((val >> i) & 0xf);

		if (x < 10)
			x += '0';
		else
			x += 'a' - 10;

		print_char(x);
	}
}

void jump_into_space(unsigned long long target)
{
	printhex(target);
	print_string("\r\nJump in the fire!\r\n\r\n");
}

