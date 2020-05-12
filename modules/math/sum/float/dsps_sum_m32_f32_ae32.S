// Copyright 2018-2019 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License. 


// This is a 32bit-masked array sum for ESP32 processor.
    .text
    .align  4
    .global dsps_sum_m32_f32_ae32
    .type   dsps_sum_m32_f32_ae32,@function
// The function implements the following C code:
//esp_err_t dsps_sum_m8_f32_ansi(const float *input, const float *mask, float *output, int len, int step_in, int step_mask)
//{
//    float acc = 0;
//    for (int i = 0 ; i < len ; i++) {
//        acc += input[i * step_in] * mask[i * step_mask];
//    }
//    *output = acc;
//    return ESP_OK;
//}

dsps_sum_m32_f32_ae32:
// input    - a2
// mask     - a3
// output   - a4
// len      - a5
// step_in  - a6
// step_mask- a7

    entry	a1, 16
    
    slli 	a6, a6, 2    // a6 - step_in<<2
    slli 	a7, a7, 2    // a7 - step_mask<<2

    // init acc to 0
    movi.n  a8, 0
    wfr     f2, a8

    // Version without dotprod method
    loopnez a5, loop_end_sum_m32_f32_ae32
        lsxp    f0, a2, a6  // load input in f0 and post-incr with step_in
        lsxp    f1, a3, a7  // load mask in f1 and post-incr with step_mask
        madd.s  f2, f1, f0  // f2 += f1 * f0

loop_end_sum_m32_f32_ae32:
    ssi     f2, a4, 0   // store result in output
    movi.n	a2, 0       // return status ESP_OK
    retw.n