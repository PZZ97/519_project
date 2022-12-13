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
#include "main_functions.h"
#include "tusb_hid/hid_src.h"
#include "pico/stdlib.h"
// This is the default main used on systems that have the standard C entry
// point. Other devices (for example FreeRTOS or ESP32) that have different
// requirements for entry code (like an app_main function) should specialize
// this main.cc file in a target-specific subfolder.
enum TASKS{
  KEYBOARD=0,
  MOUSE
};
int main(int argc, char *argv[]) {
  setup();
  uint8_t state=0;
  while (true) {
    static bool switch_keyboard_mouse=true;
    switch_keyboard_mouse=gpio_get(KEYBOARD_SWITCH_IO);
    if(!switch_keyboard_mouse){  // btn pressed
      switch_keyboard_mouse=true;
      state=~state;
       char str[50] ="switch\r\n";
        uart_puts(uart0, str);
    }
      if(state==MOUSE){
          mouse_abs_position(); 
      }
      else
      {        
         keyboard_loop();
        // char str[50] ="Keyboard\r\n";
        // uart_puts(uart0, str);
        tud_task();
        // hid_task();
      }
  }
}
