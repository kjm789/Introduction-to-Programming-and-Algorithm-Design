/* 
 * File:   main.c
 * Author: TylerN
 * Goals: 
 *      create a simple linked list
 *      print out the linked list.
 * 
 * Created on July 2, 2015, 4:25 AM
 */

typedef struct node {
    int stuID;
    struct node* nextPtr;
} Node;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Node* create_node(int stuID);
Node* add_node(Node* listHead, Node* newNode);
void print_list(Node* listHead);
void free_list(Node* listHead);

/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(NULL));

    int i;
    Node* listHead = NULL;

    //The variable below is an ever-changing temp variable. 
    Node* newNode = NULL;
    int tempStuID;

    for (i = 0; i < 5; i++) {
        tempStuID = (rand() % 1000) + 1;
        newNode = create_node(tempStuID);
        
        listHead = add_node(listHead, newNode);
        
    }
    
    print_list(listHead);
    free_list(listHead);
    return (EXIT_SUCCESS);
}

Node*  create_node(int stuID) {
    Node * newNode= (Node*)malloc(sizeof(Node));
    
    newNode->stuID = stuID;
    newNode->nextPtr = NULL;

    return newNode;
}

void free_list(Node* listHead) {
    //Use temp to be able to free nodes as we traverse the list.
    Node* temp;

    //set temp = listHead and see if our lists is empty...
    while ((temp = listHead) != NULL) {
        //set the head of the list to the next node...
        listHead = listHead->nextPtr;
        //and free the node we are on. 
        free(temp);
    }
    return;
}

Node* add_node(Node* listHead, Node* newNode){
    Node* currentNode = listHead;
    
    //We have the check for the case where the list is empty first. 
    if (currentNode == NULL){
        return newNode;
    }
    
    //We want to go to the end of the list, so we use a loop to get there.
    while(currentNode->nextPtr != NULL){
        currentNode = currentNode->nextPtr;
    }
    
    //Now we are at the end of the list node, so add the newNode to the list...
    currentNode->nextPtr = newNode;
    return listHead;
}

void print_list(Node* listHead){
    Node* currentNode = listHead;
    int i = 1;
    
    while (currentNode != NULL){
        printf("Printing student %d:\n", i);
        printf("\tStudent ID: %d\n", currentNode->stuID);
        currentNode = currentNode->nextPtr;
        i++;
    }
    return;
}