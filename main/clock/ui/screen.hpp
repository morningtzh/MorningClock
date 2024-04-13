

namespace screen
{
    constexpr unsigned short width = 32;
    constexpr unsigned short height = 8;

    struct RGB8
    {
        uint8_t r,g,b;
    };

    class Screen
    {
    private:
        RGB8 *buffer[width][height];

    public:
        int *GetBuffer();
        Screen(/* args */);
        ~Screen();
    };

}