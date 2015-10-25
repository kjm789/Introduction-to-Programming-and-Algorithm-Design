/***************************
 * Name: Tyler Nivin
 *
 * Description: This is a small example of declaring and using an int array that gets it size at run time. 
 *
 * Last Modified: Sun Oct 25, 2015  02:32AM
 **************************/
#include <stdlib.h>
#include <stdio.h>

void print_int_array(int array[], int size);

int main(int argc, char* argv[]) {
    
    //Declare a variable that we will use to size our array after reading it in. 
    int arraySize = 0;
    int i;

    printf("Please enter the size of array that you want to use: ");
    scanf("%d", &arraySize);

    int arrayExample[arraySize]; 

    print_int_array(arrayExample, arraySize);

    //We use a for loop to give our array some value. I use 5 here, but it could be any int value.
    for (i=0; i<arraySize; ++i) {
	arrayExample[i] = 5;
    }

    print_int_array(arrayExample, arraySize);

    return 0;
}

void print_int_array(int array[], int size){
    printf("PRINTING INTEGER ARRAY OF LENGTH: %d\n", size);

    int i;
    for (i=0; i<size; i++){
	printf("%d ", array[i]);		
    }
    printf("\n");

    //return here is not STRICTLY needed, because the function is void, but I like to explicitly say when I am done. 
    return;
}
