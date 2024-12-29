#include "display.h"
#include <string.h>
#include <stdio.h>

/* Font array definition */
const uint8_t s_font5x7[96][5] = {
    /* 0x20 (space) */ {0x00,0x00,0x00,0x00,0x00},
    /* 0x21 (!) */     {0x00,0x00,0x5F,0x00,0x00},
    /* 0x22 (") */     {0x00,0x03,0x00,0x03,0x00},
    /* 0x23 (#) */     {0x14,0x7F,0x14,0x7F,0x14},
    /* 0x24 ($) */     {0x24,0x2A,0x7F,0x2A,0x12},
    /* 0x25 (%) */     {0x23,0x13,0x08,0x64,0x62},
    /* 0x26 (&) */     {0x36,0x49,0x55,0x22,0x50},
    /* 0x27 (') */     {0x00,0x05,0x03,0x00,0x00},
    /* 0x28 (() */     {0x00,0x1C,0x22,0x41,0x00},
    /* 0x29 ()) */     {0x00,0x41,0x22,0x1C,0x00},
    /* 0x2A (*) */     {0x14,0x08,0x3E,0x08,0x14},
    /* 0x2B (+) */     {0x08,0x08,0x3E,0x08,0x08},
    /* 0x2C (,) */     {0x00,0x50,0x30,0x00,0x00},
    /* 0x2D (-) */     {0x08,0x08,0x08,0x08,0x08},
    /* 0x2E (.) */     {0x00,0x60,0x60,0x00,0x00},
    /* 0x2F (/) */     {0x20,0x10,0x08,0x04,0x02},
    /* 0x30 (0) */     {0x3E,0x51,0x49,0x45,0x3E},
    /* 0x31 (1) */     {0x00,0x42,0x7F,0x40,0x00},
    /* 0x32 (2) */     {0x42,0x61,0x51,0x49,0x46},
    /* 0x33 (3) */     {0x21,0x41,0x45,0x4B,0x31},
    /* 0x34 (4) */     {0x18,0x14,0x12,0x7F,0x10},
    /* 0x35 (5) */     {0x27,0x45,0x45,0x45,0x39},
    /* 0x36 (6) */     {0x3C,0x4A,0x49,0x49,0x30},
    /* 0x37 (7) */     {0x01,0x71,0x09,0x05,0x03},
    /* 0x38 (8) */     {0x36,0x49,0x49,0x49,0x36},
    /* 0x39 (9) */     {0x06,0x49,0x49,0x29,0x1E},
    /* 0x3A (:) */     {0x00,0x36,0x36,0x00,0x00},
    /* 0x3B (;) */     {0x00,0x56,0x36,0x00,0x00},
    /* 0x3C (<) */     {0x08,0x14,0x22,0x41,0x00},
    /* 0x3D (=) */     {0x14,0x14,0x14,0x14,0x14},
    /* 0x3E (>) */     {0x00,0x41,0x22,0x14,0x08},
    /* 0x3F (?) */     {0x02,0x01,0x51,0x09,0x06},
    /* 0x40 (@) */     {0x32,0x49,0x79,0x41,0x3E},
    /* 0x41 (A) */     {0x7E,0x11,0x11,0x11,0x7E},
    /* 0x42 (B) */     {0x7F,0x49,0x49,0x49,0x36},
    /* 0x43 (C) */     {0x3E,0x41,0x41,0x41,0x22},
    /* 0x44 (D) */     {0x7F,0x41,0x41,0x22,0x1C},
    /* 0x45 (E) */     {0x7F,0x49,0x49,0x49,0x41},
    /* 0x46 (F) */     {0x7F,0x09,0x09,0x09,0x01},
    /* 0x47 (G) */     {0x3E,0x41,0x49,0x49,0x7A},
    /* 0x48 (H) */     {0x7F,0x08,0x08,0x08,0x7F},
    /* 0x49 (I) */     {0x00,0x41,0x7F,0x41,0x00},
    /* 0x4A (J) */     {0x20,0x40,0x41,0x3F,0x01},
    /* 0x4B (K) */     {0x7F,0x08,0x14,0x22,0x41},
    /* 0x4C (L) */     {0x7F,0x40,0x40,0x40,0x40},
    /* 0x4D (M) */     {0x7F,0x02,0x04,0x02,0x7F},
    /* 0x4E (N) */     {0x7F,0x04,0x08,0x10,0x7F},
    /* 0x4F (O) */     {0x3E,0x41,0x41,0x41,0x3E},
    /* 0x50 (P) */     {0x7F,0x09,0x09,0x09,0x06},
    /* 0x51 (Q) */     {0x3E,0x41,0x51,0x21,0x5E},
    /* 0x52 (R) */     {0x7F,0x09,0x19,0x29,0x46},
    /* 0x53 (S) */     {0x46,0x49,0x49,0x49,0x31},
    /* 0x54 (T) */     {0x01,0x01,0x7F,0x01,0x01},
    /* 0x55 (U) */     {0x3F,0x40,0x40,0x40,0x3F},
    /* 0x56 (V) */     {0x1F,0x20,0x40,0x20,0x1F},
    /* 0x57 (W) */     {0x7F,0x20,0x10,0x20,0x7F},
    /* 0x58 (X) */     {0x63,0x14,0x08,0x14,0x63},
    /* 0x59 (Y) */     {0x07,0x08,0x70,0x08,0x07},
    /* 0x5A (Z) */     {0x61,0x51,0x49,0x45,0x43},
    /* 0x5B ([) */     {0x00,0x7F,0x41,0x41,0x00},
    /* 0x5C (\) */     {0x02,0x04,0x08,0x10,0x20},
    /* 0x5D (]) */     {0x00,0x41,0x41,0x7F,0x00},
    /* 0x5E (^) */     {0x04,0x02,0x01,0x02,0x04},
    /* 0x5F (_) */     {0x80,0x80,0x80,0x80,0x80},
    /* 0x60 (`) */     {0x00,0x03,0x07,0x00,0x00},
    /* 0x61 (a) */     {0x20,0x54,0x54,0x54,0x78},
    /* 0x62 (b) */     {0x7F,0x48,0x44,0x44,0x38},
    /* 0x63 (c) */     {0x38,0x44,0x44,0x44,0x20},
    /* 0x64 (d) */     {0x38,0x44,0x44,0x48,0x7F},
    /* 0x65 (e) */     {0x38,0x54,0x54,0x54,0x18},
    /* 0x66 (f) */     {0x08,0x7E,0x09,0x01,0x02},
    /* 0x67 (g) */     {0x08,0x54,0x54,0x54,0x3C},
    /* 0x68 (h) */     {0x7F,0x08,0x04,0x04,0x78},
    /* 0x69 (i) */     {0x00,0x44,0x7D,0x40,0x00},
    /* 0x6A (j) */     {0x20,0x40,0x44,0x3D,0x00},
    /* 0x6B (k) */     {0x7F,0x10,0x28,0x44,0x00},
    /* 0x6C (l) */     {0x00,0x41,0x7F,0x40,0x00},
    /* 0x6D (m) */     {0x7C,0x04,0x18,0x04,0x7C},
    /* 0x6E (n) */     {0x7C,0x08,0x04,0x04,0x78},
    /* 0x6F (o) */     {0x38,0x44,0x44,0x44,0x38},
    /* 0x70 (p) */     {0x7C,0x14,0x14,0x14,0x08},
    /* 0x71 (q) */     {0x08,0x14,0x14,0x14,0x7C},
    /* 0x72 (r) */     {0x7C,0x08,0x04,0x04,0x08},
    /* 0x73 (s) */     {0x48,0x54,0x54,0x54,0x20},
    /* 0x74 (t) */     {0x04,0x3F,0x44,0x40,0x20},
    /* 0x75 (u) */     {0x3C,0x40,0x40,0x20,0x7C},
    /* 0x76 (v) */     {0x1C,0x20,0x40,0x20,0x1C},
    /* 0x77 (w) */     {0x3C,0x40,0x30,0x40,0x3C},
    /* 0x78 (x) */     {0x44,0x28,0x10,0x28,0x44},
    /* 0x79 (y) */     {0x0C,0x50,0x50,0x50,0x3C},
    /* 0x7A (z) */     {0x44,0x64,0x54,0x4C,0x44},
    /* 0x7B ({) */     {0x00,0x08,0x36,0x41,0x00},
    /* 0x7C (|) */     {0x00,0x00,0x7F,0x00,0x00},
    /* 0x7D (}) */     {0x00,0x41,0x36,0x08,0x00},
    /* 0x7E (~) */     {0x08,0x04,0x08,0x10,0x08},
    /* 0x7F (DEL) */   {0x00,0x00,0x00,0x00,0x00}
};

