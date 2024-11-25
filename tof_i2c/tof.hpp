#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

static const uint8_t TOF_ADDR = 0x52;

// Sensor class for managing I2C communication and distance measurement
class Sensor {
private:
    i2c_inst_t* i2c_port;
    uint sda_pin;
    uint scl_pin;
    uint8_t device_addr;
    static constexpr uint32_t i2c_baudrate = 400000; // 400 kHz

public:
    // Constructor: Initialize I2C pins and port
    Sensor(i2c_inst_t* i2c, uint sda, uint scl, uint8_t addr)
        : i2c_port(i2c), sda_pin(sda), scl_pin(scl), device_addr(addr) {
        i2c_init(i2c_port, i2c_baudrate);
        gpio_set_function(sda_pin, GPIO_FUNC_I2C);
        gpio_set_function(scl_pin, GPIO_FUNC_I2C);
        gpio_pull_up(sda_pin);
        gpio_pull_up(scl_pin);
    }

    // Read distance from the sensor
    uint16_t get_distance() {
        uint8_t buffer[2] = {0}; // Buffer to store raw sensor data
        uint8_t write_addr = 0x00; // Distance register address
        i2c_write_blocking(i2c_port, device_addr, &write_addr, 1, true); // Point to write register
        i2c_read_blocking(i2c_port, device_addr, buffer, 2, false);  // Read 2 bytes
        return (buffer[0] << 8) | buffer[1]; // Combine bytes to form 16-bit distance
    }

    // Display distance measurement
    void to_string(uint16_t *distance) {
        printf("Distance (mm): %d\n", *distance);
    }
};

#endif // SENSOR_HPP
