/* 
 * File:   main.c
 * Author: TylerN
 * 
 * Goals: 
 *  Introduce fwrite and fopen. 
 *  Use structs as a fixed-size record.
 *  Further review of structs and pointers.
 *  sequential write to a file. 
 *  Introduce memcpy.
 *  
 * Created on June 22, 2015, 1:52 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 25
#define NUM_SCORES 3

typedef struct student {
    char name[NAME_SIZE];
    int scores[NUM_SCORES];
} Student;

void load_student_data(Student* newStudent, char* name, int* scores);
void write_to_text_file(Student* students, int numStudents, const char* fileName);
void acquire_student_data(Student* students, int numStudents);

/*
 * 
 */
int main(int argc, char** argv) {

    //Ask the user how many student structures to create.
    int numStudents, i;
    printf("Please tell me how many student records you want to create: ");
    scanf("%d", &numStudents);

    //Declare the array of Students. 
    Student students[numStudents];

    //call acquire_student_data which in turn calls load_student_data.
    acquire_student_data(students, numStudents);

    /*for (i = 0; i < numStudents; i++) {
        printf("\nName: %s\n"
                "Score 1: %d\n"
                "Score 2: %d\n"
                "Score 3: %d\n",
                students[i].name,
                students[i].scores[0],
                students[i].scores[1],
                students[i].scores[2]);
    }*/


    //write the information to a text file. 
    write_to_text_file(students, numStudents, "input.txt");


    return (EXIT_SUCCESS);
}

/**
 * This function will repeatedly ask the user for the data we want to store into
 * the student records and will call load_student_data in order to store the data. 
 * 
 * 
 * @param students - This is a pointer to the students array.
 * @param numStudents - This is the number of student records. 
 */
void acquire_student_data(Student* students, int numStudents) {

    //Declare the scores array and initialize it to 0. 
    int scores[] = {0, 0, 0};
    char newName[NAME_SIZE];
    int i, j;


    //Manual
    for (i = 0; i < numStudents; i++) {
        printf("\nPlease enter student %d's name: ", i + 1);
        scanf("%s", newName);

        printf("Please enter the exam scores\n");

        for (j = 0; j < NUM_SCORES; j++) {
            printf("Please enter score %d: ", j + 1);
            scanf("%d", &scores[j]);
        }

        //Test that this function works. 
        /*printf("\nName: %s\n"
                "Score 1: %d\n"
                "Score 2: %d\n"
                "Score 3: %d\n",
                newName,
                scores[0],
                scores[1],
                scores[2]);*/
        
        load_student_data(&students[i], newName, scores);
    }
    return;
}

/**
 * This function takes a pointer to a student, a character pointer that we treat
 *  as a string, and a pointer to an array of scores. 
 * 
 * Given the inputs, this function stores to name and the three scores into the
 *  student that the newStudent pointer points to. 
 * 
 * @param newStudent - This is a pointer to a student. 
 * @param name - This is a character pointer that we treat as a string. We will 
 *  copy this into the student struct. 
 * @param scores - This is a pointer to an array of integer scores. We will copy
 *  the entire array into the student struct. 
 */
void load_student_data(Student* newStudent, char* name, int* scores) {

    //Copy the name to the struct.
    strcpy(newStudent->name, name);

    //This method uses the memcpy function to copy the array. 
    //I suggest looking it up and using it.
    //memcpy(newStudent->scores, scores, sizeof(int) * 3);

    //Another method in case you are intimidated by memcpy();
    int i;
    for (i = 0; i < NUM_SCORES; i++) {
        newStudent->scores[i] = scores[i];
    }

    //Verify everything worked.
    /*printf("\nName: %s\n"
                "Score 1: %d\n"
                "Score 2: %d\n"
                "Score 3: %d\n",
                newStudent->name,
                newStudent->scores[0],
                newStudent->scores[1],
                newStudent->scores[2]);*/

    return;
}

/**
 * This function takes the students array and writes the array and all of it's data 
 * to a file. 
 * 
 * 
 * @param students
 * @param numStudents
 * @param fileName - A constant char * that we treat as a string. This is used to 
 * open the file that we want to write to. It is the name of the file. For example,
 * if we wanted to write the data to a file called "output.txt" we would call 
 * the function like this: write_to_file(students, numStudents, "output.txt");
 * Be sure to close the file pointer when we are done. 
 */
void write_to_text_file(Student* students, int numStudents, const char* fileName) {
    FILE* outputFile;
    Student test;
    int i, j;

    //Open the file for writing. If the file exists, it will be deleted. 
    //If the file can not be opened, exit. 

    if ((outputFile = fopen(fileName, "wb")) == NULL) {
        printf("Could not open output file. Exiting.\n");
        return;
    }

    fwrite(students, sizeof (Student), numStudents, outputFile);

    fclose(outputFile);

    //Verify that we wrote the records by reading them in. 
    if ((outputFile = fopen("input.txt", "rb")) == NULL) {
        printf("Could not open output file. Exiting.\n");
        return;
    }
    for (i = 0; i < numStudents; i++) {
        fread(&test, sizeof (test), 1, outputFile);
        printf("\nINSIDE WRITE FUNCTION\nName: %s\n", test.name);
        for (j = 0; j < NUM_SCORES; j++) {
            printf("Score: %d\n", test.scores[j]);
        }
    }

    fclose(outputFile);


    return;

}

