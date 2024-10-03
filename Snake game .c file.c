#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h> 

#define WIDTH 30
#define HEIGHT 30
#define MAX_LENGTH 100

// Directions
typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

char board[HEIGHT][WIDTH];

// Function prototypes
void initializeBoard();
void clearBoard();
void drawBorders();
void updateBoard(int snake[][2], int snakeLength, int foodX, int foodY);
void moveSnake(int snake[][2], int *snakeLength, Direction dir, int grow);
void placeFood(int *foodX, int *foodY, int snake[][2], int snakeLength);
void printBoard();
void clearScreen();
void handleInput(Direction *dir, int *snakeLength);

// Test functions (if needed)
void testMoveSnake();
void testPlaceFood();
void testUpdateBoard();

int main() {
    // Uncomment the lines below to run tests
    // testMoveSnake();
    // testPlaceFood();
    // testUpdateBoard();

    int snake[MAX_LENGTH][2];
    int snakeLength = 1;

    srand(time(NULL));
    snake[0][0] = rand() % (WIDTH - 2) + 1; 
    snake[0][1] = rand() % (HEIGHT - 2) + 1;

    Direction dir = RIGHT;
    int foodX, foodY;
    placeFood(&foodX, &foodY, snake, snakeLength);

    while (1) {
        clearBoard();
        updateBoard(snake, snakeLength, foodX, foodY);
        handleInput(&dir, &snakeLength);

        // Check for food consumption
        int grow = (snake[0][0] == foodX && snake[0][1] == foodY);
        moveSnake(snake, &snakeLength, dir, grow);

        // If the snake grew, place new food
        if (grow) {
            placeFood(&foodX, &foodY, snake, snakeLength);
        }

        printBoard();
        usleep(100000);
    }

    return 0;
}

void clearBoard() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            board[y][x] = ' ';
        }
    }
}

void drawBorders() {
    for (int x = 0; x < WIDTH; x++) {
        board[0][x] = '#'; // Top border
        board[HEIGHT - 1][x] = '#'; // Bottom border
    }
    for (int y = 0; y < HEIGHT; y++) {
        board[y][0] = '#'; // Left border
        board[y][WIDTH - 1] = '#'; // Right border
    }
}

void updateBoard(int snake[][2], int snakeLength, int foodX, int foodY) {
    // Draw snake segments
    for (int i = 0; i < snakeLength; i++) {
        board[snake[i][1]][snake[i][0]] = 'O'; // Snake segment
    }

    // Place food
    board[foodY][foodX] = 'X'; // Food
}

void moveSnake(int snake[][2], int *snakeLength, Direction dir, int grow) {
    // Calculate the next position of the head
    int nextX = snake[0][0];
    int nextY = snake[0][1];

    switch (dir) {
        case UP: nextY--; break;
        case DOWN: nextY++; break;
        case LEFT: nextX--; break;
        case RIGHT: nextX++; break;
    }

    // Wrap around logic
    if (nextX < 1) nextX = WIDTH - 2; 
    if (nextX > WIDTH - 2) nextX = 1; 
    if (nextY < 1) nextY = HEIGHT - 2; 
    if (nextY > HEIGHT - 2) nextY = 1;

    // Shift the body of the snake
    for (int i = *snakeLength - 1; i > 0; i--) {
        snake[i][0] = snake[i - 1][0];
        snake[i][1] = snake[i - 1][1];
    }

    // Update the head position
    snake[0][0] = nextX;
    snake[0][1] = nextY;

    if (grow) {
        (*snakeLength)++;
    }
}

void placeFood(int *foodX, int *foodY, int snake[][2], int snakeLength) {
    int validPosition = 0;

    while (!validPosition) {
        *foodX = rand() % (WIDTH - 2) + 1; 
        *foodY = rand() % (HEIGHT - 2) + 1;

        validPosition = 1; 
        for (int i = 0; i < snakeLength; i++) {
            if (snake[i][0] == *foodX && snake[i][1] == *foodY) {
                validPosition = 0; 
                break;
            }
        }
    }
}

void printBoard() {
    clearScreen();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", board[y][x]);
        }
        printf("\n");
    }
}

void clearScreen() {
    printf("\033[H\033[J");
}

void handleInput(Direction *dir, int *snakeLength) {
    if (_kbhit()) { 
        char key = _getch();
        switch (key) {
            case 'w': *dir = UP; break; 
            case 'e': *dir = DOWN; break; 
            case 's': *dir = LEFT; break; 
            case 'd': *dir = RIGHT; break; 
            case 'g': 
                if (*snakeLength < MAX_LENGTH) {
                    (*snakeLength)++;
                }
            break;
            case 'q':
                printf("Exiting game...\n");
                exit(0);
        }
    }
}

