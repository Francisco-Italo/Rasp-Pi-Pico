#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

static const uint8_t TOF_REG = 0x52;

/*
 * Prototypes
 */
uint16_t get_distance(i2c_inst_t*, uint8_t*);
void to_str(uint16_t*);

/*
 * Main
 */
int main()
{
	// Pins
	const uint sda = 16;
	const uint scl = 17;

	i2c_inst_t *i2c = i2c0;		// Port
	
	uint16_t dist = 0; 			// Distance measured
	uint8_t buf[2];			// Store sensor raw reads

	stdio_init_all(); 		// Starting selected serial port
	i2c_init(i2c, 400*1000);	// Initialize I2C at 400 kHz
	
	// Initialize I2C pins
	gpio_set_function(sda, GPIO_FUNC_I2C);
	gpio_set_function(scl, GPIO_FUNC_I2C);
	// Set internal pull up registers
	gpio_pull_up(sda);
	gpio_pull_up(scl);

	while(1)
	{
		dist = get_distance(i2c, buf);
		to_str(&dist);
		sleep_ms(2000);
	}
}

/*
 * Function definitions
 */
uint16_t get_distance(i2c_inst_t *i2c, uint8_t buf[2])
{
	uint8_t addr = 0x00;		// Set distance register
	// I2C transaction
	if(i2c_write_blocking(i2c, TOF_REG, &addr, 1, true) != 1)
	{
		printf("Write failed.\n");
		return 0;
	}

	if(i2c_read_blocking(i2c, TOF_REG, buf, 2, false) != 2)
	{
		printf("Read failed.\n");
		return 0;
	}
	
	return (buf[0] << 8 | buf[1]);
}

void to_str(uint16_t *dist)
{
	printf("%d mm\n", *dist);
}
