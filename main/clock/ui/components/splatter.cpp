//
// Created by MorningTZH on 2024/4/19.
//

#include <esp_log.h>
#include <cstring>
#include "png_reader.hpp"
#include "splatter.hpp"

static const char *MODULE = "UISplatter";


const char *SPLATTER_FILE = "/assets/images/Splatter-rgba.png";

Point CalcLocation(uint8_t index) {

    Point p;

    uint8_t x = index % 5;
    uint8_t y = index / 5;

    p.x = x * 16;
    p.y = y * 8;

    return p;
}

Splatter::Splatter(Point location, Size s, BaseComponent *p) : BaseComponent(location, s, p) {

    ESP_LOGI(MODULE, "Init");

    // 清空内存
    memset(buffer, 0, sizeof(&buffer));

    ESP_LOGI(MODULE, "Alloc frame buffer");

//    for (int i = 0; i < SplatterAction::BUTT; i++) {
//        for (int j = 0; j < MAX_FRAME_EVERY_ACTION; ++j) {
//            int _frameIndex = SplatterActionFrame[i][j];
//            if (_frameIndex == -1) { continue; }
//            if (buffer[_frameIndex] == nullptr) {
//
//                int _frameIndex = 2;
//
//                ESP_LOGI(MODULE, "will read frame %d", _frameIndex);
//
////                buffer[_frameIndex] = RGB8::MakeMartix(Splatter::size);
//
//    auto tmp = RGB8::MakeMartix(size);
//
//                Point _location = CalcLocation(_frameIndex);
//
//                ESP_LOGI(MODULE, "Frame %d Location is %s", _frameIndex, _location.toString().c_str());
//
//                PngReadPart(SPLATTER_FILE, _location, size, tmp);
//
//                ESP_LOGI(MODULE, "Frame  %d ok", _frameIndex);
//            }
//        }
//    }

    ESP_LOGI(MODULE, "Alloc frame buffer finish");

}

bool Splatter::Update() {

    auto playFrame = SplatterActionFrame[action][frameIndex];

    if (buffer[playFrame] == nullptr) {
        ESP_LOGE(MODULE, "update action %d, frame %d failed, buffer %d is null", action, frameIndex, playFrame);
        return false;
    }

    drawer->DrawBuffer(Splatter::size, buffer[playFrame]);

    frameIndex++;
    if (frameIndex >=MAX_FRAME_EVERY_ACTION || SplatterActionFrame[action][frameIndex] == -1) {
        frameIndex = 0;
    }

    return BaseComponent::Update();
}

bool Splatter::FreeActionBuffer(SplatterAction a) {

    for (int j = 0; j < MAX_FRAME_EVERY_ACTION; ++j) {
        int _frameIndex = SplatterActionFrame[a][j];
        if (_frameIndex == -1) { continue; }
        if (buffer[_frameIndex] != nullptr) {

            ESP_LOGI(MODULE, "will free frame %d", _frameIndex);

            RGB8::FreeMartix(buffer[_frameIndex],size);
            buffer[_frameIndex] = nullptr;

            ESP_LOGI(MODULE, "Frame free %d ok", _frameIndex);
        }
    }

    return true;
}

bool Splatter::SetAction(SplatterAction a) {

    ESP_LOGI(MODULE, "Set Action to %d", a);

    FreeActionBuffer(action);

    action = a;
    frameIndex = 0;

    for (int j = 0; j < MAX_FRAME_EVERY_ACTION; ++j) {
        int _frameIndex = SplatterActionFrame[a][j];
        if (_frameIndex == -1) { continue; }
        if (buffer[_frameIndex] == nullptr) {

            ESP_LOGI(MODULE, "will read frame %d", _frameIndex);

            buffer[_frameIndex] = RGB8::MakeMartix(Splatter::size);

            auto tmp = RGB8::MakeMartix(size);

            Point _location = CalcLocation(_frameIndex);

            ESP_LOGI(MODULE, "Frame %d Location is %s", _frameIndex, _location.toString().c_str());

            Size s(16,8);
            PngReadPart(SPLATTER_FILE, _location, s, buffer[_frameIndex]);

            ESP_LOGI(MODULE, "Frame  %d ok", _frameIndex);
        }
    }


    return true;
}


