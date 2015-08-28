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
 * Board is usually a 10 X 10 square, but in case we want to change dimensions we use a macro here.
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

typedef struct {
    int row;
    int col;
} Coordinates;

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

    //Declare and create the THREE game boards.
    char userGameBoard[BOARD_SIZE_ROW][BOARD_SIZE_COLUMN];
    char computerGameBoard[BOARD_SIZE_ROW][BOARD_SIZE_COLUMN];
    //This game board is displayed to the user. It shows a history of their strikes.
    char userGameState[BOARD_SIZE_ROW][BOARD_SIZE_COLUMN];

    //Two variables to track both players health 
    //Health = summation of all ship lengths. 
    int userHealth = 17;
    int computerHealth = 17;
    
    Coordinates strikeAttempt;
    bool didHit; //Holds the boolean value of whether or not the last strike hit a ship.

    //Seed random number generator
    srand((int)time(NULL));

    //Init Game Boards
    init_game_board(userGameBoard, WATER);
    init_game_board(computerGameBoard, WATER);
    init_game_board(userGameState, MYSTERY);

    //Print Users Game Board (for Debug reasons)
    //print_game_board(userGameBoard, USER);

    //Randomly place computer ships.
    place_ships_randomly(computerGameBoard);
    //Print computers gameboard (for debug reasons)
    //print_game_board(computerGameBoard, COMPUTER);

    //Manually place player ships.
    //place_ships_manually(userGameBoard);
    //FOR DEBUG
    place_ships_randomly(userGameBoard);

    //Take turns firing at each other until someone wins.
    do {
        //USER GOES FIRST!
        //Print Users Game Board
        print_game_board(userGameBoard, USER);
        //Print users view of opponents game board
        print_game_board(userGameState, OPPONENT);
        //DEBUG print computers screen.
        print_game_board(computerGameBoard, COMPUTER);

        acquire_strike_coordinates(userGameBoard, &strikeAttempt);
        printf("Strike coordinates are: %d, %d\n", strikeAttempt.row, strikeAttempt.col);
        //strikeAttempt.row = rand() % BOARD_SIZE_ROW;
        //strikeAttempt.col = rand() % BOARD_SIZE_COLUMN;
        if (strikeAttempt.row == -1){
            userHealth = 0;
            break;
        } else if (strikeAttempt.row == -2){
            computerHealth = 0;
            break;
        }
        //call fire_missile
        didHit = fire_missile(computerGameBoard, strikeAttempt);
        //If it was a hit then update the game boards accordingly. 
        if (didHit) {
            update_game_board(userGameState, strikeAttempt, HIT);
            update_game_board(computerGameBoard, strikeAttempt, HIT);
            computerHealth--;
        } else {
            //if not, update the game boards accordingly.
            update_game_board(userGameState, strikeAttempt, MISS);
            update_game_board(computerGameBoard, strikeAttempt, MISS);
        }
        // END USER TURN
        strikeAttempt.row = rand() % BOARD_SIZE_ROW;
        strikeAttempt.col = rand() % BOARD_SIZE_COLUMN;

        didHit = fire_missile(userGameBoard, strikeAttempt);
        //If it was a hit then update the game boards accordingly. 
        if (didHit) {
            update_game_board(userGameBoard, strikeAttempt, HIT);
            userHealth--;
        } else {
            //if not, update the game boards accordingly.
            update_game_board(userGameBoard, strikeAttempt, MISS);
        }

    } while (userHealth > 0 && computerHealth > 0);

    //When the code reaches this point, someone has won. 
    if (userHealth > 0){
        printf("\n~~~Congratulations! You won!~~~\n");
        //Print Users game board one last time
        print_game_board(userGameBoard, USER);
        //print computers screen.
        print_game_board(computerGameBoard, COMPUTER);
    } else {
        printf("\n~~~Sorry! You lost!~~~\n");
        //Print Users game board one last time
        print_game_board(userGameBoard, USER);
        //print computers screen.
        print_game_board(computerGameBoard, COMPUTER);
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
    gameBoard[coord.row][coord.col] = value;
}

bool fire_missile(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates coord) {
    //store the value of the game board at the position into a char for easy comparison.
    char strikeZone = gameBoard[coord.row][coord.col];

    //IF the strike zone is not water, miss, or hit then it is a ship.
    if (strikeZone != '~' && strikeZone != 'x' && strikeZone != '*') {
        return true;
    } else {
        return false;
    }
}

