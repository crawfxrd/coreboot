/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef AMD_PICASSO_PSP_VERSTAGE_ADDR_H
#define AMD_PICASSO_PSP_VERSTAGE_ADDR_H

/*
 * Start of available space is 0x15000 and this is where the
 * header for the user app (verstage) must be mapped.
 * Size is 0x28000 bytes
 */
#define PSP_SRAM_START			0x15000
#define PSP_SRAM_SIZE			(160K)
#define VERSTAGE_START			PSP_SRAM_START

/*
 * The temp stack can be made much smaller if needed - even 256 bytes
 * should be sufficient.  This is just for the function mapping the
 * actual stack.
 */
#define PSP_VERSTAGE_TEMP_STACK_START	0x32000
#define PSP_VERSTAGE_TEMP_STACK_SIZE	(4K)

/*
 * The top of the stack must be 4k aligned, so set the bottom as 4k aligned
 * and make the size a multiple of 4k
 */

#define PSP_VERSTAGE_STACK_START	0x33000
#define PSP_VERSTAGE_STACK_SIZE		(40K)

#endif  /* AMD_PICASSO_PSP_VERSTAGE_ADDR_H */
