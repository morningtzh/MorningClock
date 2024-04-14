
#include "screen.hpp"
#include "memory"
#include "ui/components/emoji.hpp"
#include <esp_log.h>

static const char *MODULE = "MODE";

namespace screen
{
    Screen::Screen()
    {
        buffer = new RGB8*[width];
        for(int i = 0; i < width; i++) {
            buffer[i] = new RGB8[height];
        }

        drawer = new Drawer(Size(width, height), buffer);
        mainComponent = new MainComponent(drawer);

        Size s(1,1);
        for (int i = 0; i < 8; ++i) {
            Point p(i,i);
            auto e = new Emoji(p, s, mainComponent);
            mainComponent->AddComponent(e);
        }

        Point p(2,4);
        auto e = new Emoji(p, s, mainComponent);
        mainComponent->AddComponent(e);
    }

    RGB8 *Screen::GetPoint(uint x, uint y) {
        if (x >= width || y >= height) {
            ESP_LOGE(MODULE, "Get Screen Point not on board(%u,%u): {%u,%u}", width, height, x,y);
            return nullptr;
        }

        if (buffer == nullptr) {
            ESP_LOGE(MODULE, "Get Screen Point buffer(%p) is null", buffer);
            return nullptr;
        }

        if (buffer[x] == nullptr) {
            ESP_LOGE(MODULE, "Get Screen Point buffer x(%p) is null", buffer[x]);
            return nullptr;
        }

        return &(buffer[x][y]);
    }

    bool Screen::Update() {

        mainComponent->Update();

        return false;
    }

    Screen::~Screen() {
        delete mainComponent;
        delete drawer;
        delete buffer;
    }
}