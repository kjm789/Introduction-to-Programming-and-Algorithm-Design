/* 
 * File:   main.c
 * Author: TylerN
 *
 * Created on July 21, 2015, 7:24 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>



/*
 * 
 */

const char* memoName = "memo1.txt";
const char* dictionaryFileName = "words.txt";
const char* outputFileName = "output.txt";

#define MAX_WORD_SIZE 25
//Use a separate macro because Addresses can be longer than our words.
#define MAX_DATA_LENGTH 50

typedef struct word_tree_node {
    char data[MAX_WORD_SIZE];
    struct word_tree_node* left;
    struct word_tree_node* right;
} Tree_Node_t;

typedef struct word_list_node {
    char data[MAX_WORD_SIZE];
    struct word_list_node* next;
} List_Node_t;

typedef struct data_node {
    char data[MAX_DATA_LENGTH];
    struct data_node* next;
} Data_Node_t;

typedef struct {
    int num;
    Data_Node_t* stack;
} Data_Stack_Meta_t;

typedef struct {
    int num;
    List_Node_t* stack;
} Word_Stack_Meta_t;


void readWordFile(const char * filename, Tree_Node_t ** treeHead);
bool spellCheck(const char * currWord, Tree_Node_t * treeHead);

void printList(List_Node_t* listHead);
void preOrderPrintTree(Tree_Node_t* tree);
void freeTree(Tree_Node_t* tree);
void freeList(List_Node_t* tree);
bool stringIsNumber(const char * string);

Data_Stack_Meta_t* createDataStack(void);
void pushData(const char* data, Data_Stack_Meta_t* stack);
void popData(Data_Stack_Meta_t* stack);
void freeDataStack(Data_Stack_Meta_t* dataStackMeta);

Word_Stack_Meta_t* createWordStack(void);
void pushWord(const char* data, Word_Stack_Meta_t* stack);
void popWord(Word_Stack_Meta_t* stack, char* data);
void freeWordStack(Word_Stack_Meta_t* wordStackMeta);

void spellCheckFile(const char* memoFile, Tree_Node_t* treeHead, Word_Stack_Meta_t* wordStackMeta);

void parseFile(const char * memoFile, Tree_Node_t* treeRoot,
        Data_Stack_Meta_t* addressStack, Data_Stack_Meta_t* emailStack,
        Data_Stack_Meta_t* phoneNumberStack, Data_Stack_Meta_t* salaryStack,
        Data_Stack_Meta_t* nameStack, Word_Stack_Meta_t* wordStack);

void printEmpData(const char * outFile,
        Data_Stack_Meta_t* addressStack, Data_Stack_Meta_t* emailStack,
        Data_Stack_Meta_t* phoneNumberStack, Data_Stack_Meta_t* salaryStack,
        Data_Stack_Meta_t* nameStack, Word_Stack_Meta_t* wordStack);

bool isEmail(const char*);
bool isSalary(const char*);
bool isPhoneNumber(const char*);

int main(int argc, char** argv) {

    //allocate a handle for our balanced BST
    Tree_Node_t* treeHead = NULL;
    //allocate a stack to store the misspelled words.
    Word_Stack_Meta_t* wordStack = createWordStack();

    //allocate handles for stacks.
    Data_Stack_Meta_t* nameStack = createDataStack();
    Data_Stack_Meta_t* addressStack = createDataStack();
    Data_Stack_Meta_t* emailStack = createDataStack();
    Data_Stack_Meta_t* phoneNumberStack = createDataStack();
    Data_Stack_Meta_t* salaryStack = createDataStack();


    int i;


    readWordFile(dictionaryFileName, &treeHead);
    //spellCheckFile("memo.txt", treeHead, wordStack);
    parseFile(memoName, treeHead, addressStack, emailStack,
            phoneNumberStack, salaryStack, nameStack, wordStack);

    printEmpData(outputFileName, addressStack, emailStack,
            phoneNumberStack, salaryStack, nameStack, wordStack);


    
    //These functions will free any nodes that might have gotten left on the 
    //stack and will free the meta data structure. 
    freeDataStack(nameStack);
    freeDataStack(addressStack);
    freeDataStack(emailStack);
    freeDataStack(phoneNumberStack);
    freeDataStack(salaryStack);

    freeWordStack(wordStack);


    //freeTree(treeHead);
    return (EXIT_SUCCESS);
}

