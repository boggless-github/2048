#define ROWS    4
#define COLS    4
#define TILES   ROWS*COLS
#define INDEX(r,c) r*COLS+c
class Game2048{
    public:
    struct Tile{
        int value; // 0 means empty
    };

    Tile board[TILES];

    int score;

    void restart();

    void move_left();
    void move_right();
    void move_up();
    void move_down();

    bool move(char dir);

    int get_score();

    void spawn_tile();

    Game2048();

    void display_console();
};