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

#define NUM_PEOPLE 100

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

    srand(time(NULL));
    
    struct timeval start, end;
    double elapsedTime;

    Person* people = (Person*) malloc(sizeof (Person) * NUM_PEOPLE);
    
    fill_array(people, NUM_PEOPLE);
    printf("\nBEFORE SORTING: \n");
    print_array(people, NUM_PEOPLE);
    
    //Start time.
    /**
     * 
     * some code goes here to handle seeing how long the bubble_sort will take. 
     * I encourage you to google for an example, and the solution to the prelab 
     * is posted on Github under my account. -Tyler
     */
    gettimeofday(&start, NULL);
    bubble_sort(people, NUM_PEOPLE);
    gettimeofday(&end, NULL);
    
    
    printf("\nAFTER SORTING: \n");
    print_array(people, NUM_PEOPLE);
    
     // compute and print the elapsed time in millisec
    elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;   // us to ms
    
    printf("Bubblesort took %lf ms for %d records.\n", elapsedTime, NUM_PEOPLE);
    
    free(people);
    return (EXIT_SUCCESS);
}

void fill_array(Person* people, int numPeople) {
    int i;
    
    for (i = 0; i < numPeople; i++) {
        //generate a random number between 17 and 25 for the age.
        people[i].age = (rand() % 9) + 17;
        //generate a random number between 1 - 10000 for the ID. 
        //NOTE: this is susceptible to collisions. 
        people[i].id = (rand() % 10000) + 1;
    }
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
    return;
}

void print_array(Person* people, int numPeople){
    int i;
    
    for (i = 0; i < numPeople; i++) {
        printf("Person %d:\n"
                "\tID: %d\n"
                "\tAge: %d\n",
                i+1, people[i].id, people[i].age);
    }
    return;
}