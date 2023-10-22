// #include <iostream>
// #include <random>
// #include <2048.hpp>
// #include <defines.hpp>
// #include <string.h>

// void Game2048::restart(){
//     // set score to 0
//     score = 0;
//     // make all tiles blank
//     for(int i = 0; i < TILES; i++){
//         board[i].value = 0;
//     }

//     // spawn 2 tiles;
//     for(int i = 0; i < 2; i++){
//         spawn_tile();
//     }
// }

// void Game2048::move_left(){
//     for(int r = 0; r < ROWS; r++){
//         int leftmost = 0;
//         for(int c = 0; c < COLS; c++){
//             int value = board[INDEX(r,c)].value;
//             if(value == 0) continue;

//             board[INDEX(r,c)].value = 0;
//             if(board[INDEX(r,leftmost)].value == 0){
//                 board[INDEX(r,leftmost)].value = value;
//             }
//             else if(board[INDEX(r,leftmost)].value == value){
//                 value += 1;
//                 board[INDEX(r,leftmost)].value = value;
//                 score += 1 << value;
//                 leftmost++; // prevent double combinations
//             } else{
//                 leftmost++;
//                 board[INDEX(r,leftmost)].value = value;
//             }
//         }
//     }

//     spawn_tile();
// }
// void Game2048::move_right(){
//     for(int r = 0; r < ROWS; r++){
//         int rightmost = COLS-1;
//         for(int c = COLS-1; c >= 0; c--){
//             int value = board[INDEX(r,c)].value;
//             if(value == 0) continue;
            
//             board[INDEX(r,c)].value = 0;
//             if(board[INDEX(r,rightmost)].value == 0){
//                 board[INDEX(r,rightmost)].value = value;
//             }
//             else if(board[INDEX(r,rightmost)].value == value){
//                 value += 1;
//                 board[INDEX(r,rightmost)].value = value;
//                 score += 1 << value;
//                 rightmost--; // prevent double combinations
//             } else{
//                 rightmost--;
//                 board[INDEX(r,rightmost)].value = value;
//             }
//         }
//     }

//     spawn_tile();
// }
// void Game2048::move_up(){
//     for(int c = 0; c < COLS; c++){
//         int topmost = 0;
//         for(int r = 0; r < ROWS; r++){
//             int value = board[INDEX(r,c)].value;
//             if(value == 0) continue;

//             board[INDEX(r,c)].value = 0;
//             if(board[INDEX(topmost,c)].value == 0){
//                 board[INDEX(topmost,c)].value = value;
//             }
//             else if(board[INDEX(topmost,c)].value == value){
//                 value += 1;
//                 board[INDEX(topmost,c)].value = value;
//                 score += 1 << value;
//                 topmost++; // prevent double combinations
//             } else{
//                 topmost++;
//                 board[INDEX(topmost,c)].value = value;
//             }
//         }
//     }

//     spawn_tile();
// }
// void Game2048::move_down(){                 
//     for(int c = 0; c < COLS; c++){
//         int topmost = ROWS-1;
//         for(int r = ROWS-1; r >= 0; r--){
//             int value = board[INDEX(r,c)].value;
//             if(value == 0) continue;

//             board[INDEX(r,c)].value = 0;
//             if(board[INDEX(topmost,c)].value == 0){
//                 board[INDEX(topmost,c)].value = value;
//             }
//             else if(board[INDEX(topmost,c)].value == value){
//                 value += 1;
//                 board[INDEX(topmost,c)].value = value;
//                 score += 1 << value;
//                 topmost--; // prevent double combinations
//             } else{
//                 topmost--;
//                 board[INDEX(topmost,c)].value = value;
//             }
//         }
//     }

//     spawn_tile();
// }

// bool Game2048::move(char dir){
//     if(dir == 'q') return false;
//     if(dir == '1' || dir == 'A' || dir == 'a'){
//         move_left();
//     }
//     if(dir == '2' || dir == 'D' || dir == 'd'){
//         move_right();
//     }
//     if(dir == '3' || dir == 'W' || dir == 'w'){
//         move_up();
//     }
//     if(dir == '4' || dir == 'S' || dir == 's'){
//         move_down();
//     }
//     // return game_end;
//     return true;
// }

