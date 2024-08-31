/*
 * fbl.c
 *
 *  Created on: Aug 31, 2024
 *      Author: alex
 */

#include "stm32f7xx_hal.h"
#include "fbl.h"

void fbl_blink_alive(int ticks){

}


void fbl_jump_app(const unsigned long address) {
	volatile fcnPtr_t appl_reset_handler_addr;
	uint32_t stack_pointer = *(__IO uint32_t*)address;


	// Check if the stack pointer is within a valid range
    // Check if the stack pointer is within the valid RAM range
    if ((stack_pointer >= FBL_RAM_START_ADDR) && (stack_pointer <= (FBL_RAM_START_ADDR + (FBL_RAM_SIZE_KB * 1024)))) {

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
	} else {
		// Invalid address
		__asm("nop");
	}
}
