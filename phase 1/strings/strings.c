/* strings.c
 * 
 * Author: Tyler Nivin
 *
 * Purpose: The following is a supplemental program to demonstrate how strings and different string
 *   functions in C work. On it's own, compiled and ran as-is, it's not hugely insightful.
 *   The real benefit comes from analyzing what is happening and uncommenting and commenting different parts
 *   of the program.
 *
 * Prior Knowledge: A basic understanding of pointers would be helpful, as well as a cursory introduction to malloc and memset
 *   although this is not strictly required to understand what is happening. 
 * 
 * Warning: This program produces a large amount of output in an effort to explain what's happening. It may be easier to read the output file and
 * run the program to see it in action/ refer to the source to see exactly what happens. 
 *
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 24
//INPUT_LENGTH is the maximum length of input we want to store. 
#define INPUT_LENGTH 15

const char* TEST_INPUT_TOO_LONG = "Computer's are the best and this won't fit in our input length.";
const char* TEST_INPUT_WILL_FIT = "This fits.";

void print_valid_c_string(const char* input);
void print_entire_buffer_as_chars(const char* input);
void print_entire_buffer_as_ints(const char* input);

int main(void){
    
    //allocate an "input buffer" that will be larger than our expected input.
    char* inputBuffer;
    inputBuffer = malloc(sizeof(char) * BUFFER_SIZE); 
    char input2[50];

    //Use memset to fill our input buffer with '~' so we can see what's left in our buffer after various functions. 
    //NOTE: 126 is the ASCII value for '~'. 
    memset(inputBuffer, 126, BUFFER_SIZE);
    
    print_valid_c_string(TEST_INPUT_WILL_FIT);
    print_entire_buffer_as_chars(TEST_INPUT_WILL_FIT);


    //Tell the user the sizes that we are working with.
    fprintf(stdout, "We have defined the following:\n"
	    "BUFFER_SIZE: %d - The maximum length of our input buffer.\n"
	    "INPUT_LENGTH: %d - The maximum length of input to \"read in\".\n"
	    "TEST_INPUT_TOO_LONG: \"%s\" - This is a string that is longer than we have space to store in our \"input\".\n"
	    "TEST_INPUT_WILL_FIT: \"%s\" - This is a string that WILL fit in our \"input\".\n"
	    "We use these two strings to see what happens in different scenarios.\n",
	    BUFFER_SIZE, INPUT_LENGTH, TEST_INPUT_TOO_LONG, TEST_INPUT_WILL_FIT);

    fprintf(stdout, "\nUsing:\nstrncpy(inputBuffer,TEST_INPUT_TOO_LONG,INPUT_LENGTH);\n");
    fprintf(stdout, "\nThis is what happens when we use function strncpy() to try to read in MORE chars into a buffer\n"
	    " than we have space to hold all of the chars.\n"
	    "As you can see, it is NOT a valid C string. Here, we see the extra \'~\' characters that are in our buffer, \n"
	    " but in practice we would be printing whatever was in memory for who knows how long.\n"
	    "This is because strncpy() will NOT append a null terminator\n"
	    " if it reaches the max size specified in the function call before finding a null terminator.\n");
    
    strncpy(inputBuffer, TEST_INPUT_TOO_LONG, INPUT_LENGTH);
    puts("");
    print_valid_c_string(inputBuffer);
    
    puts("");
    print_entire_buffer_as_chars(inputBuffer);
    
    puts("");
    print_entire_buffer_as_ints(inputBuffer);

    
    fprintf(stdout, "\nUsing: \n"
	    "strncpy(inputBuffer, TEST_INPUT_TOO_LONG, INPUT_LENGTH);\n"
	    "inputBuffer[INPUT_LENGTH] = 0;\n");
    fprintf(stdout, "\nNow we do something similar to above, but THIS TIME we manually add the null terminator \n"
	    " after the number of chars we want to read in.\n"
	    "Note: \'= 0\' is a valid way of adding the null terminator since 0 and null are the same in ASCII.\n"
	    "Note2: This is NOT the representation of the \"character\" 0, but rather the integer 0.\n"
	    "Refer to the ASCII charts for further clarification.\n");
    
    memset(inputBuffer, 126, BUFFER_SIZE);
    strncpy(inputBuffer, TEST_INPUT_TOO_LONG, INPUT_LENGTH);
    inputBuffer[INPUT_LENGTH] = 0;
    
    puts("");
    print_valid_c_string(inputBuffer);
    
    puts("");
    print_entire_buffer_as_chars(inputBuffer);
    
    puts("");    
    print_entire_buffer_as_ints(inputBuffer);
    puts("");

    fprintf(stdout, "The advantage of this method is that we can control EXACTLY how many chars are read in at most. This prevents\n"
	    " buffer overflow attacks and just general shenanigans. It's always best to use a function that allows us to control how much\n"
	    " of the data is being written, whether it's copying/moving strings or any other type of data.\n");


    fprintf(stdout, "\nNow, let's look at what happens when our input DOES fit in our buffer, based on the parameter we pass strncpy().\n"
	    "Using: \n"
	    "strncpy(inputBuffer, TEST_INPUT_WILL_FIT, INPUT_LENGTH);\n");

    memset(inputBuffer, 126, BUFFER_SIZE);
    strncpy(inputBuffer, TEST_INPUT_WILL_FIT, INPUT_LENGTH);
    
    puts("");
    print_valid_c_string(inputBuffer);
    
    puts("");
    print_entire_buffer_as_chars(inputBuffer);
    
    puts("");    
    print_entire_buffer_as_ints(inputBuffer);
    puts("");

    fprintf(stdout, "\nNotice something? strncpy() fills our buffer with \'0\' until it copies the number of bytes we tell it to.\n"
	    "This is how it ensures that the strings it copies are valid C strings AS LONG AS the destination can hold all of the source.\n");
    
    fprintf(stdout, "\nThe next method uses the function strcpy(). First we'll see what happens when the source we try to\n"
	    " copy is too large for the destination to store.\n"
	    "\nUsing: \n"
	    "strcpy(inputBuffer, TEXT_INPUT_TOO_LONG);\n");

    //WARNING: This line will probably cause a memory map on some systems. It doesn't on mac in terminal, but does/has on Windows.
    memset(inputBuffer, 126, BUFFER_SIZE);
    //strcpy(inputBuffer, TEST_INPUT_TOO_LONG);
    
    puts("");
    print_valid_c_string(inputBuffer);
    
    puts("");
    print_entire_buffer_as_chars(inputBuffer);
    
    puts("");    
    print_entire_buffer_as_ints(inputBuffer);
    puts("");

    fprintf(stdout, "Notice something about our input buffer? It's full of the test source string, regardless of the fact that\n"
	    " there wasn't enough room for it.\n"
	    "This is one of the \"dangers\" of using strcpy; it copies everything from the source into the destination until it finds\n"
	    " a null terminator. This can result in you over-writing memory that you didn't intend to and is a buffer-overflow.\n");

    fprintf(stdout, "\nFinally, we'll have one last scenario: where we use strcpy() and our destination can hold our source.\n"
	    "\nUsing: \n"
	    "strcpy(inputBuffer, TEST_INPUT_WILL_FIT);\n");
    
    memset(inputBuffer, 126, BUFFER_SIZE);
    strcpy(inputBuffer, TEST_INPUT_WILL_FIT);
    
    puts("");
    print_valid_c_string(inputBuffer);
    
    puts("");
    print_entire_buffer_as_chars(inputBuffer);
    
    puts("");    
    print_entire_buffer_as_ints(inputBuffer);
    puts("");
    fflush(stdout);

    memset(inputBuffer, 126, BUFFER_SIZE);
    strcpy(inputBuffer, TEST_INPUT_WILL_FIT);
    inputBuffer[strlen(inputBuffer)] = 126;
    strcpy(input2, inputBuffer);

    puts("");
    print_valid_c_string(inputBuffer);
    puts("");
    print_entire_buffer_as_chars(inputBuffer);
    
    puts("");    
    print_entire_buffer_as_ints(inputBuffer);
    puts("");



    fprintf(stdout, "\n\nSummary: As you can see, there are a few options and scenarios when working with strings in C and this \n"
	    " is NOT an all-inclusive lesson. Hopefully you can now see why you generally want to use strncpy over strcpy and \n"
	    " how each function handles the source and destination strings. Further recommended reading involves looking into \n"
	    " fgets(), fgetc(), scanf(), fscanf(), sscanf(), and sprintf(). Generally, I hope that what strings are in C, and how they work, is clearer\n"
	    " as a result of this lesson. Thanks!\n\n");

    free(inputBuffer);
    return 0;
}

/* This function takes a c string of any length and prints the string as you would expect normally. 
 * It works with pointers and prints until it finds a null terminator, but other methods for printing
 * valid c strings work just as well. 
 * I added an incrementor to prevent printing past our input buffer.
 */
void print_valid_c_string(const char* input){
    int i = 0;
    fprintf(stdout, "Using a \"regular\" method of printing a string: \n");
    while (*input != '\0' && i < BUFFER_SIZE){
	fprintf(stdout, "%c", *input);
	input++;
	i++;
    }
    //add a newline just for output formatting's sake.
    puts("");
    return;
}
/* This function displays the entire buffer's char contents. The limit is based on the macro defined at the top of the file. 
 */
void print_entire_buffer_as_chars(const char* input){
    int i;
    fprintf(stdout, "Using a method that allows us to print the char representation of our entire input buffer: \n");
    for(i=0; i < BUFFER_SIZE; i++) {
	fprintf(stdout, "\'%c\' ", input[i]);
    }
    puts("");
}

void print_entire_buffer_as_ints(const char* input){
    int i;
    fprintf(stdout, "Using a method that allows us to print the integer representation of our entire input buffer: \n");
    for(i=0; i < BUFFER_SIZE; i++) {
	fprintf(stdout, "\'%d\' ", input[i]);
    }
    puts("");
}


