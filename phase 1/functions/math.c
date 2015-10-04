/***************************
 * Name: Tyler Nivin
 *
 * Description: A small program to show an example of calling functions and using their return values.
 *
 * Last Modified: Sun Oct 04, 2015  03:49PM
 * Comments: The below code is not optimized for anything special e.g. performace. 
 * It is written this way to emphasize the use of functions. 
 *
 * We don't do error checking on the numbers passed to the addition and multiplication functions because adding or multiplying
 * two floats or ints should never cause a problem. (i'm excluding times when the result would be an overflow.)
 **************************/
#include <stdlib.h>
#include <stdio.h>

//Function prototypes belong at the top
void print_menu(void);
int check_input(int choice);

int add_int(int, int);
float add_float(float, float);

int multiply_int(int, int);
float multiply_float(float, float);

int main(int argc, char* argv[]) {
    //Declare and initialize local variables
    int choice = -1;
    int num1 = 0, num2 = 0;
    float num1Float = 0, num2Float = 0;

    do {
	//Call print menu so out user knows what selection they are making
	print_menu();
	//read in the choice from the user
	scanf("%d", &choice);

	//Check to see if the choice was bad; if so, tell the user and let the loop do the rest.
	if (check_input(choice) == 0) {
	    printf("\nIncorrect selection.\n");
	}

	//loop while the user has selected "bad" input.
    } while (check_input(choice) == 0);

    // The code past this line is a little... Well, I wouldn't be writing it if I wasn't trying to show using different 
    // data types and functions. Generally, we try to avoid having large sections of code wrapped in control blocks. 
    
    switch (choice) {
	//Integer addition
	case 1: 
	    printf("Please enter the first number you want to add: ");
	    scanf("%d", &num1);
	    printf("Please enter the second number you want to add: ");
	    scanf("%d", &num2);
	    
	    printf("Addition of %d and %d is: %d", num1, num2, add_int(num1,num2));
	    break;
	//Float Addition
	case 2: 
	    printf("Please enter the first number you want to add: ");
	    scanf("%f", &num1Float);
	    printf("Please enter the second number you want to add: ");
	    scanf("%f", &num2Float);
	    
	    printf("Addition of %.2f and %.2f is: %.2f", num1Float, num2Float, add_float(num1Float,num2Float));
	    break;
	
	//Int Multiplication
	case 3:
	    printf("Please enter the first number you want to multiply: ");
	    scanf("%d", &num1);
	    printf("Please enter the second number you want to multiply: ");
	    scanf("%d", &num2);
	    
	    printf("Multiplication of %d and %d is: %d", num1, num2, multiply_int(num1,num2));
	    break;
	
	//Float Multiplication
	case 4: 
	    printf("Please enter the first number you want to multiply: ");
	    scanf("%f", &num1Float);
	    printf("Please enter the second number you want to multiply: ");
	    scanf("%f", &num2Float);
	    
	    printf("Multiplication of %.2f and %.2f is: %.2f", num1Float, num2Float, multiply_float(num1Float,num2Float));
	    break;
	
	//No default necessary, 1-4 are the only possible values for choice since we error-checked it earlier.

    }

    return 0;
}

void print_menu(void){
    printf("Please select which operation you would like to do:\n"
	   "1) Integer Addition\n"
	   "2) Floating-point Number Addition\n"
	   "3) Integer Multiplication\n"
	   "4) Floating-point Number Multiplication\n"
	   "Enter Selection: ");
}

int check_input(int choice){
    //If the users choice is between 1 and 4 INCLUSIVE, then reurn 1 saying it is a good choice.
    if (choice > 0 && choice < 5) return 1;
    else return 0;
}

int add_int(int num1, int num2){
    return num1 + num2;
}

float add_float(float num1, float num2){
    return num1 + num2;
}

int multiply_int(int num1, int num2){
    return num1 * num2;
}

float multiply_float(float num1, float num2){
    return num1 * num2;
}