/**
 * 
 * @param gameBoard
 * @param initValue the constant character value to initialize the board with. 
 * It will be either WATER or MYSTERY, and is passed in to this function.
 */
void init_game_board(char gameBoard[][BOARD_SIZE_COLUMN], const char initValue) {
    int i, j;

    for (i = 0; i < BOARD_SIZE_ROW; i++) {
        for (j = 0; j < BOARD_SIZE_COLUMN; j++) {
            gameBoard[i][j] = initValue;
        }
    }
}

void print_game_board(char gameBoard[][BOARD_SIZE_COLUMN], Player player) {
    int i, j;

    char* whichPlayer;
    if (player == USER) {
        //whichPlayer = "Player";
        //strdu
    } else if (player == COMPUTER) {
        whichPlayer = "Computer";
    } else {
        whichPlayer = "Opponent";
    }
    
    printf("~~~ %s\'s game board ~~~\n\n", whichPlayer);

    
    //Add a 2 column padding for the row labels.
    printf("%2c", ' ');
    
    //Decorate the game board with labels
    //Here we take advantage of the ASCII table to be able to incrememt i to change the letter we print.
    for (i = 0; i < BOARD_SIZE_ROW; i++) {
        printf("%2c", 65 + i);
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
 * @param gameBoard
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
        
        printf("Enter col: ");
        col = fgetc(stdin);
        
        //Now, check to see if the coords are valid and tell the user 
        // if they are not valid. 
        coordsAreValid = check_strike_coords(row, col);
        if (coordsAreValid == false) {
            printf("Sorry, those coordinates are invalid. Please try again.\n\n");
            print_game_board(gameBoard, USER);
        }

    } while (check_strike_coords(row, col) == false);

    //If the program reaches this point, then the strike coordinates are valid.
    //Set the coordinates HINT: use the strikeAttempt parameter.
    strikeAttempt->row = row;
    strikeAttempt->col = col;

}

/**
 * This function verifies that the strike coords are on the board.
 * @param row
 * @param col
 * @return This function returns false if the row or column argument would be off
 *  of the edge of the board. 
 */
bool check_strike_coords(int row, int col) {

    //THIS IS -2 FOR DEBUGGING
    //To expand, I enter a -1 to force a loss and a -2 to force a win condition.
    //Feel free to do something similar in your assignments, but be sure to state
    //as much so that I know that it was intentional. 
    if (row < -2 || row >= BOARD_SIZE_ROW || col < 0 || col >= BOARD_SIZE_COLUMN) {
        return false;
    } else return true;
}

/**
 * This function will set all 5 ships on the game board randomly. 
 * This function is used to place the computers ships. 
 *  
 * @param gameBoard
 */
