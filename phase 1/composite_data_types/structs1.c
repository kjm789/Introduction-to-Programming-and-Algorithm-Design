/***************************
 * Name: Tyler Nivin
 *
 * Description: A small intro to structs in C using a "person" struct as an example. 
 * 
 * Notes: I do some things in this example with strings that are considered "unsafe". I do this so we can focus on the struct composite data type. 
 * If you are working on a personal project or assignment, it's best to properly buffer and sanitize the input you recieve from the user.
 *
 * Last Modified: Mon Oct 26, 2015  08:03PM
 **************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 50

typedef struct person {
    char name[MAX_NAME_LENGTH];
    int age;
    bool isStudent;    
} Person_t;

int main(int argc, char* argv[]) {
    //We declare a variable named "person" the is type Person_t. 
    Person_t person;

    printf("Please enter the name of the person: ");
    scanf("%s", person.name);
    
    printf("Please enter the age of the person: ");
    scanf("%d", &(person.age));

    printf("Is the person a student? 1 for yes, 0 for no: ");
    scanf("%d", (int*)&(person.isStudent));

    printf("Student Info: \n"
	    "Name: %s\n"
	    "Age: %d\n"
	    "isStudent: %s\n",
	    person.name,
	    person.age,
	    (person.isStudent) ? "yes" : "no");

    return 0;
}

/* Let's review what we did. 
 * We declared a variable called "person" that has data type Person_t. We defined Person_t as a struct that contains a 
 * char array of length MAX_NAME_LENGTH for the name, an int for the age, and a bool for whether or not they were a student. 
 *
 * Later, we used scanf to read in information about our person. We wanted to store what we read in into our struct, and specifically, into the correct
 * member of the struct. So, to access the correct member we use the dot operator, ".", in the fashion above. The syntax is $variablename.$membername, same as above.
 * 
 * Because of the data types of each member of our struct, we get to see some different scenarios when working with scanf. Recall, scanf takes the address of the 
 * place where you want to store the data. Since our name member is a char array, we use it similarly to how we use a normal char array; we access the name member 
 * by using person.name and give that directly to scanf. 
 *
 * For the age, we want to give scanf the address of the age member. So, we get the age member via person.age and use the address operator, "&", to give scanf the
 * correct arguement. Due to the way order of precendence is handled in C for the dot operator and the address operator, the parenthesis are not STRICTLY needed here.
 * However, it does make it very clear what you are trying to do, and is not a bad habit to have.
 *
 * Finally, we see something of particular interest when we want to set the person.isStudent member. This member has type bool, which is a special data type from 
 * stdbool.h. Strictly speaking, it's an int that has been defined to have only the values 0 or 1. This can give us a compile warning if we don't typecast the 
 * member to match the format specifier that we gave scanf originally. So, how do we do that? Well, it simply follows the rules for typecasting that you already know. 
 * We get the adress of person.isStudent the same way we did with person.age, and then we have a bool address. But we need an int address, so we typecast it to an 
 * int *. If you have a strong grasp of pointers, this should all be fairly obvious to you, but if you haven't gotten to pointers yet than look back at what we 
 * did here after learning about them. 
 *
 * Thoughts: Did you notice that things seem to break if you type in a name with a space? This is because we are using scanf(). Now would be a good time to 
 * look at some documentation for scanf(), and see if you know of or can find a better function to use that would allow you to read in a string with spaces.
 * 
 *
 *
 */

