#include "Motor.h"

void Motor_Init(void) {
    // 使能电机驱动（STBY引脚置高）
    HAL_GPIO_WritePin(STBY_PORT, STBY_PIN, GPIO_PIN_SET);

    // 初始化所有电机为停止状态
    Motor_SetDir(MOTOR1, MOTOR_STOP);
    Motor_SetDir(MOTOR2, MOTOR_STOP);
    Motor_SetDir(MOTOR3, MOTOR_STOP);
    Motor_SetDir(MOTOR4, MOTOR_STOP);
}

void Motor_SetDir(uint8_t motor, Motor_DirTypeDef dir) {
    switch (motor) {
        case MOTOR1:
            switch (dir) {
                case MOTOR_STOP:
                    HAL_GPIO_WritePin(MOTOR1_A_PORT, MOTOR1_A_PIN, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(MOTOR1_B_PORT, MOTOR1_B_PIN, GPIO_PIN_SET);
                    break;
                case MOTOR_FORWARD:
                    HAL_GPIO_WritePin(MOTOR1_A_PORT, MOTOR1_A_PIN, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(MOTOR1_B_PORT, MOTOR1_B_PIN, GPIO_PIN_SET);
                    break;
                case MOTOR_BACKWARD:
                    HAL_GPIO_WritePin(MOTOR1_A_PORT, MOTOR1_A_PIN, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(MOTOR1_B_PORT, MOTOR1_B_PIN, GPIO_PIN_RESET);
                    break;
            }
            break;
        case MOTOR2:
            switch (dir) {
                case MOTOR_STOP:
                    HAL_GPIO_WritePin(MOTOR2_A_PORT, MOTOR2_A_PIN, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(MOTOR2_B_PORT, MOTOR2_B_PIN, GPIO_PIN_SET);
                    break;
                case MOTOR_FORWARD:
                    HAL_GPIO_WritePin(MOTOR2_A_PORT, MOTOR2_A_PIN, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(MOTOR2_B_PORT, MOTOR2_B_PIN, GPIO_PIN_RESET);
                    break;
                case MOTOR_BACKWARD:
                    HAL_GPIO_WritePin(MOTOR2_A_PORT, MOTOR2_A_PIN, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(MOTOR2_B_PORT, MOTOR2_B_PIN, GPIO_PIN_SET);
                    break;
            }
            break;
        case MOTOR3:
            switch (dir) {
                case MOTOR_STOP:
                    HAL_GPIO_WritePin(MOTOR3_A_PORT, MOTOR3_A_PIN, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(MOTOR3_B_PORT, MOTOR3_B_PIN, GPIO_PIN_SET);
                    break;
                case MOTOR_FORWARD:
                    HAL_GPIO_WritePin(MOTOR3_A_PORT, MOTOR3_A_PIN, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(MOTOR3_B_PORT, MOTOR3_B_PIN, GPIO_PIN_RESET);
                    break;
                case MOTOR_BACKWARD:
                    HAL_GPIO_WritePin(MOTOR3_A_PORT, MOTOR3_A_PIN, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(MOTOR3_B_PORT, MOTOR3_B_PIN, GPIO_PIN_SET);
                    break;
            }
            break;
        case MOTOR4:
            switch (dir) {
                case MOTOR_STOP:
                    HAL_GPIO_WritePin(MOTOR4_A_PORT, MOTOR4_A_PIN, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(MOTOR4_B_PORT, MOTOR4_B_PIN, GPIO_PIN_SET);
                    break;
                case MOTOR_FORWARD:
                    HAL_GPIO_WritePin(MOTOR4_A_PORT, MOTOR4_A_PIN, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(MOTOR4_B_PORT, MOTOR4_B_PIN, GPIO_PIN_SET);
                    break;
                case MOTOR_BACKWARD:
                    HAL_GPIO_WritePin(MOTOR4_A_PORT, MOTOR4_A_PIN, GPIO_PIN_SET);
                    HAL_GPIO_WritePin(MOTOR4_B_PORT, MOTOR4_B_PIN, GPIO_PIN_RESET);
                    break;
            }
            break;
    }
}

void Motor_SetSpeed(uint8_t motor, uint16_t speed) {
    if (speed > MAX_PWM) speed = MAX_PWM;

    switch (motor) {
        case MOTOR1:
            __HAL_TIM_SET_COMPARE(&PWM_TIM2, PWM_CHANNEL3, speed);
            break;
        case MOTOR2:
            __HAL_TIM_SET_COMPARE(&PWM_TIM2, PWM_CHANNEL4, speed);
            break;
        case MOTOR3:
            __HAL_TIM_SET_COMPARE(&PWM_TIM3, PWM_CHANNEL1, speed);
            break;
        case MOTOR4:
            __HAL_TIM_SET_COMPARE(&PWM_TIM3, PWM_CHANNEL2, speed);
            break;
    }
}

void Motor_Stop_Coast(void)//自然刹车
{
	 //将所有电机的方向引脚设置为停止状态，这在某些驱动芯片上可以实现制动
     Motor_SetDir(MOTOR1, MOTOR_STOP);
     Motor_SetDir(MOTOR2, MOTOR_STOP);
     Motor_SetDir(MOTOR3, MOTOR_STOP);
     Motor_SetDir(MOTOR4, MOTOR_STOP);
}

void Motor_Stop_Brake(void)//急刹
{
	 //将所有电机的方向引脚设置为停止状态，这在某些驱动芯片上可以实现制动
    Motor_SetSpeed(MOTOR1, 0);//右前1
    Motor_SetSpeed(MOTOR2, 0);//右后2
    Motor_SetSpeed(MOTOR3, 0);//左前3
    Motor_SetSpeed(MOTOR4, 0);//左后4
}


void Motor_Turn_Left(uint16_t speed)
{
    if (speed > MAX_PWM) speed = MAX_PWM;

    // 右轮（M1, M2）前进
    Motor_SetDir(MOTOR1, MOTOR_FORWARD);
    Motor_SetDir(MOTOR2, MOTOR_FORWARD);

    // 左轮（M3, M4）向后退
    Motor_SetDir(MOTOR3, MOTOR_BACKWARD);
    Motor_SetDir(MOTOR4, MOTOR_BACKWARD);

    // 所有电机设置为相同的速度，以实现原地旋转
    Motor_SetSpeed(MOTOR1, speed);
    Motor_SetSpeed(MOTOR2, speed);
    Motor_SetSpeed(MOTOR3, speed);
    Motor_SetSpeed(MOTOR4, speed);
}


void Motor_Turn_Right(uint16_t speed)
{
    if (speed > MAX_PWM) speed = MAX_PWM;

    //右轮（M1, M2）后退
    Motor_SetDir(MOTOR1, MOTOR_BACKWARD);
    Motor_SetDir(MOTOR2, MOTOR_BACKWARD);

    //左轮（M3, M4）前进
    Motor_SetDir(MOTOR3, MOTOR_FORWARD);
    Motor_SetDir(MOTOR4, MOTOR_FORWARD);

    // 所有电机设置为相同的速度，以实现原地旋转
    Motor_SetSpeed(MOTOR1, speed);
    Motor_SetSpeed(MOTOR2, speed);
    Motor_SetSpeed(MOTOR3, speed);
    Motor_SetSpeed(MOTOR4, speed);
}

void Motor_Forward(uint16_t speed)
{
    if (speed > MAX_PWM) speed = MAX_PWM;

    Motor_SetDir(MOTOR1, MOTOR_FORWARD);
    Motor_SetDir(MOTOR2, MOTOR_FORWARD);

    Motor_SetDir(MOTOR3, MOTOR_FORWARD);
    Motor_SetDir(MOTOR4, MOTOR_FORWARD);

    Motor_SetSpeed(MOTOR1, speed);//右前1
    Motor_SetSpeed(MOTOR2, speed);//右后2
    Motor_SetSpeed(MOTOR3, speed);//左前3
    Motor_SetSpeed(MOTOR4, speed);//左后4
}

void Motor_Backward(uint16_t speed)
{
    if (speed > MAX_PWM) speed = MAX_PWM;

    Motor_SetDir(MOTOR1, MOTOR_BACKWARD);
    Motor_SetDir(MOTOR2, MOTOR_BACKWARD);

    Motor_SetDir(MOTOR3, MOTOR_BACKWARD);
    Motor_SetDir(MOTOR4, MOTOR_BACKWARD);

    Motor_SetSpeed(MOTOR1, speed);//右前1
    Motor_SetSpeed(MOTOR2, speed);//右后2
    Motor_SetSpeed(MOTOR3, speed);//左前3
    Motor_SetSpeed(MOTOR4, speed);//左后4
}
