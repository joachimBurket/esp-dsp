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

#ifndef _dsps_sum_H_
#define _dsps_sum_H_
#include "dsp_err.h"


#ifdef __cplusplus
extern "C"
{
#endif


/**@{*/
/**
 * @brief   sum an array's members
 * 
 * The function sums the members of an array
 * out += input1[i*step1]; i=[0..len)
 * The implementation use ANSI C and could be compiled and run on any platform
 *
 * @param[in] input: input array
 * @param output: output sum
 * @param len: length of the array
 * @param step_in: step over input array (by default should be 1)
 *
 * @return
 *      - ESP_OK on success
 *      - One of the error codes from DSP library
 */
esp_err_t dsps_sum_f32_ansi(const float *input, float *output, int len, int step_in);
esp_err_t dsps_sum_f32_ae32(const float *input, float *output, int len, int step_in);
/**@}*/


/**@{*/
/**
 * @brief   sum an array's members depending on a float 32bit mask (slightly faster)
 *
 * The function sums the members of an array according to a mask array
 * out += if(mask[i*step_in]) input[i*step_mask]; i=[0..len)
 * The implementation use ANSI C and could be compiled and run on any platform
 *
 * @param[in] input: input array
 * @param[in] mask: mask array
 * @param output: output sum
 * @param len: length of the array
 * @param step_in: step over input array (by default should be 1)
 * @param step_mask: step over mask array (by default should be 1)
 *
 * @return
 *      - ESP_OK on success
 *      - One of the error codes from DSP library
 */
esp_err_t dsps_sum_m32_f32_ansi(const float *input, const float *mask, float *output, int len, int step_in, int step_mask);
esp_err_t dsps_sum_m32_f32_ae32(const float *input, const float *mask, float *output, int len, int step_in, int step_mask);
/**@}*/

/**@{*/
/**
 * @brief   sum an array's members depending on a 8bit mask (slower due to conversion to float)
 *
 * The function sums the members of an array according to a mask array
 * out += if(mask[i*step_mask]) input[i*step_in]; i=[0..len)
 * The implementation use ANSI C and could be compiled and run on any platform
 *
 * @param[in] input: input array
 * @param[in] mask: mask array (Must be in uint8_t!)
 * @param output: output sum
 * @param len: length of the array
 * @param step_in: step over input array (by default should be 1)
 * @param step_mask: step over mask array (by default should be 1)
 *
 * @return
 *      - ESP_OK on success
 *      - One of the error codes from DSP library
 */
esp_err_t dsps_sum_m8_f32_ansi(const float *input, const uint8_t *mask, float *output, int len, int step_in, int step_mask);
esp_err_t dsps_sum_m8_f32_ae32(const float *input, const uint8_t *mask, float *output, int len, int step_in, int step_mask);
/**@}*/


#ifdef __cplusplus
}
#endif


#ifdef CONFIG_DSP_OPTIMIZED
#define dsps_sum_f32 dsps_sum_f32_ae32
#define dsps_sum_m8_f32 dsps_sum_m8_f32_ae32
#define dsps_sum_m32_f32 dsps_sum_m32_f32_ae32
#endif
#ifdef CONFIG_DSP_ANSI
#define dsps_sum_f32 dsps_sum_f32_ansi
#define dsps_sum_m8_f32 dsps_sum_m8_f32_ansi
#define dsps_sum_m32_f32 dsps_sum_m32_f32_ansi
#endif

#endif // _dsps_sum_H_