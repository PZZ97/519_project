/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.
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

// #include "hardware/gpio.h"
// #include "tensorflow/lite/micro/micro_error_reporter.h"
// #include "tensorflow/lite/micro/micro_interpreter.h"
// #include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
// #include "tensorflow/lite/schema/schema_generated.h"
// #include "tensorflow/lite/version.h"
// #include <hardware/irq.h>
// #include <hardware/uart.h>
// #include <pico/stdio_usb.h>

// #include "magic_wand_model_data.h"

// #include <stdio.h>
// #include <string.h>
// #include "pico/stdlib.h"
// #include "pico/binary_info.h"
// #include "hardware/i2c.h"
// #include "hardware/uart.h"
// #include "hardware/adc.h"

// #include "pico/stdlib.h"
#include "main_functions.h"

#define SCREEN 0

#if SCREEN

#include "LCD_st7735.h"

#endif

#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define I2C_SDA_PIN 2
#define I2C_SCL_PIN 3
#define UART1_TX_PIN 4
#define UART1_RX_PIN 5
#define ADDR_PIN1 26
#define ADDR_PIN2 27
#define CLICK_THRES 2.0
namespace {
bool     linked     = false;
bool     first      = true;
uint16_t send_index = 0;

// Constants for image rasterization
constexpr int raster_width      = 32;
constexpr int raster_height     = 32;
constexpr int raster_channels   = 3;
constexpr int raster_byte_count = raster_height * raster_width * raster_channels;
int8_t        raster_buffer[raster_byte_count];

// Create an area of memory to use for input, output, and intermediate arrays.
// The size of this will depend on the model you're using, and may need to be
// determined by experimentation.
constexpr int kTensorArenaSize = 7 * 1024 + 1888;
uint8_t       tensor_arena[kTensorArenaSize];

tflite::ErrorReporter    *error_reporter = nullptr;
const tflite::Model      *model          = nullptr;
tflite::MicroInterpreter *interpreter    = nullptr;

// -------------------------------------------------------------------------------- //
// UPDATE THESE VARIABLES TO MATCH THE NUMBER AND LIST OF GESTURES IN YOUR DATASET  //
// -------------------------------------------------------------------------------- //
constexpr int label_count       = 10;
const char *labels[label_count] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
}  // namespace

#ifndef DO_NOT_OUTPUT_TO_UART
// RX interrupt handler
uint8_t command[32]   = { 0 };
bool    start_flag    = false;
int     receive_index = 0;
uint8_t previous_ch   = 0;

void on_uart_rx() {
  uint8_t cameraCommand = 0;
  while (uart_is_readable(UART_ID)) {
    cameraCommand = uart_getc(UART_ID);
    //    //printf("%c \n", cameraCommand);
    if (start_flag) {
      command[receive_index++] = cameraCommand;
    }
    if (cameraCommand == 0xf4 && previous_ch == 0xf5) {
      start_flag = true;
    }
    else if (cameraCommand == 0x0a && previous_ch == 0x0d) {
      start_flag = false;
      // add terminator
      command[receive_index - 2] = '\0';

      receive_index = 0;
      if (strcmp("IND=BLECONNECTED", (const char *)command) == 0) {
        linked = true;
      }
      else if (strcmp("IND=BLEDISCONNECTED", (const char *)command) == 0) {
        linked = false;
      }
      //printf("%s\n", command);
    }
    previous_ch = cameraCommand;
  }
}

void setup_uart() {
  // Set up our UART with the required speed.
  uint baud = uart_init(UART_ID, BAUD_RATE);
  // Set the TX and RX pins by using the function select on the GPIO
  // Set datasheet for more information on function select
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
  // Set our data format
  uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
  // Turn off FIFO's - we want to do this character by character
  uart_set_fifo_enabled(UART_ID, false);
  // Set up a RX interrupt
  // We need to set up the handler first
  // Select correct interrupt for the UART we are using
  int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

  // And set up and enable the interrupt handlers
  irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
  irq_set_enabled(UART_IRQ, true);

  // Now enable the UART to send interrupts - RX only
  uart_set_irq_enables(UART_ID, true, false);
}

