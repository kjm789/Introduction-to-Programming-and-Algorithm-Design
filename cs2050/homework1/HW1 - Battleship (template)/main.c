/* 
 * File:   main.c
 * Author: TylerN
 *
 * Created on June 10, 2015, 9:34 PM
 */

#include <stdio.h>
#include <stdlib.h> //for malloc and rand
#include <stdbool.h>
#include <time.h>   // to seed rand() function


/**
 * Board is usually a square, but in case we want to change dimensions.
 * Here the size is 17 to account for the case 
 *  where all ships are placed end to end.
 ***/
#define BOARD_SIZE_ROW 10
#define BOARD_SIZE_COLUMN 10

//Declare some constant expressions to use in our program

const char WATER = '~';
const char HIT = '*';
const char MISS = 'x';
const char MYSTERY = '?';

const char CARRIER = 'c';
const char BATTLESHIP = 'b';
const char CRUISER = 'r';
const char SUBMARINE = 's';
const char DESTROYER = 'd';

/**
 * Define a struct with two integers.
 * This will be the struct that stores the ROW and COLUMN 
 * for when a user "fires a missile".
 */
typedef struct {
    /*@TODO*/
} Coordinates;

/**Some enums. They make our code easier to read and understand. 
 * You will use them, but they have been defined for you.
 */
typedef enum {
    USER, COMPUTER, OPPONENT
} Player;

typedef enum {
    NORTH, SOUTH, EAST, WEST
} Direction;

typedef enum {
    CARRIER_LENGTH = 5,
    BATTLESHIP_LENGTH = 4,
    CRUISER_LENGTH = 3,
    SUBMARINE_LENGTH = 3,
    DESTROYER_LENGTH = 2
} ShipLength;

/**
 * Function prototypes. See the function definitions for the descriptions. 
 */
void init_game_board(char gameBoard[][BOARD_SIZE_COLUMN], const char initValue);
void place_ships_randomly(char gameBoard[][BOARD_SIZE_COLUMN]);
void place_ships_manually(char gameBoard[][BOARD_SIZE_COLUMN]);
bool check_ship_placement(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates startingPoint, Direction dir, ShipLength len);
void place_ship(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates startingPoint, Direction dir, const char shipType, ShipLength len);

void print_game_board(char gameBoard[][BOARD_SIZE_COLUMN], Player player);

void acquire_strike_coordinates(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates* strikeAttempt);
bool check_strike_coords(int row, int col);

bool fire_missile(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates coord);
void update_game_board(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates coord, const char value);


/*
 * 
 */
int main(int argc, char** argv) {

    /**
     * Declare and create the THREE game boards.
     * 1) The users game board. It will show their ships appropriately labeled
     *      and also the hits and misses of where the computer has fired.
     * 2) The users "game state" board. This board will at first be filled 
     *      with the MYSTERY character i.e. '?' and will change to HIT or MISS 
     *      depending on if they guessed the position of the computers ship correctly.
     * 3) The computer's game board. This will be used to store the computer's 
     *      ships and we will know if we hit the computer's ship by checking this board. 
     ***/ 
    char userGameBoard[BOARD_SIZE_ROW][BOARD_SIZE_COLUMN];
    char computerGameBoard[BOARD_SIZE_ROW][BOARD_SIZE_COLUMN];
    char userGameState[BOARD_SIZE_ROW][BOARD_SIZE_COLUMN];
    
    //Two variables to track both players health 
    //Health = summation of all ship lengths. 
    int userHealth = 17;
    int computerHealth = 17;

    Coordinates strikeAttempt;
    bool didHit; //Holds the boolean value of whether or not the last strike hit a ship.

    //Seed random number generator
    //@TODO

    //Init Game Boards
    /* @TODO */
    

    //Randomly place computer ships.
    /* @TODO */
    

    //Manually place player ships.
    /* @TODO */

    //Take turns firing at each other until someone wins.
    do {
        //USER GOES FIRST!
        //Print Users Game Board
        /* @TODO */
        //Print users view of opponents game board
        /* @TODO */

        //acquire AND DISPLAY the strike coordinates
        /* @TODO */
        printf("Strike coordinates are: %d, %d\n", /* @TODO */, /* @TODO */);
        
        //call fire_missile HINT: set the return value equal to didHit
        
        /* @TODO */
        //If it was a hit then update the game boards accordingly. 
        if (didHit) {
            /* @TODO Stuff*/
        } else {
            //if not, update the game boards accordingly.
            /* @TODO More stuff */
        }
        // END USER TURN
        
        //store random values into strikeAttempt for computers turn.
        /* @TODO */

        /**
         * @IMPORTANT 
         * The rest of this section has the same logic as the users turn. 
         * I am going to "@TODO" a bunch of code now. 
         */
        
        /* @TODO */

    } while (/* @TODO */);

    //When the code reaches this point, someone has won. 
    if (/* @TODO */){
        printf("\n~~~Congratulations! You won!~~~\n");
        //Print Users game board one last time
        /* @TODO */
        //print computers screen.
        /* @TODO */
    } else {
        printf("\n~~~Sorry! You lost!~~~\n");
        //Print Users game board one last time
        /* @TODO */
        //print computers screen.
        /* @TODO */
    }
    
    


    return (EXIT_SUCCESS);
}

