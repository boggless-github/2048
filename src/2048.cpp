#include <iostream>
#include <random>
#include <2048.hpp>
#include <string.h>

void Game2048::restart(){
    // set score to 0
    score = 0;
    // make all tiles blank
    for(int i = 0; i < rows*cols; i++){
        board[i].SetValue(0);
    }

    // spawn 2 tiles;
    for(int i = 0; i < 2; i++){
        spawn_tile();
    }

}

void Game2048::move_left(){
    for(int r = 0; r < rows; r++){
        int leftmost = 0;
        for(int c = 0; c < cols; c++){
            int i = c + r * cols;
            int i2 = leftmost + r * cols;
            int value = board[i].GetValue();
            if(value == 0) continue;

            board[i].SetValue(0);
            if(board[i2].GetValue() == 0){
                // This is where it should go
            }
            else if(board[i2].GetValue() == value){
                // Combination case
                value += 1;
                board[i2].SetValue(value);
                score += 1 << value;
                leftmost++; // prevent double combinations
            } else {
                leftmost++;
                i2 = leftmost + r * cols;
            }
            board[i2].SetValue(value);
        }
    }

    spawn_tile();
}
void Game2048::move_right(){
    for(int r = 0; r < rows; r++){
        int rightmost = cols-1;
        for(int c = cols-1; c >= 0; c--){
            int i = c + r * cols;
            int i2 = rightmost + r * cols;
            int value = board[i].GetValue();
            if(value == 0) continue;
            
            board[i].SetValue(0);
            if(board[i2].GetValue() == 0){
                // This is where it should go
            }
            else if(board[i2].GetValue() == value){
                value += 1;
                board[i2].SetValue(value);
                score += 1 << value;
                rightmost--; // prevent double combinations
            } else{
                rightmost--;
                i2 = rightmost + r * cols;
            }
            board[i2].SetValue(value);
        }
    }

    spawn_tile();
}
void Game2048::move_up(){
    for(int c = 0; c < cols; c++){
        int topmost = 0;
        for(int r = 0; r < rows; r++){
            int i = c + r * cols;
            int i2 = c + topmost * cols;
            int value = board[i].GetValue();
            if(value == 0) continue;

            board[i].SetValue(0);
            if(board[i2].GetValue() == 0){
                // This is where it should go
            }
            else if(board[i2].GetValue() == value){
                value += 1;
                board[i2].SetValue(value);
                score += 1 << value;
                topmost++; // prevent double combinations
            } else{
                topmost++;
                i2 = c + topmost * cols;
            }
            board[i2].SetValue(value);
        }
    }

    spawn_tile();
}
void Game2048::move_down(){                 
    for(int c = 0; c < cols; c++){
        int lowest = rows-1;
        for(int r = rows-1; r >= 0; r--){
            int i = c + r * cols;
            int i2 = c + lowest * cols;
            int value = board[i].GetValue();
            if(value == 0) continue;

            board[i].SetValue(0);
            if(board[i2].GetValue() == 0){
                // This is where it should go
            }
            else if(board[i2].GetValue() == value){
                value += 1;
                board[i2].SetValue(value);
                score += 1 << value;
                lowest--; // prevent double combinations
            } else{
                lowest--;
                i2 = c + lowest * cols;
            }
            board[i2].SetValue(value);
        }
    }

    spawn_tile();
}

bool Game2048::move(char dir){
    if(dir == 'q') return false;
    if(dir == '1' || dir == 'A' || dir == 'a'){
        move_left();
    }
    if(dir == '2' || dir == 'D' || dir == 'd'){
        move_right();
    }
    if(dir == '3' || dir == 'W' || dir == 'w'){
        move_up();
    }
    if(dir == '4' || dir == 'S' || dir == 's'){
        move_down();
    }
    // return game_end;
    return true;
}

int Game2048::get_score(){
    return score;
}

void Game2048::spawn_tile(){ 
    int value = rand() % 10; // should have 90% chance of 2, 10% chance of 4
    if(value == 0) value = 2; // note that value = 2 -> 1 << 2 = 4
    else value = 1; 

    int available = 0;
    for(int i = 0; i < rows*cols; i++){
        if(board[i].GetValue() == 0) available++; 
    }

    if(available == 0){
        // end game
        std::cerr << "Game should end!" << std::endl;
    }

    int random_spot = rand() % available;
    for(int i = 0; i < rows*cols; i++){
        if(board[i].GetValue() == 0) {
            if(random_spot-- == 0){
                board[i].SetValue(value);
            }
        }
    }
}


int Game2048::Tile::GetValue(){
    return value;
}

void Game2048::Tile::SetValue(int value){
    this->value = value;
    SetFormat(fmts[value]);
    SetText(nums[value]);
}

const char *Game2048::Tile::fmts[] = {
    "\033[48;5;233m",
    "\033[48;5;1m",
    "\033[48;5;2m",
    "\033[48;5;3m",
    "\033[48;5;11m",
    "\033[48;5;10m",
    "\033[48;5;9m",
    "\033[48;5;196m",
    "\033[48;5;201m",
    "\033[48;5;21m",
    "\033[48;5;28m",
    "\033[48;5;208m",
    "\033[48;5;213m",
    "\033[48;5;33m",
    "\033[48;5;40m",
    "\033[48;5;220m"
};

const char *Game2048::Tile::nums[] = {
    "\n       ",
    "\n   2   ",
    "\n   4   ",
    "\n   8   ",
    "\n   16  ",
    "\n   32  ",
    "\n   64  ",
    "\n  128  ",
    "\n  256  ",
    "\n  512  ",
    "\n  1024 ",
    "\n  2048 ",
    "\n  4096 ",
    "\n  8192 ",
    "\n 16384 ",
    "\n 32768 "
};

Game2048::Game2048(int rows, int cols){
    srand(time(nullptr));
    screen.Resize(38,18);
    this->rows = rows;
    this->cols = cols;
    finish = false;
    board = new Tile[rows*cols];

    screen.SetFormat("\033[48;5;0m");
    board_screen.SetFormat("\033[48;5;233m");
    board_screen.Resize(32, 12);
    board_screen.SetPos(Vec3(3, 5, 1));

    screen.AddChild(&title);
    title.Resize(8, 3);
    title.SetPos(Vec3(8, 1, 1));
    title.SetValue(11); // 2048

    screen.AddChild(&board_screen);

    for (int i = 0; i < rows*cols; i++){
        board[i].Resize(8, 3);
        board[i].SetPos(Vec3(8 * (i%cols), 3 * (i/cols), 1));
        board_screen.AddChild(&board[i]);
    }

    restart();

    while (!finish) {
        display_console();
        char input;
        std::cin >> input;
        if (!move(input)) break;
    }
};

Game2048::~Game2048(){
    if (board) delete[] board;
}

void Game2048::display_console(){
    screen.Print();
}