/* Forward declarations of internal static functions */
static HAL_StatusTypeDef display_send_command(Display_t *pDisp, uint8_t cmd);
static HAL_StatusTypeDef display_send_data(Display_t *pDisp, const uint8_t *data, uint16_t size);
static HAL_StatusTypeDef display_hw_init(Display_t *pDisp);
static void display_draw_char(Display_t *pDisp, char c);
static void display_draw_char_at_cursor(Display_t *pDisp, char c);

/*
 * Initialize the display structure and run the hardware init sequence.
 */
HAL_StatusTypeDef display_init(Display_t *pDisp, I2C_HAL_SVC_t *pI2C, uint8_t i2cAddress)
{
    if (!pDisp || !pI2C) return HAL_ERROR;

    pDisp->pI2C = pI2C;
    pDisp->i2cAddress = i2cAddress;

    // Clear buffer
    memset(pDisp->buffer, 0x00, sizeof(pDisp->buffer));

    // Initialize text properties
    pDisp->currentLine = 0;
    pDisp->maxLines = DISPLAY_HEIGHT / 8;  // 32/8 = 4 lines
    pDisp->lineHeight = 8;
    pDisp->currentCol = 0;
    pDisp->cursorLine = 0;
    pDisp->cursorCol = 0;

    // Initialize hardware
    return display_hw_init(pDisp);
}