// int Game2048::get_score(){
//     return score;
// }

// void Game2048::spawn_tile(){ 
//     int value = rand() % 10; // should have 90% chance of 2, 10% chance of 4
//     if(value == 0) value = 2; // note that value = 2 -> 1 << 2 = 4
//     else value = 1; 

//     int available = 0;
//     for(int i = 0; i < TILES; i++){
//         if(board[i].value == 0) available++; 
//     }

//     if(available == 0){
//         // end game
//         std::cerr << "Game should end!" << std::endl;
//     }

//     int random_spot = rand() % available;
//     for(int i = 0; i < TILES; i++){
//         if(board[i].value == 0) {
//             if(random_spot-- == 0){
//                 board[i].value = value;
//             }
//         }
//     }
    
// }

// Game2048::Game2048(Screen *parent, int rows, int cols){
//     this->rows = rows;
//     this->cols = cols;
//     this->board = new Tile[rows*cols];
//     this->parent = parent;
//     restart();
// }

// const char* const Game2048::Tile::strings[] = {
//     "\033[0m\033[48;5;0m"       "       "   "\033[0m",
//     "\033[0m\033[48;5;1m"       "   2   "   "\033[0m",
//     "\033[0m\033[48;5;2m"       "   4   "   "\033[0m",
//     "\033[0m\033[48;5;3m"       "   8   "   "\033[0m",
//     "\033[0m\033[48;5;11m"      "   16  "   "\033[0m",
//     "\033[0m\033[48;5;10m"      "   32  "   "\033[0m",
//     "\033[0m\033[48;5;9m"       "   64  "   "\033[0m",
//     "\033[0m\033[48;5;196m"     "  128  "   "\033[0m",
//     "\033[0m\033[48;5;201m"     "  256  "   "\033[0m",
//     "\033[0m\033[48;5;21m"      "  512  "   "\033[0m",
//     "\033[0m\033[48;5;28m"      "  1024 "   "\033[0m",
//     "\033[0m\033[48;5;208m"     "  2048 "   "\033[0m",
//     "\033[0m\033[48;5;213m"     "  4096 "   "\033[0m",
//     "\033[0m\033[48;5;33m"      "  8192 "   "\033[0m",
//     "\033[0m\033[48;5;40m"      " 16384 "   "\033[0m",
//     "\033[0m\033[48;5;220m"     " 32768 "   "\033[0m"};

// void Game2048::display_console(){
//     char buf[1024];
//     int offset = 0;
//     memset(&buf[0], 0, sizeof(buf));
//     offset += snprintf(&buf[offset], sizeof(buf)-offset, "  %s \tScore: %d\n \033[48;5;8m%30s\033[0m", Tile::strings[11], score, "");
//     for(int i = 0; i < ROWS; i++){
//         offset += snprintf(&buf[offset], sizeof(buf)-offset, "\n \033[48;5;8m \033[0m");
//         for(int j = 0; j < COLS; j++){
//             offset += snprintf(&buf[offset], sizeof(buf)-offset, "%7s", Tile::strings[board[i*COLS + j].value]);
//         }
//         offset += snprintf(&buf[offset], sizeof(buf)-offset, "\033[48;5;8m \033[0m");
//     }
//     offset += snprintf(&buf[offset], sizeof(buf)-offset, "\n \033[48;5;8m%30s\033[0m", "");
//     std::cout << &buf[0] << std::endl << std::endl;
// }

// // int main(){
// //     srand(time(nullptr));
// //     Screen screen(39, 13);
// //     Game2048 game = Game2048(&screen, 4, 4);
// //     while(true){
// //         CLEAR;
// //         game.display_console();
// //         char input;
// //         std::cin >> input;
// //         if(!game.move(input)) break;
// //     }
// // }