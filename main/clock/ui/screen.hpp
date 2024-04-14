#include "../../base.hpp"
#include "components/component.hpp"

namespace screen {
    constexpr unsigned short width = 32;
    constexpr unsigned short height = 8;

    typedef bool (*Render)(int, int);

    class Screen {
    private:
        RGB8 **buffer;
        Drawer *drawer;
        bool dirty = true;
        MainComponent *mainComponent;

    public:
        Size size {
            width, height
        };
        RGB8 *GetPoint(uint x, uint y);

        RGB8 **GetBuffer() {
            return buffer;
        }

        bool isDirty() {
            return dirty;
        }

        Screen(/* args */);

        bool Update();

        ~Screen();
    };

}