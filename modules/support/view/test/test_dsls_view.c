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

#include <string.h>
#include "unity.h"
#include "test_utils.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portable.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_clk.h"
#include "esp_log.h"
#include "soc/cpu.h"

#include "dsls_view.h"


static const char *TAG = "dsls_view";

static float data[1024];

TEST_CASE("dsls_view functionality", "[dsls]")
{
    for (int i = 0 ; i < 1024 ; i++) {
        data[i] = -100;
    }
    data[256] = 0;
    dsls_view_spectrum(data, 1024, -100, 0);

    ESP_LOGI(TAG, "Just a check\n");
}