/*
* partners: vmagow2, vkhemka2, dhruvv4
* Algorithm: we start the code with the createMaze function, where we first read the file and make sure that it is not null,
* next we allocate memory for the maze and scan the height and width from the said file. Nextly, we allocate memory for each cell in the matrix,
* since it is a 2d matrix we first allocate memory for the rows and then running a loop allocate memory for each column. Then using the getc method we initialise our array.
* Then in the destroyMze function all we do is free the memory that is allocated to the matrix using the free function.
* Next, we print the matrix out using 2 for loops and a newline print statement in between them.
* Finally we reach our solveMaze method, where we first check our base cases which could be the col or row being out of bounds,
* or reaching the ending position (E), or the cell being not empty.
* Then, we check if the cell is not 'S or 'E' and if true we put a '*'.
* We recursively call the function to check the right, up, left and lower cells in the order to check the same until the base case has been reached. 
* Lastly we swap any cell that has been visited but is not part of the solution with a '~'
*/
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    FILE * file=fopen(fileName, "r");		//checks for file
    if(file==NULL){
        printf("No file present\n");
        return NULL;
    }
    maze_t * maze=malloc(sizeof(maze_t));		//alocate mem for the maze
    fscanf(file, "%u %u", &maze->height, &maze->width);		//gets width and height of the maze

    //added new
    maze->cells = malloc(sizeof(char*) * maze->height);
    for(int i=0; i<maze->height; i++){
        maze->cells[i] = malloc(sizeof(char) * maze->width);
    }

    char temp[50];
    fgets(temp,sizeof(temp),file);
    for(int i=0; i<maze->height; i++){
        for(int j=0; j<maze->width; j++){
            maze->cells[i][j]=fgetc(file);		//loops are used to save cells
            if(maze->cells[i][j]=='S'){			//if S or E found update init row and col
                maze->startRow=i;
                maze->startColumn=j;
            }
            if(maze->cells[i][j]=='E'){
                maze->endRow=i;
                maze->endColumn=j;
            }
        }
        fgetc(file);
    }

    fclose(file);
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    for(int i=0; i<maze->height; i++){
        free(maze->cells[i]);		//delocating memory for each cell
    }
    free(maze->cells);			//delocatinf mem for cell array
    free(maze);				//delocating mem for maze
    /*free(maze->height);
    free(maze->width);
    free(maze->startRow);
    free(maze->startColumn);
    free(maze->endRow);
    free(maze->endColumn);*/
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    for(int i =0; i<maze->height; i++){
        for(int j = 0; j<maze->width; j++){
            printf("%c",maze->cells[i][j]);// prints all cells
        }
	printf("\n");// newline
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently being visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // The provided gold files recursively visit neighbors in the order
    // right, down, left, up. It is okay to deviate from this if you'd 
    // like, but your outputs will be different.

    // Your code here. Make sure to replace following line with your own code.
    if(col<0 || col>=maze->width)		//checks validity of the rows and columnsw
        return 0;
    if(row<0 || row>=maze->height)
        return 0;

    if(maze->cells[row][col] == 'E')			//return 1 if end reached
        return 1;

    char node = maze->cells[row][col];

    if(node == '%' || node == '*' || node == '~')	//return 0 if cell if not empty	 
        return 0;

    if(node != 'S' && node != 'E'){		//put * in cell if its not start or end
        maze->cells[row][col] = '*';
    }

    if(solveMazeDFS(maze, col+1, row)) return 1;	//check right cell
    if(solveMazeDFS(maze, col, row+1)) return 1;	//check upper cell
    if(solveMazeDFS(maze, col-1, row)) return 1;	//check left cell
    if(solveMazeDFS(maze, col, row-1)) return 1;	//check lower cell

    if(maze->cells[row][col] == '*'){			//return to prev state
        maze->cells[row][col] = '~';
    }

    return 0;
}
