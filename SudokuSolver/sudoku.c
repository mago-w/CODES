//partners- vkhemka2, vmagow2, dhruvv4

#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------
//Algorithm:
// You are free to declare any private functions if needed.
// The given functions, is_val_in_row, is_val_in_col have been changed,
// now they have the loop logic to go through a specific row/ column and 
//search for a particular value. The function is_val_in_3x3_zone now uses nested
// loops to go though the specific grid. We calculate that grid by dividing the i & j values given, 
//by 3 and adding the iteration value. is_val_valid checks for the validation of is_val_in_row, is_val_in_col, and is_val_in_3x3_zone.
// solve_sudoku first checks if the sudoku is already solved.
// If not, it iterates through numbers 1-9 to check for validation of them using is_val_valid and adds the numbers if valid.
// Using backtracking logic, we also ensured that if no number fits the location, we put 0 there instead.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
	for(int a=0; a<9; a++)		//loop goes through the row and checks it the given value is in the grid
	{
		if(sudoku[i][a]== val)
			return 1;	//returns 1 if the value exists in the sudoku	
	}
  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
	for(int a=0; a<9; a++)		//loop goes through the column and checks it the given value is in the grid
	{
		if(sudoku[a][j]== val)
			return 1;	//returns 1 if the value exists in the sudoku	
	}
  
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  	int zone_row= i/3;	//stores the starting row of the grid which the value to be checked
	int zone_col= j/3;	//stores the starting column of the grid which the value to be checked
//now we have the location of the grid to be checked
	for(int a=0; a<3; a++)	//these nested loops go through every single element in the selected grid
	{
		for(int b=0; b<3; b++)
		{
			if(sudoku[((zone_row*3)+a)][((zone_col*3)+b)] == val)	//checks if the value is there in the grid
				return 1;
		}	
	}
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
	if(is_val_in_row(val,i,sudoku) || is_val_in_col(val,j,sudoku) || is_val_in_3x3_zone(val,i,j,sudoku))	//checks if the the value is valid by going through all the functions
		return 0;

  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.

	//this part of the code checks if the sudoku is already solved 
	int check=0;
	int i,j;
	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
			if(sudoku[i][j]==0)	//returns 1 if any element is still zero, which means the sudoku is not complete yet
			{
			check=1;
			break;	
			}

		}
		if(check==1)
			break;
	}
	
	if(check==0)
	return 1;

	
	for(int value=1; value<=9; value++)	//loop goes through all numbers from 1-9
	{
		if(is_val_valid(value,i,j,sudoku))	//checks if the number is valid for the current grid
		{
			sudoku[i][j]=value;
			if(solve_sudoku(sudoku))	//if sudoku is solved, returns true
				return 1;
			
				
		}
		sudoku[i][j]=0;		//if not, it changes that element to zero
	}
	

		
	
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
