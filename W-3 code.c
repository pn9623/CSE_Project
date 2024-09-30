#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <conio.h> 

 #define WIDTH 40 // Width of the display 
 
 void Init() {
  printf("Welcome to the Marquee Display!\n");
   printf("Press 'l' for left, 'r' for right, and 'q' to quit.\n\n"); 
   } 
   
   char getUserInput() { 
   if (_kbhit()) { // Check if a key was pressed 
   return _getch(); // Get the pressed key
    } return 0; // No input
	 }
	 
	void animateMarquee(const char *message) {
	  int len = strlen(message); 
	char display[WIDTH + 1];
	int direction = 1; // 1 for right, -1 for left
	int position = 0; 
		 
		for (;;) {
		// Fill the display array with spaces 
		memset(display, ' ', WIDTH);
		display[WIDTH] = '\0';
		  
		   // Create the marquee effect 
		   for (int j = 0; j < WIDTH; j++) {
		   int index = (position + j * direction + len) % len;
			display[j] = message[index]; 
			}
			// Print the display
			  
			printf("\r%s", display); 
			fflush(stdout);
			usleep(100000); // Adjust the speed of the marquee
			  
			   
			// Check for user input to change direction or terminate 
			char ch = getUserInput(); 
			if (ch == 'l') { // Left 
			direction = -1;
			  } else if (ch == 'r') { // Right 
			direction = 1;
			} else if (ch == 'q') { // Quit 
		     break;
				
			 } 
				 
			position += direction; // Update position 
			if (position < 0) position += len; // Wrap around 
			position %= len; // Ensure position stays within bounds
			 }
			  }
			int main() {
				const char *message = "Welcome to the Marquee Display! Press 'l' for left, 'r' for right, and 'q' to quit."; 
					 
				Init(); // Call Init to print the opening message 
				animateMarquee(message); // Start the marquee animation
					 
				printf("\nGoodbye!\n"); 
				 return 0;
				 }
