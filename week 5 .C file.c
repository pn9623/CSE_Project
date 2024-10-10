#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <time.h> 
#include <windows.h> 

#define WIDTH 32  
#define HEIGHT 32 
#define MAX_LENGTH 100 


int snakeX[MAX_LENGTH];
int snakeY[MAX_LENGTH];
int snakeLength = 1; 
int fruitX, fruitY;
int score = 0;
int gameOver = 0;


char board[HEIGHT][WIDTH];
// function prototypes
void initializeBoard();
void drawBoard();
void updateBoard();
int isFruitLocationValid(int x, int y);
void updateSnake (int dir);

void initializeBoard() {
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                board[i][j] = '#'; 
            else
                board[i][j] = ' ';
        }
    }

    
    snakeX[0] = rand() % (WIDTH - 2) + 1; 
    snakeY[0] = rand() % (HEIGHT - 2) + 1; 
    board[snakeY[0]][snakeX[0]] = 'O'; 


    do {
        fruitX = rand() % (WIDTH - 2) + 1; 
        fruitY = rand() % (HEIGHT - 2) + 1;
    }
	 while (!isFruitLocationValid(fruitX, fruitY)); 
    board[fruitY][fruitX] = '*'; 
}

void drawBoard() {
    system("cls"); 
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d\n", score); 
}

void updateBoard() {
    
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDTH - 1; j++) {
            board[i][j] = ' '; // Clear inside
        }
    }


    for (int i = 0; i < snakeLength; i++) {
        if (i == 0) {
            board[snakeY[i]][snakeX[i]] = 'O'; 
        } else {
            board[snakeY[i]][snakeX[i]] = 'o'; 
        }
    }

    
    board[fruitY][fruitX] = '*';
}

int isFruitLocationValid(int x, int y) {
    
    if (x <= 0 || x >= WIDTH - 1 || y <= 0 || y >= HEIGHT - 1) {
        return 0; 
    }
    for (int i = 0; i < snakeLength; i++) {
        if (snakeX[i] == x && snakeY[i] == y) {
            return 0; 
        }
    }
    return 1; 
}

void updateSnake(int dir) {
    int prevX = snakeX[0];
    int prevY = snakeY[0];
    int prev2X, prev2Y;

    
    switch (dir) {
        case 0: snakeY[0]--; break; // Up
        case 1: snakeX[0]++; break; // Right
        case 2: snakeY[0]++; break; // Down
        case 3: snakeX[0]--; break; // Left
    }


    if (snakeX[0] <= 0 || snakeX[0] >= WIDTH - 1 || snakeY[0] <= 0 || snakeY[0] >= HEIGHT - 1) {
        gameOver = 1; 
        return; 
    }


    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = 1; 
            return; 
        }
    }


    for (int i = 1; i < snakeLength; i++) {
        prev2X = snakeX[i];
        prev2Y = snakeY[i];
        snakeX[i] = prevX;
        snakeY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        if (snakeLength < MAX_LENGTH) {
            snakeLength++; 
            score++; 
        }
        
        do {
            fruitX = rand() % (WIDTH - 2) + 1; 
            fruitY = rand() % (HEIGHT - 2) + 1; 
        } while (!isFruitLocationValid(fruitX, fruitY)); 
    }
}

int main() {
    srand(time(NULL)); 
    int direction = 1; 
    initializeBoard();

    while (!gameOver) {
        updateBoard(); 
        drawBoard(); 
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
                case 'w': direction = 0; break; // Up
                case 'd': direction = 1; break; // Right
                case 's': direction = 2; break; // Down
                case 'a': direction = 3; break; // Left
            }
        }
        updateSnake ( direction);
        Sleep (200);// 200 ms delay
    }
    printf("Game Over! Final score:%\n",score);
    
    return 0;
}

