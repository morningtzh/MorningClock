//
// Created by MorningTZH on 2024/4/15.
//

#include "emoji.hpp"

bool Emoji::Update() {

        Point p(0,0);
        RGB8 r(199,199,100);
        drawer->DrawRGB(p,r);


    return BaseComponent::Update();
}
