/****************************************************************************************************************************

 * @author: Ngo Kien Hoang
 * @email: hoang.ngo000187@gmail.com
 *
 * This file contains the library for communicating with MPU6050 sensor.

 ****************************************************************************************************************************/

/****************************************************************************************************************************
 * INCLUDE
 ****************************************************************************************************************************/
#include <Macro.h>

/****************************************************************************************************************************
 * STRUCT / ENUM
 ****************************************************************************************************************************/
typedef struct _MPU6050_RawData{
	INT16 nAccel_X_RAW;
	INT16 nAccel_Y_RAW;
	INT16 nAccel_Z_RAW;

	INT16 nGyro_X_RAW;
	INT16 nGyro_Y_RAW;
	INT16 nGyro_Z_RAW;
}MPU6050_RawData;

typedef struct _MPU6050_Data{
	FLOAT fAccel_X;
	FLOAT fAccel_Y;
	FLOAT fAccel_Z;

	FLOAT fGyro_X;
	FLOAT fGyro_Y;
	FLOAT fGyro_Z;
}MPU6050_Data;

/****************************************************************************************************************************
 * PROTOTYPE
 ****************************************************************************************************************************/
void AppControl_MPU6050_Init(void);
void AppControl_MPU6050ReadData();
void AppControl_MPU6050_Read_Accel(void);
void AppControl_MPU6050_Read_Gyro(void);
MPU6050_RawData* AppControl_MPU6050GetRawData();
MPU6050_Data* AppControl_MPU6050GetData();
/****************************************************************************************************************************
 * MACRO
 ****************************************************************************************************************************/
/*
 * MPU6050 Address: 0xD0
 * 		. 7bit address of MPU6050: [b6:b1] = 0b110100X;
 * 		. b0 = X = AD0 = 0 --> [b6:b0] = 0b1101000 = 0x68
 * 		. bit R/\W: MPU6050 write data for Microcontroller read data --> bit R/\W = 0 -- Address = 0b1101 0000 = (0x68 << 1)
 */
#define MPU6050_ADDR	(0x68 << 1)

#define WHO_AM_I_REG	    (0x75)
#define PWR_MGMT_1_REG	    (0x6B)
#define SMPRT_DIV_REG	    (0x19)
#define GYRO_CONFIG_REG     (0x1B)         
#define ACCEL_CONFIG_REG    (0x1C)
#define ACCEL_XOUT_H_REG    (0x3B)
#define ACCEL_XOUT_L_REG    (0x3C)
#define ACCEL_YOUT_H_REG    (0x3D)
#define ACCEL_YOUT_L_REG    (0x3E)
#define ACCEL_ZOUT_H_REG    (0x3F)
#define ACCEL_ZOUT_L_REG    (0x40)
#define GYRO_XOUT_H_REG     (0x43)
#define GYRO_XOUT_L_REG     (0x44)
#define GYRO_YOUT_H_REG     (0x45)
#define GYRO_YOUT_L_REG     (0x46)
#define GYRO_ZOUT_H_REG     (0x47)
#define GYRO_ZOUT_L_REG     (0x48)
