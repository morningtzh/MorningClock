//
// Created by MorningTZH on 2024/4/14.
//

#include "base.hpp"

Point::Point(uint16_t x, uint16_t y): x(x), y(y) {};

Point Point::operator+(const Point &b) const {
    return Point(x + b.x, y + b.y);
}

bool Point::operator<(const Size &b) const {
    return x < b.w && y < b.h;
}

bool Point::operator>(const Size &b) const {
    return x > b.w && y > b.h;
}
bool Point::operator<=(const Size &b) const {
    return x < b.w && y < b.h;
}

bool Point::operator>=(const Size &b) const {
    return x >= b.w && y >= b.h;
}

const std::string Size::toString() const {
    return std::format("GetSize[{},{}]", w,h);
}

bool Size::operator<(const Size &b) const {
    return (h < b.h) && (w < b.w);
}

bool Size::operator>(const Size &b) const {
    return (h > b.h) && (w > b.w);
}

bool Size::operator<=(const Size &b) const {
    return (h > b.h) && (w > b.w);
}

bool Size::operator>=(const Size &b) const {
    return (h > b.h) && (w > b.w);
}

RGB8 **RGB8::MakeMartix(Size size) {

    RGB8 **buffer = new RGB8*[size.w];
    for(int i = 0; i < size.w; i++) {
        buffer[i] = new RGB8[size.h];
    }

    return buffer;
}

void RGB8::FreeMartix(RGB8 **buffer, Size size) {
    for(int i = 0; i < size.w; i++) {
        delete buffer[i];
    }

    delete buffer;
}
