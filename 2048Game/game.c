// partners: vmagow2, dhruvv4, vkhemka2

/*In this code we make the game 2048. First we implement a function to make the game to start off. We then make a function to remake the game in case the user presses the remake game key. The main part of the code is implementing the shifting and merging of the rows and columns of the matrix to implement the game of 2048. 

For move_w: we check for the first non empty element/block in the matrix by traversing through the whole array. We then check if the element is in the bounds of the matrix and isnt at the top of the matrix touching the boundary. We then see if it is possible to shift the element above by checking if the space above it is free or the same as the current cell. We then merge the row elements or shift accordingly.

For move_a: we check for the first non empty element/block in the matrix by traversing through the whole array. We then check if the element is in the bounds of the matrix and isnt at the left of the matrix touching the boundary. We then see if it is possible to shift the element to the left by checking if the space to the left is free or the same as the current cell. We then merge the column elements or shift accordingly.

The other two funnctions are basically modifications of these two functions to check if the blocks can shift/merge to the right and down.

In total three nested loops are used in the functions. The first two are to find the desired element in the matrix and the last one is to manipulate multiple elements in that matrix

*/
#include "game.h"
game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
	mygame->rows= rows;
	mygame->cols = cols;

	mygame->score=0;	//score initialized
	int area= rows*cols;
	for(int i=0; i< area ; i++) //assigning -1 to all cells in the matrix
		mygame->cells[i]= -1;	


    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows = new_rows;	
	(*_cur_game_ptr)->cols = new_cols;
	(*_cur_game_ptr)->score = 0;

	int area= new_rows*new_cols;

	for(int i=0; i< area ; i++)		//assign all cells with -1 again to reset
		(*_cur_game_ptr)->cells[i]= -1;


	return;	

}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
    
*/
{
    //YOUR CODE STARTS HERE
    int location = row*cur_game->cols+col;  //finding the element in a 1D array method 
    if(row<0 || row>cur_game->rows || col<0 || col>cur_game->cols)
    return NULL;
    else 
    return &(cur_game->cells[location]);
    
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    int r = cur_game->rows;
    int l = cur_game->cols;
    int flag = 0; // a checker for shift/merge
    for(int i = 0; i<r; i++){ // go through each row and column
        for(int j = 0; j<l; j++){
            if(cur_game->cells[i*l+j] != -1){ //check if the current cell isnt empty
                for(int k = 0; k<=i ; k++){ //once the element is found use this loop to manipulate matrix 
		
                if(cur_game->cells[k*l+j] == -1){ //check if there is space to shift the element
                    cur_game->cells[k*l+j] = cur_game->cells[i*l+j]; //shift elements up
                    cur_game->cells[i*l+j] = -1; //empty out the space
                    flag = 1; 
                }
                if(cur_game->cells[k*l+j] == cur_game->cells[(k-1)*l+j] && cur_game->cells[k*l+j]!=-1){ 
                    cur_game->cells[(k-1)*l+j] = 2*cur_game->cells[k*l+j]; //merging process
		    cur_game->score+= cur_game->cells[k*l+j]*2; //increment score
                    cur_game->cells[k*l+j] = -1;
		    
                    flag = 1;
		    break;

                }
                
  
        }
            }
    }}
    return flag;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int r = cur_game->rows;
    int l = cur_game->cols;
    int flag = 0; // a checker for shift/merge
    for(int i = r-1; i>=0; i--){ // go through each row and column
        for(int j = 0; j<l; j++){
            if(cur_game->cells[i*l+j] != -1){ //check if the current cell isnt empty
                for(int k = r-1; k>=i ; k--){ //once the element is found use this loop to manipulate matrix 
		
                if(cur_game->cells[k*l+j] == -1){
                    cur_game->cells[k*l+j] = cur_game->cells[i*l+j]; //shift elements down
                    cur_game->cells[i*l+j] = -1; //empty out the space
                    flag = 1;
                }
                if(cur_game->cells[k*l+j] == cur_game->cells[(k+1)*l+j] && k!=0 && cur_game->cells[k*l+j]!=-1){
                    cur_game->cells[(k+1)*l+j] = 2*cur_game->cells[k*l+j];
		    cur_game->score+= cur_game->cells[k*l+j]*2; //merging process 
                    cur_game->cells[k*l+j] = -1;
		    
                    flag = 1;
		    break;

                }
                
  
        }
            }
    }}
    return flag;
    
};
int move_a(game * cur_game) //slide left
{
     //YOUR CODE STARTS HERE
    int r = cur_game->rows;
    int l = cur_game->cols;
    int flag = 0; // a checker for shift/merge
    for(int i = 0; i<r; i++){ // go through each row and column
        for(int j = 0; j<l; j++){
            if(cur_game->cells[i*l+j] != -1){ //check if the current cell isnt empty
                for(int k = 0; k<=i ; k++){ //once the element is found use this loop to manipulate matrix 
		
                if(cur_game->cells[i*l+k] == -1){
                    cur_game->cells[i*l+k] = cur_game->cells[i*l+j]; //shift elements to the left
                    cur_game->cells[i*l+j] = -1; //empty out the space
                    flag = 1;
                }
                if(cur_game->cells[i*l+k] == cur_game->cells[(k-1)+i*l] && cur_game->cells[i*l+k]!=-1){
                    cur_game->cells[(k-1)+i*l] = 2*cur_game->cells[i*l+k]; //merging process 
		    cur_game->score+= cur_game->cells[i*l+k]*2;
                    cur_game->cells[i*l+k] = -1;
		    
                    flag = 1;
		    break;

                }
                
  
        }
            }
    }}
    return flag;
    
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int r = cur_game->rows;
    int l = cur_game->cols;
    int flag = 0; // a checker for shift/merge
    for(int i = 0; i<r; i++){ // go through each row and column
        for(int j = l-1; j>=0; j--){
            if(cur_game->cells[i*l+j] != -1){ //check if the current cell isnt empty
                for(int k = l-1; k>j ; k--){ //once the element is found use this loop to manipulate matrix 
		
                if(cur_game->cells[i*l+k] == -1){
                    cur_game->cells[i*l+k] = cur_game->cells[i*l+j]; //shift elements to the right
                    cur_game->cells[i*l+j] = -1; //empty out the space
                    flag = 1;
                }
                if(cur_game->cells[i*l+k] == cur_game->cells[(k+1)+i*l] && k!=0 && cur_game->cells[i*l+k]!=-1){
                    cur_game->cells[(k+1)+i*l] = 2*cur_game->cells[i*l+k];
		    cur_game->score+= cur_game->cells[i*l+k]*2; //merging process here
                    cur_game->cells[i*l+k] = -1;
		    
                    flag = 1;
		    break;

                }
                
  
        }
            }
    }}
    return flag;

    
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE

	int r,c,i,j,val=0,a=0,b=0;
	r= cur_game->rows;	//assigning the pointer values of rows and columns
	c= cur_game->cols;
	
	for(i=0; i<r; i++)
	{
		for(j=0; j<c ;j++)
			{
				a=(i*c)+j;
				b=(i+1)*c+j;	
				if(cur_game->cells[a] == -1)
					val++;
				
				if(i<(r-1) && cur_game->cells[a]==cur_game->cells[b])
					val++;

				if(j<(c-1) && cur_game->cells[a]==cur_game->cells[a+1])
					val++;
}
}

	


    return val;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
	}
return 1;
}
