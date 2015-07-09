/* 
 * File:   main.c
 * Author: TylerN
 * 
 * Goals: 
 *  Introduce fwrite and fopen. 
 *  Use structs as a fixed-size record.
 *  Further review of structs and pointers.
 *  random access to a file. 
 *  
 *  
 * Created on June 22, 2015, 1:52 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 25
#define NUM_SCORES 3

//THIS WILL NOT CHANGE!
//This is the number of records in the file. 
#define NUM_STUDENTS 100

typedef struct {
    char name[NAME_SIZE];
    int scores[NUM_SCORES];
} Student;

Student read_student_data(const char* fileName, int index);
void update_student_data(const char* fileName, int index, Student updatedStudent);

/*
 * 
 */
int main(int argc, char** argv) {

    int index;
    int i;
    Student student;

    do {
        printf("Enter the index of the student you want to load(1-%d): ", NUM_STUDENTS);
        scanf("%d", &index);
        if (index > 100 || index < 1) {
            printf("Invalid index. Please try again.\n");
        }
    } while (index > 100 || index < 1);


    student = read_student_data("input.txt", index);


    printf("\nName: %s\n"
            "Score 1: %d\n"
            "Score 2: %d\n"
            "Score 3: %d",
            student.name,
            student.scores[0],
            student.scores[1],
            student.scores[2]);

    printf("\nUpdating this student's scores.\n");
    for (i = 0; i < NUM_SCORES; i++) {
        do {
            printf("Please enter a new score for exam %d: ", i + 1);
            scanf("%d", &student.scores[i]);
            if (student.scores[i] > 100 || student.scores[i] < 0) {
                printf("Invalid score. Please enter a score between 0 and 100 inclusive.\n");
            }
        } while (student.scores[i] > 100 || student.scores[i] < 0);
    }

    update_student_data("input.txt", index, student);

    printf("\nReading updated file.\n");

    student = read_student_data("input.txt", index);


    printf("\nName: %s\n"
            "Score 1: %d\n"
            "Score 2: %d\n"
            "Score 3: %d",
            student.name,
            student.scores[0],
            student.scores[1],
            student.scores[2]);

    return (EXIT_SUCCESS);
}

Student read_student_data(const char* fileName, int index) {

    FILE* inputFile;
    Student student;

    if ((inputFile = fopen(fileName, "rb+")) == NULL) {
        printf("Could not open input file");
        return student;
    }

    fseek(inputFile, (index - 1) * sizeof (Student), SEEK_SET);

    fread(&student, sizeof (Student), 1, inputFile);

    fclose(inputFile);
    return student;
}

void update_student_data(const char* fileName, int index, Student updatedStudent) {

    FILE* outputFile;

    if ((outputFile = fopen(fileName, "rb+")) == NULL) {
        printf("Could not open output file. Exiting.\n");
        return;
    }

    fseek(outputFile, (index - 1) * sizeof (Student), SEEK_SET);

    fwrite(&updatedStudent, sizeof (Student), 1, outputFile);

    fclose(outputFile);
    return;
}

