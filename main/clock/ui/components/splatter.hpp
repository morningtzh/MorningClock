//
// Created by MorningTZH on 2024/4/19.
//

#ifndef MORNINGRING_SPLATTER_HPP
#define MORNINGRING_SPLATTER_HPP


#include "component.hpp"

enum SplatterAction {
    WALK,
    BAT,
    CLEAVER,
    PUNCH,
    SHOOT,
    BUTT,
};

const uint8_t MAX_FRAME_EVERY_ACTION = 5;

const int SplatterActionFrame[SplatterAction::BUTT][MAX_FRAME_EVERY_ACTION] {
        {0,15,-1,-1,-1},
        {2,5,4,-1,-1},
        {5,6,7,8,9},
        {10,12,11,-1,-1},
        {1,16,-1,-1,-1}
};

const uint8_t MAX_FRAME = SplatterAction::BUTT * MAX_FRAME_EVERY_ACTION;

class Splatter:public BaseComponent {

private:
    SplatterAction action = SplatterAction::WALK;
    int frameIndex = 0;
    RGB8 **buffer[20];

    bool FreeActionBuffer(SplatterAction a);

public:

    constexpr static const Size size = {16, 8};

    Splatter(Point location, Size s, BaseComponent *p);

    Splatter(Drawer *d) : BaseComponent(d) {};

    bool SetAction(SplatterAction a);


    bool Update() override;
};


#endif //MORNINGRING_SPLATTER_HPP
