// port_disco_svc.c

#include "boot_fn.h"
#include "svo_svc.h"        // For serial_hal_svc_send
#include "stm32h7xx_hal.h"  // STM32 HAL library
#include <string.h>
#include <stdio.h>

#define FBL_RESET_HANDLER_OFFSET	4
#define JUMP_ADDRESS                0x8060000


typedef void (*fcnPtr_t)(void);

void show_logo(void)
{
    // Define the "AlphaBoot" ASCII art
    const char* alpha_boot_art =
"                                                                                        \n "
"          d8888 888          888                    888888b.                     888    \n "
"         d88888 888          888                    888   88b                    888    \n " 
"        d88P888 888          888                    888  .88P                    888    \n "
"       d88P 888 888 88888b.  88888b.   8888b.       8888888K.   .d88b.   .d88b.  888888 \n "
"      d88P  888 888 888  88b 888  88b      88b      888   Y88b d88  88b d88  88b 888    \n "
"     d88P   888 888 888  888 888  888 .d888888      888    888 888  888 888  888 888    \n "
"    d8888888888 888 888 d88P 888  888 888  888      888   d88P Y88..88P Y88..88P Y88b.  \n "
"   d88P     888 888 88888P   888  888  Y888888      8888888P     Y88P     Y88P    Y8888 \n "
"                    888                                                                 \n "
"                    888                                                                 \n "
"                    888                                                                 \n "
"                                                                                        \n";

    // Send the "AlphaBoot" graphic
    serial_hal_svc_send(alpha_boot_art);
}


void fbl_jump_app(const unsigned long address) {
	volatile fcnPtr_t appl_reset_handler_addr;
	uint32_t stack_pointer = *(__IO uint32_t*)address; /* VALUE INDICATED BY THE DATA AT ADDRESS IN FLASH */

	// Disable all interrupts
	__disable_irq();

	// Disable Systick
	SysTick->CTRL = 0;

	// Set the vector table location
	SCB->VTOR = address;

	// Initialize user application's Stack Pointer
	__set_MSP(stack_pointer);

	// Get jump address from the reset vector

	/* The first word (4 bytes) in the vector table is the initial stack pointer value,
		* and the second word (next 4 bytes) is the address of the reset handler,
		* which is the entry point of the application.
		*/

	appl_reset_handler_addr = (fcnPtr_t)(*(__IO uint32_t*)(address + FBL_RESET_HANDLER_OFFSET));

	// Ensure all memory accesses are completed
	__DSB();
	__ISB();

	// Jump to application
	appl_reset_handler_addr();
}


void boot_jump_app(void)
{
    show_logo();
    serial_hal_svc_send_param("Jumping to address: ",JUMP_ADDRESS);
    fbl_jump_app(JUMP_ADDRESS);
}