bool stringIsNumber(const char * string) {
    while (*string != '\0') {
        if (isdigit(*string) == 0) {
            return false;
        }
        string++;
    }
    return true;
}

Tree_Node_t* createNode(const char* input) {
    Tree_Node_t* temp;

    if ((temp = (Tree_Node_t*) malloc(sizeof (Tree_Node_t))) == NULL) {
        fprintf(stderr, "unable to malloc for node.\n");
        return NULL;
    }
    memcpy(temp->data, input, MAX_WORD_SIZE);
    temp->left = NULL;
    temp->right = NULL;
    return temp;

}

/* The main function that constructs balanced BST and returns root of it.
       head_ref -->  Pointer to pointer to head node of linked list
       n  --> No. of nodes in Linked List 
 *     NOTE: 
 *     Based (almost entirely) on: http://www.geeksforgeeks.org/sorted-linked-list-to-balanced-bst/ 
 *      
 */

Tree_Node_t* sortedListToBSTRecur(List_Node_t **head_ref, int n) {
    /* Base Case */
    if (n <= 0)
        return NULL;

    /* Recursively construct the left subtree */
    Tree_Node_t* left = sortedListToBSTRecur(head_ref, n / 2);

    /* Allocate memory for root, and link the above constructed left 
       subtree with root */
    Tree_Node_t* root = createNode((*head_ref)->data);
    root->left = left;

    /* Change head pointer of Linked List for parent recursive calls */
    *head_ref = (*head_ref)->next;

    /* Recursively construct the right subtree and link it with root 
      The number of nodes in right subtree  is total nodes - nodes in 
      left subtree - 1 (for root) which is n-n/2-1*/
    root->right = sortedListToBSTRecur(head_ref, n - n / 2 - 1);

    return root;
}

void readWordFile(const char * filename, Tree_Node_t ** treeHead) {
    FILE* inFile;
    int i;
    List_Node_t* temp = NULL;
    List_Node_t* prevNode = NULL;
    List_Node_t* listHead = NULL;

    int num = 0;
    if ((inFile = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "can't open input file.\n");
        exit(1);
    }

    //first node.
    temp = malloc(sizeof (List_Node_t));
    fscanf(inFile, "%s", temp->data);
    temp->next = NULL;

    //set the listHead to the node we just malloced and set prevNode to the
    //first node in the linked list.
    listHead = temp;
    prevNode = listHead;


    while (!feof(inFile)) {
        if ((temp = (List_Node_t*) malloc(sizeof (List_Node_t))) == NULL) {
            fprintf(stderr, "unable to malloc for node.\n");
            freeList(listHead);
            fclose(inFile);
        }
        fscanf(inFile, "%s", temp->data);
        temp->next = NULL;
        prevNode->next = temp;
        prevNode = temp;
        num++;
    }

    temp = listHead;

    *treeHead = sortedListToBSTRecur(&temp, num);

    //We are done with the linked list, so free it.
    freeList(listHead);

    fclose(inFile);
    return;
}

void freeList(List_Node_t* tree) {
    if (!(tree)) {
        return;
    }
    freeList(tree->next);
    free(tree);
    return;
}

void freeTree(Tree_Node_t* tree) {
    //If past a null node, do nothing. 
    if (!(tree)) {
        return;
    }

    //Now, go as far left as we can, then go right, recursively freeing. 
    freeTree(tree->left);
    freeTree(tree->right);

    //Now we can free the current node.
    free(tree);
    return;
}

void preOrderPrintTree(Tree_Node_t* tree) {
    //If we reach a null node, do nothing.
    if (!(tree)) {
        return;
    }

    //Print curr node BEFORE moving left or right. 
    printf(" %s\n", tree->data);

    preOrderPrintTree(tree->left);
    preOrderPrintTree(tree->right);
    return;
}

void printList(List_Node_t* listHead) {
    List_Node_t* currentNode = listHead;

    while (currentNode != NULL) {
        printf("%s\n", currentNode->data);
        currentNode = currentNode->next;
    }
    return;
}

bool spellCheck(const char * currWord, Tree_Node_t * treeHead) {
    //This is more or less a recurse binary search. 
    //Just to check things out...
    //printf("%s\n", currWord);
    //printf("%s\n", treeHead->data);

    // If treeHead is null, it was not found.
    if (!treeHead) {
        return false;
    }

    //Evaluate strcmp so we don't have to call it multiple times
    int direction = strcmp(currWord, treeHead->data);

    //If we have found it
    if (direction == 0) {
        return true;
    }//If the word we are searching for is on the left.
    else if (direction < 0) {
        return spellCheck(currWord, treeHead->left);
    }//If the word we are searching for is on the right.
    else {
        return spellCheck(currWord, treeHead->right);
    }

}

