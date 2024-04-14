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

std::string Size::toString() {
    return std::format("GetSize[{},{}]", w,h);
}

bool Size::operator<(const Size &b) const {
    return (h < b.h) && (w < b.w);
}