/**
 * This is a one line function that simply updates the character 
 * stored at a given position in a given game board.
 * @param gameBoard
 * @param coord
 * @param value
 */
void update_game_board(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates coord, const char value) {
    /* @TODO */
}
/**
 * 
 * @param gameBoard - This is the game board of the person who is being fired AT.
 *  We will check this board to see if we have hit them. 
 * @param coord - strikeAttempt. 
 * @return whether or not we hit them.
 */
bool fire_missile(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates coord) {
    //store the value of the game board at the position into a char for easy comparison.
    char strikeZone = gameBoard[/* @TODO */][/* @TODO */];

    //IF the strike zone is not water, miss, or hit then it is a ship.
    /* @TODO */
}

/**
 * This function places the value initValue into every cell of the gameboard.
 * @param gameBoard
 * @param initValue - The constant character value to initialize the board with. 
 * It will be either WATER or MYSTERY, and is passed in to this function.
 */
void init_game_board(char gameBoard[][BOARD_SIZE_COLUMN], const char initValue) {
    /* @TODO */
}
/**
 * I'm giving you guys this one. 60 different formatting styles would make
 * my head explode. 
 * @param gameBoard
 * @param player
 */
void print_game_board(char gameBoard[][BOARD_SIZE_COLUMN], Player player) {
    int i, j;

    char* whichPlayer;
    if (player == USER) {
        whichPlayer = "Player";
    } else if (player == COMPUTER) {
        whichPlayer = "Computer";
    } else {
        whichPlayer = "Opponent";
    }

    printf("~~~ %s\'s game board ~~~\n\n", whichPlayer);

    //Decorate the game board with labels
    //Add a 2 column padding for the row labels.
    printf("%2c", ' ');
    for (i = 0; i < BOARD_SIZE_ROW; i++) {
        printf("%2d", i);
    }
    printf("\n"); // add new line;


    for (i = 0; i < BOARD_SIZE_ROW; i++) {
        //at the beginning of every row, add a row label.
        printf("%2d", i);
        for (j = 0; j < BOARD_SIZE_COLUMN; j++) {
            //For each row, print the characters
            printf("%2c", gameBoard[i][j]);
        }
        //Drop to the next line
        printf("\n");
    }
}

/**
 * This function should prompt the user to enter the coordinates they want to 
 * fire at for this turn. This function should also verify that the entered 
 * coordinates are part of the game board. If they are not, inform the user
 * and ask them for new coordinates. 
 * 
 * @param coord
 *   This is a pointer to a coord struct. We only need to use one for
 *   the whole game, simply changing the values each turn.  
 * @return void
 */