void pushData(const char* data, Data_Stack_Meta_t* stack) {
    Data_Node_t* temp;

    if ((temp = malloc(sizeof (Data_Node_t))) == NULL) {
        printf("Unable to malloc for node.\n");
        //We should do some clean proper clean up, but not worried about that right now
        exit(1);
    }
    if (data) {
        memcpy(temp->data, data, MAX_DATA_LENGTH);
    } else {
        memcpy(temp->data, "\0", 1);
    }
    temp->next = stack->stack;
    stack->stack = temp;
    stack->num++;
    return;

}

void popData(Data_Stack_Meta_t* stack) {
    Data_Node_t* temp;
    if (stack->num == 0) {
        fprintf(stderr, "Unable to pop, stack is empty.\n");
        return;
    }

    //Grab the current top of the stack so we can free it
    temp = stack->stack;
    //change stack to point to the next node
    stack->stack = stack->stack->next;
    stack->num--;
    free(temp);
    return;

}

Data_Stack_Meta_t* createDataStack(void) {
    Data_Stack_Meta_t* newStack;

    if ((newStack = malloc(sizeof (Data_Stack_Meta_t))) == NULL) {
        fprintf(stderr, "Unable to create new stack.\n");
        //Handle this better than this. 
        exit(1);
    }

    newStack->num = 0;
    newStack->stack = NULL;
    return newStack;
}

Word_Stack_Meta_t* createWordStack(void) {
    Word_Stack_Meta_t* newStack;

    if ((newStack = malloc(sizeof (Word_Stack_Meta_t))) == NULL) {
        fprintf(stderr, "Unable to create new stack.\n");
        //Handle this better than this. 
        exit(1);
    }

    newStack->num = 0;
    newStack->stack = NULL;
    return newStack;
}

void pushWord(const char* data, Word_Stack_Meta_t* stack) {
    List_Node_t* temp;

    if ((temp = malloc(sizeof (List_Node_t))) == NULL) {
        printf("Unable to malloc for node.\n");
        //We should do some clean proper clean up, but not worried about that right now
        exit(1);
    }

    memcpy(temp->data, data, MAX_WORD_SIZE);
    temp->next = stack->stack;
    stack->stack = temp;
    stack->num++;
    return;
}

void popWord(Word_Stack_Meta_t* stack, char* data) {
    List_Node_t* temp = NULL;
    if (stack->num == 0) {
        fprintf(stderr, "Unable to pop, stack is empty.\n");
        return;
    }

    if (data) {
    //copy the data we want.
        memcpy(data, stack->stack->data, MAX_DATA_LENGTH);
    }
    //Grab the current top of the stack so we can free it
    temp = stack->stack;
    //change stack to point to the next node
    stack->stack = stack->stack->next;
    stack->num--;
    free(temp);
    return;
}

void freeDataStack(Data_Stack_Meta_t* dataStackMeta) {
    Data_Node_t* temp;
    while ((temp = dataStackMeta->stack) != NULL) {
        dataStackMeta->stack = dataStackMeta->stack->next;
        free(temp);
        temp = NULL;
    }
    free(dataStackMeta);
    return;
}

void freeWordStack(Word_Stack_Meta_t* wordStackMeta) {
    //List_Node_t* temp = NULL;
    //if (wordStackMeta->num == 0){ return; }
    while (wordStackMeta->num > 0) {
        popWord(wordStackMeta, NULL);
    }
    free(wordStackMeta);
    return;
   
}

/* This function will push on to the stack any words it can not find in the tree.
 * main() will handle the rest.
 */
void spellCheckFile(const char* memoFile, Tree_Node_t* treeHead, Word_Stack_Meta_t* wordStackMeta) {
    FILE* inputFile;
    char currWord[MAX_WORD_SIZE];

    if ((inputFile = fopen(memoFile, "r")) == NULL) {
        fprintf(stderr, "Could not open memo file.\n");
        return;
    }

    //Read in the memo one word at a time, pushing onto the stack when something
    //is misspelled.
    while (fscanf(inputFile, "%s", currWord) > 0) {

        //We need to make sure that there is no period... 
        currWord[strcspn(currWord, ".")] = 0;
        //printf("%s\n", currWord);

        if (!spellCheck(currWord, treeHead)) {
            pushWord(currWord, wordStackMeta);
        }
    }

    fclose(inputFile);
    return;
}

