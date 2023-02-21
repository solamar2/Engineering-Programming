/* =========================================================
 * Student name:
 *   Sol Amara (ID: 209240050)
 *   solamar@post.bgu.ac.il
 *   Department of Industry and Managering Engineering
 *
 * Course:
 *     C Programming / Zion Sicsic
 *     Exercise 1 
 *
 * Date: 28-Nov-2019
 * Last submitting date: 25-Nov-2019
 *
 * =========================================================
this program has a menu that can
1/ calculate if the number is prime 
2/ calculate a new date
3/ show a sqare
 * ========================================================= */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void main() {
	int flag = 0, menu;
	int num1, num2, numgermn, nummarsn, prime = 1, germn = 1, marsn = 0, i, u; //option1
	int flag1, day, month, year, hist; //option2
	int height, width, flag2, Mw, Mh, Ow, Oh, Iw, Ih, j, t; //option3



	do {
		printf("Please choose from the menu:\n0. Exit \n1. Prime time \n2. Calender calculating \n3. Matrix printing\n");
		scanf("%d", &menu);
		if (menu > 3 || menu < 0)
		{
			flag++;
			if (flag == 1)
				printf("%d error out of 5, try again,\n", flag);
			else
				if (flag != 5)
					printf("%d errors out of 5, try again,\n", flag);
		}
		if (menu == 0)
			break;


		if (menu == 1) {  //option1
			do {
				printf("Enter a number between 1 and 1000000:\n");
				scanf("%d", &num1);
			} while (num1 < 1 || num1>1000000);


			printf("\t N|P|G|M|\n\t u|r|e|a|\n\t m|i|r|r|\n\t b|m|m|s|\n\t r|e|n|n|\n----------+-+-+-+\n");


			for (u = -9; u != 10; u++) {
				num2 = num1 + u;
				prime = 1; germn = 1; marsn = 0;

				if (num2 > 0 && num2<=1000000) {  //check the numbers only if he is positive

					if (num2 > 0)  //check the number only if he is positive
					{
						for (i = 2; i < num2; i++)
						{
							if (num2%i == 0)
								prime = 0;
						}
					}
					else prime = 0;



					numgermn = 2 * num2 + 1;

					if (prime == 1)  // check germn (only if he is prime)
					{
						for (i = 2; i < numgermn; i++)
							if (numgermn% i == 0)
								germn = 0;

					}
					else germn = 0;


					nummarsn = num2 + 1;

					if (prime == 1)     // check marsn (only if he is prime)
					{
						for (; nummarsn != 1;) {
							if (nummarsn % 2 == 0)
								nummarsn = nummarsn / 2;
							else
								break;
						}
					}

					if (nummarsn == 1)
						marsn = 1;

					if (num2 == 1)
					{
						prime = 0; germn = 0; marsn = 0;
					}
					printf("%2d)%7d|%d|%d|%d|\n", u, num2, prime, germn, marsn);
				}
			}

			printf("----------+-+-+-+\n");
		}




		if (menu == 2) { //option2
			do {
				flag1 = 0;
				printf("Enter day month and year:\n");
				scanf("%d%d%d", &day, &month, &year);

				if (year < 0 || year>9999)
					flag1++;  //if the year incorrect flag1++

				if (month < 0 || month>12)
					flag1++;  //if the month incorrect flag++

				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
					if (day > 31 || day < 0)
						flag1++;  //check if the day is right

				if (month == 4 || month == 6 || month == 9 || month == 11)
					if (day > 30 || day < 0)
						flag1++;  //check if the day is right

				if (month == 2) {  //check februar
					if (year % 400 == 0) {
						if (day > 29 || day < 0)
							flag1++;
					}
					else
						if (year % 100 == 0) {
							if (day > 28 || day < 0)
								flag1++;
						}
						else
							if (year % 4 == 0) {
								if (day > 29 || day < 0)
									flag1++;
							}
							else
								if (day > 28 || day < 0)
									flag1++;
				}

			} while (flag1 != 0);


			do {
				printf("Enter a number between -1000000 and 1000000:\n");
				scanf("%d", &hist);
			} while (hist > 1000000 || hist < -1000000); //get hist

			if (hist > 0) {  //calculatr for positive hist
				hist = hist + (day - 1);
				day = 1;
				while (hist > 30)  //calculate the new month and year
				{
					if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
						if (hist >= 31) {
							month++;
							hist = hist - 31;
							if (month > 12)
							{
								year++;
								month = month - 12;
							}


						}

					if (month == 4 || month == 6 || month == 9 || month == 11)
						if (hist >= 30)
						{
							month++;
							hist = hist - 30;
						}


					if (month == 2) {
						if (year % 400 == 0 && hist >= 29) {
							month++;
							hist = hist - 29;

						}
						else
							if (year % 100 == 0 && hist >= 28) {
								month++;
								hist = hist - 28;
							}
							else
								if (year % 4 == 0 && hist >= 29) {
									month++;
									hist = hist - 29;
								}
								else
									if (hist >= 28)
									{
										month++;
										hist = hist - 28;
									}
					}


				}

				day = day + hist;
				// calculate the day:

				if (month == 4 || month == 6 || month == 9 || month == 11)
					if (day > 30)
					{
						month++;
						day = day - 30;
					}

				if (month == 2) {
					if (year % 400 == 0) {
						if (day > 29)
						{
							month++;
							day = day - 29;
						}
					}
					else
						if (year % 100 == 0) {
							if (day > 28)
							{
								month++;
								day = day - 28;
							}
						}
						else
							if (year % 4 == 0) {
								if (day > 29)
								{
									month++;
									day = day - 29;
								}
							}
							else
								if (day > 28)
								{
									month++;
									day = day - 28;
								}
				}
			}



			if (hist < 0) {  //calculate for negative hist
				hist = hist + (day - 1);
				day = 1;
				while (hist < -30)  //calculate the new month and year
				{
					if (month - 1 == 1 || month - 1 == 3 || month - 1 == 5 || month - 1 == 7 || month - 1 == 8 || month - 1 == 10 || month == 1) {
						if (hist <= -31) {
							month--;
							hist = hist + 31;
						}
						if (month < 1)
						{
							year--;
							month = month + 12;
						}
					}


						

					if (month-1 == 4 || month-1 == 6 || month-1 == 9 || month-1 == 11)
						if (hist <= -30)
						{
							month--;
							hist = hist + 30;
						}


					if (month-1 == 2) {
						if (year % 400 == 0 && hist <= -29) {
							month--;
							hist = hist + 29;

						}
						else
							if (year % 100 == 0 && hist <= -28) {
								month--;
								hist = hist +28;
							}
							else
								if (year % 4 == 0 && hist <= -29) {
									month--;
									hist = hist + 29;
								}
								else
									if (hist <= -28)
									{
										month--;
										hist = hist + 28;
									}
					}


				}

				day = day + hist;
				// calculate the day:

				if (month - 1 == 1 || month - 1 == 3 || month - 1 == 5 || month - 1 == 7 || month - 1 == 8 || month - 1 == 10 || month == 1)
				{
					if (day <= 0)
					{
						month--;
						day = day + 31;
						if (month == 0)
						{
							month = 12;
							year--;
						}
					}
				}
				


				if (month-1 == 4 || month-1 == 6 || month-1 == 9 || month-1 == 11)
					if (day <= 0)
					{
						month--;
						day = day + 30;
					}

				if (month-1 == 2) {
					if (year % 400 == 0) {
						if (day <= 0)
						{
							month--;
							day = day + 29;
						}
					}
					else
						if (year % 100 == 0) {
							if (day <= 0)
							{
								month--;
								day = day + 28;
							}
						}
						else
							if (year % 4 == 0) {
								if (day <= 0)
								{
									month--;
									day = day + 29;
								}
							}
							else
								if (day <= 0)
								{
									month--;
									day = day + 28;
								}
				}
			}




			if (year > 9999)
			{
				day = 31; month = 12; year = 9999;
			}  //cant be out of this date

			if (year < 0)
			{
				day = 1; month = 1; year = 0;
			}  //cant be out of this date

			printf("The new date is: %02d.%02d.%4d\n", day, month, year);
		}




		if (menu == 3) {  //option3
			do {
				flag2 = 0;
				printf("Please enter the square odd height, range 5-21 :\n");
				scanf("%d", &height);

				if (height % 2 == 0 || height > 21 || height < 5)
					flag2++;

			} while (flag2 == 1);

			do {

				flag2 = 0;
				printf("Please enter the square odd width, range 5-21 :\n");
				scanf("%d", &width);


				if (width % 2 == 0 || width > 21 || width < 5)
					flag2++;

			} while (flag2 == 1);



			if (width <= 21 && width > 15) //calculate the width
				Iw = 5;
			if (width <= 15 && width > 9)
				Iw = 3;
			if (width <= 9)
				Iw = 1;

			if (((width - Iw) / 2) % 2 == 0)
				Mw = Ow = (width - Iw) / 2;
			else
			{
				Mw = (width - Iw) / 2 - 1;
				Ow = (width - Iw) / 2 + 1;
			}



			if (height <= 21 && height > 15) //calculate the height
				Ih = 5;
			if (height <= 15 && height > 9)
				Ih = 3;
			if (height <= 9)
				Ih = 1;

			if (((height - Ih) / 2) % 2 == 0)
				Mh = Oh = (height - Ih) / 2;
			else
			{
				Mh = (height - Ih) / 2 - 1;
				Oh = (height - Ih) / 2 + 1;
			}



			// print 

			for (t = 0; t < Oh / 2; t++)   //print O linee
			{
				for (j = 0; j < width; j++)
					printf("O");
				printf("\n");
			}

			for (t = 0; t < Mh / 2; t++)  //print M and O lines
			{
				for (j = 1; j <= Ow / 2; j++)
					printf("O");

				for (j = 1; j <= Mw + Iw; j++)
					printf("M");

				for (j = 1; j <= Ow / 2; j++)
					printf("O");

				printf("\n");
			}


			for (t = 0; t < Ih; t++)   //print the middle lines
			{
				for (j = 1; j <= Ow / 2; j++)
					printf("O");

				for (j = 1; j <= Mw / 2; j++)
					printf("M");

				for (j = 1; j <= Iw; j++)
					printf("I");

				for (j = 1; j <= Mw / 2; j++)
					printf("M");

				for (j = 1; j <= Ow / 2; j++)
					printf("O");

				printf("\n");

			}



			for (t = 0; t < Mh / 2; t++)  //print O and M lines
			{
				for (j = 1; j <= Ow / 2; j++)
					printf("O");

				for (j = 1; j <= Mw + Iw; j++)
					printf("M");

				for (j = 1; j <= Ow / 2; j++)
					printf("O");

				printf("\n");
			}


			for (t = 0; t < Oh / 2; t++)     //print O lines
			{
				for (j = 0; j < width; j++)
					printf("O");
				printf("\n");
			}

		}


	} while (flag < 5);

	if (flag == 5)


		printf("5 errors out of 5, bye bye.\n"); //and of the program: 5 chances
	if (menu == 0)
		printf("You chose to end the program, bye bye.\n"); //and of the program: exit

}


