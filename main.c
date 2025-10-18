#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "snake.c"


int main(){
    snake cobra;
    food comida;
    bomb bomba;
    int speed=1;

    clear_screen();
    cobra.lives = 1;
    setup(&cobra, &comida, &bomba);
    draw(cobra, comida, bomba);
    Sleep(1000);

    while(cobra.lives){
        if (check_collision(&cobra)) {
            cobra.lives--;
        }

        input(&cobra);
        move_snake(&cobra);
        increasePoints(&cobra, &comida);
        decreasePoints(&cobra, &bomba);
        draw(cobra, comida, bomba);
        speed = ((cobra.length)/2)+1;
        Sleep(200 / (speed));

    }

    clear_screen();
    printf("Game Over! Pontos: %d\n", cobra.length);
    Sleep(10000);

    destroySnake(&cobra);


}