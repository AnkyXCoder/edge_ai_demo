cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Board-specific shield
if(BOARD STREQUAL "nrf52840dk/nrf52840")
    set(SHIELD x_nucleo_iks01a3_shub)
endif()

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(ei_inference_app)

# Add Edge Impulse model (must be Zephyr-compatible)
add_subdirectory(model)

# App sources
target_sources(app PRIVATE
    src/main.cpp
)

# Enable C++17 properly
target_compile_features(app PRIVATE cxx_std_17)

# Edge Impulse / CMSIS-NN flags (apply to app instead of unknown target)
add_definitions(-DEIDSP_USE_CMSIS_DSP=1
                -DEIDSP_LOAD_CMSIS_DSP_SOURCES=1
                -DEI_CLASSIFIER_TFLITE_ENABLE_CMSIS_NN=1
                -DARM_MATH_LOOPUNROLL)
