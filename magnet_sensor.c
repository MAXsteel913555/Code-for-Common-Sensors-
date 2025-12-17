#include "magnet_sensor.h"

/* 私有变量 */
static uint8_t magnet_detected = 0;
static uint8_t last_state = 0;

/**
  * @brief  磁铁传感器初始化
  * @retval None
  */
void MagnetSensor_Init(void)
{
    last_state = HAL_GPIO_ReadPin(MAGNET_GPIO_PORT, MAGNET_GPIO_PIN);
    magnet_detected = last_state;
}

/**
  * @brief  更新磁铁传感器状态
  * @retval None
  */
void MagnetSensor_Update(void)
{
    magnet_detected = HAL_GPIO_ReadPin(MAGNET_GPIO_PORT, MAGNET_GPIO_PIN);
}

/**
  * @brief  获取当前磁铁状态
  * @retval GPIO_PIN_SET或GPIO_PIN_RESET
  */
uint8_t MagnetSensor_GetState(void)
{
    return magnet_detected;
}

/**
  * @brief  处理磁铁状态变化
  * @retval None
  */
void MagnetSensor_Process(void)
{
    if (magnet_detected != last_state)
    {
        last_state = magnet_detected;

        if (magnet_detected == GPIO_PIN_RESET) // 低电平表示磁铁靠近
        {
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_PIN_SET); // LED亮
        }
        else
        {
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_PIN_RESET); // LED灭
        }
    }
}
