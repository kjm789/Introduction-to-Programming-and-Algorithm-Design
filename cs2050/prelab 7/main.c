/* 
 * File:   main.c
 * Author: TylerN
 * Prelab 7: Intro to BSTs
 * 
 * Notes: 
 *  We are not trying to keep the BST balanced.
 *  We are not doing any searching, deleting, or updating. 
 *  In this particular tree, left is < currentNode, right is >= currentNode.
 *
 * Created on July 16, 2015, 9:39 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> //For time() function

typedef struct node_struct {
    int data;
    struct node_struct* left;
    struct node_struct* right;
} Node;

Node* createNode(int data);
void buildTree(Node** tree, int num);
void freeTree(Node* tree);
void printTree(Node* tree);

//Helper functions used while writing the solution. Provided to see the testing process.
//These would be removed before submitting as a finished solution.

//This function allows us to see that we have created our node successfully.

void printNode(Node* temp) {
    printf("data: %d, left: %p, right %p\n", temp->data, temp->left, temp->right);
}

/*
 * 
 */
int main(int argc, char** argv) {
    Node* tree = NULL;
    
    buildTree(&tree, 5);
    buildTree(&tree, 6);
    buildTree(&tree, 15);
    buildTree(&tree, 3);
    buildTree(&tree, 7);
    buildTree(&tree, 2);
    buildTree(&tree, 10);
    buildTree(&tree, 4);
    buildTree(&tree, 8);
    buildTree(&tree, 1);
    
    
    printf("In-order print: ");
    printTree(tree);
    
    freeTree(tree);
    
    //printNode(temp);


    return (EXIT_SUCCESS);
}

Node* createNode(int data) {
    Node* newNode;
    //Potential memory leak because we are working with a BST:
    if ((newNode = (Node*) malloc(sizeof (Node))) == NULL) {
        fprintf(stderr, "unable to allocate space for a node to hold: %d\n", data);
        exit(1);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void buildTree(Node** tree, int num) {
    //See if we have found the spot to insert the node.
    //Do this by checking for NULL
    if (!(*tree)) {
        *tree = createNode(num);
        return;
    }
    //else, move left or right accordingly.
    if (num < (*tree)->data)
        buildTree(&(*tree)->left, num);
    else
        buildTree(&(*tree)->right, num);
    return;
}

void freeTree(Node* tree) {
    //If past a null node, do nothing. 
    if (!(tree)) {
        return;
    }
    
    //Now, go as far left as we can, then go right, recursively freeing. 
    freeTree(tree->left);
    freeTree(tree->right);
    
    //Now we can free the current node.
    printf("\nFreeing node %d", tree->data);
    free(tree);
    return;
}
void printTree(Node* tree){
    //This function should be "primed" in main. We print JUST the number here.
    //This is an IN-ORDER print. 
    
    //If we reach a null node, do nothing.
    if (!(tree)){
        return;
    }
    
    printTree(tree->left);
    //Print curr node BEFORE moving right. 
    printf(" %d", tree->data);
    printTree(tree->right);
    return;
}