void acquire_strike_coordinates(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates* strikeAttempt) {
    int row, col;
    bool coordsAreValid = false;

    /** IMPORTANT NOTE: FOR THIS FUNCTION, it is OK to use scanf. 
     *  The reason I am not insisting that you guys use fgets or fgetc here is 
     *  because it would be a decent amount of work to parse in the value properly
     *  and while a GOOD solution would be using fgets or fgetc and verifying 
     *  the the inputted values were indeed integers, this homework assignment
     *  is already pretty large and I don't want you guys to worry about parsing
     *  right now.  
     *  - Tyler
     */

    do {
        printf("Please enter in the coordinates that you want to strike: \n");
        printf("Enter row: ");
        scanf("%d", &row);
        printf("Enter col: ");
        scanf("%d", &col);
        //Now, check to see if the coords are valid and tell the user 
        // if they are not valid. 
        coordsAreValid = /* @TODO */;
        if (/* @TODO */) {
            printf("Sorry, those coordinates are invalid. Please try again.\n\n");
            print_game_board(gameBoard, USER);
        }

    } while (/* @TODO */);

    //If the program reaches this point, then the strike coordinates are valid.
    //Set the coordinates 
    // HINT: use the strikeAttempt parameter. 
    // DOUBLE HINT: don't forget that it is a STRUCT.
    /* @TODO */

}

/**
 * This function verifies that the strike coords are on the board.
 * @param row
 * @param col
 * @return This function returns false if the row or column argument would be off
 *  of the edge of the board. 
 */
bool check_strike_coords(int row, int col) {

  /* @TODO */
}

/**
 * This function will set all 5 ships on the game board randomly. 
 * This function is used to place the computers ships. 
 *  
 * @param gameBoard
 */
void place_ships_randomly(char gameBoard[][BOARD_SIZE_COLUMN]) {
    //Declare a startingPoint and randomly initialize the values. 
    /* @TODO */

    //Declare a direction and randomly initialize it. 
    
    //@IMPORTANT I'm giving you this here, but PAY ATTENTION. 
    //There's something unique about this line that you will need to remember
    //later.
    Direction dir = (Direction) rand() % 4;

    //Place Battleship
    //keep randomizing the values until check_ship_placement is true
    //Yes, this can possibly take a while... especially on small game boards.
    //Theoretically, this could NEVER finish. However, since we start with the 
    // biggest ship and work down it should not be a problem. 

    while (/* @TODO */) {
        //Change values and try again
        /* @TODO */
    }

    //If the code reaches here then we can use the values to place the ship
    /* @TODO */

    //Repeat this process for the rest of the ships

    //Place Carrier 
    while (/* @TODO */) {
        //Change values and try again
        /* @TODO */
    }

    //If the code reaches here then we can use the values to place the ship
    /* @TODO */


    //Place Cruiser
    while (/* @TODO */) {
        //Change values and try again
        /* @TODO */
    }

    //If the code reaches here then we can use the values to place the ship
    /* @TODO */

    //Place Submarine
    while (/* @TODO */) {
        //Change values and try again
        /* @TODO */
    }

    //If the code reaches here then we can use the values to place the ship
    /* @TODO */

    //Place Destroyer
    while (/* @TODO */) {
        //Change values and try again
        /* @TODO */
    }

    //If the code reaches here then we can use the values to place the ship
    /* @TODO */

}

/**
 * This function will check to see if the ship can be placed in a given position based on ship length, 
 *  starting point, and direction. It WILL account for the borders of the game board and intersecting ships. 
 * 
 * @param gameBoard
 * @param startingPoint - the starting point of where to place the ship
 * @param dir - the direction in which to try to place the ship
 * @param len - the length of the ship being placed
 * @return True if the ship placement is ok to be used. 
 * 
 * Make sure that ships do not overlap and are entirely on the board. 
 * HINT: Use the ShipLength enum, direction, and a starting point variable. 
 *  What would happen if you add shipLength to startingPoint while accounting for direction?
 * HINT: if you are trying to use something like startingPoint.col - len you are VERY CLOSE, but you have a logic error. 
 *  Draw it out to see why you have a logic error. 
 * @SUPERIMPORTANT: You will HAVE to typecast len to an int. As an enum, it is unsigned.
 * having an unsigned int when trying to do some of the comparisons will result in broken ships.
 * 
 */
