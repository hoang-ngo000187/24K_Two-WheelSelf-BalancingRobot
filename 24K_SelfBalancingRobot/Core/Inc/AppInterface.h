/****************************************************************************************************************************
 * @author: Ngo Kien Hoang
 * @email: hoang.ngo000187@gmail.com
 *
 * This file contains the include paths of other files.
 ****************************************************************************************************************************/
#include <stdlib.h>
#include <math.h>
#include <Macro.h>

#include <AppControlMPU6050.h>
#include "stm32f1xx_hal.h"

void AOSpeedMotorLeft(INT16 Param);
void AOSpeedMotorRight(INT16 Param);
I2C_HandleTypeDef* AppGet_hi2c1(void);

/*DEBUG MACRO*/
#define DEBUG_MPU6050	1
#define DEBUG_NEMA17	1
