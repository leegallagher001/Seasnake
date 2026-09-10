#include <stdio.h> // Standard I/O library
#include <stdlib.h> // Standard C library
#include <conio.h> // Console I/O library for getch() and putch()
#include <time.h> // Time library for C

#define cols 20 // width of the game board
#define rows 20 // height of the game board
#define foods 10 // number of food pieces on the board

char board[cols * rows]; // character array to represent the game board

int isGameOver = 0; // game over = false

void fill_board() // design of game board char element
{
    int x, y;

    for (y = 0; y < rows; y++)
    {
        for (x = 0; x < cols; x++)
        {
            if (x == 0 || y == 0 || x == cols - 1 || y == rows - 1)
            {
                board[y * cols + x] = '#';
            }
            else
            {
                board[y * cols + x] = ' ';
            }
        }
    }
}

void clear_screen()
{
    system("cls");
}

void print_board()
{
    int x, y;

    for (y = 0; y < rows; y++)
    {
        for (x = 0; x < cols; x++)
        {
            putch(board[y * cols + x]);
        }
        putch('\n');
    }
}

#define SNAKE_MAX_LEN 256

struct SnakePart
{
    int x, y;
};

struct Snake
{
    int length;
    struct SnakePart part[SNAKE_MAX_LEN];
};

struct Snake snake;

struct  Food {
    int x, y;
    int consumed;
};

struct Food food[foods];

void draw_snake()
{
    int i;

    for (i = snake.length; i >= 0; i--)
    {
        board[snake.part[i].y * cols + snake.part[i].x] = '*';
        snake.part[i];
    }
    board[snake.part[0].y * cols + snake.part[0].x] = '@';
}

void move_snake(int deltaX, int deltaY)
{
    int i;

    for (i = snake.length - 1; i > 0; i--)
    {
        snake.part[i] = snake.part[i - 1];
    }

    snake.part[0].x += deltaX;
    snake.part[0].y += deltaY;
}

void read_keyboard()
{
    int ch = getch();

    switch (ch)
    {
    case 'w':
        move_snake(0, -1);
        break;
    case 'a':
        move_snake(-1, 0);
        break;
    case 's':
        move_snake(0, 1);
        break;
    case 'd':
        move_snake(1, 0);
        break;
    }
}

void place_food() {
    int i;

    for (i = 0; i < foods; i++) {
        if (!food[i].consumed) {
            board[food[i].y * cols + food[i].x] = '+';
        }
    }
}

void setup_food() {
    int i;

    for (i = 0; i < foods; i++) {
        food[i].x = 1 + rand() % (cols - 2);
        food[i].y = 1 + rand() % (rows - 2);
        food[i].consumed = 0;
    }
}

void setup_snake() {
    snake.length = 1;
    snake.part[0].x = 1 + rand() % (cols - 2);
    snake.part[0].y = 1 + rand() % (rows - 2);
}

void game_rules() {
    int i;

    for (i = 0; i < foods; i++) {
        if (!food[i].consumed) {
            if (food[i].x == snake.part[0].x && food[i].y == snake.part[0].y) {
                food[i].consumed = 1;
                snake.length++;
            }
        }
    }

    if (snake.part[0].x == 0 || snake.part[0].x == cols - 1 || snake.part[0].y == 0 || snake.part[0].y == rows - 1) {
        isGameOver = 1;
    }
}

int main(int argc, char **argv)
{
    srand(time(0));

    setup_snake();
    setup_food();

    while (!isGameOver)
    {
        fill_board();
        place_food();
        draw_snake();
        game_rules();
        clear_screen();
        printf("S E A S N A K E\n\n");
        printf("Score: %d\n\n", (snake.length - 1) * 100);
        print_board();
        printf("\n\nLength: %d\n\n", snake.length);
        printf("Positioning Data:\n");
        printf("%d %d\n", snake.part[0].x, snake.part[0].y);
        printf("%d %d\n", snake.part[1].x, snake.part[1].y);
        printf("%d %d\n", snake.part[2].x, snake.part[2].y);
        read_keyboard();
    }

    printf("Game Over. Final Score: %d\n", (snake.length - 1) * 100);

    while(1) getch();

    return 0;
}
