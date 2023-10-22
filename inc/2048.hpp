#define ROWS    4
#define COLS    4
#define TILES   ROWS*COLS
#define INDEX(r,c) r*COLS+c
#include <Screen.hpp>

class Game2048{
    public:
    class Tile{
        uint32_t flags;
        uint32_t value;
        Tile *left, *right, *up, *down;

        void goLeft();
        void goRight();
        void goUp();
        void goDown();
    };

    Screen *parent;
    Tile *board;
    int rows, cols;

    int score;

    void restart();

    void move_left();
    void move_right();
    void move_up();
    void move_down();

    bool move(char dir);

    int get_score();

    void spawn_tile();

    Game2048(Screen *parent, int rows, int cols);

    void display_console();
};