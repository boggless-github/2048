#include <Screen.hpp>
#include <random>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    srand(0);
    Screen bg(39,15);
    Screen fg(3,1);
    bg.SetFormat("\033[48;5;0m");

    bg.SetText("\n\n\n\n\t\tHi!");

    bg.AddChild(&fg);
    fg.SetText("bye");
    fg.SetFormat("");
    fg.SetPos(Vec3(10, 5,-1));

    for (int i = 0; i < 100; i++){
        int x = rand() % 3 - 1;
        int y = rand() % 3 - 1;
        Vec3 now = fg.GetPos();
        now.x += x;
        now.y += y;
        fg.SetPos(now);
        bg.Print();
    }
}