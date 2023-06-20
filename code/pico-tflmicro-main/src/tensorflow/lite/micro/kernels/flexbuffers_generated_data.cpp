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

// This file is generated. See:
// tensorflow/lite/micro/kernels/detection_postprocess_test/README.md

#include "tensorflow/lite/micro/kernels/flexbuffers_generated_data.h"

const int g_gen_data_size_none_regular_nms = 242;
const unsigned char g_gen_data_none_regular_nms[] = {
    0x6d, 0x61, 0x78, 0x5f, 0x64, 0x65, 0x74, 0x65, 0x63, 0x74, 0x69, 0x6f,
    0x6e, 0x73, 0x00, 0x6d, 0x61, 0x78, 0x5f, 0x63, 0x6c, 0x61, 0x73, 0x73,
    0x65, 0x73, 0x5f, 0x70, 0x65, 0x72, 0x5f, 0x64, 0x65, 0x74, 0x65, 0x63,
    0x74, 0x69, 0x6f, 0x6e, 0x00, 0x64, 0x65, 0x74, 0x65, 0x63, 0x74, 0x69,
    0x6f, 0x6e, 0x73, 0x5f, 0x70, 0x65, 0x72, 0x5f, 0x63, 0x6c, 0x61, 0x73,
    0x73, 0x00, 0x75, 0x73, 0x65, 0x5f, 0x72, 0x65, 0x67, 0x75, 0x6c, 0x61,
    0x72, 0x5f, 0x6e, 0x6d, 0x73, 0x00, 0x6e, 0x6d, 0x73, 0x5f, 0x73, 0x63,
    0x6f, 0x72, 0x65, 0x5f, 0x74, 0x68, 0x72, 0x65, 0x73, 0x68, 0x6f, 0x6c,
    0x64, 0x00, 0x6e, 0x6d, 0x73, 0x5f, 0x69, 0x6f, 0x75, 0x5f, 0x74, 0x68,
    0x72, 0x65, 0x73, 0x68, 0x6f, 0x6c, 0x64, 0x00, 0x6e, 0x75, 0x6d, 0x5f,
    0x63, 0x6c, 0x61, 0x73, 0x73, 0x65, 0x73, 0x00, 0x79, 0x5f, 0x73, 0x63,
    0x61, 0x6c, 0x65, 0x00, 0x78, 0x5f, 0x73, 0x63, 0x61, 0x6c, 0x65, 0x00,
    0x68, 0x5f, 0x73, 0x63, 0x61, 0x6c, 0x65, 0x00, 0x77, 0x5f, 0x73, 0x63,
    0x61, 0x6c, 0x65, 0x00, 0x0b, 0x78, 0x12, 0x94, 0xa4, 0x43, 0x58, 0x33,
    0x6a, 0x11, 0x22, 0x2b, 0x0b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x0b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x40,
    0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xa0, 0x40, 0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0x20, 0x41,
    0x06, 0x0e, 0x06, 0x06, 0x0e, 0x0e, 0x06, 0x6a, 0x0e, 0x0e, 0x0e, 0x37,
    0x26, 0x01,
};
const int g_gen_data_size_regular_nms = 242;
const unsigned char g_gen_data_regular_nms[] = {
    0x6d, 0x61, 0x78, 0x5f, 0x64, 0x65, 0x74, 0x65, 0x63, 0x74, 0x69, 0x6f,
    0x6e, 0x73, 0x00, 0x6d, 0x61, 0x78, 0x5f, 0x63, 0x6c, 0x61, 0x73, 0x73,
    0x65, 0x73, 0x5f, 0x70, 0x65, 0x72, 0x5f, 0x64, 0x65, 0x74, 0x65, 0x63,
    0x74, 0x69, 0x6f, 0x6e, 0x00, 0x64, 0x65, 0x74, 0x65, 0x63, 0x74, 0x69,
    0x6f, 0x6e, 0x73, 0x5f, 0x70, 0x65, 0x72, 0x5f, 0x63, 0x6c, 0x61, 0x73,
    0x73, 0x00, 0x75, 0x73, 0x65, 0x5f, 0x72, 0x65, 0x67, 0x75, 0x6c, 0x61,
    0x72, 0x5f, 0x6e, 0x6d, 0x73, 0x00, 0x6e, 0x6d, 0x73, 0x5f, 0x73, 0x63,
    0x6f, 0x72, 0x65, 0x5f, 0x74, 0x68, 0x72, 0x65, 0x73, 0x68, 0x6f, 0x6c,
    0x64, 0x00, 0x6e, 0x6d, 0x73, 0x5f, 0x69, 0x6f, 0x75, 0x5f, 0x74, 0x68,
    0x72, 0x65, 0x73, 0x68, 0x6f, 0x6c, 0x64, 0x00, 0x6e, 0x75, 0x6d, 0x5f,
    0x63, 0x6c, 0x61, 0x73, 0x73, 0x65, 0x73, 0x00, 0x79, 0x5f, 0x73, 0x63,
    0x61, 0x6c, 0x65, 0x00, 0x78, 0x5f, 0x73, 0x63, 0x61, 0x6c, 0x65, 0x00,
    0x68, 0x5f, 0x73, 0x63, 0x61, 0x6c, 0x65, 0x00, 0x77, 0x5f, 0x73, 0x63,
    0x61, 0x6c, 0x65, 0x00, 0x0b, 0x78, 0x12, 0x94, 0xa4, 0x43, 0x58, 0x33,
    0x6a, 0x11, 0x22, 0x2b, 0x0b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x0b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x40,
    0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xa0, 0x40, 0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0x20, 0x41,
    0x06, 0x0e, 0x06, 0x06, 0x0e, 0x0e, 0x06, 0x6a, 0x0e, 0x0e, 0x0e, 0x37,
    0x26, 0x01,
};
