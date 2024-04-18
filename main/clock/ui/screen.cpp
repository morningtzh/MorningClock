
#include "screen.hpp"
#include "memory"
#include "ui/components/emoji.hpp"
#include <esp_log.h>

static const char *MODULE = "Screen";

namespace screen
{
    Screen::Screen()
    {
        buffer = RGB8::MakeMartix(size);

        drawer = new Drawer(size, buffer);
        mainComponent = new MainComponent(drawer);

        Size s(8,8);
        Point p(8,0);
        auto e = new EmojiTest(p, s, mainComponent);
        mainComponent->AddComponent(e);

         p=Point(20,0);
         auto e2 = new Emoji(p, s, mainComponent);
        e2->SetEmoji(EmojiName::D);
        mainComponent->AddComponent(e2);




        Size s1(1,1);
            Point p1(2,2);
            auto pi1 = new CPoint(p1, s1, mainComponent);
            pi1->SetColor(255,0,0);
            mainComponent->AddComponent(pi1);

        Point p2(3,3);
        auto pi2 = new CPoint(p2, s1, mainComponent);
        pi2->SetColor(0,255,0);
        mainComponent->AddComponent(pi2);

        Point p3(4,4);
        auto pi3 = new CPoint(p3, s1, mainComponent);
        pi3->SetColor(0,0,255);
        mainComponent->AddComponent(pi3);
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