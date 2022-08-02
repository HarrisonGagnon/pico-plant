cmake_minimum_required(VERSION 3.22)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_compile_options(
    -Wall
    -Werror
    -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-unused-function # we have some for the docs that aren't called
    -Wno-maybe-uninitialized
)
if (TARGET tinyusb_device)
    add_executable(
        picoplant # Name of the executable
        picoplant.c # Name of the files to compile
        arm.h
    )

    # pull in common dependencies
    target_link_libraries(picoplant pico_stdlib hardware_adc)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(picoplant 1)
    pico_enable_stdio_uart(picoplant 0)

    # create map/bin/hex file etc.
    pico_add_extra_outputs(picoplant)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building pico because TinyUSB submodule is not initialized in the SDK")
endif()