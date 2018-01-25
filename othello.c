#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "board.h"
#include "player.h"
#include "gamelogic.h" 

int main(void)
{

	//Moves
	int turnes[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int numOfTurn = 0;
	int invalidTurn = 0;
	//Rows and columns	
	int rows = 0;
	int columns = 0;
	int x = 0;
	char y = 0;
	char again = 0;
	int playerIndicator = 0;

	//The players
	player player1, player2;
	player1.name=malloc(100);
	player2.name=malloc(100);
	
	
	//Gets the players name & sets score
	printf("Enter name of Player 1: ");
	fgets(player1.name, 100, stdin);
	player1.name[strlen(player1.name)-1] = '\0';
	printf("Enter name of Player 2: ");
	fgets(player2.name, 100, stdin);
	player2.name[strlen(player2.name)-1] = '\0';
	player1.score = 0;
	player2.score = 0;
	
	//Initialize board
	Board currentBoard;
	initBoard(&currentBoard);

	do
	{
		//Prints board
		printBoard(&currentBoard);
		//Checks if player 1 or 2
		if(++playerIndicator % 2)
		{
			//Checks if valid move
			if(validMoves(&currentBoard, turnes, '@'))
			{
				char input[20];
				for(;;)
				{
					//Prints player1 name 
					printf("%s's turn. You are '@' Enter your move: \n", player1.name);
					fgets(input, sizeof(input), stdin);
					sscanf(input, "%c %d", &y, &x);
					y = tolower(y) - 'a';
					x--;
					if(y>=0 && x>=0 && y<BOARD_SIZE && x<BOARD_SIZE && turnes[y][x])
					{
						makeMove(&currentBoard, y, x, '@');
						numOfTurn++;
						break;
					}
					else
					{
						printf("Not a valid move or not right input! Alphabet first and Number after example: \t [a4]  Please try again.\n");
					}
				}
			}
			else
			{
				//Checks if any valid moves left
				if(++invalidTurn < 2)
				{
					printf("No available move, press return to pass");
					scanf("%c", &again);
				}
				else
				{
					printf("No more moves available for both players. Game over...");
				}
			}
		}
		else
		{
			//Check if valid move
			if(validMoves(&currentBoard, turnes, '.'))
			{
				char input[20];
				for(;;)
				{
					//Prints player1 name
					printf("%s's turn. You are '.' Enter your move: \n", player2.name);
					fgets(input, sizeof(input), stdin);
					sscanf(input, "%c %d", &y, &x);
					y = tolower(y) - 'a';
					x--;
					if(y>=0 && x>=0 && y<BOARD_SIZE && x<BOARD_SIZE && turnes[y][x])
					{
						makeMove(&currentBoard, y, x, '.');
						numOfTurn++;
						break;
					}
					else
					{
						printf("Not a valid move or not right input! Alphabet first and Number after example: \t [a4]  Please try again.\n");
					}
				}
			}
			else
			{	
				//Checks if any valid moves left
				if(++invalidTurn < 2)
				{
					printf("No available move, press return to pass");
					scanf("%c", &again);
				}
				else
				{
					printf("No more moves available for both players. Game over...");
				}
			}
		}

	}while(numOfTurn < BOARD_SIZE*BOARD_SIZE && invalidTurn<2);

	printBoard(&currentBoard);

	for(rows = 0; rows < BOARD_SIZE; rows++)
	{
		for(columns = 0; columns < BOARD_SIZE; columns++)
		{
			player1.score += currentBoard.fields[rows][columns] == '@';
			player2.score += currentBoard.fields[rows][columns] == '.';
		}
	}
	//Prints the final score after the game ends
	printf("Game over! \n Final score: \n");
	printf("%s: %d \n%s: %d\n", player1.name, player1.score, player2.name, player2.score);
	//Prints the winner fo the game
	if(player1.score > player2.score){
		printf("%s is the winner!\n", player1.name);
	}else{
		printf("Congrats %s is the winner !\n", player2.name);
	}
	
	free(player1.name);
	free(player2.name);
}


