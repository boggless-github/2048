class Game2048{
    public:
    class Tile{
        int value; // 0 means empty
        int pos_x, pos_y;
    };

    Tile board[16];

    int score;

    void restart();

    void move_left();
    void move_right();
    void move_up();
    void move_down();

    int get_score();

    void spawn_tile();
};