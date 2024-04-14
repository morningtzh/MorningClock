//
// Created by MorningTZH on 2024/4/14.
//

#ifndef MORNINGRING_COMPONENT_HPP
#define MORNINGRING_COMPONENT_HPP

#include <list>

#include "../../../base.hpp"



//typedef bool (*Draw)(uint16_t x, uint16_t y, RGB8 *rgb);
//
//Draw *MakeDraw(uint16_t x, uint16_t y, uint16_t w, uint16_t h, RGB8 *buffer) {
//    return [x,y,w,h, &buffer](uint16_t _x, uint16_t _y, RGB8 *rgb)-> bool {
//        if ((_x < x || _x >= x + w) ||
//                (_y < y || _y >= y + h)) {
//            return false;
//        }
//        memcpy(buffer[_x][_y], rgb);
//    }
//}
//
//#define AddComponent(x,y,w,h,c) c(MakeDraw(x,y,w,h,buffer))

class Drawer {
private:

    RGB8 **buffer;

    // 绝对地址
    Point _absolutLocation;

    // 相对地址
    Point _relativeLocation;

    // 大小
    Size _size;

public:
    // 绝对坐标创建
    Drawer(Size size, RGB8 **buffer):
    buffer(buffer) , _absolutLocation(0,0), _relativeLocation(0,0), _size(size){};

    // 双坐标创建
    Drawer(Point absolutLocation, Point _relativeLocation, Size size, RGB8 **buffer):
            buffer(buffer) , _absolutLocation(absolutLocation), _relativeLocation(_relativeLocation), _size(size){};


    // 传入相对坐标
    Drawer *Sub(Point relativeLocation, Size size) ;

    const Size &GetSize();


    bool DrawRGB(Point &p, RGB8 &rgb);
//
//    RGB8 &GetRGB(Point &p) {
//
//        return buffer[p.x][p.y];
//    }

    bool SetHSV(Point &p, uint16_t h, uint8_t s, uint8_t v);

};

class BaseComponent {
private:
    std::list<BaseComponent *>  sons;
    bool dirty = true;

protected:
    Drawer *drawer;

public:
    BaseComponent(Drawer *drawer): drawer(drawer) {}
    BaseComponent(Point location, Size s, BaseComponent *p): drawer(p->drawer->Sub(location, s)) {}

    virtual ~BaseComponent();

    const Size &GetSize();

    virtual bool Update();

    bool isDirty() {
        return dirty;
    }

    bool AddComponent(BaseComponent *son);

//    template<typename T>
//    bool AddComponent<T>(Point &location, Size &size);
};

class MainComponent: public BaseComponent { ;

public:
    explicit MainComponent(Drawer *d): BaseComponent(d){}

    bool Update() override;
};


#endif //MORNINGRING_COMPONENT_HPP
