//
// Created by MorningTZH on 2024/4/14.
//

#ifndef MORNINGRING_BASE_HPP
#define MORNINGRING_BASE_HPP


#include <cstdint>
#include <string>
#include <format>

struct Size {
    uint16_t w, h;

    const std::string toString() const;

    bool operator<(const Size &b) const;

    bool operator>(const Size &b) const;

    bool operator<=(const Size &b) const;

    bool operator>=(const Size &b) const;
};

struct Point {
    uint16_t x, y;

    std::string toString() const {
        return std::format("Point[{},{}]", x, y);
    }

    Point() = default;

    Point(uint16_t x, uint16_t y);

    Point operator+(const Point &b) const;

    bool operator<(const Size &b) const;

    bool operator>(const Size &b) const;

    bool operator<=(const Size &b) const;

    bool operator>=(const Size &b) const;
};

struct RGB8 {
    uint8_t r, g, b;
    bool mask = false;
    RGB8():r(0), g(0), b(0){}
    RGB8(uint8_t r,uint8_t g,uint8_t b):r(r), g(g), b(b){}

    static RGB8 **MakeMartix(Size size);

    static void FreeMartix(RGB8 **buffer, Size size);
};

#endif //MORNINGRING_BASE_HPP
