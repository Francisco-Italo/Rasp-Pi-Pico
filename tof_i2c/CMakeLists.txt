cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Pull in FreeRTOS
include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(app C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(tof_i2c ./v2/main2.cpp ./v2/tof.cpp ./v2/i2c_sensors.cpp)

target_include_directories(tof_i2c PRIVATE ${CMAKE_CURRENT_LIST_DIR})
 
# pull in common dependencies
target_link_libraries(tof_i2c pico_stdlib hardware_i2c FreeRTOS-Kernel FreeRTOS-Kernel-Heap4)

# Enable usb output, disable uart output
pico_enable_stdio_usb(tof_i2c 1)
pico_enable_stdio_uart(tof_i2c 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(tof_i2c)
