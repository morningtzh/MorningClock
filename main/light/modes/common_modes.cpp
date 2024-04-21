//
// Created by MorningTZH on 2023/1/22.
//
#include <exception>
#include <esp_log.h>
#include "light.hpp"
#include "mode.hpp"
#include "common_modes.hpp"

static const char *MODULE = "MODE";

namespace light::mode {

    ConfigData HSVRing::defaultConfig{
            {"InsideRingDirect",  {CLOCKWISE}},
            {"OutsideRingDirect", {COUNTERCLOCKWISE}},
            {"InsideRingStep",    {1}},
            {"OutsideRingStep",   {2}},
    };

    Screen::Screen(light::LightBuffer &lightBuffer, bool start) : Mode(lightBuffer) {

        ESP_LOGI(MODULE, "Start Mode: Screen");
        screen = new screen::Screen();

        ESP_LOGI(MODULE, "Screen transBuffer");

        transBuffer();

    };

    void Screen::CalculateNext() {
        ESP_LOGI(MODULE, "Screen CalculateNext Update");

        screen->Update();
        ESP_LOGI(MODULE, "Screen transBuffer");

        transBuffer();
    }

    bool Screen::transBuffer() {
        try {
            for (int i = 0; i < screen->size.w; ++i) {
                for (int j = 0; j < screen->size.h; ++j) {
                    auto rgb = screen->GetPoint(i, j);
                    if (rgb == nullptr) {
                        ESP_LOGE(MODULE, "screen->GetPoint failed [%d, %d]", i, j);
                        return false;
                    }

                    int index = ((screen->size.w - 1) - i) * screen->size.h + j;
                    lightBuffer.SetRGB(INSIDE_RING, index, rgb);
                }
            }
        } catch (std::exception &e) {
            ESP_LOGE(MODULE, "Mode Screen transBuffer failed: %s", e.what());
        }

        try {

            // Test
            for (int j = 0; j < screen->size.h; ++j) {
                for (int i = 0; i < screen->size.w; ++i) {
                    auto rgb = screen->GetPoint(i, j);
                    if (rgb == nullptr) {
                        ESP_LOGE(MODULE, "screen->GetPoint failed [%d, %d]", i, j);
                        return false;
                    }

                    printf("%d", rgb->b > 0);
                }
                printf("\n");
            }
        } catch (std::exception &e) {
            ESP_LOGE(MODULE, "Mode Screen transBuffer failed: %s", e.what());
        }

        return true;
    }



}