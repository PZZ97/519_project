/* 2023 Pneumatic Hopper
Authors: Rongqian Chen
==============================================================================*/

#include "main_functions.h"
#include "pico/stdlib.h"

int main(int argc, char *argv[]) {
  setup();
  while (true) {
    uint16_t result = adc_read();
    char str[20];
    sprintf(str, "result= %d\r\n", result);
    uart_puts(uart0, str);
    // printf("Hello, world!\n");
  }
}
