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

#include "dsps_sum.h"


inline esp_err_t dsps_sum_m8_f32_ansi(const float *input, const uint8_t *mask, float *output, int len, int step_in, int step_mask)
{
    if (NULL == input) return ESP_ERR_DSP_PARAM_OUTOFRANGE;
    if (NULL == output) return ESP_ERR_DSP_PARAM_OUTOFRANGE;

    float acc = 0;

    for (int i = 0 ; i < len ; i++) {
        acc += input[i * step_in] * mask[i * step_mask];
    }
    *output = acc;
    return ESP_OK;
}
