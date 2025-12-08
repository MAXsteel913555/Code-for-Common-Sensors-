#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"
#include "tim.h"  // 新增：包含定时器头文件
//前
//1  4
//2  3
//后
/* 电机编号定义 */
#define MOTOR1 0
#define MOTOR2 1
#define MOTOR3 2
#define MOTOR4 3

/* TB6612控制引脚定义（根据实际接线修改） */
// 电机1方向控制引脚
#define MOTOR1_A_PORT   GPIOA
#define MOTOR1_A_PIN    GPIO_PIN_0
#define MOTOR1_B_PORT   GPIOA
#define MOTOR1_B_PIN    GPIO_PIN_1

// 电机2方向控制引脚
#define MOTOR2_A_PORT   GPIOA
#define MOTOR2_A_PIN    GPIO_PIN_2
#define MOTOR2_B_PORT   GPIOA
#define MOTOR2_B_PIN    GPIO_PIN_3

// 电机3方向控制引脚
#define MOTOR3_A_PORT   GPIOA
#define MOTOR3_A_PIN    GPIO_PIN_4
#define MOTOR3_B_PORT   GPIOA
#define MOTOR3_B_PIN    GPIO_PIN_5

// 电机4方向控制引脚
#define MOTOR4_A_PORT   GPIOA
#define MOTOR4_A_PIN    GPIO_PIN_6
#define MOTOR4_B_PORT   GPIOA
#define MOTOR4_B_PIN    GPIO_PIN_7

// STBY引脚（所有电机共用，高电平使能）
#define STBY_PORT       GPIOB
#define STBY_PIN        GPIO_PIN_0

/* 电机方向定义 */
typedef enum {
    MOTOR_STOP = 0,
    MOTOR_FORWARD,
    MOTOR_BACKWARD
} Motor_DirTypeDef;

/* PWM配置参数 */
#define PWM_TIM2        htim2
#define PWM_CHANNEL3    TIM_CHANNEL_3  // 电机1
#define PWM_CHANNEL4    TIM_CHANNEL_4  // 电机2

#define PWM_TIM3        htim3
#define PWM_CHANNEL1    TIM_CHANNEL_1  // 电机3
#define PWM_CHANNEL2    TIM_CHANNEL_2  // 电机4

#define MAX_PWM         1000  // 最大PWM值（与定时器ARR一致）

/* 函数声明 */
void Motor_Init(void);

void Motor_SetDir(uint8_t motor, Motor_DirTypeDef dir);
void Motor_SetSpeed(uint8_t motor, uint16_t speed);

void Motor_Stop_Brake(void);
void Motor_Stop_Coast(void);
void Motor_Turn_Left(uint16_t speed);
void Motor_Turn_Right(uint16_t speed);
void Motor_Forward(uint16_t speed);
void Motor_Backward(uint16_t speed);

#endif /* MOTOR_H */
