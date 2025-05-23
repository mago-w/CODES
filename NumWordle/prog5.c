/*	partners: vmagow2, dhruvv4, vkhemka2		
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*INTRODUCTION - The program follows a structured flow to manage a number-guessing game.
 * set_seed first checks the user input and initializes the random number generator using a user-provided seed.
 * start_game then generates four random solution numbers (1–8) and stores them for comparison. 
 * The game progresses through make_guess, which takes user input, and extracts four guessed numbers, 
 * and compares them to the solution. It counts "perfect matches" (correct number and position) and 
 * "misplaced matches" (correct number, wrong position) using a series of conditional checks. 
 * If the guess is valid, the function prints feedback and increments guess_number; otherwise,it reports an error. 
 * 
 * 
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>
#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
//   Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
    int seed;
    char post[2];
//    The sscanf statement below reads the integer into seed. 
    if (sscanf (seed_str, "%d%1s", &seed, post) == 1)
	{
		srand(seed);	//valid seed
		return 1;
	}
	
	else
	{
		printf("set_seed: invalid seed\n");	//invalid seed
		return 0;
	}	
    

//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
    

    
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
    guess_number = 1;
     
    int upper = 8; // upper bound
    
    int lower  = 1; // lower bound 

    // using pseudo- random number generation method from the link provided for all 4 digits
    solution1 = ((rand() % (upper - lower + 1)) + lower);
    solution2 = ((rand() % (upper - lower + 1)) + lower);
    solution3 = ((rand() % (upper - lower + 1)) + lower);
    solution4 = ((rand() % (upper - lower + 1)) + lower);

    // setting pointers
    *one = solution1;
    *two = solution2;
    *three = solution3;
    *four = solution4;

}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
// w, x, y, z - stores the 4 numbers if the guess is valid
// perf- stores the number of perfect guesses
// mism- stores the number of mismatches guesses
// w1,x1,y1,z1 - if these variables are 1, it means the respective number has been found
// s1,s2,s3,s4 - supporting variables for checking of the numbers

	int w = 0;
	int x = 0;
	int y = 0;
	int z = 0;	
	char post[2];
	int perf=0, mism=0;
	//supporting variables
	int w1=0;
	int x1=0;
	int y1=0;
	int z1=0;
	int s1=0;
	int s2=0;
	int s3=0;
	int s4=0;
	//int guess=0;	

	if(!one || !two || !three || !four){ // invalid check for pointers
		printf("make_guess: invalid guess\n");
		return 0;
	}
	int ret_chars = sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
	
	if(ret_chars != 4){ // invalid check for extra string in input(not just 4 digits)
		printf("make_guess: invalid guess\n");
		return 0;
	}
	
	if(w<1 || w>8 || x<1 || x>8 || y<1 || y>8 || z<1 || z>8){ // invalid check for digits entered to be between 1-8
		printf("make_guess: invalid guess\n");
		return 0;
	}
	// store the guessed digits in the output variables.
    // this lets the caller use the user's guesses 
	*one = w;
	*two = x;
	*three = y;
	*four = z;
	

	if(solution1 == w) 	//checks if the first number is right
	{
		perf++;
		w1 = 1;
		s1 = 1;
	}
	
	if(solution2 == x) 	//checks if the second number is right
	{
		perf++;
		x1 = 1;
		s2 = 1;
	}	
	
	if(solution3 == y) 	//checks if the third number is right
	{
		perf++;
		y1 = 1;
		s3 = 1;
	}	
	
	if(solution4 == z)	//checks if the fourth number is right	
	{
		perf++;
		z1= 1;
		s4 = 1;
	}	
	
	if((solution2 == w) && (w1==0) && (s2==0))	//checks if the first number is equal to any other number
	{
		mism++;
		w1++;
		s2++;
	}

	if((solution3 == w) && (w1==0) && (s3==0))	//checks if the first number is equal to any other number
	{
		mism++;
		w1++;
		s3++;
	}
	
	if((solution4 == w) && (w1==0) && (s4==0))	//checks if the first number is equal to any other number
	{
		mism++;
		w1++;
		s4++;
	}

	if((solution1 == x) && (x1==0) && (s1==0))	//checks if the second number is equal to any other number
	{
		mism++;
		x1++;
		s1++;
	}
	
	if((solution3 == x) && (x1==0) && (s3==0))	//checks if the second number is equal to any other number
	{
		mism++;
		x1++;
		s3++;
	}
	
	if((solution4 == x) && (x1==0) && (s4==0))	//checks if the second number is equal to any other number
	{
		mism++;
		x1++;
		s4++;
	}
	
	if((solution1 == y) && (y1==0) && (s1==0))	//checks if the third number is equal to any other number
	{
		mism++;
		y1++;
		s1++;
	}
	
	if((solution2 == y) && (y1==0) && (s2==0))	//checks if the third number is equal to any other number
	{
		mism++;
		y1++;
		s2++;
	}

	if((solution4 == y) && (y1==0) && (s4==0))	//checks if the third number is equal to any other number
	{
		mism++;
		y1++;
		s4++;
	}

	if((solution1 == z) && (z1==0) && (s1==0))	//checks if the fourth number is equal to any other number
	{
		mism++;
		z1++;
		s1++;
	}
	
	if((solution2 == z) && (z1==0) && (s2==0))	//checks if the fourth number is equal to any other number
	{
		mism++;
		z1++;
		s2++;
	}

	if((solution3 == z) && (z1==0) && (s3==0))	//checks if the fourth number is equal to any other number
	{
		mism++;
		z1++;
		s3++;
	}
	printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guess_number,perf,mism);		//prints the output if the guess is valid
	guess_number++;		//guess++
	//guess++;		//was going for a different approach
	
	return 1;
}