/*
 * De-initialize (optionally turn off display).
 */
HAL_StatusTypeDef display_deinit(Display_t *pDisp)
{
    if (!pDisp) return HAL_ERROR;
    display_send_command(pDisp, DISPLAY_CMD_DISPLAY_OFF);
    return HAL_OK;
}

/*
 * Clear the buffer and push to display.
 */
HAL_StatusTypeDef display_clear(Display_t *pDisp)
{
    if (!pDisp) return HAL_ERROR;
    memset(pDisp->buffer, 0x00, sizeof(pDisp->buffer));
    pDisp->currentLine = 0;
    pDisp->currentCol = 0;
    pDisp->cursorLine = 0;
    pDisp->cursorCol = 0;
    return display_update(pDisp);
}

/*
 * Push the entire buffer to the display.
 */
HAL_StatusTypeDef display_update(Display_t *pDisp)
{
    if (!pDisp) return HAL_ERROR;

    // Iterate over each page (8 rows)
    for (uint8_t page = 0; page < (DISPLAY_HEIGHT / 8); page++) {
        // Set page address
        display_send_command(pDisp, DISPLAY_CMD_SET_PAGE_START + page);
        // Set lower column address
        display_send_command(pDisp, DISPLAY_CMD_SET_LOW_COL);
        // Set higher column address
        display_send_command(pDisp, DISPLAY_CMD_SET_HIGH_COL);

        // Calculate buffer offset
        uint16_t offset = page * DISPLAY_WIDTH;
        // Send the page data
        display_send_data(pDisp, &pDisp->buffer[offset], DISPLAY_WIDTH);
    }

    return HAL_OK;
}

/* ---------------------------------------------------------------------
 * Cursor Management
 * -------------------------------------------------------------------*/

/*
 * Set the cursor position.
 * line: 0 to maxLines-1
 * col: 0 to (DISPLAY_WIDTH / 6) -1
 */
HAL_StatusTypeDef display_set_cursor(Display_t *pDisp, uint8_t line, uint8_t col)
{
    if (!pDisp || line >= pDisp->maxLines || col >= (DISPLAY_WIDTH / 6)) {
        return HAL_ERROR;
    }
    pDisp->cursorLine = line;
    pDisp->cursorCol = col;
    return HAL_OK;
}

/* ---------------------------------------------------------------------
 * Text Printing
 * -------------------------------------------------------------------*/

/*
 * Draw a single character (c) into the display’s buffer at 
 * (currentLine, currentCol). 5x7 font + 1 column space => 6 columns used.
 */