bool isEmail(const char* data) {
    while ('\0' != *data) {
        if (*data == '@') {
            return true;
        }
        data++;
    }
    return false;
}

bool isSalary(const char* data) {
    //Must start with '$'
    if (data[0] != '$') {
        return false;
    }

    //make sure there is a "." before the last two spots i.e. XXX.00
    if (strcspn(data, ".") + 1 != (strlen(data) - 2)) {
        return false;
    }

    return true;
}

bool isPhoneNumber(const char* data) {
    //If BOTH the 4th char and 8th char are '-' it's a phone number.
    //Remember, at this point we've already verified that the first char is a 
    //digit. 
    if (data[3] != '-' || data[7] != '-') {
        return false;
    } else return true;
}

//This file will push things onto the appropriate stacks. It will also determine
//Which parts of the sentence are what. This is the beefy one.

/*
 * memoFile -> The name of the memo file to open.
 * treeRoot -> The address of the root node of the balanced BST.
 * addressStack, emailStack, phoneNumberStack, salaryStack, nameStack 
 *  -> The address of the corresponding stack meta data structure.
 * wordStack -> The address of the stack to hold misspelled words.
 * 
 */

void parseFile(const char * memoFile, Tree_Node_t* treeRoot,
        Data_Stack_Meta_t* addressStack, Data_Stack_Meta_t* emailStack,
        Data_Stack_Meta_t* phoneNumberStack, Data_Stack_Meta_t* salaryStack,
        Data_Stack_Meta_t* nameStack, Word_Stack_Meta_t* wordStack) {
    FILE* inputFile;
    fpos_t currPos;

    bool nameFound = false;
    bool addressFound = false;
    bool salaryFound = false;
    bool phoneNumberFound = false;
    bool emailFound = false;

    char currWord[MAX_DATA_LENGTH];
    //declaring a second char array will allow us to "look-ahead"
    char nextWord[MAX_DATA_LENGTH];


    if ((inputFile = fopen(memoFile, "r")) == NULL) {
        fprintf(stderr, "Could not open memo file.\n");
        return;
    }

    //Read in the memo one word at a time, deciding if it's related to the data 
    //we want to keep or if it's a word to spell check as we go.
    while (fscanf(inputFile, "%s", currWord) > 0) {
        
        //strip any trailing punctuation...
        if (ispunct(currWord[(strlen(currWord) - 1)])) {
            currWord[(strlen(currWord) - 1)] = 0;
        }

        //check if it's possibly a name first...
        // -- Start by seeing if the first character of the word is uppercase.
        if (isupper(currWord[0])) {
            //Grab the current position of the file pointer in case this is NOT
            // a name.
            fgetpos(inputFile, &currPos);

            //if it is, grab the next word and see if IT starts with an uppercase.
            fscanf(inputFile, "%s", nextWord);
            if (isupper(nextWord[0])) {
                //One last quick and dirty cheat to avoid e.g. Jill Smith's 
                // and similar words.
                if (strcspn(nextWord, "'") < strlen(nextWord) - 2) {
                    fsetpos(inputFile, &currPos);
                    continue;
                }

                //If so, this is a name. Push it onto the name stack.
                strcat(currWord, " ");
                strcat(currWord, nextWord);
                pushData(currWord, nameStack);
                
                //HANDLE MAKING SURE STACKS ARE CONSISTENT!
                if (nameFound == false) {
                    //If this is the first name we have encountered,simply set
                    //the flag and continue.
                    nameFound = true;
                    //continue so we don't check the other possibilities.
                    continue;
                } else {
                    //Push any empty nodes that we need to...
                    if (!addressFound) {
                        pushData(NULL, addressStack);
                    }
                    if (!salaryFound) {
                        pushData(NULL, salaryStack);
                    }
                    if (!emailFound) {
                        pushData(NULL, emailStack);
                    }
                    if (!phoneNumberFound) {
                        pushData(NULL, phoneNumberStack);
                    }
                    //Set all flags (except name) to false...
                    addressFound = false;
                    salaryFound = false;
                    emailFound = false;
                    phoneNumberFound = false;
                    //and continue.
                    continue;
                }
            } else {
                //If it's NOT a name, we need to move the file pointer back
                // before continuing.
                fsetpos(inputFile, &currPos);
                //So, first letter was capital, but not the first letter of next word.
                //Possible types: Email, word.
                if (isEmail(currWord)) {
                    //If it's an email, push it onto the stack.
                    pushData(currWord, emailStack);
                    emailFound = true;
                    continue;
                } else {
                    //If it's NOT a name, or an email, it's just a word.
                    //lowercase the first letter and search for it. 
                    currWord[0] = tolower(currWord[0]);
                    if (!spellCheck(currWord, treeRoot)) {
                        //If the word is NOT found in the dictionary...
                        //push it onto the stack of misspelled words.
                        pushWord(currWord, wordStack);
                        continue;
                    }
                }
            }
        }// If the first letter is NOT a capital letter...
            //Possibilities: Salary, Address, Phone number, email (lower first word)
            //Check for salary first...
        else if (isSalary(currWord)) {
            pushData(currWord, salaryStack);
            salaryFound = true;
            continue;
        }//check for Phone number... 
        else if (isPhoneNumber(currWord)) {
            pushData(currWord, phoneNumberStack);
            phoneNumberFound = true;
            continue;
        }//check for email
        else if (isEmail(currWord)) {
            pushData(currWord, emailStack);
            emailFound = true;
            continue;
        }//To check for address, see if the current word is a string of digits...
        else if (stringIsNumber(currWord)) {
            //If that returns true, concat the words until the next word that
            //is all number is read in. 
            do {
                //grab the next word, check if it's the end, concat if it's not.
                fscanf(inputFile, "%s", nextWord);
                //make sure we trim any periods...
                nextWord[strcspn(nextWord, ".")] = 0;
                if (stringIsNumber(nextWord)) {
                    //Found the end of the address.
                    strcat(currWord, " ");
                    strcat(currWord, nextWord);
                    pushData(currWord, addressStack);
                    addressFound = true;
                    break;
                } //else, we haven't yet found the end so concat and keep looping...
                strcat(currWord, " ");
                strcat(currWord, nextWord);
            } while (1);
            continue;
        }// At this point, all it can be is a regular word. 
        else {
            //remove the "." if there is one. 
            currWord[strcspn(currWord, ".")] = 0;
            //If we search for it and don't find it, add it to the list of 
            //misspelled words.
            if (!spellCheck(currWord, treeRoot)) {
                pushWord(currWord, wordStack);
                continue;
            }
        } //end search words
    } // end while loop.
    // Push any empty nodes that we need to...
    if (!addressFound) {
        pushData(NULL, addressStack);
    }
    if (!salaryFound) {
        pushData(NULL, salaryStack);
    }
    if (!emailFound) {
        pushData(NULL, emailStack);
    }
    if (!phoneNumberFound) {
        pushData(NULL, phoneNumberStack);
    }
    
    fclose(inputFile);
}

