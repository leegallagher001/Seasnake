#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define cols 20
#define rows 20
#define foods 10

char board[cols * rows];

int isGameOver = 0;

void fill_board()
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

    clear_screen();

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

int main(int argc, char **argv)
{
    srand(time(0));

    snake.length = 3;
    snake.part[0].x = cols / 2;
    snake.part[0].y = rows / 2;
    snake.part[1].x = cols / 2 - 1;
    snake.part[1].y = rows / 2;
    snake.part[2].x = cols / 2 - 2;
    snake.part[2].y = rows / 2;

    setup_food();

    while (!isGameOver)
    {
        fill_board();
        place_food();
        draw_snake();
        print_board();
        printf("\n\nLength: %d\n\n", snake.length);
        printf("Positioning Data:\n");
        printf("%d %d\n", snake.part[0].x, snake.part[0].y);
        printf("%d %d\n", snake.part[1].x, snake.part[1].y);
        printf("%d %d\n", snake.part[2].x, snake.part[2].y);
        read_keyboard();
    }

    return 0;
}