#else
void setup_uart() {ST7735_FillScreen(ST7735_RED);}
#endif

//static int addr = 0x69; // when AD0 is HIGH
// #ifdef i2c_default

void mpu6050_read_raw(uint8_t addr, int16_t accel[3], int16_t gyro[3]) { // add int16_t *temp for temperature if needs
    // For this particular device, we send the device the register we want to read
    // first, then subsequently read from the device. The register is auto incrementing
    // so we don't need to keep sending the register we want, just the first.

    uint8_t buffer[6];

    // Start reading acceleration registers from register 59 (0x3B) for 6 bytes, x,y,z each with two bits
    // default +- 2g, 16384 b/g
    uint8_t val = 0x3B;
    i2c_write_blocking(i2c1, addr, &val, 1, true); // true to keep master control of bus
    i2c_read_blocking(i2c1, addr, buffer, 6, false);

    for (int i = 0; i < 3; i++) {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    // Now gyro data from reg 67 (0x43) for 6 bytes
    // The register is auto incrementing on each read
    val = 0x43;
    i2c_write_blocking(i2c1, addr, &val, 1, true);
    i2c_read_blocking(i2c1, addr, buffer, 6, false);  // False - finished with bus

    for (int i = 0; i < 3; i++) {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);;
    }

    // // Now temperature from reg 0x41 for 2 bytes
    // // The register is auto incrementing on each read
    // val = 0x41;
    // i2c_write_blocking(i2c1, addr, &val, 1, true);
    // i2c_read_blocking(i2c1, addr, buffer, 2, false);  // False - finished with bus

    // *temp = buffer[0] << 8 | buffer[1];
}
// #endif
void mpu6050_read_data(uint8_t addr, float _accel[3], float _gyro[3]) { // add int16_t *temp for temperature if needs
    // For this particular device, we send the device the register we want to read
    // first, then subsequently read from the device. The register is auto incrementing
    // so we don't need to keep sending the register we want, just the first.

    uint8_t buffer[6];

    // Start reading acceleration registers from register 59 (0x3B) for 6 bytes, x,y,z each with two bits
    // default +- 2g, 16384 b/g
    uint8_t val = 0x3B;
    i2c_write_blocking(i2c1, addr, &val, 1, true); // true to keep master control of bus
    i2c_read_blocking(i2c1, addr, buffer, 6, false);

    int16_t accel[3];
    for (int i = 0; i < 3; i++) {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
        _accel[i]=(float)accel[i]*2.0 / 32768.0;
    }

    int16_t gyro[3];
    // Now gyro data from reg 67 (0x43) for 6 bytes
    // The register is auto incrementing on each read
    val = 0x43;
    i2c_write_blocking(i2c1, addr, &val, 1, true);
    i2c_read_blocking(i2c1, addr, buffer, 6, false);  // False - finished with bus

    for (int i = 0; i < 3; i++) {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
        _gyro[i]=(float)gyro[i]*250.0 / 32768.0;
    }
}
// #endif


void imu_print() {
    int16_t acceleration1[3], gyro1[3], temp1;
    int16_t acceleration2[3], gyro2[3], temp2;
    mpu6050_read_raw(0x68, acceleration1, gyro1);// &temp1
    char str[100];
    sprintf(str,"Acc1. X = %d, Y = %d, Z = %d\n", acceleration1[0], acceleration1[1], acceleration1[2]);
    uart_puts(uart0,str);
    sprintf(str,"Gyro1. X = %d, Y = %d, Z = %d\n", gyro1[0], gyro1[1], gyro1[2]);
    uart_puts(uart0,str);
    
    // mpu6050_read_raw(0x69, acceleration2, gyro2);// &temp2
    // These are the raw numbers from the chip, so will need tweaking to be really useful.
    printf("Acc1. X = %d, Y = %d, Z = %d\n", acceleration1[0], acceleration1[1], acceleration1[2]);
    // printf("Acc2. X = %d, Y = %d, Z = %d\n", acceleration2[0], acceleration2[1], acceleration2[2]);
    //printf("Gyro1. X = %d, Y = %d, Z = %d\n", gyro1[0], gyro1[1], gyro1[2]);
    //printf("Gyro2. X = %d, Y = %d, Z = %d\n", gyro2[0], gyro2[1], gyro2[2]);
    // Temperature is simple so use the datasheet calculation to get deg C.
    // Note this is chip temperature.
    ////printf("Temp. = %f\n", (temp1 / 340.0) + 36.53);
}

