#include <stdio.h>   
#include <stdlib.h>  
#include <conio.h>   
#include <time.h>    
#include <windows.h> 

#define WIDTH 32  
#define HEIGHT 32 

// Function prototypes
void displayWelcomeMessage();
void initializeBoard();
void drawBoard();
void updateBoard();
int isFruitLocationValid(int x, int y);
void updateSnake(int dir);
void gameOverMessage();

// Arrays to hold the snake's position on the board
int snakeX[HEIGHT * WIDTH] = {0}; // X-coordinates of the snake segments
int snakeY[HEIGHT * WIDTH] = {0}; // Y-coordinates of the snake segments
int snakeLength = 1; // Current length of the snake, starts at 1

// Coordinates for the fruit on the board
int fruitX = 0, fruitY = 0; // Positions for the fruit

// Scoring variables
int score = 0; // Current score for the current game session
int totalScore = 0; // Total score accumulated across multiple games

// Game state variables
int gameOver = 0; // Flag to indicate whether the game is over

// The game board
char board[HEIGHT][WIDTH] = {0}; // 2D array representing the game board

// Main function to control the game flow
int main() {
    srand(time(NULL)); 
    int direction = 1; // Direction of the snake movement

    while (1) { // Main game loop
        displayWelcomeMessage(); // Call welcome message
        initializeBoard(); // Initialize the game board

        while (!gameOver) { // Loop until the game is over
            updateBoard(); 
            drawBoard(); 
            if (_kbhit()) { // Check if a key is pressed
                char key = _getch();
                switch (key) {
                    case 'w': if (direction != 2) direction = 0; break; // Up
                    case 'd': if (direction != 3) direction = 1; break; // Right
                    case 's': if (direction != 0) direction = 2; break; // Down
                    case 'a': if (direction != 1) direction = 3; break; // Left
                    case 'q': // Quit the game
                        gameOver = 1;
                        break;
                }
            }
            updateSnake(direction); // Update snake position based on direction
            Sleep(200); // Delay for snake movement speed
        }

        gameOverMessage(); // Call the game over message when the game ends
    }
    
    return 0;
}

// Function to display the welcome message and instructions
void displayWelcomeMessage() {
    system("cls"); // Clear the console
    printf("Welcome to Snake Game!\n");
    printf("Use 'W' to move Up\n");
    printf("Use 'A' to move Left\n");
    printf("Use 'S' to move Down\n");
    printf("Use 'D' to move Right\n");
    printf("Press SPACE to start the game...\n");

    // Wait for the spacebar to start the game
    while (_getch() != ' ') {
        
    }
}

// Function to initialize the game board, snake, and fruit positions
void initializeBoard() {
    // Initialize the game board with borders and empty spaces
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                board[i][j] = '#'; // Set borders
            else
                board[i][j] = ' '; // Set empty space inside
        }
    }

    // Place the snake's initial position randomly on the board
    snakeX[0] = rand() % (WIDTH - 2) + 1; 
    snakeY[0] = rand() % (HEIGHT - 2) + 1; 
    board[snakeY[0]][snakeX[0]] = 'O';  

    // Place the fruit randomly on the board
    do {
        fruitX = rand() % (WIDTH - 2) + 1; 
        fruitY = rand() % (HEIGHT - 2) + 1;
    } while (!isFruitLocationValid(fruitX, fruitY)); 
    board[fruitY][fruitX] = '*'; 
}

// Function to draw the current state of the board to the console
void drawBoard() {
    system("cls"); // Clear the console before drawing the board
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]); // Print each character on the board
        }
        printf("\n");
    }
    printf("Current Score: %d\n", score); 
    printf("Total Score: %d\n", totalScore); // Display total score
}

// Function to update the board state before drawing
void updateBoard() {
    // Clear the inside of the board
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDTH - 1; j++) {
            board[i][j] = ' '; // Clear inside
        }
    }

    // Update the board with the snake's position
    for (int i = 0; i < snakeLength; i++) {
        if (i == 0) {
            board[snakeY[i]][snakeX[i]] = 'O'; // Head of the snake
        } else {
            board[snakeY[i]][snakeX[i]] = 'o'; // Body of the snake
        }
    }

    board[fruitY][fruitX] = '*'; // Draw the fruit on the board
}

// Function to check if the fruit's location is valid (not colliding with walls or snake)
int isFruitLocationValid(int x, int y) {
    // Check if the fruit location is valid (not outside the borders or on the snake)
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

// Function to update the snake's position based on user input
void updateSnake(int dir) {
    int prevX = snakeX[0]; // Store previous head position
    int prevY = snakeY[0];
    int prev2X, prev2Y;

    // Update the snake's head position based on direction
    switch (dir) {
        case 0: snakeY[0]--; break; // Up
        case 1: snakeX[0]++; break; // Right
        case 2: snakeY[0]++; break; // Down
        case 3: snakeX[0]--; break; // Left
    }

    // Check for collision with walls
    if (snakeX[0] <= 0 || snakeX[0] >= WIDTH - 1 || snakeY[0] <= 0 || snakeY[0] >= HEIGHT - 1) {
        gameOver = 1; 
        return; 
    }

    // Check for collision with itself
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = 1; 
            return; 
        }
    }

    // Move the snake's body
    for (int i = 1; i < snakeLength; i++) {
        prev2X = snakeX[i];
        prev2Y = snakeY[i];
        snakeX[i] = prevX;
        snakeY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Check if the snake has eaten the fruit
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        snakeLength++; // Just increase the length without checking for MAX_LENGTH
        score++; // Increase the score
        totalScore++; // Increase total score
        
        // Place a new fruit in a valid location
        do {
            fruitX = rand() % (WIDTH - 2) + 1; 
            fruitY = rand() % (HEIGHT - 2) + 1; 
        } while (!isFruitLocationValid(fruitX, fruitY)); 
    }
}

// Function to display the game over message and prompt for action
void gameOverMessage() {
    char choice;

    while (1) {
        system("cls"); // Clear the console
        printf("Game Over! Final score: %d\n", score);
        printf("Total Score: %d\n", totalScore);
        printf("Press R to restart or Q to quit.\n");

        choice = _getch(); // Wait for user input
        if (choice == 'r' || choice == 'R') {
            // Reset the game state
            score = 0;
            snakeLength = 1;
            gameOver = 0; // Reset game over flag
            initializeBoard(); // Reinitialize the board
            return; // Exit the function to return to the main game loop
        } else if (choice == 'q' || choice == 'Q') {
            exit(0); // Exit the program
        }
    }
}


