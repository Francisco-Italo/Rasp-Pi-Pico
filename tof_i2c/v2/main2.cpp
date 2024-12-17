#include "i2c_sensors.hpp"
#include "tof.hpp"
#include "FreeRTOS.h"
#include "task.h"

// Task to handle the ToF sensor
void ToFTask(void *pvParameters)
{
    // Retrieve the TOF10120 sensor object passed as a parameter
    TOF10120* tof_sensor = static_cast<TOF10120*>(pvParameters);

    while (true)
    {
        uint16_t distance = tof_sensor->get_distance();
        tof_sensor->to_string(&distance);

        // Add a delay to prevent excessive polling
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main()
{
    // Create sensor object with specific I2C pins and address
    const uint sda = 16;
    const uint scl = 17;
    const uint8_t addr = TOF_ADDR;
    const uint32_t baudrate = 400000;

    // Instantiate the TOF10120 sensor
    TOF10120 tof_sensor(i2c0, sda, scl, addr, baudrate);

    // Initialize the sensor
    tof_sensor.initialize();

    // Create the ToF task, passing the sensor object as a parameter
    xTaskCreate(ToFTask, "ToF Task", 1024, &tof_sensor, 1, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // Code should never reach here
    while (true) {}

    return 0;
}
// End of file
