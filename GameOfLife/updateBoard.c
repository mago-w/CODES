/* partners: dhruvv4, vmagow2, vkhemka2
 * Algorithm: 
 * We start the code with the function countLiveNeighbour where we go around the 8 neighboring positions, keeping in mind that the edgge cells have lesser neighboring cells.
 * If the neighbor has a value of 1 we increment the neighbor counter and if 0 move to the next iteration, at the end of the function we return the count of neighbors.
 * Next, the function updateBoard where we update the board based on the conditions given. 
 * We create a temporary array and go through the board to make our comparisons, if a cell is live and has either 2 or 3 live neighbors then it stays alive otherwise,
 * we change its value to 0 and its dead. Alternatively, if a cell is dead and has exactly 3 alive neighbors we change its value to 1 and it is alive. We do this by 
 * calling the countLiveNeighbour for each cell. At the end we run a loop to update the board by putting the temporary array values in the board array.
 * Lastly, the function aliveStable where we check if the alive cells remain the same for the next step. We run the same loop as in updateBoard and with the same conditions
 * check if an alive cell is becoming dead or a dead cell is coming to life, if any of these are true we return 0, but if the loops finishes running we return 1 and 
 * know that the alive cells remain the same.
 * 
 * countliveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){


int neighbor=0; // to count the number of neighbors
for(int i=row-1; i<=row+1; i++){ // running the outer loop from the row above it to the row below it
    if(i>=0 && i<boardRowSize){ // checking if it is an edge cell or not 
        for(int j=col-1; j<=col+1; j++){ // running column loop from the column to its left to the column on its right
            if(j>=0 && j<boardColSize){ // checking if it is an edge cell 
                if(!(i==row && j==col)){ // if its not the cell we are currently checking for
                    if(board[i*boardColSize+j]==1){ // if it is alive we incremenmt neighbor
                        neighbor++;
                    }
                }
            }
        }
    }
}
return neighbor; // returning number of alive neighbors
}

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {

    int temparr[boardRowSize*boardColSize]; // temporary array to store the updated board
    for(int i=0; i<boardRowSize; i++){ // running outside loop till row size
        for(int j=0; j< boardColSize; j++){ // runnning inner loop till column size
            int alive = countLiveNeighbor(board,boardRowSize,boardColSize,i,j); // calling countLiveNeighbor function
            if(board[i*boardColSize+j]==1){ // checking if current cell is alive
                if(alive<2 || alive>3){ // if current cell is alive and has less than two or more than 3 alive neighbors
                temparr[i*boardColSize+j]=0; // we change it to dead
                }
                else{
                temparr[i*boardColSize+j]=1; // otherwise it stays alive 
                }
            }
            else{ // has to be zero here 
                if(alive==3){ // if a dead cell has exactly 3 neighbors
                    temparr[i*boardColSize+j]=1; // we change it to alive
                }
                else{
                    temparr[i*boardColSize+j]=0; // otherwise it remains dead
                }
            }
        }
    }
    for(int i=0; i<boardRowSize* boardColSize; i++){ // loop to store updated board from the temp array to the board array
        board[i]=temparr[i];
    }
}


/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same
 * as the current step.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){

for(int i=0; i<boardRowSize; i++){ // running outer loop till row size
        for(int j=0; j< boardColSize; j++){ // running inner loop till column size
            if(board[i*boardColSize+j]==1){ // checking if cell is alive
                if(countLiveNeighbor(board,boardRowSize,boardColSize,i,j)<2 || countLiveNeighbor(board,boardRowSize,boardColSize,i,j)>3){
                    return 0; // if an alive cell has less than 2 or more than 3 neighbors means that it is now dead, hence, we return 0
                }
                else{ // empty else case
                   
                }
            }
            if(board[i*boardColSize+j]==0 && countLiveNeighbor(board,boardRowSize,boardColSize,i,j)==3){
                return 0; // if a dead cell has exactly 3 neighbors it means that its alive now so we return 0
            }
        }
    }
    return 1; // if nothing changes at the end of the loop we return 1

}
				
				
			

