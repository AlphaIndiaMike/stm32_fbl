#include "i2c_hal_svc.h"

/*
 * Initialize the I2C bus with a manual approach. 
 * If you already have CubeMX-generated code for pin config and I2C init,
 * you can skip the pin config here and just call HAL_I2C_Init().
 */
HAL_StatusTypeDef i2c_hal_svc_init(
    I2C_HAL_SVC_t *pI2C,
    I2C_TypeDef *instance,
    uint32_t timing,
    GPIO_TypeDef *portSCL,
    uint16_t pinSCL,
    GPIO_TypeDef *portSDA,
    uint16_t pinSDA
)
{
    if (pI2C == NULL) {
        return HAL_ERROR;
    }
    
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pinSCL | pinSDA;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP; 
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1; // depends on your board/pin
    HAL_GPIO_Init(portSCL, &GPIO_InitStruct);

    // Fill in the HAL I2C struct
    pI2C->hi2c.Instance = instance;
    pI2C->hi2c.Init.Timing = timing;
    pI2C->hi2c.Init.OwnAddress1 = 0;
    pI2C->hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    pI2C->hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    pI2C->hi2c.Init.OwnAddress2 = 0;
    pI2C->hi2c.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    pI2C->hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    pI2C->hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    // Initialize
    HAL_StatusTypeDef status = HAL_I2C_Init(&pI2C->hi2c);
    if (status != HAL_OK) {
        return status;
    }

    // Configure analog & digital filters (optional)
    status = HAL_I2CEx_ConfigAnalogFilter(&pI2C->hi2c, I2C_ANALOGFILTER_ENABLE);
    if (status != HAL_OK) {
        return status;
    }

    status = HAL_I2CEx_ConfigDigitalFilter(&pI2C->hi2c, 0);
    if (status != HAL_OK) {
        return status;
    }

    return HAL_OK;
}

/*
 * I2C transmit wrapper
 */
HAL_StatusTypeDef i2c_hal_svc_transmit(
    I2C_HAL_SVC_t *pI2C,
    uint16_t devAddr,
    uint8_t *pData,
    uint16_t size,
    uint32_t timeout
)
{
    if (pI2C == NULL) {
        return HAL_ERROR;
    }
    return HAL_I2C_Master_Transmit(&pI2C->hi2c, devAddr, pData, size, timeout);
}
