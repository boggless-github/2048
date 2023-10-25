#ifndef GAME2048
#define GAME2048
#include <Screen.hpp>

class Game2048{
    public:
    class Tile : public Screen{
        int value; // 0 means empty
        static const char *fmts[16];
        static const char *nums[16];

        public:
        int GetValue();
        void SetValue(int value); 
    };

    Screen screen;
    Screen board_screen;
    Tile *board;
    Tile title;

    bool finish;

    int score;
    int rows, cols;

    void restart();

    void move_left();
    void move_right();
    void move_up();
    void move_down();

    bool move(char dir);

    int get_score();

    void spawn_tile();

    Game2048(int rows=4, int cols=4);
    ~Game2048();

    void display_console();
};
#endif