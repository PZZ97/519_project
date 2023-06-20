
cmake_minimum_required(VERSION 3.13)

project(hopper_sensing C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

set(FAMILY rp2040)
set(BOARD pico_sdk)
set(TINYUSB_FAMILY_PROJECT_NAME_PREFIX "tinyusb_dev_")

add_executable(hopper_sensing "")

target_include_directories(hopper_sensing
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/tusb_hid/.
  )

set_target_properties(
  hopper_sensing
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

# pico_generate_pio_header(hopper_sensing ${CMAKE_CURRENT_LIST_DIR}/pio_i2c/i2c.pio)

target_sources(hopper_sensing
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/magic_wand_model_data.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main_functions.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main_functions.h
  ${CMAKE_CURRENT_LIST_DIR}/magic_wand_model_data.h
  ${CMAKE_CURRENT_LIST_DIR}/micro_features_data.cpp
  ${CMAKE_CURRENT_LIST_DIR}/micro_features_data.h
  # ${CMAKE_CURRENT_LIST_DIR}/SparkFun_MicroPressure.cpp
  # ${CMAKE_CURRENT_LIST_DIR}/SparkFun_MicroPressure.h

  )

target_link_libraries(
  hopper_sensing
  pico-tflmicro
  hardware_pwm
  pico_stdlib
  # ICM42622
  # ICM20948
  # LCD_st7735
  # tinyusb_device
  # tinyusb_board
  hardware_adc
  hardware_i2c
  # hardware_pio
)

# enable usb output, disable uart output
pico_enable_stdio_usb(hopper_sensing 1)
pico_enable_stdio_uart(hopper_sensing 0)

pico_add_extra_outputs(hopper_sensing)
