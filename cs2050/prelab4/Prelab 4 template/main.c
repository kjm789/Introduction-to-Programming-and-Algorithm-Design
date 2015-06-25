/* 
 * File:   main.c
 * Author: TylerN
 *
 * Created on June 24, 2015, 7:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//For timing functions.
#include <sys/time.h>

#define NUM_PEOPLE 25

typedef struct person {
    int id;
    int age;
} Person;


void fill_array(Person* people, int numPeople);
void bubble_sort(Person* people, int numPeople);
void print_array(Person* people, int numPeople);

/*
 * 
 */
int main(int argc, char** argv) {

   
    
    //don't forget to free your memory.
    
    return (EXIT_SUCCESS);
}

void fill_array(Person* people, int numPeople) {
    
    return;
}

void bubble_sort(Person* people, int numPeople) {
    int i, j;
    Person temp;
    
    for (i=0; i< numPeople - 1; i++) {
        for (j=0; j< numPeople - i - 1; j++) {
            
            if (people[j].id > people[j+1].id){
                /* swap the two structs. */ 
                memcpy(&temp, &people[j], sizeof(Person));
                memcpy(&people[j], &people[j+1], sizeof(Person));
                memcpy(&people[j+1], &temp, sizeof(Person));
            }       
        }
    }
}

void print_array(Person* people, int numPeople){
   
}

