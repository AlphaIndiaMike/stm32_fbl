#ifndef I2C_HAL_SVC_H
#define I2C_HAL_SVC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"
#include <stdint.h>

/*
 * Simple struct to hold our I2C handle and any related context.
 * You can expand this if you need multiple I2C instances or advanced features.
 */
typedef struct {
    I2C_HandleTypeDef hi2c;  
} I2C_HAL_SVC_t;

/*
 * Initialize the I2C interface (manual approach). 
 * - instance: e.g., I2C1
 * - timing:   The 'Timing' register value for desired I2C speed (CubeMX can provide)
 * - portSCL, pinSCL, portSDA, pinSDA: The actual GPIO used for SCL/SDA.
 * 
 * In a typical CubeMX project, pin assignment and clock config
 * is already handled in generated code. You can either let CubeMX do that
 * or call the needed HAL_GPIO_Init and RCC functions here manually.
 */
HAL_StatusTypeDef i2c_hal_svc_init(
    I2C_HAL_SVC_t *pI2C,
    I2C_TypeDef *instance,
    uint32_t timing,
    GPIO_TypeDef *portSCL,
    uint16_t pinSCL,
    GPIO_TypeDef *portSDA,
    uint16_t pinSDA
);

/*
 * Transmit data on I2C.
 * devAddr is the 8-bit address (e.g., 0x3C << 1 = 0x78).
 */
HAL_StatusTypeDef i2c_hal_svc_transmit(
    I2C_HAL_SVC_t *pI2C,
    uint16_t devAddr,
    uint8_t *pData,
    uint16_t size,
    uint32_t timeout
);

#ifdef __cplusplus
}
#endif

#endif /* I2C_HAL_SVC_H */
