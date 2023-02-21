/* =========================================================
 * Student name:
 *   Sol Amara (ID: 209240050)
 *   solamar@post.bgu.ac.il
 *   Department of Industry and Managering Engineering
 *
 * Course:
 *     C Programming / Zion Sicsic
 *     Exercise 3
 *
 * Date: 23-Dec-2019
 * Last submitting date: 31-Dec-2019
 *
 * =========================================================
 this program print diamond from the number that the user choose, and show all the option that can be on the stanga game
 * ========================================================= */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void menu(int try);
void diamond();
void printline(int size);
void printspace(int size);
void printdaimond1(int size, int spacesize);
void printdaimond2(int size, int spacesize);
int score2check();
void stanga();
int score2check();
void option(int score1, int score2, int newscore1, int newscore2, int i, int score[100]);
void printscore(int score[100], int size, int j);



void main() {
	int try = 1;
	printf("Menu\n1. Display menu\n2. Diamond\n3. Stanga\n4. Knight\n5. Exit\nEnter your choice:\n");
	menu(try);
}

void menu(int try) { //this function print the menu and call to the function of what the user choose
	int choice, num;
	num = 3 - try;
	if (try == 4) { 
		printf("no more tries\nBye Bye!!!\n");
		return; 
	}
	scanf("%d", &choice);
	if (choice < 1 || choice>5) {
		if (num!=0) printf("Wrong input you have %d tries left\nEnter your choice:\n", num); //the user have only 3 tries
		try++;
		menu(try);
	}
	if (choice == 5) {//exit
		printf("Bye Bye!!!\n");
		return;
	}
	if (choice == 1) {
		printf("Menu\n1. Display menu\n2. Diamond\n3. Stanga\n4. Knight\n5. Exit\nEnter your choice:\n");
		menu(try);
	}
	if (choice == 2) {
		diamond();
		printf("Enter your choice:\n");
		menu(try);
	}
	if (choice == 3) {
		stanga();
		printf("Enter your choice:\n");
		menu(try);
	}
	if (choice == 4) {
		printf("4. Knight");
		printf("Enter your choice:\n");
		menu(try);
	}
}

void diamond() {
	int size=0, spacesize=-1;
	printf("Enter the size of the diamond(2-9):\n");
	scanf("%d", &size);
	if (size < 2 || size>9) {
		diamond(); //if the size not in the range call again to the function and ask the user to enter again his choise
		return;
	}
	printdaimond1(size, spacesize); // print the lines
	printdaimond2(size-1, spacesize+1);
}

void printline(int size) { //this function responsible to print the line 
	if (size <= 0) return;
	printf("%d", size);
	printline(size - 1);
	if (size == 1) return;
	printf("%d", size);
}

void printspace(int size) { //this function responsible to print the space that change between lines
	if (size == 0) return;
	printf(" ");
	printspace(size-1);
}

void printdaimond1(int size, int spacesize) { //print the lines together
	if (size < 1) return;
	spacesize++;
	printdaimond1(size - 1, spacesize);
	printspace(spacesize);
	printline(size);
	printf("\n");
}

void printdaimond2(int size, int spacesize) { //print the lines together
	if (size < 1) return;
	spacesize++;
	printspace(spacesize);
	printline(size);
	printf("\n");
	printdaimond2(size - 1, spacesize);
}

void stanga() { // this function responsible to get the choise of the user, check that it is in the range and call to the function that print the option
	int score1, score2, newscore1=0, newscore2=0,score[100] = {0,0};
	printf("Enter the result of the 1st team(0-15): \n");
	scanf("%d", &score1);
	if (score1 > 15 || score1 < 0) {
		stanga();
		return;
	}
	score2=score2check();
	option(score1, score2, newscore1, newscore2, 2, score);
}

int score2check() { //check the score of groupe 2 (if it is in the range)
	int score2;
	printf("Enter the result of the 2nd team(0-15): \n");
	scanf("%d", &score2);
	if (score2 > 15 || score2 < 0)
		score2check();
	else return score2;
}

void option(int score1, int score2, int newscore1, int newscore2, int i, int score[100]) {
	// in this function i'm check what is the option. in the array the odd number is the score of group 2 and the even number is the score of group1
	if (score1 == newscore1 && score2 == newscore2) { // if the new score of the groups is equal to the "score" print the array
		printscore(score, i-1, 0); //call the function that print the array
		printf("\n");
		return;
	}

	if (score[i-2] + 1 <= score1) { //add 1 only if it's not more than the score1
		score[i] = score[i - 2] + 1; // in the even number on the array add 1 and add this to the new place
		score[i + 1] = score[i-1]; //don fahnge the odd number
		option(score1, score2,newscore1+1,newscore2, i + 2, score);//call the function with the new score of group 1.
	}

	if (score[i-2]+2<=score1) { //add 2 only if it's not more than the score1
		score[i] = score[i - 2] + 2;
		score[i + 1] = score[i-1];
		option(score1, score2,newscore1+2, newscore2, i + 2, score);
	}

	if (score[i-1] + 1 <= score2) {
		score[i + 1] = score[i - 1] + 1;
		score[i] = score[i-2];
		option(score1, score2,newscore1, newscore2+1, i + 2, score);
	}

	if (score[i-1] + 2 <= score2) {
		score[i + 1] = score[i - 1] + 2;
		score[i] = score[i - 2];
		option(score1, score2,newscore1, newscore2+2 ,i + 2, score);
	}
}

void printscore(int score[100], int size, int j) { //this function print the score oprion together
	if (size < j) return;
	printf("%d:%d ", score[j], score[j + 1]);
	j = j + 2;
	printscore(score, size, j);
}



