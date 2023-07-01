#include <iostream>
#include <random>
#include <2048.hpp>
#include <defines.hpp>

void Game2048::restart(){
    // set score to 0
    score = 0;
    // make all tiles blank
    for(int i = 0; i < TILES; i++){
        board[i].value = 0;
    }

    // spawn 2 tiles;
    for(int i = 0; i < 2; i++){
        spawn_tile();
    }
}

void Game2048::move_left(){
    for(int r = 0; r < ROWS; r++){
        int leftmost = 0;
        for(int c = 0; c < COLS; c++){
            int value = board[INDEX(r,c)].value;
            if(value == 0) continue;

            board[INDEX(r,c)].value = 0;
            if(board[INDEX(r,leftmost)].value == 0){
                board[INDEX(r,leftmost)].value = value;
            }
            else if(board[INDEX(r,leftmost)].value == value){
                value *= 2;
                board[INDEX(r,leftmost)].value = value;
                score += value;
                leftmost++; // prevent double combinations
            } else{
                leftmost++;
                board[INDEX(r,leftmost)].value = value;
            }
        }
    }

    spawn_tile();
}
void Game2048::move_right(){
    for(int r = 0; r < ROWS; r++){
        int rightmost = COLS-1;
        for(int c = COLS-1; c >= 0; c--){
            int value = board[INDEX(r,c)].value;
            if(value == 0) continue;
            
            board[INDEX(r,c)].value = 0;
            if(board[INDEX(r,rightmost)].value == 0){
                board[INDEX(r,rightmost)].value = value;
            }
            else if(board[INDEX(r,rightmost)].value == value){
                value *= 2;
                board[INDEX(r,rightmost)].value = value;
                score += value;
                rightmost--; // prevent double combinations
            } else{
                rightmost--;
                board[INDEX(r,rightmost)].value = value;
            }
        }
    }

    spawn_tile();
}
void Game2048::move_up(){
    for(int c = 0; c < COLS; c++){
        int topmost = 0;
        for(int r = 0; r < ROWS; r++){
            int value = board[INDEX(r,c)].value;
            if(value == 0) continue;

            board[INDEX(r,c)].value = 0;
            if(board[INDEX(topmost,c)].value == 0){
                board[INDEX(topmost,c)].value = value;
            }
            else if(board[INDEX(topmost,c)].value == value){
                value *= 2;
                board[INDEX(topmost,c)].value = value;
                score += value;
                topmost++; // prevent double combinations
            } else{
                topmost++;
                board[INDEX(topmost,c)].value = value;
            }
        }
    }

    spawn_tile();
}
void Game2048::move_down(){                 
    for(int c = 0; c < COLS; c++){
        int topmost = ROWS-1;
        for(int r = ROWS-1; r >= 0; r--){
            int value = board[INDEX(r,c)].value;
            if(value == 0) continue;

            board[INDEX(r,c)].value = 0;
            if(board[INDEX(topmost,c)].value == 0){
                board[INDEX(topmost,c)].value = value;
            }
            else if(board[INDEX(topmost,c)].value == value){
                value *= 2;
                board[INDEX(topmost,c)].value = value;
                score += value;
                topmost--; // prevent double combinations
            } else{
                topmost--;
                board[INDEX(topmost,c)].value = value;
            }
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
    int value = rand() % 4; // should have 90% chance of 2, 10% chance of 4
    if(value == 0) value = 4;
    else value = 2; 

    int available = 0;
    for(int i = 0; i < TILES; i++){
        if(board[i].value == 0) available++; 
    }

    if(available == 0){
        // end game
        std::cerr << "Game should end!" << std::endl;
    }

    int random_spot = rand() % available;
    for(int i = 0; i < TILES; i++){
        if(board[i].value == 0) {
            if(random_spot-- == 0){
                board[i].value = value;
            }
        }
    }
    
}

Game2048::Game2048(){
    restart();
}

void Game2048::display_console(){
    std::cout << "2048!!!\t\tScore: " << score << std::endl;
    for(int i = 0; i < ROWS; i++){
        std::cout << "\n|\t";
        for(int j = 0; j < COLS; j++){
            std::cout << board[i * COLS + j].value << "|\t";
        }
    }
    std::cout << std::endl << std::endl;
}

int main(){
    srand(time(nullptr));
    Game2048 game = Game2048();
    while(true){
        CLEAR;
        game.display_console();
        char input;
        std::cin >> input;
        if(!game.move(input)) break;
    }
}