void printEmpData(const char * outFile,
        Data_Stack_Meta_t* addressStack, Data_Stack_Meta_t* emailStack,
        Data_Stack_Meta_t* phoneNumberStack, Data_Stack_Meta_t* salaryStack,
        Data_Stack_Meta_t* nameStack, Word_Stack_Meta_t* wordStack) {
    
    while (nameStack->num > 0) {

        printf("Employee: %s\n", nameStack->stack->data);
        printf("Salary: %s\n", (salaryStack->stack->data[0] != '\0') ? salaryStack->stack->data : "Not available");
        printf("Address: %s\n", (addressStack->stack->data[0] != '\0') ? addressStack->stack->data : "Not available");
        printf("Email: %s\n", (emailStack->stack->data[0] != '\0') ? emailStack->stack->data : "Not available");
        printf("Phone: %s\n", (phoneNumberStack->stack->data[0] != '\0') ? phoneNumberStack->stack->data : "Not available");
        puts("");

        popData(nameStack);
        popData(salaryStack);
        popData(addressStack);
        popData(emailStack);
        popData(phoneNumberStack);
    }
    
    printf("The input memo had %d misspelled words%c\n", wordStack->num, (wordStack->num) ? ':' : '.');
    
    while (wordStack->num > 0){
        printf("%s\n", wordStack->stack->data);
        popWord(wordStack, NULL);
    }

    return;
}