/* 
 * File:   main.c
 * Author: TylerN
 * 
 * Goals: Learn about more functions to leverage when parsing data from a file.
 * Count the number of words and number of punctuation marks.
 * Look up any functions used here that you aren't familiar with.
 * It is worth looking through ctype.h and seeing what functions are available.
 * 
 * Instructions: Read in a user-typed prompt and count different parts of it. 
 *
 * Created on July 26, 2015, 2:48 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 300 chars and '\0'
#define BUFFER_SIZE 301
/*
 * 
 */
int main(int argc, char** argv) {

    char* input = malloc(sizeof(char) * BUFFER_SIZE);
    int numPuncMarks = 0;
    int numSentences = 0; 
    char curr;
    int i = 0;
    
    printf("Enter a passage with multiple sentences not longer than 300 chars.\n"
            "Anything past 300 chars will be ignored.\n"
            "Press Enter to stop reading input:\n");
    fgets(input, BUFFER_SIZE, stdin);
    
    puts("");
    puts("Used input: ");
    puts(input);
    
    while ('\0' != (curr = input[i])) {
        if (ispunct(curr)){
            numPuncMarks++;
            if ( curr == '.' || curr == '?' || curr == '!') {
                numSentences++;
            }
        }
        i++;
    }
    
    printf("Number of punctuation marks: %d\n", numPuncMarks);
    printf("Number of Sentences: %d\n", numSentences);
    
    
    free(input);
    
    return (EXIT_SUCCESS);
}