static void display_draw_char(Display_t *pDisp, char c)
{
    // If out of range, replace with '?'
    if ((uint8_t)c < 0x20 || (uint8_t)c > 0x7F) {
        c = '?';
    }
    uint8_t index = (uint8_t)c - 0x20; // shift to 0-based for font array

    // Each character is 5 columns wide
    // We also add 1 column of spacing => total 6 columns
    // The row is determined by pDisp->currentLine, col by pDisp->currentCol
    // We only handle horizontal (no wrap). If it overflows, we jump to next line.

    if (pDisp->currentLine >= pDisp->maxLines) {
        // Simple “clear and reset” if we exceed the max lines
        display_clear(pDisp);
        pDisp->currentLine = 0;
    }

    // If currentCol + 6 > DISPLAY_WIDTH, move to next line
    if (pDisp->currentCol + 6 > DISPLAY_WIDTH) {
        // Next line
        pDisp->currentLine++;
        pDisp->currentCol = 0;
        if (pDisp->currentLine >= pDisp->maxLines) {
            display_clear(pDisp);
            pDisp->currentLine = 0;
        }
    }

    // Calculate buffer offset
    uint16_t lineOffset = pDisp->currentLine * DISPLAY_WIDTH;

    // Draw each of the 5 columns from the font
    for (uint8_t col = 0; col < 5; col++) {
        pDisp->buffer[lineOffset + pDisp->currentCol + col] = s_font5x7[index][col];
    }
    // 1 column of spacing
    pDisp->buffer[lineOffset + pDisp->currentCol + 5] = 0x00;

    // Advance currentCol
    pDisp->currentCol += 6;
}

/*
 * Draw a single character at the cursor position and update the cursor.
 */
static void display_draw_char_at_cursor(Display_t *pDisp, char c)
{
    // If out of range, replace with '?'
    if ((uint8_t)c < 0x20 || (uint8_t)c > 0x7F) {
        c = '?';
    }
    uint8_t index = (uint8_t)c - 0x20; // shift to 0-based for font array

    // Each character is 5 columns wide + 1 column space
    if (pDisp->cursorCol >= (DISPLAY_WIDTH / 6)) {
        // Optionally, handle overflow (e.g., wrap to next line or clear display)
        return;
    }

    // Calculate buffer offset
    uint16_t lineOffset = pDisp->cursorLine * DISPLAY_WIDTH;

    // Draw each of the 5 columns from the font
    for (uint8_t col = 0; col < 5; col++) {
        pDisp->buffer[lineOffset + pDisp->cursorCol * 6 + col] = s_font5x7[index][col];
    }
    // 1 column of spacing
    pDisp->buffer[lineOffset + pDisp->cursorCol * 6 + 5] = 0x00;

    // Advance cursor
    pDisp->cursorCol++;
    if (pDisp->cursorCol >= (DISPLAY_WIDTH / 6)) {
        pDisp->cursorCol = 0;
        pDisp->cursorLine++;
        if (pDisp->cursorLine >= pDisp->maxLines) {
            pDisp->cursorLine = 0;
            display_clear(pDisp);
        }
    }
}

/*
 * Print a C-string at the current text cursor position, then update the display buffer.
 */
HAL_StatusTypeDef display_print(Display_t *pDisp, const char *str)
{
    if (!pDisp || !str) return HAL_ERROR;
    while (*str) {
        display_draw_char(pDisp, *str++);
    }
    // Update the display to reflect changes
    return display_update(pDisp);
}

/*
 * “Pretty print” might do line breaks or other logic; 
 * here we’ll just call display_print and move to the next line afterwards.
 */
HAL_StatusTypeDef display_pretty_print(Display_t *pDisp, const char *str)
{
    HAL_StatusTypeDef ret = display_print(pDisp, str);
    // Move to next line
    pDisp->currentLine++;
    pDisp->currentCol = 0;
    if (pDisp->currentLine >= pDisp->maxLines) {
        display_clear(pDisp);
        pDisp->currentLine = 0;
    }
    return ret;
}

/*
 * Print an integer number at the current cursor position.
 */
HAL_StatusTypeDef display_print_number(Display_t *pDisp, int num)
{
    if (!pDisp) return HAL_ERROR;
    char str[12]; // Enough for 32-bit integer
    sprintf(str, "%d", num);
    return display_print_at_cursor(pDisp, str);
}

/*
 * Print a C-string at the current cursor position, then update the display buffer.
 */
HAL_StatusTypeDef display_print_at_cursor(Display_t *pDisp, const char *str)
{
    if (!pDisp || !str) return HAL_ERROR;
    while (*str) {
        display_draw_char_at_cursor(pDisp, *str++);
    }
    return display_update(pDisp);
}

/* ---------------------------------------------------------------------
 * Internal / static functions for sending commands/data
 * -------------------------------------------------------------------*/

