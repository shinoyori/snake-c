
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "snake.h"



void initialize_queue(queue *q) {
    q->first = NULL;
    q->last = NULL;
}


void enqueue(int x, int y,  queue *q) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->items.x = x;
    newNode->items.y = y;
    newNode->next = NULL;
    if (q->first == NULL) {
        newNode->direction = UP;
        q->first = newNode;
        q->last = newNode;
        
    }
    else{
        newNode->direction = q->last->direction;
        q->last->next = newNode;
        q->last = newNode;
    }
}


int is_empty(queue *q) {
    if (q->first == NULL){
        return 1;
    };
    return 0;
}

void dequeue(queue *q) {
    if (!is_empty(q)) {
        if (q->first == q->last){
            q->first = NULL;
            q->last = NULL;
        }
        else{
            node* aux;
            aux = q->first;
            q->first = q->first->next;
            free(aux);
        }
    }
}


void gotoxy(short int x, short int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clear_screen() {
    char *os = getenv("OS");
    if (os != NULL && stricmp(os, "Windows_NT") == 0) {
        system("cls");
    } else {
        printf("\033c");
    }
}

void initialize_game_board() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                gameBoard[i][j] = WALL;
            } else {
                gameBoard[i][j] = EMPTY;
            }
        }
    }
}

void destroySnake (snake *snake1){
    while (!is_empty(&snake1->body)){
        dequeue(&snake1->body);
    }
}

void setup(snake *snake1, food *food1, bomb *bomb1) {
    initialize_queue(&snake1->body);
    snake1->length = 1;
    food1->position.x = 14;
    food1->position.y = 7;
    bomb1->position.x = 10;
    bomb1->position.y = 10;
    
    enqueue (5, 5, &snake1->body);
    initialize_game_board();
}

void draw(snake snake1, food food1, bomb bomb1) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", gameBoard[y][x]);
        }
        printf("\n");
    }
    
    initialize_game_board();
    gameBoard[food1.position.y][food1.position.x] = FOOD;
    gameBoard[bomb1.position.y][bomb1.position.x] = BOMB;
    
    point snake_head = snake1.body.first->items;

    gameBoard[snake_head.y][snake_head.x] = SNAKE_HEAD;

    if(snake1.body.first!=snake1.body.last){
        node *p;
        p = snake1.body.first->next;
        while (p!=NULL) {
            point snake_body_part = p->items;
            gameBoard[snake_body_part.y][snake_body_part.x] = SNAKE_BODY;
            p = p->next;
        }
    }

    

    gotoxy(WIDTH + 2, 2);
    printf("Pontos: %d", snake1.length);
    gotoxy(0, 0);


    fflush(stdout);
}


void input(snake *snake1) {
    if (_kbhit()) { 
        char key = (char)_getch(); 
        switch (key) {
            case 'w': 
                if (snake1->body.first->direction != DOWN) {
                    snake1->body.first->direction = UP;
                }
                break;
            case 's': 
                if (snake1->body.first->direction != UP) {
                    snake1->body.first->direction = DOWN;
                }
                break;
            case 'a': 
                if (snake1->body.first->direction != RIGHT) {
                    snake1->body.first->direction = LEFT;
                }
                break;
            case 'd': 
                if (snake1->body.first->direction != LEFT) {
                    snake1->body.first->direction = RIGHT;
                }
                break;
        }
    }
}

int check_collision(snake *snake1) 
{ 
    int retorno=0;
    
    if (snake1->body.first->items.x <= 0 || snake1->body.first->items.y >= (HEIGHT-1) || snake1->body.first->items.y <= 0 || snake1->body.first->items.x >= (WIDTH-1)) {
        retorno = 1; 
        
    }

    node *p;
    p = snake1->body.first->next;
    while (p!=NULL){
        if (snake1->body.first->items.x == p->items.x && snake1->body.first->items.y == p->items.y){
            retorno=1;
        }
        p = p->next;
    }
    
    return retorno;
}



void generate_food(food* food1) {
    time_t t;

    gameBoard[food1->position.y][food1->position.x] = EMPTY;
    srand ((unsigned int)time(&t));
    food1->position.x = (rand() % (WIDTH-2)) +1;
    food1->position.y = (rand() % (HEIGHT-2)) +1;
    
}

void generate_bomb(bomb* bomb1) {
    time_t t;

    gameBoard[bomb1->position.y][bomb1->position.x] = EMPTY;
    srand ((unsigned int)time(&t));
    bomb1->position.x = (rand() % (WIDTH-2))+1;
    bomb1->position.y = (rand() % (HEIGHT-2))+1;
    
}

void increasePoints (snake *snake1, food *food1){
    if((snake1->body.first->items.x == food1->position.x) && (snake1->body.first->items.y == food1->position.y)){ 
            snake1->length++;
            generate_food(food1);
            switch (snake1->body.last->direction) {
                case UP:
                    enqueue(snake1->body.last->items.x, snake1->body.last->items.y+1, &snake1->body);
                    snake1->body.last->direction=UP;
                    break;
                case DOWN:
                    enqueue(snake1->body.last->items.x, snake1->body.last->items.y-1, &snake1->body);
                    snake1->body.last->direction=DOWN;
                    break;
                case LEFT:
                    enqueue(snake1->body.last->items.x+1, snake1->body.last->items.y, &snake1->body);
                    snake1->body.last->direction=LEFT;
                    break;
                case RIGHT:
                    enqueue(snake1->body.last->items.x-1, snake1->body.last->items.y, &snake1->body);
                    snake1->body.last->direction=RIGHT;
                    break;
            }
        }

}

void decreasePoints(snake *snake1, bomb *bomb1){
    if((snake1->body.first->items.x == bomb1->position.x) && (snake1->body.first->items.y == bomb1->position.y)){
        if (snake1->length <= 2){
            snake1->lives--;
        }
        else{
        snake1->length = snake1->length - 2;
        generate_bomb(bomb1);
        dequeue(&snake1->body);
        dequeue(&snake1->body);
        }
    }


}




int gameOver (snake *snake1){
    if (snake1->lives == 0){
        return 1;
    }
    return 0;
}


void move_snake(snake *snake1) {
    
    int dir = snake1->body.first->direction;

    switch (snake1->body.first->direction) {
        case UP:
            snake1->body.first->items.y--;
            break;
        case DOWN:
            snake1->body.first->items.y++;
            break;
        case LEFT:
            snake1->body.first->items.x--;
            break;
        case RIGHT:
            snake1->body.first->items.x++;
            break;
    }
    
   
    node *p = snake1->body.first->next;
    int pdir;
    if(snake1->body.first != snake1->body.last){
        while (p != NULL) {
            pdir = p->direction;
            switch (p->direction) {
                case UP:
                    p->items.y--;
                    break;
                case DOWN:
                    p->items.y++;
                    break;
                case LEFT:
                    p->items.x--;
                    break;
                case RIGHT:
                    p->items.x++;
                    break;
            }
            p->direction = dir;
            dir=pdir;
            p=p->next;

        
        }
    }
    
}