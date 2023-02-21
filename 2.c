/* =========================================================
 * Student name:
 *   Sol Amara (ID: 209240050)
 *   solamar@post.bgu.ac.il
 *   Department of Industry and Managering Engineering
 *
 * Course:
 *     C Programming / Zion Sicsic
 *     Exercise 2
 *
 * Date: 09-Dec-2019
 * Last submitting date: 15-Dec-2019
 *
 * =========================================================
this program is damka playing that can calculate score and repeat on the game until the playes wants to quit.

 * ========================================================= */

#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 8 
#include <stdio.h>
#include <string.h>
void place_pawns(char board[][BOARD_SIZE]); 
void print_board(char board[][BOARD_SIZE]); 
char who_is_player(int play_number); 
int is_quit(int row, int col); 
int is_inputloc_legal(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, char player); 
int is_pawn_moveable(char board[][BOARD_SIZE], char pawn, int row, int col); 
int is_move_legal(char board[][BOARD_SIZE], char pawn, int location_row, int location_col, int destination_row, int destination_col); 
int play_single_turn(char board[][BOARD_SIZE], char pawn);
int is_eat(char board[][BOARD_SIZE], char pawn, int location_row, int location_col, int destination_row, int destination_col);
int change_board(char board[][BOARD_SIZE], char pawn, int location_row, int location_col, int destination_row, int destination_col);
char last_line(char board[][BOARD_SIZE]);
char winning(char board[][BOARD_SIZE], int scoreX, int scoreO);
void play(char board[][BOARD_SIZE]);
char play_again(char playagain);
int is_inputdes_legal(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

void main() {
	char playagain, board[BOARD_SIZE][BOARD_SIZE];
	do {
		place_pawns(board); //new board
		play(board);
		printf("Would you like to play another game?(y\\n)\n");
		getchar();
		scanf("%c", &playagain);
		if (playagain!='y'||playagain!='Y'||playagain!='n'||playagain!='N') // if he dosent answer correct ask again
			playagain=play_again(playagain);
	} while (playagain =='y'|| playagain=='Y');
}

void place_pawns(char board[][BOARD_SIZE]) { // this functuon restart the board when start new game
	int i, j;
	for (i = 0; i < 8; i++) { //place X in the lines 0,1,2
		for (j = 0; j < 8; j++) {
			if (i == 0 || i == 2)
				if (j % 2 == 0)
					board[i][j] = ' ';
				else
					board[i][j] = 'X';

			if (i == 1)
				if (j % 2 == 0)
					board[i][j] = 'X';
				else
					board[i][j] = ' ';


			if (i == 5 || i == 7) //place O in lines 5,6,7
				if (j % 2 == 0)
					board[i][j] = 'O';
				else
					board[i][j] = ' ';

			if (i == 6)
				if (j % 2 == 0)
					board[i][j] = ' ';
				else
					board[i][j] = 'O';

			if (i == 3) //place . in lines 3,4
				if (j % 2 == 0)
					board[i][j] = '.';
				else
					board[i][j] = ' ';


			if (i == 4)
				if (j % 2 == 0)
					board[i][j] = ' ';
				else
					board[i][j] = '.';
		}
	}
}

void print_board(char board[][BOARD_SIZE]) { // this function ger the board and print him on the screen
	int i, j, num = 0;
	printf("  |0 1 2 3 4 5 6 7 \n  *----------------\n");
	for (i = 0; i < 8; i++) {
		printf("%2d|", num);
		for (j = 0; j < 8; j++)
			printf("%c ", board[i][j]);
		printf(" \n");
		num++;
	}
}

char who_is_player(int play_number){ // this function get the play number and calculate who is play in this turn
	if (play_number % 2 != 0)
		return 'X';
	else
		return 'O';
}

int is_quit(int row, int col) { // this function get the location row and col that the player chose and return 1 if he decided to quit and 0 if not
	if (row == 999 || col == 999)
		return 1;
	else
		return 0;
}

int is_inputloc_legal(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, char player){ // this function check if the location row and col that the player write is legal. return 0 if its legal and 1 if not.
if (col > 7 || col < 0 || row>7 || row < 0) // check the range
	return 1;
if (player == 'X') { // if its X turn he can choose somthing that not X
	if (board[row][col] != 'X')
		return 1;
}
if (player == 'O') { // if its O turn he can choose somthing that not O
	if (board[row][col]!= 'O')
		return 1;
} return 0; // if everything untill here is ok it's mean that the chose is legal
}

int is_inputdes_legal(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {  // this function check if the destination row and col that the player write is legal. return 0 if its legal and 1 if not.
	if (col > 7 || col < 0 || row > 7 || row < 0) //check the range
		return 1;
	if (board[row][col] != '.') //destination can always be only '.'
			return 1;
	return 0; // if everything until here is ok its mean that the destination is legal
}

int is_pawn_moveable(char board[][BOARD_SIZE], char pawn, int row, int col) { //this function get the board, pawn (X or O), and the location choose. return 0 if the pawn can move and 1 if not.
	if (pawn == 'X') { //checks for pawn X:
		if (row + 1 <= 7) { // if his lines+1 is more than 7 he cant move 
			if (col + 1 <= 7)  // if his col+1 is more than 7 he cant move. can only if there is '.' (go left)
				if (board[row + 1][col + 1] == '.')
					return 0;
				else {
					if (board[row + 1][col + 1] == 'O') //check if he can eat from left
						if (row + 2 <= 7 && col + 2 <= 7)
							if (board[row + 2][col + 2] == '.')
								return 0;
				}
			if (col - 1 >= 0)  // if his lines+1 is more than 7 he cant move (go right)
				if (board[row + 1][col - 1] == '.') // if his col-1 is  less than 0 he cant move. can only if there is '.'
					return 0;
				else {
					if (board[row + 1][col - 1] == 'O')  //check if he can eat from right
						if (row + 2 <= 7 && col - 2 >= 0)
							if (board[row + 2][col - 2] == '.')
								return 0;
				}return 1;
		}}
	if (pawn == 'O') { //checks for O:
		if (row - 1 >= 0) {// if his lines+1 is less than 0 he cant move anymore
			if (col + 1 <= 7) // if his col+1 is more than 7 he cant move. can only if there is '.' (go left)
				if (board[row - 1][col + 1] == '.')
					return 0;
				else {
					if (board[row - 1][col + 1] == 'X') //check if he can eat from left
						if (row - 2 >= 0 && col + 2 <= 7)
							if (board[row - 2][col + 2] == '.')
								return 0;
				}
			if (col - 1 >= 0) // if his col-1 is less than 0 he cant move. can only if there is '.' (go right)
				if (board[row - 1][col - 1] == '.')
					return 0;
				else {
					if (board[row - 1][col - 1] == 'X') //check if he can eat from right
						if (row - 2 >= 0 && col - 2 >= 0)
							if (board[row - 2][col - 2] == '.')
								return 0;
				}
			return 1; // if in all the checks he doesnt return 0 its mean he cant move, return 1.
		}
	} return 1;
}

int is_move_legal(char board[][BOARD_SIZE], char pawn, int location_row, int location_col, int destination_row, int destination_col) { // this function check if the move is legal. return 0 if it is and 1 if its not legal.
	if (is_pawn_moveable(board, pawn, location_row, location_col) == 0) { //check the player only if he can move!
		if (pawn == 'X') {  //x player
			if (destination_row - location_row == 1) { //check if he choose to go one in left/right
				if (destination_col - location_col == 1 || location_col - destination_col == 1)
					if (board[destination_row][destination_col] == '.')
						return 0;
			}
			else {
				if (destination_row - location_row == 2) { //check if he choose to eat
					
					if (destination_col - location_col == 2) {  //check if he wants and can eat from left
						if (board[destination_row][destination_col] == '.')
							if (board[destination_row - 1][destination_col - 1] == 'O')
								return 0;
					}
					else {
						if (location_col - destination_col == 2) {  //check if he wants and can eat from right
							if (board[destination_row][destination_col] == '.')
								if (board[destination_row - 1][destination_col + 1] == 'O')
									return 0;
						}		}	} 	}	}
		if (pawn == 'O') {  //O player
			if (location_row-destination_row == 1) { //check if he choose to go one in left/right
				if (destination_col - location_col == 1 || location_col - destination_col == 1)
					if (board[destination_row][destination_col] == '.')
						return 0;
			}
			else {
				if (location_row - destination_row == 2) { //check if he choose to eat

					if (destination_col - location_col == 2) {  //check if he wants and can eat from left
						if (board[destination_row][destination_col] == '.')
							if (board[destination_row + 1][destination_col - 1] == 'X')
								return 0;
					}
					else {
						if (location_col - destination_col == 2) {  //check if he wants and can eat from right
							if (board[destination_row][destination_col] == '.')
								if (board[destination_row + 1][destination_col + 1] == 'X')
									return 0;
						}	}	}	}}	
	}return 1; //if he choose somethings that not apear until here its mean its not legal
}

int play_single_turn(char board[][BOARD_SIZE], char pawn) { //  return :-1=quit. 1=eat. 0=no eat
	int location_col, location_row, destination_row, destination_col;
	printf("Player %c - Please enter pawn's location (row number followed by column number):\n", pawn);
	do {  //get new choise of location until the choise  is legal and the pawn can move(=0)
		scanf("%d%d", &location_row, &location_col);
		if (is_quit(location_row, location_col) == 1){
			printf("Player %c decided to quit!\n", pawn); 
			return -1;
		}
		if (is_inputloc_legal(board, location_row, location_col, pawn) == 1) {
			printf("Player %c - Bad pawn's selection please enter pawn's location again:\n", pawn);
		}
		
		if (is_inputloc_legal(board, location_row, location_col, pawn) == 0 && is_pawn_moveable(board, pawn, location_row, location_col) == 1) {
			printf("This pawn has nowhere to move!\nPlayer %c - Bad pawn's selection please enter pawn's location again:\n", pawn);
		}
	} while (is_inputloc_legal(board, location_row, location_col, pawn)==1 || is_pawn_moveable(board, pawn, location_row, location_col) == 1);
	
	printf("Player %c - Please enter pawn's destination (row number followed by column number):\n", pawn);
	do { // get new choise of destination untill its legal (=0)
		scanf("%d%d", &destination_row, &destination_col);
		if (is_move_legal(board, pawn, location_row, location_col, destination_row, destination_col) == 1 || is_inputdes_legal(board, destination_row, destination_col)== 1)
			printf("Player %c - Bad pawn's destination please enter pawn's destination again:\n", pawn);
	} while (is_inputdes_legal(board, destination_row, destination_col) == 1|| is_move_legal(board, pawn, location_row, location_col, destination_row, destination_col) ==1);

	if (change_board(board, pawn, location_row, location_col, destination_row, destination_col) == 1) //changing the board
		return 1; //if he eat
	else return 0; //if not 
}

int is_eat(char board[][BOARD_SIZE], char pawn, int location_row, int location_col, int destination_row, int destination_col) { // this function checking if the pawn is eat. return 1 if yes and 0 if not. 
	if (is_move_legal(board, pawn, location_row, location_col, destination_row, destination_col) == 0){ //checking only if its legal
		if (pawn == 'X') {
			if (destination_row - location_row == 2) {
				if (destination_col - location_col == 2 || location_col - destination_col == 2)
					return 1;//the move is legal and the pawn is eat
			} 
		
		} 
		if (pawn == 'O') {
			if (location_row - destination_row == 2) {
				if (destination_col - location_col == 2 || location_col - destination_col == 2)
					return 1; //the move is legal and the pawn is eat
			}
		}
		
	} return 0; // not eat
}

int change_board(char board[][BOARD_SIZE], char pawn, int location_row, int location_col, int destination_row, int destination_col) {
	// this function coming after the loop that check if the move is legal so when we get to this function we already know that the move is legal.
	if (is_eat(board, pawn, location_row, location_col, destination_row, destination_col) == 0) { //changes for single turn without eating
		board[location_row][location_col] = '.';
		board[destination_row][destination_col] = pawn;
	}
	if (is_eat(board, pawn, location_row, location_col, destination_row, destination_col) == 1) { //changes for single turn with eating
		board[location_row][location_col] = '.';
		board[destination_row][destination_col] = pawn;
		if (pawn == 'X') {
			if (destination_col - location_col == 2) {
				board[destination_row - 1][destination_col - 1] = '.';
				return 1;
			}
			if (location_col - destination_col == 2) {
				board[destination_row - 1][destination_col + 1] = '.';
				return 1;
			}
		}
		if (pawn == 'O') {
			if (destination_col - location_col == 2) {
				board[destination_row + 1][destination_col - 1] = '.';
				return 1;
			}
			if (location_col - destination_col == 2) {
				board[destination_row + 1][destination_col + 1] = '.';
				return 1;
			}
		}
	} return 0;
}

char last_line(char board[][BOARD_SIZE]){ // this function checking every turn if someone is win by get to last line (O to 0 and X to 7).
	int i;
	for (i = 1; i < 8; i+=2)
		if (board[0][i] == 'O')
			return 'O'; //return O if he is win
	for (i = 0; i < 8; i+=2)
		if (board[7][i] == 'X')
			return 'X'; // return X if he is win

	 return 0; //return 0  if nobody win
}

char winning(char board[][BOARD_SIZE], int scoreX, int scoreO) { // this function get the score of each pawn and the result from last_line. 
	
	if (scoreX == 12 || last_line(board) == 'X') //checking if X win by get 12 score or get to the last line
		return 'X'; // return X if he is the wining
	if (scoreO == 12 || last_line(board) == 'O') //checking if O win by get 12 score or get to the last line
		return 'O'; // return X if he is the wining
	else return 0; // return 0 if nobody is the wining
}

void play(char board[][BOARD_SIZE]) { // the main function that responsible for new start of game
	int scoreX=0, scoreO=0, play_number=1, num;
	char pawn;
	printf("Lets play Draughts!\n\n----------Play number:1----------\n");
	print_board(board); //restart the board
	do {
		pawn= who_is_player(play_number); //check who is play now
		num = play_single_turn(board, pawn); 
		if (num == -1)
			break; // close the loop because the player is quit
		if (num == 1) // if num=1 its mean that the player eat
			printf("Ho nice move! you got him...\n");
		if (pawn == 'X')
			scoreX+=num; //calculate the new score if X eat
		if (pawn == 'O')
			scoreO+=num; //calculate the new score if O eat
		if (winning(board, scoreX, scoreO) == 'X') {
			printf("Wooohooo! player X Won!\n");
		}
		if (winning(board, scoreX, scoreO) == 'O') {
			printf("Wooohooo! player O Won!\n");
		}
		if (winning(board, scoreX, scoreO) != 0) // its mean that we have a winner
			break; //close the loop beacuse the game over
		play_number++; //new turn
		printf("X score:%d       O score:%d\n", scoreX, scoreO);
		printf("----------Play number:%d----------\n\n", play_number);
		print_board(board);
	} while (winning(board, scoreX, scoreO) == 0);

	print_board(board);
}

char play_again(char playagain) { // this function ask the player if hee want play again untill his answer is y or n
	for (; playagain != 'y'&&playagain != 'n' &&  playagain != 'Y'&&playagain != 'N';) {
		printf("Would you like to play another game?(y\\n)\n");
		getchar();
		scanf("%c", &playagain);
	}
	return playagain;
} 