#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 20
#define WIDTH 20

#define WALL 'O'
#define SPACE '.'
#define PLAYER '@'
#define BOX '#'
#define GOAL 'X'

char array[WIDTH][HEIGHT][2];
// array[][][0] is for the non-changeble tiles - WALL, SPACE and GOAL -> there will always be either space or goal under a box or the player; array[][][1] is for boxes and the player
int col_player;
int row_player;

void prepare_level1()
{


	for( int col = 0; col <= WIDTH; col++ )
	{
		for( int row = 0; row <= HEIGHT; row++ )
		{
			array[col][row][1] = '0';
			array[col][row][0] = SPACE;
		}
	}
	col_player = 4;
	row_player = 4;

	array[4][3][0] = WALL;
	array[3][4][0] = WALL;
	array[2][5][0] = WALL;
	array[2][6][0] = WALL;
	array[2][7][0] = WALL;
	array[3][8][0] = WALL;

	array[5][2][0] = WALL;
	array[6][2][0] = WALL;
	array[7][2][0] = WALL;
	array[8][2][0] = WALL;
	array[9][2][0] = WALL;
	array[10][2][0] = WALL;
	array[11][2][0] = WALL;
	array[12][2][0] = WALL;

	array[13][3][0] = WALL;
	array[13][4][0] = WALL;
	array[13][5][0] = WALL;
	array[13][6][0] = WALL;
	array[13][7][0] = WALL;
	array[13][8][0] = WALL;

	array[12][9][0] = WALL;
	array[11][9][0] = WALL;
	array[10][9][0] = WALL;

	array[9][8][0] = WALL;
	array[8][8][0] = WALL;
	array[7][8][0] = WALL;
	array[6][8][0] = WALL;
	array[5][8][0] = WALL;
	array[4][8][0] = WALL;

	array[8][3][0] = WALL;
	array[8][4][0] = WALL;

	array[12][5][0] = WALL;

	array[11][4][0] = GOAL;
	array[10][3][0] = GOAL;	
	array[10][8][0] = GOAL;

	array[7][4][0] = BOX;
	array[8][5][0] = BOX;
	array[9][4][0] = BOX;
}

void print_board()
{
 system( "printf \"\033c\"" );	 // a cheat to clear the console
 for( int col = 0; col < HEIGHT; col++ )
   {
    for( int row = 0; row < WIDTH; row++ )
      {
      	if( row == row_player && col == col_player ) printf("%c", PLAYER);
      	else if( array[col][row][1] != '0' )
			{
				printf("%c", array[row][col][1]);
			}
			else
			{
				printf("%c", array[row][col][0]);
			}
      }
    printf("\n");
   }
}








int main()
{
	prepare_level1();
	print_board();

	while( 1 )
	{
		system("/bin/stty raw");
   	char direction = getchar();
   	system("/bin/stty cooked");
		switch( direction )
		{
			case 'Q':
			case 'q':
				exit( 1 );
			case 'W':
			case 'w':

				break;
			case 'S':
			case 's':

				break;
			case 'A':
			case 'a':	
		
				break;
			case 'D':
			case 'd':

				break;
			default:
				printf("\nNot a direction\n");
				break;
		}
	}

	
	return 0;
}


