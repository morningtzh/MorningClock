//
// Created by MorningTZH on 2024/4/15.
//

#include "emoji.hpp"
#include <esp_log.h>
#include "../../../base.hpp"
#include "png_reader.hpp"
#include <map>

static const char *MODULE = "UIEmoji";

bool Emoji::Update() {

    drawer->DrawBuffer(GetSize(), buffer);

    return BaseComponent::Update();
}

Emoji::Emoji(Point location, Size s, BaseComponent *p)  : BaseComponent(location, s,p) {
    ESP_LOGI(MODULE, "Init");
    buffer = RGB8::MakeMartix(s);
    ESP_LOGI(MODULE, "Emoji at %s", drawer->GetAbsolutLocation().toString().c_str());

}

Point CalcLocation(EmojiName &e) {

    Point p;

    uint8_t x = e % 10;
    uint8_t y = e / 10;

    p.x = 3 + x * 13;
    p.y = 3 + y * 12;

    return p;
}

const char *EMOJI_FILE = "/assets/images/emojis-rgba.png";

bool Emoji::SetEmoji(EmojiName e) {
    ESP_LOGI(MODULE, "Set Emoji to %d", e);

    emoji = e;

    Point location = CalcLocation(e);
    Size s(8,8);

    ESP_LOGI(MODULE, "Location is %s", location.toString().c_str());


    PngReadPart(EMOJI_FILE, location, s, buffer);

    dirty = true;

    return false;
}

EmojiTest::EmojiTest(Point location, Size s, BaseComponent *p) : BaseComponent(location, s, p) {

    e = new Emoji(location, s, p);
    e->SetEmoji(emoji);

    AddComponent(e);
}

bool EmojiTest::Update() {

    emoji = static_cast<EmojiName>(emoji + 1);
    if ((int)emoji > 100) {
        emoji = EmojiName::GUEST;
    }

    e->SetEmoji(emoji);

    return BaseComponent::Update();
}
