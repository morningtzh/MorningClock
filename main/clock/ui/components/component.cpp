//
// Created by MorningTZH on 2024/4/14.
//

#include <memory>
#include <cstring>
#include "esp_log.h"
#include "component.hpp"
#include "fast_hsv2rgb.h"

[[maybe_unused]] static const char *MODULE = "BaseComponent";

bool BaseComponent::Update() {

    for (auto c: sons) {
        c.second->Update();
    }

    dirty = false;

    return true;
}

BaseComponent::~BaseComponent() {
    for (auto c: sons) {
        delete c.second;
    }

    delete drawer;
}

const Size &BaseComponent::GetSize() {
    return drawer->GetSize();
}

bool BaseComponent::AddComponent(const std::string &name, BaseComponent *son) {

    if (son->drawer == nullptr) {
        ESP_LOGE("aa", "AddComponent failed,");
        return false;
    }

    sons[name]=son;

    return true;
}


//template<typename T>
//bool BaseComponent::AddComponent<T>(Point &location, Size &size) {
//
//    auto subDrawer = drawer->Sub(location, size);
//
//    sons.emplace_back(new T(subDrawer));
//
//    return true;
//}

Drawer *Drawer::Sub(Point relativeLocation, Size size) {
    if ((_size.w < relativeLocation.x + size.w) || (_size.h < relativeLocation.y + size.h)) {
        ESP_LOGE(MODULE, "Create sub drawer is bigger %s:%s than self %s",
                 relativeLocation.toString().c_str(), size.toString().c_str(),
                 _size.toString().c_str()
        );
        return nullptr;
    }

    return new Drawer(_absolutLocation + relativeLocation, relativeLocation, size, buffer);
}

bool Drawer::DrawRGB(Point &p, RGB8 &rgb) {

    if (p >= _size) {
        ESP_LOGE(MODULE, "draw %s outside %s", p.toString().c_str(), _size.toString().c_str());
        return false;
    }

    auto absolutionPoint = _absolutLocation + p;

    memcpy(&(buffer[absolutionPoint.x][absolutionPoint.y]), &rgb, sizeof(RGB8));

    return true;
}

bool Drawer::DrawBuffer(const Size &s, RGB8 **b) {

    if (s >= _size) {
        ESP_LOGE(MODULE, "draw buffer %s outside %s", s.toString().c_str(), _size.toString().c_str());
        return false;
    }

    for (int i = 0; i < s.w; ++i) {
        for (int j = 0; j < s.h; ++j) {
            if (b[i][j].mask) {
                continue;
            }
            auto absolutionPoint = _absolutLocation + Point(i, j);

            memcpy(&(buffer[absolutionPoint.x][absolutionPoint.y]), &(b[i][j]), sizeof(RGB8));
        }
    }

    return true;
}

const Size &Drawer::GetSize() {
    return _size;
}

bool Drawer::SetHSV(Point &p, uint16_t h, uint8_t s, uint8_t v) {
    RGB8 rgb;
    fast_hsv2rgb_8bit(h, s, v, &rgb.r, &rgb.g, &rgb.b);

    return DrawRGB(p, rgb);
}

const Point &Drawer::GetAbsolutLocation() {
    return _absolutLocation;
}

const Point &Drawer::GetRelativeLocation() {
    return _relativeLocation;
}

bool Drawer::Clear() {
    for (int i = 0; i < _size.w; ++i) {
        for (int j = 0; j < _size.h; ++j) {
            auto absolutionPoint = _absolutLocation + Point(i, j);
            memset((void *)&(buffer[absolutionPoint.x][absolutionPoint.y]), 0, sizeof(RGB8));
        }
    }
    return true;
}

bool MainComponent::Update() {

    drawer->Clear();

    for (int i = 0; i < GetSize().w; ++i) {
        auto p = Point(i, 0);
        RGB8 rgb(10, 100, 10);
        drawer->DrawRGB(p, rgb);

        p = Point(i, GetSize().h - 1);
        drawer->DrawRGB(p, rgb);
    }

    for (int i = 0; i < GetSize().h; ++i) {
        auto p = Point(0, i);
        RGB8 rgb(100, 10, 10);
        drawer->DrawRGB(p, rgb);

        p = Point(GetSize().w - 1, i);
        drawer->DrawRGB(p, rgb);
    }

    return BaseComponent::Update();
}

bool CPoint::Update() {

    auto p = Point(0, 0);
    drawer->DrawRGB(p, rgb);

    return BaseComponent::Update();
}

void CPoint::SetColor(uint8_t r, uint8_t g, uint8_t b) {
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
}

CPoint::CPoint(Point location, Size s, BaseComponent *p) : BaseComponent(location, s, p) {

}