bool check_ship_placement(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates startingPoint, Direction dir, ShipLength len) {
    int i;

    //First, make sure placing the ship will not pass any of the borders
    if (dir == /* @TODO */) {
        //If the direction is west, we will /* @TODO */ the /* @TODO */ from the /* @TODO */ value
        if (/* @TODO */) {
            return false;
        }

        //If the placement does not exceed the edge then check if it will intersect a ship.
        for (i = 0; i < /* @TODO */; i++) {
            //IMPORTANT: At this point in the game there will only be ships and water. 
            if (gameBoard[/* @TODO */][/* @TODO */] != WATER) {
                return false;
            }
        }

    } else if (/* @TODO */) {
        //If the direction is east, we will /* @TODO */ the /* @TODO */ to the /* @TODO */ value
        if (/* @TODO */) {
            return false;
        }

        //If the placement does not exceed the edge then check if it will intersect a ship.
        for (i = 0; i < len; i++) {
            //IMPORTANT: At this point in the game there will only be ships and water. 
            if (gameBoard[/* @TODO */][/* @TODO */] != WATER) {
                return false;
            }
        }
    } else if (/* @TODO */) {
        //If the direction is north, we will /* @TODO */ the /* @TODO */ to the /* @TODO */ value
        if (/* @TODO */) {
            return false;
        }

        //If the placement does not exceed the edge then check if it will intersect a ship.
        for (i = 0; i < len; i++) {
            //IMPORTANT: At this point in the game there will only be ships and water. 
            if (gameBoard[/* @TODO */][/* @TODO */] != WATER) {
                return false;
            }
        }

    } else if (/* @TODO */) {
        //If the direction is south, we will /* @TODO */ the /* @TODO */ to the /* @TODO */ value
        if (/* @TODO */) {
            return false;
        }

        //If the placement does not exceed the edge then check if it will intersect a ship.
        for (i = 0; i < len; i++) {
            //IMPORTANT: At this point in the game there will only be ships and water. 
            if (gameBoard[/* @TODO */][/* @TODO */] != WATER) {
                return false;
            }
        }
    }
    //If the program reaches this point then the ship is OK to be placed.
    return true;

}

/**
 * No checking is required here because you should call check_ship_placement BEFORE calling this function. 
 * @param gameBoard
 * @param startingPoint
 * @param dir
 * @param shipType
 */
void place_ship(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates startingPoint, Direction dir, const char shipType, ShipLength len) {
    /* @TODO */
}

void place_ships_manually(char gameBoard[][BOARD_SIZE_COLUMN]) {
    //Declare a startingPoint for the ship. 
    /* @TODO */
    //Declare a direction that ship will be placed in.
    int tempDir; //user to read in direction using scanf because we have to type cast it to a direction. 
    Direction dir;

    // In this function, it is ok to use scanf again. I don't want you to worry about parsing.
    printf("\n\n~~~Placing ships!~~~\n\n");

    //Place Battleship
    print_game_board(gameBoard, USER);
    printf("Placing your battleship: \n");

    //acquire startingPoint coordinates. 
    printf("Please enter starting point row (0 - %d): ", BOARD_SIZE_ROW - 1);
    scanf("%d", /* @TODO */);
    printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
    scanf("%d", /* @TODO */);

    //acquire ship direction
    printf("Directions: North(0), South(1), East(2), West(3)\n");
    printf("Please enter a direction for the ship to \"face\": ");
    scanf("%d", &tempDir);
    dir = (Direction) tempDir;

    //Keep asking the user for values until they place the battleship properly.
    while (check_ship_placement(/* @TODO */) == false) {
        printf("Something was wrong with the starting coordinates and direction you entered. Please try again.\n");
        //Change values and try again
        print_game_board(gameBoard, USER);
        printf("Placing your battleship: \n");

        //acquire startingPoint coordinates. 
        printf("Please enter starting point row (0 - %d): ", BOARD_SIZE_ROW - 1);
        scanf("%d", /* @TODO */);
        printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
        scanf("%d", /* @TODO */);

        //acquire ship direction
        printf("Directions: North(0), South(1), East(2), West(3)\n");
        printf("Please enter a direction for the ship to \"face\": ");
        scanf("%d", &tempDir);
        dir = (Direction) tempDir;
    }

    //If the code reaches here then we can use the values to place the ship
    place_ship(/* @TODO */);

    //Repeat this process for the rest of the ships
    /* @TODO */
    //@IMPORTANT I HIGHLY recommend that you get this working for one ship and
    // then copy and paste the above for the rest and change only the necessary 
    // values. This function is 208 lines in my solution. 

  
}