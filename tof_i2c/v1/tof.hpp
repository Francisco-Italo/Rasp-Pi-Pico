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
        : i2c_port(i2c), sda_pin(sda), scl_pin(scl), device_addr(addr){}

    // Read distance from the sensor
    uint16_t get_distance();

    // Display distance measurement
    void to_string(uint16_t *distance);
};

#endif // SENSOR_HPP
