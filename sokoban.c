// Macros used for debugging
#define DEBUG_BUILD 1 // Change to 0 to not debug, to other to do a debug
#define DEBUG if( DEBUG_BUILD )
// End of debug macros

// Inclusion of used libraries and headers
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // For the usage of boolean data type.
#include <unistd.h> // Using for the usleep command
#include "stack.h"
// End of inclusion

// Changeable definition of the height and the width of the board ( is used as parameters when declaring the array )
#define HEIGHT 20
#define WIDTH 20
// End of definitions.

// Definition of characters for tiles.
#define WALL 'O'
#define SPACE '.'
#define PLAYER '@'
#define BOX '#'
#define GOAL 'X'
// End of definitons.

// The declaration of an array used for the board and col_player and row_player variables, which represent the position of the player.
char array[WIDTH][HEIGHT][2];
	// array[][][0] is for the non-changeble tiles - WALL, SPACE and GOAL -> there will always be either space or goal under a box or the player; array[][][1] is for boxes.
int col_player;
int row_player;
// The end of the declaration.

// Defining functions from header "stack.h"
void init( element** a );
int is_empty( element* a );
void push( element** a, int b );
int top( element* a );
void pop( element** a );
void remove_stack( element** a );
// End of definitions

// The start of function 'prepare_level()', which sets the elements in the array to walls, goals, boxes and the player according to the text file determined by user input in 'main()'.
void prepare_level( char level[666] )
{
	
	char level_directory[66] = "./levels/";

	int toot = 0;

	while( level[toot] != 0 )
	{
		level_directory[toot+9] = level[toot];
		toot++;
	}

	if(fopen( level_directory, "r" ) == NULL)
	{
		printf("ERROR: That is not an existing level\n");
		exit(1);
	}
	else
	{	

		FILE *file;
		file = fopen( level_directory, "r" );
		
		int col = 0;
		int row = 0;
		char character = 0;

		while( ( character = fgetc(file) ) != ' ' /* Until the cursor reaches the empty line */ )
		{
			if(character == '\n')
			{
				col=0;
				row++;
				continue;
			}
			array[col][row][0] = character;
			col++;         
		}

		col = 0;
		row = 0;
		character = fgetc(file);

		while( ( character = fgetc(file) ) != ' ' /* Until the cursor reaches the empty line */ )
		{
			if(character == '\n')
			{
				col=0;
				row++;
				continue;
			}
			array[col][row][1] = character;
			col++;         
		}		
		fclose( file );
	}
	
	DEBUG 
	{
		system( "printf \"\033c\"" );
		printf("\nThis is a DEBUG build!\n\n");
		printf("\nSuccesfully prepared level.\n\n");
		usleep( 2000000 );
	}	
}
// The end of function 'prepare_level'.

// The start of function 'print_board()', which prints the board.
void print_board()
{
 system( "printf \"\033c\"" );	 // a cheat to clear the console
	
	DEBUG printf("\nThis is a DEBUG build!\n\n");

	for( int row = 0; row < WIDTH; row++ )
	{
   	for( int col = 0; col < HEIGHT; col++ )
      {
      	if( col == col_player && row == row_player ) printf("%c", PLAYER);
      	else if( array[col][row][1] != '0' )
	 		{
				printf("%c", array[col][row][1]);
	//				printf("\nChar: %c\n", array[col][row][1]);
			}
			else		
			{
				printf("%c", array[col][row][0]);
			}	
      }	
    printf("\n");
   }
	printf("\ncol_player: %d, row_player: %d\n", col_player, row_player);
//	printf("\nChar on [0,0,0]: %c\n", array[0][0][1]);
	DEBUG printf("\nSuccesfully printed the board.\n\n");	
}
// The end of function 'print_board()'.

// The start of function 'check_goals()', which checks if all boxes are on goals.
void check_goals()
{
	int goals = 3;
	int on_goal = 0;

	for( int row = 0; row < WIDTH; row++ )
	{
   	for( int col = 0; col < HEIGHT; col++ )
      {
			if( array[col][row][0] == GOAL && array[col][row][1] == BOX )
			{
				on_goal++;
			}
			if( goals == on_goal )
			{	
				system( "printf \"\033c\"" );
				printf("Well played!\n\n");
				exit( 0 );
			}
		}
	}
}
//