/*
 * Send a single command byte to the display.
 * We use a buffer (2 bytes: control byte + cmd).
 */
static HAL_StatusTypeDef display_send_command(Display_t *pDisp, uint8_t cmd)
{
    uint8_t data[2];
    data[0] = DISPLAY_CONTROL_CMD; // Command control byte
    data[1] = cmd;
    return HAL_I2C_Master_Transmit(pDisp->pI2C, 
                                   (pDisp->i2cAddress << 1), 
                                   data, 
                                   2, 
                                   HAL_MAX_DELAY);
}

/*
 * Send a data array to the display.
 * We prepend a single control byte (0x40), so total = size + 1.
 */
static HAL_StatusTypeDef display_send_data(Display_t *pDisp, const uint8_t *data, uint16_t size)
{
    // Maximum data per transmission is 1 + 128 = 129 bytes (for one page)
    if (size > DISPLAY_WIDTH) {
        // Should never happen if we only send one page at a time
        return HAL_ERROR;
    }

    uint8_t txBuf[1 + DISPLAY_WIDTH]; // 1 + 128 = 129
    txBuf[0] = DISPLAY_CONTROL_DATA; // Data control byte
    memcpy(&txBuf[1], data, size);

    return HAL_I2C_Master_Transmit(pDisp->pI2C, 
                                   (pDisp->i2cAddress << 1), 
                                   txBuf, 
                                   size + 1, 
                                   HAL_MAX_DELAY);
}

/* ---------------------------------------------------------------------
 * Hardware Initialization
 * -------------------------------------------------------------------*/

/*
 * Hardware init sequence for the display.
 * The sequence is based on the Arduino driver's Init() function.
 */
static HAL_StatusTypeDef display_hw_init(Display_t *pDisp)
{
    if (!pDisp) return HAL_ERROR;

    HAL_Delay(100); // Wait for display to power up

    // Send initialization commands
    display_send_command(pDisp, 0xE2);
    HAL_Delay(10);
    display_send_command(pDisp, 0xA3);          // Select bias
    display_send_command(pDisp, 0xA0);          // Segment remap
    display_send_command(pDisp, 0xC8);          // COM scan direction
    display_send_command(pDisp, 0x22);          // Set multiplex ratio
    display_send_command(pDisp, 0x81);          // Contrast control
    display_send_command(pDisp, 0x30);          // Set contrast value
    display_send_command(pDisp, 0x2C);          // Set charge pump
    display_send_command(pDisp, 0x2E);          // Set charge pump
    display_send_command(pDisp, 0x2F);          // Enable charge pump
    display_clear(pDisp);                        // Initialize DDRAM
    display_send_command(pDisp, 0xFF);
    display_send_command(pDisp, 0x72);          // Display setting mode on
    display_send_command(pDisp, 0xFE);          // Exit display setting mode
    display_send_command(pDisp, 0xD6);          // Set display duty
    display_send_command(pDisp, 0x90);          // Set display parameters
    display_send_command(pDisp, 0x9D);          // Frame rate and duty
    display_send_command(pDisp, DISPLAY_CMD_DISPLAY_ON);   // Display on
    display_send_command(pDisp, 0x40);          // Set display start line
    HAL_Delay(100); // Wait for settings to take effect

    return HAL_OK;
}

/* ---------------------------------------------------------------------
 * Additional Helper Functions (if needed)
 * -------------------------------------------------------------------*/

/*
 * Example function to clear the display using low-level commands.
 * Not strictly necessary if display_clear is used, but included for completeness.
 */
HAL_StatusTypeDef Clear_Display(Display_t *pDisp) {
    if (!pDisp) return HAL_ERROR;

    for (int x = 0; x < (DISPLAY_HEIGHT / 8); x++) {
        display_send_command(pDisp, DISPLAY_CMD_SET_PAGE_START + x);   // Set page address
        display_send_command(pDisp, DISPLAY_CMD_SET_HIGH_COL);         // Set high nibble of column address
        display_send_command(pDisp, DISPLAY_CMD_SET_LOW_COL);          // Set low nibble of column address
        uint8_t zero[DISPLAY_WIDTH];
        memset(zero, 0x00, sizeof(zero));
        display_send_data(pDisp, zero, DISPLAY_WIDTH);                  // Clear the page
    }
    return HAL_OK;
}
