#include <stdio.h>
#include <stdlib.h>

#include "gamelogic.h"

int validMoves(Board* board, int moves[][BOARD_SIZE], char player)
{
	int x = 0;
	int y = 0;

	int rows = 0;
	int columns = 0;
	
	int rowdelta = 0;
	int coldelta = 0;
	int noOfMoves = 0;

	// Sets opponent
	char opponent = (player == '@')? '.' : '@';

	// Initialize moves array to zero
	for(rows = 0; rows < BOARD_SIZE; rows++)
	{
		for(columns = 0; columns < BOARD_SIZE; columns++)
		{
			moves[rows][columns] = 0;
		}
	}	

	for(rows = 0; rows < BOARD_SIZE; rows++)
	{
		for(columns = 0; columns < BOARD_SIZE; columns++)
		{
			if(board->fields[rows][columns] != ' ')
			{
				continue;
			}
			for(rowdelta = -1; rowdelta <= 1; rowdelta++)
			{
				for(coldelta = -1; coldelta <= 1; coldelta++)
				{
					if(rows + rowdelta < 0 || rows + rowdelta >= BOARD_SIZE ||
						columns + coldelta < 0 || columns + coldelta >= BOARD_SIZE ||
						(rowdelta==0 && coldelta==0))
					{
						continue;
					}
					if(board->fields[rows + rowdelta][columns + coldelta] == opponent)
					{
						x = rows + rowdelta;
						y = columns + coldelta;

						for(;;)
						{
							x += rowdelta;
							y += coldelta;
							if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
							{
								break;
							}

							if(board->fields[x][y] == ' ')
							{
								break;	
							}

							if(board->fields[x][y] == player)
							{
								moves[rows][columns] = 1;
								noOfMoves++;
								break;
							}
						}
					}
				}
			}
		}
	}
	return noOfMoves;
}

void makeMove(Board* board, int rows, int columns, char player)
{
	int rowdelta = 0;
	int coldelta = 0;
	int x = 0;
	int y = 0;

	// Sets opponent
	char opponent = (player == '@')? '.' : '@';

	board->fields[rows][columns] = player;

	for(rowdelta = -1; rowdelta <= 1; rowdelta++)
	{
		for(coldelta = -1; coldelta <= 1; coldelta++)
		{
			if(rows + rowdelta < 0 || rows + rowdelta >= BOARD_SIZE ||
				columns + coldelta < 0 || columns + coldelta >= BOARD_SIZE ||
				(rowdelta==0 && coldelta== 0))
			{
				continue;
			}

			if(board->fields[rows + rowdelta][columns + coldelta] == opponent)
			{
				x = rows + rowdelta;
				y = columns + coldelta;

				for(;;)
				{
					x += rowdelta;
					y += coldelta;

					if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
					{
						break;
					}

					if(board->fields[x][y] == ' ')
					{
						break;
					}

					if(board->fields[x][y] == player)
					{
						while(board->fields[x-=rowdelta][y-=coldelta]==opponent)
							board->fields[x][y] = player;
						break;
					}
				}
			}
		}
	}







}
