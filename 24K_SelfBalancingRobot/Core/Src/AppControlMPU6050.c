/****************************************************************************************************************************

 * @author: Ngo Kien Hoang
 * @email: hoang.ngo000187@gmail.com
 *
 * This file contains the library for communicating with MPU6050 sensor.

 ****************************************************************************************************************************/

/****************************************************************************************************************************
 * INCLUDE
 ****************************************************************************************************************************/
#include "AppInterface.h"

MPU6050_RawData sMPU6050RawData;
MPU6050_Data sMPU6050Data;

void AppControl_MPU6050_Init(void)
{
	UINT8 u8Check, u8Data;
	I2C_HandleTypeDef* ptr_hi2c = AppGet_hi2c1();

	/* 01 - Check if the sensor is responding or not */
	HAL_I2C_Mem_Read (ptr_hi2c, MPU6050_ADDR, WHO_AM_I_REG, 1, &u8Check, 1, 1000);

	if (104 == u8Check) // the sensor is present
	{
		/* 02 - Write all bit 0 to Power management register (Addr: 0x6B) to wake the sensor up */
		u8Data = 0;
		HAL_I2C_Mem_Write(ptr_hi2c, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &u8Data, 1, 1000);

		/* 03 - Set DATA RATE = 1KHz by writing to SMPLRT_DIV register */
		u8Data = 7;
		HAL_I2C_Mem_Write(ptr_hi2c, MPU6050_ADDR, SMPRT_DIV_REG, 1, &u8Data, 1, 1000);

		/* 04 - Set the Full scale range of ± 2g in ACCEL_CONFIGRegister and a Full scale range of ± 250 °/s in GYRO_CONFIG*/
		u8Data = 0;
		HAL_I2C_Mem_Write(ptr_hi2c, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &u8Data, 1, 1000);
		u8Data = 0;
		HAL_I2C_Mem_Write(ptr_hi2c, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &u8Data, 1, 1000);
	}
}

void AppControl_MPU6050_Read_Accel(void)
{
	UINT8 u8Rec_Data[6];
	
	I2C_HandleTypeDef* ptr_hi2c = AppGet_hi2c1();
	// Read 6 bytes of data starting from ACCEL_XOUT_H register
	HAL_I2C_Mem_Read(ptr_hi2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, u8Rec_Data, 6, 1000);

	sMPU6050RawData.nAccel_X_RAW = (INT16)(u8Rec_Data[0] << 8 | u8Rec_Data[1]);
	sMPU6050RawData.nAccel_Y_RAW = (INT16)(u8Rec_Data[2] << 8 | u8Rec_Data[3]);
	sMPU6050RawData.nAccel_Z_RAW = (INT16)(u8Rec_Data[4] << 8 | u8Rec_Data[5]);

	sMPU6050Data.fAccel_X = sMPU6050RawData.nAccel_X_RAW/16384.0;
	sMPU6050Data.fAccel_Y = sMPU6050RawData.nAccel_Y_RAW/16384.0;
	sMPU6050Data.fAccel_Z = sMPU6050RawData.nAccel_Z_RAW/16384.0;
}

void AppControl_MPU6050_Read_Gyro(void)
{
	UINT8 u8Rec_Data[6];
	
	I2C_HandleTypeDef* ptr_hi2c = AppGet_hi2c1();
	// Read 6 bytes of data starting from GYRO_XOUT_H register
	HAL_I2C_Mem_Read(ptr_hi2c, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, u8Rec_Data, 6, 1000);

	sMPU6050RawData.nGyro_X_RAW = (INT16)(u8Rec_Data[0] << 8 | u8Rec_Data[1]);
	sMPU6050RawData.nGyro_Y_RAW = (INT16)(u8Rec_Data[2] << 8 | u8Rec_Data[3]);
	sMPU6050RawData.nGyro_Z_RAW = (INT16)(u8Rec_Data[4] << 8 | u8Rec_Data[5]);

	sMPU6050Data.fGyro_X = sMPU6050RawData.nGyro_X_RAW/16384.0;
	sMPU6050Data.fGyro_Y = sMPU6050RawData.nGyro_Y_RAW/16384.0;
	sMPU6050Data.fGyro_Z = sMPU6050RawData.nGyro_Z_RAW/16384.0;
}

void AppControl_MPU6050ReadData()
{
	AppControl_MPU6050_Read_Accel();
	AppControl_MPU6050_Read_Gyro();
}

MPU6050_RawData* AppControl_MPU6050GetRawData()
{
	return &sMPU6050RawData;
}

MPU6050_Data* AppControl_MPU6050GetData()
{
	return &sMPU6050Data;
}
