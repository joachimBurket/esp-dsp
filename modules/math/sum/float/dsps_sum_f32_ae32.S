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

#include "dsps_dotprod_f32_m_ae32.S"

// This is a simple array sum for ESP32 processor.
    .text
    .align  4
    .global dsps_sum_f32_ae32
    .type   dsps_sum_f32_ae32,@function
// The function implements the following C code:
//esp_err_t dsps_sum_f32_ansi(const float *input, float *output, int len, int step_in)
//{
//    float acc = 0;
//    for (int i = 0 ; i < len ; i++) {
//        acc += input[i * step_in];
//    }
//    *output = acc;
//    return ESP_OK;
//}

dsps_sum_f32_ae32:
// input    - a2
// output   - a3
// len      - a4
// step_in  - a5

    entry	a1, 16
    
    slli 	a5, a5, 2    // a5 - step_in<<2

    // init acc to 0
    movi.n  a6, 0
    wfr     f2, a6

    // load 1 into f1
    movi.n  a6, 1
    ufloat.s f1, a6, 0

    // Version without accumulator
    //loopnez a4, loop_end_sum_f32_ae32
    //    lsxp     f0, a2, a5     // load input in f0 and post-increment with step
    //    mov.s    f2, f1         // copy sum in f1
    //    add.s    f1, f2, f0     // f2 = f1 + f0

    // Version with accumulator (faster)
    loopnez a4, loop_end_sum_f32_ae32
        lsxp    f0, a2, a5  // load input in f0 and post-incr with step_in
        madd.s  f2, f1, f0  // f2 += f1 * f0


loop_end_sum_f32_ae32:
    ssi     f2, a3, 0   // store result in output
    movi.n	a2, 0       // return status ESP_OK
    retw.n
