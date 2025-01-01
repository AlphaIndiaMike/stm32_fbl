#include "i2c_hal_svc.h"

/*
 * Enable GPIO clock based on GPIO port
 */
static void Enable_GPIO_Clock(GPIO_TypeDef *port) {
    if (port == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (port == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (port == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } else if (port == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    } else if (port == GPIOE) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    } else if (port == GPIOF) {
        __HAL_RCC_GPIOF_CLK_ENABLE();
    } else if (port == GPIOG) {
        __HAL_RCC_GPIOG_CLK_ENABLE();
    } else if (port == GPIOH) {
        __HAL_RCC_GPIOH_CLK_ENABLE();
    } else if (port == GPIOI) {
        __HAL_RCC_GPIOI_CLK_ENABLE();
    } else if (port == GPIOJ) {
        __HAL_RCC_GPIOJ_CLK_ENABLE();
    } else if (port == GPIOK) {
        __HAL_RCC_GPIOK_CLK_ENABLE();
    }
}

/*
 * Enable I2C clock based on I2C instance
 */
static void Enable_I2C_Clock(I2C_TypeDef *instance) {
    if (instance == I2C1) {
        __HAL_RCC_I2C1_CLK_ENABLE();
    } else if (instance == I2C2) {
        __HAL_RCC_I2C2_CLK_ENABLE();
    } else if (instance == I2C3) {
        __HAL_RCC_I2C3_CLK_ENABLE();
    } else if (instance == I2C4) {
        __HAL_RCC_I2C4_CLK_ENABLE();
    }
}

/*
 * Get Alternate Function for I2C instance
 */
static uint32_t Get_I2C_Alternate_AF(I2C_TypeDef *instance) {
    if (instance == I2C1 || instance == I2C3) {
        return GPIO_AF4_I2C1;
    } else if (instance == I2C2 || instance == I2C4) {
        return GPIO_AF4_I2C2;
    }
    return GPIO_AF4_I2C1;
}

/*
 * Initialize the I2C bus with a manual approach.
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

    Enable_GPIO_Clock(portSCL);
    Enable_GPIO_Clock(portSDA);
    Enable_I2C_Clock(instance);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = Get_I2C_Alternate_AF(instance);

    GPIO_InitStruct.Pin = pinSCL;
    HAL_GPIO_Init(portSCL, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = pinSDA;
    HAL_GPIO_Init(portSDA, &GPIO_InitStruct);

    pI2C->hi2c.Instance = instance;
    pI2C->hi2c.Init.Timing = timing;
    pI2C->hi2c.Init.OwnAddress1 = 0;
    pI2C->hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    pI2C->hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    pI2C->hi2c.Init.OwnAddress2 = 0;
    pI2C->hi2c.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    pI2C->hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    pI2C->hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    HAL_StatusTypeDef status = HAL_I2C_Init(&pI2C->hi2c);
    if (status != HAL_OK) {
        return status;
    }

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
