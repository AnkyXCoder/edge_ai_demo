cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(BOARD STREQUAL "nrf52840dk/nrf52840")
# This sample is specific to x_nucleo_iks01a3 shield. Enforce -DSHIELD option
    set(SHIELD x_nucleo_iks01a3_shub)
endif()

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(ei-dataforwarder)

# Needed for colorful output
zephyr_compile_options(-fdiagnostics-color=always)

target_sources(app PRIVATE src/main.cpp)
