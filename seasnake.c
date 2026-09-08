#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define cols 20
#define rows 20

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

int main(int argc, char **argv)
{

    snake.length = 1;
    snake.part[0].x = cols / 2;
    snake.part[0].y = rows / 2;

    while (!isGameOver)
    {
        fill_board();
        draw_snake();
        print_board();
        read_keyboard();
    }

    return 0;
}
