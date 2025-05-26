cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(mcp4251_driver)

set(CMAKE_C_STANDARD 11)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_executable(mcp4251_driver
	main.c
)



target_include_directories(mcp4251_driver
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/../
)

target_link_libraries(mcp4251_driver
	pico_stdlib 
	hardware_spi
	hardware_gpio
	pico_bootrom)

pico_enable_stdio_usb(mcp4251_driver 1)
pico_enable_stdio_uart(mcp4251_driver 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(mcp4251_driver)

