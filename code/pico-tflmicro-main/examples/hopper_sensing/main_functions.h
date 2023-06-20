/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_MAGIC_WAND_MAIN_FUNCTIONS_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_MAGIC_WAND_MAIN_FUNCTIONS_H_
// #include "pico/stdlib.h"
#define KEYBOARD_SWITCH_IO 28 // don't use pin4, it's for IMU on board   
//// Expose a C friendly interface for main functions.
//#ifdef __cplusplus
// extern "C" {
//#endif
#include "hardware/gpio.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include <hardware/irq.h>
#include <hardware/uart.h>
#include <pico/stdio_usb.h>

#include "magic_wand_model_data.h"

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "hardware/adc.h"

#include "pico/stdlib.h"


// Initializes all data needed for the example. The name is important, and needs
// to be setup() for Arduino compatibility.
void setup();

// Runs one iteration of data gathering and inference. This should be called
// repeatedly from the application code. The name needs to be loop() for Arduino
// compatibility.
void loop();
void read_redundant_data();
void mouse_abs_position(bool initial_cursor_flag);
void imu_print();
void screen_show();
void IMUupdate();
void keyboard_loop(char&);
bool click_detect();
//#ifdef __cplusplus
//}
//#endif

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_MAGIC_WAND_MAIN_FUNCTIONS_H_
