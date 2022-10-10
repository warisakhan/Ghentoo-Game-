/* Warisa Khan G01257446
CS 262, Lab Section 208
Project 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Create the function prototypes
 */

int is_valid_name(char name[]);
int is_valid_seed(int *seed, char seedValue[]);
int game_logic(char name[], int newNetValue);
int throw_ball(int height);
int calculate_net_height(char net_height[]);

/**
 * This is the main  method that will look for the input values..
 */

int main(){
	/*creating variables and char arrays for input
	 */
	char name[50];
	char net_height[50];
	char input1[50];
	char input2[50];
	char input3[50];

	char seedValue[50];
	int newNetValue;
	int seed;
	seed = 0;
	

	printf("Welcome to the Gehntoo game\n");
	/*making sure a name is correct and meets the valid format
	 */
	do{
		printf("Enter your name: \n");
		fgets(input1, 50, stdin);
		sscanf(input1, "%s", name);

		if (is_valid_name(name) == 0){
			printf("Wrong name, enter name again: \n");
		}
	}while (is_valid_name(name) == 0);

	/**
	 *making sure the seed value is valid 
	 */
	do{
		printf("Enter a seed value to use in the range of [1-99999] ");
		fgets(input2, 50, stdin);
		sscanf(input2, "%s", seedValue);

		if (is_valid_seed(&seed, seedValue) == 0){
			printf("Invalid seed, please enter a new seed value in the range [1-99999] \n");
		}
	}while (is_valid_seed(&seed, seedValue) == 0);
	printf("Seed value to use is %s\n", seedValue);
	/*srand generates random numbers based on seed
	 */
	srand(seed);
	/*checks the height and makes sure it is a valid input
	 */

	do{
		printf("Enter the height of the net in feet and inches [xxfeet xxin] where xx must be [1-99]\n");
		fgets(input3, 50, stdin);
		sscanf(input3, "%s", net_height);

	} while (calculate_net_height(net_height) == 0);

	/*calling calculate_net_height to get net height
	 */
	
    newNetValue = calculate_net_height(net_height);
	printf("Height of the net: %d inches\n", newNetValue);	
	/*calling game logic to run the game
	 */
    game_logic(name, newNetValue);

	return 0;
}
/**
 * This function checks the input value for the seed and validates that only digits were entered, and
 * that the value ranges in [1, 99999], inclusive. If at least one of these conditions is not met, then the
 * function returns 0 otherwise 1.
 */
int is_valid_seed(int *seed, char seedValue[]){
	int i;
	/*using a for loop to loop through each char and if it does not meet the requirements returns 0 for false
	 */
	for(i = 0; i< strlen(seedValue); i++){
		if ((seedValue[i] != '0' && seedValue[i] != '1' && seedValue[i] != '2' && seedValue[i] != '3' && seedValue[i] != '4' && seedValue[i] != '5' && seedValue[i] != '6' && seedValue[i] != '7' && seedValue[i] != '8' && seedValue[i] > '9') || strlen(seedValue) > 5){
                        return 0;
                }
	}
	/*built in function that converts char to int 
	 */
	
	*seed = atoi(seedValue);

	return 1;
}

