/***************************
 * Name: Tyler Nivin
 *
 * Description: This is another version of math.c that shows something about data types in C. Because we can go from int to float without losing precision, we can implement the functions from math.c using only the float data type. See the code below 
 *
 * A small program to show an example of calling functions and using their return values.
 *
 * Last Modified: Sun Oct 04, 2015  04:54PM
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

float add_float(float, float);
float multiply_float(float, float);

int main(int argc, char* argv[]) {
    //Declare and initialize local variables
    int choice = -1;
    float num1 = 0, num2 = 0;

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

    //ask the user for the two numbers to add or multiply
    printf("Enter the first number to use: ");
    scanf("%f", &num1);
    printf("Enter the second number to use: ");
    scanf("%f", &num2);

    
    //User wants addition
    if (choice == 1) {
	printf("Addition of %.2f and %.2f is: %.2f", num1, num2, add_float(num1, num2));
    } 
    //User wants multiplication
    else {
	printf("Multiplication of %.2f and %.2f is: %.2f", num1, num2, multiply_float(num1, num2));
    }


    return 0;
}

void print_menu(void){
    printf("Please select which operation you would like to do:\n"
	   "1) Addition\n"
	   "2) Multiplication\n"
	   "Enter Selection: ");
}

int check_input(int choice){
    //If the users choice is between 1 and 4 INCLUSIVE, then reurn 1 saying it is a good choice.
    if (choice == 1 || choice == 2) return 1;
    else return 0;
}

float add_float(float num1, float num2){
    return num1 + num2;
}

float multiply_float(float num1, float num2){
    return num1 * num2;
}



