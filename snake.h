#ifndef SNAKE_H_
#define SNAKE_H_

#define MAX_SIZE 100
#define MAX_SNAKE_LENGTH 10
#define WIDTH 30
#define HEIGHT 15

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define SNAKE_HEAD 'O'
#define SNAKE_BODY 'o'
#define FOOD '*'
#define WALL '#'
#define EMPTY ' '
#define BOMB 'X'

typedef struct {
    int x, y;
}point;


struct Node {
    point items;
    int direction;
    struct Node *next;
};

typedef struct Node node;

typedef struct {
    node *first;
    node *last;
}queue;

void initialize_queue(queue *q);
void enqueue(int x, int y,  queue *q);
int is_empty(queue *q);
void dequeue(queue *q);

char gameBoard[HEIGHT][WIDTH];

typedef struct {
    queue body;
    int length;
    int lives;
    int speed;
} snake;

typedef struct{
    point position;
}food;

typedef struct{
    point position;
}bomb;

void gotoxy(short int x, short int y) ;
void clear_screen();
void initialize_game_board();
void destroySnake (snake *snake1);
void setup(snake *snake1, food *food1, bomb  *bomb1);
void draw(snake snake1, food food1, bomb bomb1);
void input(snake *snake1);
int check_collision(snake *snake1);
void generate_food(food *food1);
void generate_bomb(bomb *bomb1);
void increasePoints (snake *snake1, food *food1);
void decreasePoints (snake *snake1, bomb *bomb1);
int gameOver (snake *snake1);
void move_snake(snake *snake1);





#endif