/**This function implements the game logic as indicated by the rules above.
 */
 int game_logic(char name[], int newNetValue){
        /**
         * initilaizing variables 
         */
    int timesToPlay;
    int playrPoints;
    int computerPoints;
    int bet;
    int playerWins;
    int computerWins;
    int ballHeight;
    double halfHeight;
    char turn;
    char playAgain;
    char throwAgain;
    char input[50];
    playAgain = ' ';

    playrPoints = 75;
    computerPoints = 75;
    turn = 'a';
    timesToPlay = 0;
    halfHeight = 0;
    playerWins = 0;
    computerWins = 0;

   /**
    * informing player that each player starts w 75 points 
    */
    printf("Each player is starting with 75 points\n");

    /*
     * making sure the game has not been played 3 times or else the run is over 
     */
    while (timesToPlay < 3){
        /* making sure neither player has won the game yet 
         */
        while (playrPoints > 0 || computerPoints > 0){
            /*using a char checker to see who's turn it is, a indicates the player 
             */
            if (turn == 'a'){
		    /*asking player how much they would like to bet
		     */
                do{
                printf("%s's turn. How much would you like to bet towards your throw? \n", name);
                fgets(input, 50, stdin);
                sscanf(input, "%d", &bet);
                /*if the bet does not meet the requirements, ask for bet again
                 */
                if (bet > playrPoints || bet < 1 || bet > 11){
                    printf("\tYour bet was not within the valid range of [1, 11] or you attempted to bet more points than you currently have. Please enter a valid bet:\n");
                }
               
                }while(bet > playrPoints || bet < 1 || bet > 11);
               /**
                * calling the throw_ball method to get the net height and ball height 
                */

                printf("\tbet %d point(s)\n", bet);
                ballHeight = throw_ball(newNetValue);
                halfHeight = (double) newNetValue / 2;
                /**
                 * if the ball height is greater than the net height, bet is decreased from the player points 
                 */
                if (ballHeight > newNetValue){
                    playrPoints -= bet;
		    /*informing user of what happened
		     */
                    printf("\tBall height: %d inches, the ball is over the net\n", ballHeight);
                    printf("\tDeducting %d points\n", bet);
                    printf("\t%s now has %d points\n", name, playrPoints);
                     }
                /*if the ball height is less than half the height, asks player if they want to throw again 
                 */
                else if (ballHeight < halfHeight){
			/*scanning in user input correctly
			 */
                    printf("\tBall height: %d inches, Throw again? Type Y or N: \n ", ballHeight);
                    fgets(input, 50, stdin);
                    sscanf(input, "%c", &throwAgain);
                    /**
                     * if player says yes then the throw ball function is called again 
                     */
                    if (throwAgain == 'Y' || throwAgain == 'y'){
                       ballHeight =  throw_ball(newNetValue);
                       /**
                        * if the rethrow is greater than the net height, deducts the bet points 
                        */
                        if (ballHeight > newNetValue){
                            playrPoints -= bet;
                            printf("\tBall height: %d inches, the ball is over the net\n", ballHeight);
                            printf("\tDeducting %d points\n", bet);
                            printf("\t%s now has %d points\n", name, playrPoints);
                        }
                        /**
                         * if the rethrow is less than the net height, add 4 points to player points 
                         */
                        else{
                            playrPoints += 4;
                            printf("\tBall height: %d inches, the ball is below the net\n", ballHeight);
                            printf("\tAdding 4 points\n");
                            printf("\t%s now has %d points\n", name, playrPoints);
                        }
                    }
                    /**
                     * if you choose not to rethrow, bet is added to player points 
                     */
                    else{
                        playrPoints += bet;
                        printf("\tAdding %d points\n", bet);
                        printf("\t%s now has %d points\n", name, playrPoints);
                    }
                }
                /**
                 * if the ball height is less than net height but greater than half height, add 2 points to player 
                 */
                else{
                    playrPoints += 2;
                    printf("\tBall height: %d inches, the ball is below the net\n", ballHeight);
                    printf("\tAdding 2 points\n");
                    printf("\t%s now has %d points\n", name, playrPoints);
                }
                /**
                 * if player points == 0; player wins the game 
                 */

                if (playrPoints == 0){
                    break;
                }
                /**
                 * this indicates that it is the computer's turn, using b as the checker 
                 */

                turn = 'b';

                 }
            /*
             * computers turn
             */
            else{
		    /*informing that it is the computer turn to user
		     */
                printf("Computer's turn\n");
                ballHeight = throw_ball(newNetValue);
                halfHeight = (double) newNetValue / 2;

                /**
                 *if the ball height is greater than the net height, deducts 9 points from the computer 
                 */
                if (ballHeight > newNetValue){
                    computerPoints -= 9;
                    printf("\tBall height: %d inches, the ball is over the net\n", ballHeight);
                    printf("\tDeducting 9 points\n");
                    printf("\tComputer now has %d points\n", computerPoints);
                }
                 /**
                 *if the ball height is less than half the height, automatically rethrows 
                 */
                else if (ballHeight < halfHeight){
                    printf("\tBall height: %d inches, the ball is below the net, throwing once more\n", ballHeight);
                    ballHeight = throw_ball(newNetValue);
                 /**
                 *if ball height is less than  the net height, add 6 points to the computer
                 */
                    if (ballHeight <= newNetValue){
                        computerPoints += 6;
			/*informing user of the error 
			 */
                        printf("\tBall height: %d inches, the ball is below the net\n", ballHeight);
                        printf("\tAdding 6 points\n");
                        printf("\tComputer now has %d points\n", computerPoints);
                    }
                 /**
                 *if the new rethrow is less than the net height, deduct 7 points 
                 */
                    else{
                        computerPoints -= 7;
			/*informing user 
			 */
                        printf("\tBall height: %d inches, the ball is over the net\n", ballHeight);
                        printf("\tDeducting 7 points\n");
                        printf("\tComputer now has %d points\n", computerPoints);
                    }
                }
                /**
                 *if the ball height is less than the net height but greater than the half height, add 4 points
                 */
                else{
                    computerPoints += 4;
                    printf("\tBall height: %d inches, the ball is below the net\n", ballHeight);
                    printf("\tAdding 4 points\n");
                    printf("\tComputer now has %d points\n", computerPoints);
                }
                /**
                 *if computer points == 0, the computer wins the game 
                 */
                if (computerPoints == 0){
                    break;
                }
                turn = 'a';
                 }
        }
    /*
     * if player wins, outputs to user 
     */
    if (playrPoints == 0){
        playerWins++;
        printf("%s has won the current game, congratulations\n", name);
    }
    /*
     * if computer wins, outputs to user 
     */
    else{
        computerWins++;
        printf("Computer has won the current game\n");
    }

    /*
     * if the plays are less than 3, reprompts user to play or else run is over
     */
    if (timesToPlay < 3){
	    /*getting input from the user to ask about playing again
	     */
        printf("Would you like to play again? Type Y or N: \n ");
        fgets(input, 50, stdin);
        sscanf(input, "%c", &playAgain);
        /**
         * if the player says yes, restarts rhe game
         */
        if (playAgain == 'y' || playAgain == 'Y'){
          
            timesToPlay++;
            printf("Starting over now!\n");
            continue;
        }
        /**
         * if the player says no, states the stats for the games
         */
        else{
            printf("%s chose not to play again. Thanks for playing\n", name);
            break;
        }
    }
}
        
            printf("Printing out game statistics now:\n");
                        printf("\t%s has won a total of %d time(s):\n", name, playerWins);
                        printf("\tComputer has won a total of %d time(s):\n", computerWins);
            return 0;
}




