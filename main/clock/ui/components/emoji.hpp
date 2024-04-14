//
// Created by MorningTZH on 2024/4/15.
//

#ifndef MORNINGRING_EMOJI_HPP
#define MORNINGRING_EMOJI_HPP

#include "component.hpp"

class Emoji : public BaseComponent {

public:
    Emoji(Point location, Size s, BaseComponent *p) : BaseComponent(location, s,p) {};

    Emoji(Drawer *d) : BaseComponent(d) {};

    bool Update() override;
};


#endif //MORNINGRING_EMOJI_HPP
