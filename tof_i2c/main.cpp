#include "tof.hpp"

int main()
{
    stdio_init_all(); // Initialize standard I/O

    // Create sensor object with specific I2C pins and address
    const uint sda = 16;
    const uint scl = 17;
    const uint8_t addr = TOF_ADDR;
    Sensor tof_sensor(i2c0, sda, scl, addr);

    uint16_t distance;

    while (true) {
        distance = tof_sensor.get_distance(); // Get distance
        tof_sensor.to_string(&distance);
        sleep_ms(1000); // Wait 1 second before the next read
    }

    return 0;
}
