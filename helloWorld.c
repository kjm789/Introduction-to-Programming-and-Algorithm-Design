/*****************************
 * Name: Tyler Wolfe Nivin
 * 
 * Purpose: 
 *
 * Last Modified: Tue Feb 17, 2015  10:39AM
 * **************************/

#include <stdio.h>

int main (void){
	//Declare an int so we can store user input somewhere
	int x;

	//print a message to the user asking for input, get the input, and tell the user what the input was.
	printf("Hello! Please enter a number: ");
	scanf("%d", &x);
	printf("The number entered was: %d\n",x);

}
