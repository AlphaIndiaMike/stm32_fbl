/*
 * fbl.h
 *
 *  Created on: Aug 31, 2024
 *      Author: alex
 */

#ifndef INC_FBL_H_
#define INC_FBL_H_

#define FBL_RESET_HANDLER_OFFSET	4
#define FBL_RAM_SIZE_KB				320
#define FBL_RAM_START_ADDR			0x20000000

typedef void (*fcnPtr_t)(void);

void fbl_blink_alive(int ticks);

void fbl_jump_app(unsigned long address);

#endif /* INC_FBL_H_ */