/**
 * This function throws the ball to a random height using the rand() function. The height
 * generated at random must range in [0, net_height+16].
 */
int throw_ball(int newNetValue){
	/*rand generates random numbers for the ball height)
	 */
	int calculate;
	calculate = rand() % (newNetValue + 16 +1);
	return calculate;
}

/**This function determines if a valid name is entered by the user. A name must not be longer than
 * 7 characters and must contain only letters or blank spaces. If name is valid, return 1 otherwise return 0.
 */
int is_valid_name(char name[])
{
	/*initializing varibales
	 */
	int i;
	/*for loop that loops through every char to check if each input is valid
	 */
	for (i = 0; i < strlen(name); i++)
	{
		
		if (((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || name[i] == ' ') && strlen(name) <= 7)
		{
			continue;
		}
		else
		{
			return 0;
		}
	}

	return 1;
}

/**
 * This function determines the height of the net in inches of the net string that is input by the user.
 * Return the calculated net height in inches.
 */
int calculate_net_height(char net_height[]){
/*initializng variables
 */
 int finalHeight;
 int i;
 int w;
 int find;
 int feet;
 int inches;
    char tempArr[150];
    finalHeight = 0;
    i = 0;
    w = 0;
    find = 0;
    feet = 0;
    inches = 0;

    /** removes all the white space to determine how to store the ft and in
     */

    while (net_height[i] != '\0'){
        if (net_height[i] == ' '){
            i++;
            continue;
        }
        else{
            tempArr[find] = net_height[i];
            find++;
            i++;
        }
    }

    i = 0;
    while (tempArr[i] != '\0'){
	    /*checks the location of ft to store the numbers before it
	     */

        if ((tempArr[i] >= '0' && tempArr[i] <= '9') && (tempArr[i + 1] >= '0' && tempArr[i + 1] <= '9') && (tempArr[i + 2] >= '0' && tempArr[i + 2] <= '9')){
            return 0;
        }
        i++;
    }
    i = 0;
    while (tempArr[i] != '\0'){
	/*places the number in the tens place
	 */
        if ((tempArr[i] >= '0' && tempArr[i] <= '9') && (tempArr[i + 2] == 'f' || tempArr[i + 2] == 'F'))
        {
            w = tempArr[i] - '0';
            feet = feet + (w * 10);
        }
	/*places the number in the ones place
	 */
        else if ((tempArr[i] >= '0' && tempArr[i] <= '9') && (tempArr[i + 2] == 't' || tempArr[i + 2] == 'T')){
            w = tempArr[i] - '0';
            feet = feet + w;
        }
	/*places the inches number in the tens place
	 */
        else if ((tempArr[i] >= '0' && tempArr[i] <= '9') && (tempArr[i + 2] == 'i' || tempArr[i + 2] == 'I'))
        {
            w = tempArr[i] - '0';
            inches = inches + (w * 10);
        }
	/*places the inches number in the ones place
	 */
        else if ((tempArr[i] >= '0' && tempArr[i] <= '9') && (tempArr[i + 2] == 'n' || tempArr[i + 2] == 'N')){
            w = tempArr[i] - '0';
            inches = inches + w;
        }
        i++;
    }
    /*finalheight calculates the total inches
     */
    finalHeight = (feet * 12) + 3;
    return finalHeight;
}