// #define 
void setup() {
  // gpio_init(25);
  // gpio_set_dir(25, GPIO_OUT);
  // gpio_put(25, !gpio_get(25));
  
  
#if SCREEN
  ST7735_Init();
  ST7735_DrawImage(0, 0, 80, 160, arducam_logo);
#endif

  // setup_uart();// Start serial
  // stdio_usb_init(); //can't use under tinyusb mode
  // ADC setup
  adc_init();
  // Make sure GPIO is high-impedance, no pullups etc
  adc_gpio_init(26);
  // Select ADC input 0 (GPIO26)
  adc_select_input(0);
  
/*Set up UART0 for test debugging*/
  uart_init(uart0, BAUD_RATE);
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
  uart_puts(uart0, " UART0 Setup!\n");
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  static tflite::MicroErrorReporter micro_error_reporter;  // NOLINT
  error_reporter = &micro_error_reporter;


  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(g_magic_wand_model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // Pull in only the operation implementations we need.
  // This relies on a complete list of all the ops needed by this graph.
  // An easier approach is to just use the AllOpsResolver, but this will
  // incur some penalty in code space for op implementations that are not
  // needed by this graph.
  static tflite::MicroMutableOpResolver<4> micro_op_resolver;  // NOLINT
  micro_op_resolver.AddConv2D();
  micro_op_resolver.AddMean();
  micro_op_resolver.AddFullyConnected();
  micro_op_resolver.AddSoftmax();

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
    model, micro_op_resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  interpreter->AllocateTensors();

  // Set model input settings
  TfLiteTensor *model_input = interpreter->input(0);
  if ((model_input->dims->size != 4) || (model_input->dims->data[0] != 1)
      || (model_input->dims->data[1] != raster_height)
      || (model_input->dims->data[2] != raster_width)
      || (model_input->dims->data[3] != raster_channels)
      || (model_input->type != kTfLiteInt8)) {
    TF_LITE_REPORT_ERROR(error_reporter, "Bad input tensor parameters in model");
    return;
  }

  // Set model output settings
  TfLiteTensor *model_output = interpreter->output(0);
  if ((model_output->dims->size != 2) || (model_output->dims->data[0] != 1)
      || (model_output->dims->data[1] != label_count)
      || (model_output->type != kTfLiteInt8)) {
    TF_LITE_REPORT_ERROR(error_reporter, "Bad output tensor parameters in model");
    return;
  }
  gpio_put(25, !gpio_get(25));

/* initialize the MPU6050 */
  i2c_init(i2c1, 400 * 1000);
  gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA_PIN);
  gpio_pull_up(I2C_SCL_PIN);
  // Make the I2C pins available to picotool
  bi_decl(bi_2pins_with_func(I2C_SDA_PIN, I2C_SCL_PIN, GPIO_FUNC_I2C)); // use GP2 (SDA) and GP3 (SCL)

  // set up the address control pins
  // gpio_set_dir(ADDR_PIN1, GPIO_OUT);
  // gpio_set_dir(ADDR_PIN2, GPIO_OUT);
  // gpio_put(ADDR_PIN1, 0);
  // gpio_put(ADDR_PIN2, 1);
  // printf("Finish initialize MPU6050! Reading raw data from registers...\n");
  // estimate the gravity in ICM42622

}

void adc_reading(){

}