void place_ships_randomly(char gameBoard[][BOARD_SIZE_COLUMN]) {
    //Declare a startingPoint and randomly initialize the values. 
    Coordinates startingPoint;
    startingPoint.row = rand() % BOARD_SIZE_ROW;
    startingPoint.col = rand() % BOARD_SIZE_COLUMN;

    //Declare a direction randomly initialize it. 
    Direction dir = (Direction) rand() % 4;

    //Place Battleship
    //keep randomizing the values until check_ship_placement is true
    //Yes, this can possibly take a while... especially on small game boards.
    //Theoretically, this could NEVER finish. However, since we start with the 
    // biggest ship and work down it should not be a problem. 

    //Place Carrier 
    while (check_ship_placement(gameBoard, startingPoint, dir, CARRIER_LENGTH) == false) {
        //Change values and try again
        startingPoint.row = rand() % BOARD_SIZE_ROW;
        startingPoint.col = rand() % BOARD_SIZE_COLUMN;
        dir = (Direction) rand() % 4;
    }

    //If the code reaches here then we can use the values to place the ship
    place_ship(gameBoard, startingPoint, dir, CARRIER, CARRIER_LENGTH);
    
    //Repeat this process for the rest of the ships
    
    while (check_ship_placement(gameBoard, startingPoint, dir, BATTLESHIP_LENGTH) == false) {
        //Change values and try again
        startingPoint.row = rand() % BOARD_SIZE_ROW;
        startingPoint.col = rand() % BOARD_SIZE_COLUMN;
        dir = (Direction) rand() % 4;
    }

    //If the code reaches here then we can use the values to place the ship
    place_ship(gameBoard, startingPoint, dir, BATTLESHIP, BATTLESHIP_LENGTH);

    
    //Place Cruiser
    while (check_ship_placement(gameBoard, startingPoint, dir, CRUISER_LENGTH) == false) {
        //Change values and try again
        startingPoint.row = rand() % BOARD_SIZE_ROW;
        startingPoint.col = rand() % BOARD_SIZE_COLUMN;
        dir = (Direction) rand() % 4;
    }

    //If the code reaches here then we can use the values to place the ship
    place_ship(gameBoard, startingPoint, dir, CRUISER, CRUISER_LENGTH);

    //Place Submarine
    while (check_ship_placement(gameBoard, startingPoint, dir, SUBMARINE_LENGTH) == false) {
        //Change values and try again
        startingPoint.row = rand() % BOARD_SIZE_ROW;
        startingPoint.col = rand() % BOARD_SIZE_COLUMN;
        dir = (Direction) rand() % 4;
    }

    //If the code reaches here then we can use the values to place the ship
    place_ship(gameBoard, startingPoint, dir, SUBMARINE, SUBMARINE_LENGTH);

    //Place Destroyer
    while (check_ship_placement(gameBoard, startingPoint, dir, DESTROYER_LENGTH) == false) {
        //Change values and try again
        startingPoint.row = rand() % BOARD_SIZE_ROW;
        startingPoint.col = rand() % BOARD_SIZE_COLUMN;
        dir = (Direction) rand() % 4;
    }

    //If the code reaches here then we can use the values to place the ship
    place_ship(gameBoard, startingPoint, dir, DESTROYER, DESTROYER_LENGTH);

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
 * 
 */
bool check_ship_placement(char gameBoard[][BOARD_SIZE_COLUMN], Coordinates startingPoint, Direction dir, ShipLength len) {
    int i;

    //First, make sure placing the ship will not pass any of the borders
    if (dir == WEST) {
        //If the direction is west, we will SUBTRACT the ship length from the col value
        if ((startingPoint.col - ((int) len - 1)) < 0) {
            return false;
        }

        //If the placement does not exceed the edge then check if it will intersect a ship.
        for (i = 0; i < len; i++) {
            //IMPORTANT: At this point in the game there will only be ships and water. 
            if (gameBoard[startingPoint.row][startingPoint.col - i] != WATER) {
                return false;
            }
        }

    } else if (dir == EAST) {
        //If the direction is east, we will ADD the ship length to the col value
        if ((startingPoint.col + (len - 1)) >= BOARD_SIZE_COLUMN) {
            return false;
        }

        //If the placement does not exceed the edge then check if it will intersect a ship.
        for (i = 0; i < len; i++) {
            //IMPORTANT: At this point in the game there will only be ships and water. 
            if (gameBoard[startingPoint.row][startingPoint.col + i] != WATER) {
                return false;
            }
        }
    } else if (dir == NORTH) {
        //If the direction is north, we will SUBTRACT the ship length from the row value
        if ((startingPoint.row - ((int) len - 1)) < 0) {
            return false;
        }

        //If the placement does not exceed the edge then check if it will intersect a ship.
        for (i = 0; i < len; i++) {
            //IMPORTANT: At this point in the game there will only be ships and water. 
            if (gameBoard[startingPoint.row - i][startingPoint.col] != WATER) {
                return false;
            }
        }

    } else if (dir == SOUTH) {
        //If the direction is south, we will ADD the ship length to the row value
        if ((startingPoint.row + (len - 1)) >= BOARD_SIZE_ROW) {
            return false;
        }

        //If the placement does not exceed the edge then check if it will intersect a ship.
        for (i = 0; i < len; i++) {
            //IMPORTANT: At this point in the game there will only be ships and water. 
            if (gameBoard[startingPoint.row + i][startingPoint.col] != WATER) {
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
    int i;
    //First, we find which direction we will move in. 
    if (dir == WEST) {
        //Use a for loop to change the character to the correct ship type. 
        for (i = 0; i < len; i++) {
            //IMPORTANT: At this point in the game there will only be ships and water. 
            gameBoard[startingPoint.row][startingPoint.col - i] = shipType;
        }

    } else if (dir == EAST) {
        //Use a for loop to change the character to the correct ship type. 
        for (i = 0; i < len; i++) {
            gameBoard[startingPoint.row][startingPoint.col + i] = shipType;
        }
    } else if (dir == NORTH) {
        //Use a for loop to change the character to the correct ship type. 
        for (i = 0; i < len; i++) {
            gameBoard[startingPoint.row - i][startingPoint.col] = shipType;
        }

    } else if (dir == SOUTH) {
        //Use a for loop to change the character to the correct ship type. 
        for (i = 0; i < len; i++) {
            gameBoard[startingPoint.row + i][startingPoint.col] = shipType;
        }
    }
}

void place_ships_manually(char gameBoard[][BOARD_SIZE_COLUMN]) {
    //Declare a startingPoint for the ship. 
    Coordinates startingPoint;
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
    scanf("%d", &startingPoint.row);
    printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
    scanf("%d", &startingPoint.col);

    //acquire ship direction
    printf("Directions: North(0), South(1), East(2), West(3)\n");
    printf("Please enter a direction for the ship to \"face\": ");
    scanf("%d", &tempDir);
    dir = (Direction) tempDir;

    //Keep asking the user for values until they place the battleship properly.
    while (check_ship_placement(gameBoard, startingPoint, dir, BATTLESHIP_LENGTH) == false) {
        printf("Something was wrong with the starting coordinates and direction you entered. Please try again.\n");
        //Change values and try again
        print_game_board(gameBoard, USER);
        printf("Placing your battleship: \n");

        //acquire startingPoint coordinates. 
        printf("Please enter starting point row (0 - %d): ", BOARD_SIZE_ROW - 1);
        scanf("%d", &startingPoint.row);
        printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
        scanf("%d", &startingPoint.col);

        //acquire ship direction
        printf("Directions: North(0), South(1), East(2), West(3)\n");
        printf("Please enter a direction for the ship to \"face\": ");
        scanf("%d", &tempDir);
        dir = (Direction) tempDir;
    }

    //If the code reaches here then we can use the values to place the ship
    place_ship(gameBoard, startingPoint, dir, BATTLESHIP, BATTLESHIP_LENGTH);

    //Repeat this process for the rest of the ships

    //Place Carrier
    print_game_board(gameBoard, USER);
    printf("Placing your carrier: \n");

    //acquire startingPoint coordinates. 
    printf("Please enter starting point row (0 - %d): ", BOARD_SIZE_ROW - 1);
    scanf("%d", &startingPoint.row);
    printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
    scanf("%d", &startingPoint.col);

    //acquire ship direction
    printf("Directions: North(0), South(1), East(2), West(3)\n");
    printf("Please enter a direction for the ship to \"face\": ");
    scanf("%d", &tempDir);
    dir = (Direction) tempDir;

    //Keep asking the user for values until they place the battleship properly.
    while (check_ship_placement(gameBoard, startingPoint, dir, CARRIER_LENGTH) == false) {
        printf("Something was wrong with the starting coordinates and direction you entered. Please try again.\n");
        //Change values and try again
        print_game_board(gameBoard, USER);
        printf("Placing your carrier: \n");

        //acquire startingPoint coordinates. 
        printf("Please enter starting point row (0 - %d): ", BOARD_SIZE_ROW - 1);
        scanf("%d", &startingPoint.row);
        printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
        scanf("%d", &startingPoint.col);

        //acquire ship direction
        printf("Directions: North(0), South(1), East(2), West(3)\n");
        printf("Please enter a direction for the ship to \"face\": ");
        scanf("%d", &tempDir);
        dir = (Direction) tempDir;
    }

    //If the code reaches here then we can use the values to place the ship
    place_ship(gameBoard, startingPoint, dir, CARRIER, CARRIER_LENGTH);


    //Place Cruiser
    print_game_board(gameBoard, USER);
    printf("Placing your cruiser: \n");

    //acquire startingPoint coordinates. 
    printf("Please enter starting point row (0 - %d): ", BOARD_SIZE_ROW - 1);
    scanf("%d", &startingPoint.row);
    printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
    scanf("%d", &startingPoint.col);

    //acquire ship direction
    printf("Directions: North(0), South(1), East(2), West(3)\n");
    printf("Please enter a direction for the ship to \"face\": ");
    scanf("%d", &tempDir);
    dir = (Direction) tempDir;

    //Keep asking the user for values until they place the battleship properly.
    while (check_ship_placement(gameBoard, startingPoint, dir, CRUISER_LENGTH) == false) {
        printf("Something was wrong with the starting coordinates and direction you entered. Please try again.\n");
        //Change values and try again
        print_game_board(gameBoard, USER);
        printf("Placing your cruiser: \n");

        //acquire startingPoint coordinates. 
        printf("Please enter starting point row (0 - %d): ", BOARD_SIZE_ROW - 1);
        scanf("%d", &startingPoint.row);
        printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
        scanf("%d", &startingPoint.col);

        //acquire ship direction
        printf("Directions: North(0), South(1), East(2), West(3)\n");
        printf("Please enter a direction for the ship to \"face\": ");
        scanf("%d", &tempDir);
        dir = (Direction) tempDir;
    }

    //If the code reaches here then we can use the values to place the ship
    place_ship(gameBoard, startingPoint, dir, CRUISER, CRUISER_LENGTH);

    //Place Submarine
    print_game_board(gameBoard, USER);
    printf("Placing your submarine: \n");

    //acquire startingPoint coordinates. 
    printf("Please enter starting point row (0 - %d): ", BOARD_SIZE_ROW - 1);
    scanf("%d", &startingPoint.row);
    printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
    scanf("%d", &startingPoint.col);

    //acquire ship direction
    printf("Directions: North(0), South(1), East(2), West(3)\n");
    printf("Please enter a direction for the ship to \"face\": ");
    scanf("%d", &tempDir);
    dir = (Direction) tempDir;

    //Keep asking the user for values until they place the battleship properly.
    while (check_ship_placement(gameBoard, startingPoint, dir, SUBMARINE_LENGTH) == false) {
        printf("Something was wrong with the starting coordinates and direction you entered. Please try again.\n");
        //Change values and try again
        print_game_board(gameBoard, USER);
        printf("Placing your submarine: \n");

        //acquire startingPoint coordinates. 
        printf("Please enter starting point row (0 - %d): ", BOARD_SIZE_ROW - 1);
        scanf("%d", &startingPoint.row);
        printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
        scanf("%d", &startingPoint.col);

        //acquire ship direction
        printf("Directions: North(0), South(1), East(2), West(3)\n");
        printf("Please enter a direction for the ship to \"face\": ");
        scanf("%d", &tempDir);
        dir = (Direction) tempDir;
    }

    //If the code reaches here then we can use the values to place the ship
    place_ship(gameBoard, startingPoint, dir, SUBMARINE, SUBMARINE_LENGTH);

    //Place Destroyer
    print_game_board(gameBoard, USER);
    printf("Placing your destroyer: \n");

    //acquire startingPoint coordinates. 
    printf("Please enter starting point row (0 - %d): ", BOARD_SIZE_ROW - 1);
    scanf("%d", &startingPoint.row);
    printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
    scanf("%d", &startingPoint.col);

    //acquire ship direction
    printf("Directions: North(0), South(1), East(2), West(3)\n");
    printf("Please enter a direction for the ship to \"face\": ");
    scanf("%d", &tempDir);
    dir = (Direction) tempDir;

    //Keep asking the user for values until they place the battleship properly.
    while (check_ship_placement(gameBoard, startingPoint, dir, DESTROYER_LENGTH) == false) {
        printf("Something was wrong with the starting coordinates and direction you entered. Please try again.\n");
        //Change values and try again
        print_game_board(gameBoard, USER);
        printf("Placing your destroyer: \n");

        //acquire startingPoint coordinates. 
        printf("Please enter starting point row (0 - %d): ", BOARD_SIZE_ROW - 1);
        scanf("%d", &startingPoint.row);
        printf("Please enter starting point column (0 - %d): ", BOARD_SIZE_COLUMN - 1);
        scanf("%d", &startingPoint.col);

        //acquire ship direction
        printf("Directions: North(0), South(1), East(2), West(3)\n");
        printf("Please enter a direction for the ship to \"face\": ");
        scanf("%d", &tempDir);
        dir = (Direction) tempDir;
    }

    //If the code reaches here then we can use the values to place the ship
    place_ship(gameBoard, startingPoint, dir, DESTROYER, DESTROYER_LENGTH);
}