// The start of function 'box_movement()', which checks if player can move a box and moves it if he can.
bool box_movement( int coordinate_x, int coordinate_y )
{
	if( coordinate_x == col_player && coordinate_y == row_player+1 ) // Player is above the box
	{
		if( array[coordinate_x][coordinate_y+1][1] == BOX || array[coordinate_x][coordinate_y+1][0] == WALL )
		{
			return false;
		}
		array[coordinate_x][coordinate_y+1][1] = BOX;
		array[coordinate_x][coordinate_y][1] = '0';
		return true;
	}

	if( coordinate_x == col_player && coordinate_y == row_player-1 ) // Player is beneath the box
	{
		if( array[coordinate_x][coordinate_y-1][1] == BOX || array[coordinate_x][coordinate_y-1][0] == WALL )
		{
			return false;
		}
		array[coordinate_x][coordinate_y-1][1] = BOX;
		array[coordinate_x][coordinate_y][1] = '0';
		return true;
	}

	if( coordinate_x == col_player+1 && coordinate_y == row_player )	// Player is to the left of the box
	{
		if( array[coordinate_x+1][coordinate_y][1] == BOX || array[coordinate_x+1][coordinate_y][0] == WALL )
		{
			return false;
		}
		array[coordinate_x+1][coordinate_y][1] = BOX;
		array[coordinate_x][coordinate_y][1] = '0';
		return true;
	}

	if( coordinate_x == col_player-1 && coordinate_y == row_player )	// Player is to the right of the box
	{
		if( array[coordinate_x-1][coordinate_y][1] == BOX || array[coordinate_x-1][coordinate_y][0] == WALL )
		{
			return false;
		}
		array[coordinate_x-1][coordinate_y][1] = BOX;
		array[coordinate_x][coordinate_y][1] = '0';
		return true;
	}
	
	system( "printf \"\033c\"" );
	printf("\nERROR\n");
	exit( 1 );

}
// End of function 'box_movement'.

// The start of function 'check_player_step(), which checks the tile where the player wants to move.
bool check_player_step( int coordinate_x, int coordinate_y )
{
	if( array[coordinate_x][coordinate_y][0] == WALL  || coordinate_x > ( WIDTH-1 ) || coordinate_x < 0 || coordinate_y > ( HEIGHT-1 ) || coordinate_y < 0 )
	{
		return false;
	}

	if( array[coordinate_x][coordinate_y][1] == BOX )
	{
		return box_movement( coordinate_x, coordinate_y );
	}

	return true;
}
// The end of function 'check_player_step()'

// The start of function 'move_player()', which moves the player according to the input from main().
bool move_player( int coordinate_x, int coordinate_y )
{
	if( check_player_step( coordinate_x, coordinate_y ) == false)
	{
		print_board();
		return false;
	}
	col_player = coordinate_x;
	row_player = coordinate_y;
	print_board();
	return true;
}
// The end of 'move_player()' function

// The start of main().
int main()
{
	char level[666];

	for( int i=0; i<66; i++)
	{
		level[i] = 0;
	}

	scanf("%s", level);

	prepare_level( level );

			col_player = 4;
			row_player = 4;

	print_board();			

	while( 1 )
	{
		check_goals();

		system("/bin/stty raw");
   	char direction = getchar();
   	system("/bin/stty cooked");
		switch( direction )
		{
			case 'Q':
			case 'q':
				exit( 3 );
			case 'W':	
			case 'w':
				move_player(col_player,(row_player-1));
				break;
			case 'S':
			case 's':
				move_player(col_player,(row_player+1));
				break;
			case 'A':
			case 'a':	
				move_player((col_player-1),row_player);
				break;
			case 'D':
			case 'd':
				move_player((col_player+1),row_player);
				break;
			default:
				printf("\nNot a direction\n");
				break;
		}
	}

	return 0;
}
// The end of main() and the program.

