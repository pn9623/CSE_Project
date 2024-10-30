# CSE_Project
                                                   README file                             group-1            Nikunj and melvince 




Game Overview
In this Snake game, the player controls a snake that moves around a bounded 2D grid. The objective is to eat fruits, which causes the snake to grow longer. The game ends when the snake collides with the walls or itself.


Features
•	Classic Snake gameplay with simple controls.
•	Randomly generated fruit placement.
•	Score tracking for both current and total scores.
•	Restart or quit options upon game over.
•	Basic collision detection.




Requirements
•	A C compiler (e.g., GCC, MinGW) to compile the code.
•	A Windows environment for compatibility with conio.h and windows.h functions.







Gameplay Instructions
•	Movement Controls:
o	W: Move Up
o	A: Move Left
o	S: Move Down
o	D: Move Right
o	P: Pause/Unpause the game
o	Q: Quit the game



•	Objective:
o	Collect fruits (*) to grow the snake and increase your score.
o	Avoid colliding with walls (#) or the snake itself.




Code Structure
The code consists of several key functions:
•	main(): Controls the main game loop and user input.
•	displayWelcomeMessage(): Shows the welcome message and game instructions.
•	initializeBoard(): Sets up the game board with borders, the snake, and fruit.
•	drawBoard(): Renders the current state of the game board to the console.
•	updateBoard(): Updates the board state based on the current position of the snake and fruit.
•	isFruitLocationValid(): Validates if the fruit can be placed at the given coordinates.
•	updateSnake(int dir): Updates the snake's position and checks for collisions.
•	gameOverMessage(): Displays the game over message and allows the player to restart or quit.

