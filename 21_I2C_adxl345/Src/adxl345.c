#include "adxl345.h"




char data;

uint8_t data_rec[6];

void adxl_read_address (uint8_t reg){

	I2C1_byteRead(DEVICE_ADDR, reg, &data);

}

void adx1_write(uint8_t reg, char value){

	char data[1];
	data[0] = value;

	I2C1_burstWrite(DEVICE_ADDR, reg, 1, data);
}

void adxl_read_values (uint8_t reg){

	I2C1_burstRead(DEVICE_ADDR, reg, 6, (char*)data_rec);
}

void adxl_init(void){

	// Enable I2C
	I2C1_init();

	// Read the DEVID, this should return 0xE5
	adxl_read_address(DEVID_R);

	// Set data format range to +-4g
	adx1_write(DATA_FORMAT_R, FOUR_G);

	// Reset all bits
	adx1_write(POWER_CTL_R, RESET);

	// Configure power control measure bit
	adx1_write(POWER_CTL_R, SET_MEASURE_B);
}
