//
// Created by MorningTZH on 2024/4/15.
//

#ifndef MORNINGRING_EMOJI_HPP
#define MORNINGRING_EMOJI_HPP

#include "component.hpp"

#include <png.h>

// Emoji from IoT-Emoji-Sign
// https://github.com/moononournation/IoT-Emoji-Sign
enum EmojiName {
    GUEST = 0,
    B,C,D,E,F,G,H,I,J,K,L,M, N
};

class Emoji : public BaseComponent {

private:
    EmojiName emoji;
    RGB8 **buffer = nullptr;
    uint8_t **alpha = nullptr;

public:
    Emoji(Point location, Size s, BaseComponent *p);

    Emoji(Drawer *d) : BaseComponent(d) {};

    bool SetEmoji(EmojiName e);

    bool Update() override;
};

class EmojiTest : public BaseComponent {

private:
    EmojiName emoji = EmojiName::GUEST;
    Emoji *e;

public:
    EmojiTest(Point location, Size s, BaseComponent *p);

    EmojiTest(Drawer *d) : BaseComponent(d) {};

    bool Update() override;
};


#endif //MORNINGRING_EMOJI_HPP
