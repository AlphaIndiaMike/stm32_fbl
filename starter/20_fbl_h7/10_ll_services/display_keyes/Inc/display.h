#ifndef DISPLAY_H
#define DISPLAY_H

#include "stm32h7xx_hal.h"
#include "i2c_hal_svc.h"

/* SSD1306-like Command Definitions */
#define DISPLAY_CMD_DISPLAY_OFF        0xAE
#define DISPLAY_CMD_DISPLAY_ON         0xAF
#define DISPLAY_CMD_SET_DISPLAY_CLOCK  0xD5
#define DISPLAY_CMD_SET_MULTIPLEX      0xA8
#define DISPLAY_CMD_SET_DISPLAY_OFFSET 0xD3
#define DISPLAY_CMD_SET_START_LINE     0x40
#define DISPLAY_CMD_CHARGE_PUMP        0x8D
#define DISPLAY_CMD_MEMORY_MODE        0x20
#define DISPLAY_CMD_SEG_REMAP          0xA1
#define DISPLAY_CMD_COM_SCAN_DIR       0xC8
#define DISPLAY_CMD_SET_CONTRAST       0x81
#define DISPLAY_CMD_SET_PRECHARGE      0xD9
#define DISPLAY_CMD_SET_COMP_PINS      0xDA
#define DISPLAY_CMD_SET_VCOM_DETECT    0xDB

#define DISPLAY_CMD_SET_PAGE_START     0xB0  // 0xB0 to 0xB7
#define DISPLAY_CMD_SET_LOW_COL        0x00  // 0x00 to 0x0F
#define DISPLAY_CMD_SET_HIGH_COL       0x10  // 0x10 to 0x1F

/* Control bytes */
#define DISPLAY_CONTROL_CMD   0x00
#define DISPLAY_CONTROL_DATA  0x40

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32

/* Display Structure */
typedef struct {
    I2C_HAL_SVC_t *pI2C;
    uint8_t i2cAddress;
    uint8_t buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];
    uint8_t currentLine;
    uint8_t maxLines;
    uint8_t lineHeight;
    uint8_t currentCol;
    uint8_t cursorLine;
    uint8_t cursorCol;
} Display_t;

/* Function declarations */
HAL_StatusTypeDef display_init(Display_t *pDisp, I2C_HAL_SVC_t *pI2C, uint8_t i2cAddress);
HAL_StatusTypeDef display_deinit(Display_t *pDisp);
HAL_StatusTypeDef display_clear(Display_t *pDisp);
HAL_StatusTypeDef display_update(Display_t *pDisp);
HAL_StatusTypeDef display_print(Display_t *pDisp, const char *str);
HAL_StatusTypeDef display_pretty_print(Display_t *pDisp, const char *str);
HAL_StatusTypeDef display_set_cursor(Display_t *pDisp, uint8_t line, uint8_t col);
HAL_StatusTypeDef display_print_at_cursor(Display_t *pDisp, const char *str);
HAL_StatusTypeDef display_print_number(Display_t *pDisp, int num);

/* Font array declaration */
extern const uint8_t s_font5x7[96][5];
#endif // DISPLAY_H
