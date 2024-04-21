//
// Created by MorningTZH on 2024/4/17.
//

#ifndef MORNINGRING_PNG_READER_HPP
#define MORNINGRING_PNG_READER_HPP

#include "../base.hpp"

int PngReadPart(const char *path, const Point &p, const Size &s, RGB8 **buffer);

#endif //MORNINGRING_PNG_READER_HPP
