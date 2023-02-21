/* =========================================================
 * Student name:
 *   Sol Amara (ID: 209240050)
 *   solamar@post.bgu.ac.il
 *   Department of Industry and Managering Engineering
 *
 * Course:
 *     C Programming / Zion Sicsic
 *     Exercise 4
 *
 * Date: 10-January-2020
 * Last submitting date: 24-january-2020
 *
 * =========================================================
 this program is about files.
 * ========================================================= */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct serie {
	char serieName[20];
	int serieCode;
	int numSeasons;
	int rank;
	int* watchingDetails;
}serie;

void showmenu(serie*arr[1000], int menu);
int Unify_Database();
int Get_Unify_Database_Details(serie *arr[1000]);
void print(serie*arr[1000], int nums);
void  Get_Watching_Details(serie*arr[1000], int nums);
void show_watching_deatails();
void bubble_sort_rank(serie*arr[1000], int nums);
void bubble_sort_code(serie*arr[1000], int nums);
void print_series_sortedbyrank(serie*arr[1000], int nums);
void Make_Series_File_Sorted_By_Rank(serie*arr[1000], int nums);
void Exit(serie*arr[1000], int nums);

void main() {
	int menu = 0;
	serie *arr[1000];
	showmenu(arr, menu);
}

void showmenu(serie*arr[1000], int menu) { //the menu
	int unify=0, nums = 0;

	while (unify != 1) { // in the beginnigs can only choose in option 1 or 8
		printf("**********Main Menu **************\n1. Unify Database.\n2. Get Unify Database Details.\n3. Print The Series List Sorted By Code.\n4. Get Watching Details.\n5. Show All Watching Details.\n6. Print Series Sorted By Rank.\n7. Make Series File Sorted By Rank.\n8. Exit.\nEnter Your Selection:");
		scanf("%d%*c", &menu);

		if (menu <= 0 || menu > 8) printf("Wrong Option, Try Again !!! \n");
		if (menu > 0 && menu < 8 && menu != 1) printf("You must unify database before using this option!!!\n");
		if (menu == 8) {
			Exit(arr, nums);
			break;
		}
		if (menu == 1) {
			unify = Unify_Database();
			if (unify == 1) printf("Unify Succeeded\n");
			if (unify == EOF) exit(1);
		}
	}


	if (menu != 8) {
		while (nums == 0 && unify == 1) { //can choose only in option 2
			printf("**********Main Menu **************\n1. Unify Database.\n2. Get Unify Database Details.\n3. Print The Series List Sorted By Code.\n4. Get Watching Details.\n5. Show All Watching Details.\n6. Print Series Sorted By Rank.\n7. Make Series File Sorted By Rank.\n8. Exit.\nEnter Your Selection:");
			scanf("%d%*c", &menu);
			if (menu == 8) {
				Exit(arr, nums);
				break;
			}
			if (menu == 1) printf("Unify Database Has Been Done Already !!!\n");
			if (menu <= 0 || menu > 8) printf("Wrong Option, Try Again !!!\n");
			if (menu > 0 && menu < 8 && menu != 2 && menu != 1) printf("You must Get Unify Database Details before using this option!!!\n");
			if (menu == 2 && nums == 0) {
				nums = Get_Unify_Database_Details(arr);
				if (nums != EOF) printf("Get Unify Database Details Succeeded\n");
				else exit(1);
			}
		}
	}

	if (menu != 8) {
		do {

			printf("**********Main Menu **************\n1. Unify Database.\n2. Get Unify Database Details.\n3. Print The Series List Sorted By Code.\n4. Get Watching Details.\n5. Show All Watching Details.\n6. Print Series Sorted By Rank.\n7. Make Series File Sorted By Rank.\n8. Exit.\nEnter Your Selection:");
			scanf("%d%*c", &menu);
			if (menu <= 0 || menu > 8) printf("Wrong Option, Try Again !!!\n");
			if (menu == 1 && unify == 1) printf("Unify Database Has Been Done Already !!!\n");
			if (menu == 2 && nums != 0) printf("Get Unify Database Details Has Been Done Already !!!\n");

			if (menu == 3 && nums != 0 && unify == 1) print(arr, nums);

			if (menu == 4 && nums != 0 && unify == 1) Get_Watching_Details(arr, nums);

			if (menu == 5 && nums != 0 && unify == 1)  show_watching_deatails();

			if (menu == 6 && nums != 0 && unify == 1) print_series_sortedbyrank(arr, nums);

			if (menu == 7 && nums != 0 && unify == 1)  Make_Series_File_Sorted_By_Rank(arr, nums);

			if (menu == 8 && nums != 0 && unify == 1) {
				Exit(arr, nums);
				break;
			}
		} while (menu != 8);
	}
}

int Unify_Database() { //option1:
	FILE *txt2, *txt1, *seriestxt;
	int code1, code2, season1, season2, ok1, ok2;
	char  filename1[50], filename2[50], series1[20], series2[20], active1, active2;

	do { //file 1
		printf("Enter First File Name:\n");
		gets(filename1);
		txt1 = fopen(filename1, "r");
		if (txt1 == NULL) printf("error in opening file %s !!!\n", &filename1);
	} while (txt1 == NULL); //until it's open

	do { //file 2
		printf("Enter Second File Name:\n");
		gets(filename2);
		txt2 = fopen(filename2, "r");
		if (txt2 == NULL) printf("error in opening file %s !!!\n", &filename2);
	} while (txt2 == NULL);//until its open

	seriestxt = fopen("series.txt", "w");
	if (seriestxt == NULL) exit(1);
	//reading first line from both files:
	ok1 = fscanf(txt1, "%[^,] %*c %d %*c %d %*c %c", &series1, &code1, &season1, &active1);
	ok2 = fscanf(txt2, "%[^,] %*c %d %*c %d %*c %c", &series2, &code2, &season2, &active2);

	while (ok1 != EOF && ok2 != EOF) {
		if (code1 == code2) {
			if (active1 == 'Y'&&active2 == 'Y') { //active in both files, choose the one whis more season
				if (season1 >= season2) fprintf(seriestxt, "%s,%d,%d\n", series1, code1, season1);
				if (season2 > season1) fprintf(seriestxt, "%s,%d,%d\n", series2, code2, season2);
			}
			//active only in one file
			if (active1 == 'Y'&&active2 == 'N') fprintf(seriestxt, "%s,%d,%d\n", series1, code1, season1);
			if (active2 == 'Y'&&active1 == 'N') fprintf(seriestxt, "%s,%d,%d\n", series2, code2, season2);
			//progress in both files
			ok1 = fscanf(txt1, "%*[\n]%[^,] %*c %d %*c %d %*c %c", &series1, &code1, &season1, &active1);
			ok2 = fscanf(txt2, "%*[\n]%[^,] %*c %d %*c %d %*c %c", &series2, &code2, &season2, &active2);
			continue;
		}
		if (code1 < code2) { 
			if (active1 == 'Y') {
				fprintf(seriestxt, "%s,%d,%d\n", series1, code1, season1);
			}//progree noly file1
			ok1 = fscanf(txt1, "%*[\n]%[^,] %*c %d %*c %d %*c %c", &series1, &code1, &season1, &active1);
			continue;
		}

		if (code2 < code1) {
			if (active2 == 'Y') {
				fprintf(seriestxt, "%s,%d,%d\n", series2, code2, season2);
			} //progress only file2
			ok2 = fscanf(txt2, "%*[\n]%[^,] %*c %d %*c %d %*c %c", &series2, &code2, &season2, &active2);
			continue;
		}
	}

	if (ok1 == EOF && ok2 != EOF) { //if there is more series in file2 write them on the series file (file1=eof)
		while (ok2 != EOF) {
			if (active2 == 'Y') fprintf(seriestxt, "%s,%d,%d\n", series2, code2, season2);
			ok2 = fscanf(txt2, "%*[\n]%[^,] %*c %d %*c %d %*c %c", &series2, &code2, &season2, &active2);
		}
	}

	if (ok2 == EOF && ok1 != EOF) { //if there is more series in file1 write them on the series file (file2=eof)
		while (ok1 != EOF) {
			if (active1 == 'Y') fprintf(seriestxt, "%s,%d,%d\n", series1, code1, season1);
			ok1 = fscanf(txt1, "%*[\n]%[^,] %*c %d %*c %d %*c %c", &series1, &code1, &season1, &active1);
		}
	}

	//close all the files and check it's done
	if(fclose(txt1)==EOF||fclose(txt2)==EOF||fclose(seriestxt)==EOF) exit(1);
	return 1; // this option done.
}

int Get_Unify_Database_Details(serie *arr[1000]) { //option2:
	FILE *seriestxt, *watchingtxt;
	int i, j, ok = 0, code, season;
	char name[20];

	seriestxt = fopen("series.txt", "r");
	if (seriestxt == NULL) {
		printf("error in opening file series.txt !!!\n");
		exit(1);
	}

	watchingtxt = fopen("watching.txt", "w"); //open end colse to restart the file(delete all)
	if (watchingtxt == NULL) exit(1);
	if (fclose(watchingtxt) == EOF) exit(1);

	for (i = 0;ok != EOF;i++) { // untill end of file
		ok = fscanf(seriestxt, "%[^,] %*c %d %*c %d %*[\n]", &name, &code, &season); //get from the txt file to the array
		arr[i] = (serie*)malloc(sizeof(serie));
		strcpy(arr[i]->serieName, name);
		arr[i]->serieCode = code;
		arr[i]->numSeasons = season;
		arr[i]->rank = 0;
		arr[i]->watchingDetails = (int*)malloc(sizeof(int)*season);
		for (j = 0;j < season;j++) arr[i]->watchingDetails[j] = 0;
	}

	if(fclose(seriestxt)==EOF) exit(1); //check it's done
	return (i - 1);
}

void print(serie*arr[1000], int nums) { //option 3:
	int i;
	bubble_sort_code(arr, nums); //Arrange the array by code
	printf("Series List\n");
	for (i = 0;i < nums;i++) { //print the array
		printf("%03d-%s(%d)\n", arr[i]->serieCode, arr[i]->serieName, arr[i]->numSeasons);
	}
	printf("\n");
}

void  Get_Watching_Details(serie*arr[1000], int nums) { //oprion4:
	int code, season, i, j = -1;
	FILE *watchingtxt;
	printf("Insert Serie Code:");
	scanf("%d", &code);

	do {
		for (i = 0;i < nums;i++) {
			if (code == arr[i]->serieCode) { //check if the code is legal
				j = i;
			}
		}
		if (j == -1) {
			printf("wrong serie code, try again!!!\n");
			scanf("%d", &code); //if not ask again
		}
	} while (j == -1); //if after this j=-1 its mean that the user dosent choose good code

	printf("Insert Season Number (1 - %d):", arr[j]->numSeasons);
	scanf("%d", &season);
	do {
		if (season<1 || season>arr[j]->numSeasons) { //check that the season is in the range
			printf("wrong season number, try again!!!\n");
			scanf("%d", &season);
		}
	} while (season<1 || season>arr[j]->numSeasons);

	arr[j]->rank++; 
	arr[j]->watchingDetails[season - 1]++;
	watchingtxt = fopen("watching.txt", "a"); //continue writing from the end 
	if (watchingtxt == NULL) exit(1);
	fprintf(watchingtxt, "%03d,%d\n", code, season); //add the new details
	printf("series: %d, season: %d accepted!!!\n", code, season);
	if (fclose(watchingtxt) == EOF) exit(1);

}

void show_watching_deatails() { //oprion5:
	FILE *fp;
	int ok = 0, code, season;
	fp = fopen("watching.txt", "r");
	if (fp == NULL) exit(1);
	printf("Watching Details\n");
	for (;ok != EOF;) { //print untill the end of the file
		ok = fscanf(fp, "%d%*c%d%*c", &code, &season);
		if (ok != EOF) printf("Series Code:%03d, Season Number:%d\n", code, season);
	}

	if (fclose(fp) == EOF) exit(1);
}

void bubble_sort_rank(serie*arr[1000], int nums) { //Arrange the array by rank for option 6
	int i, j, flag = 1;
	serie temp;
	for (i = nums - 1; i&&flag;i--) {
		for (j = flag = 0; j < i;j++) {
			if ((*arr[j + 1]).rank > (*arr[j]).rank) {
				temp = *arr[j];
				*arr[j] = *arr[j + 1];
				*arr[j + 1] = temp;
				flag = 1;
			}
		}
	}
}

void bubble_sort_code(serie*arr[1000], int nums) {  //Arrange the array by code for option 3
	int i, j, flag = 1;
	serie temp;
	for (i = nums - 1; i&&flag;i--) {
		for (j = flag = 0; j < i;j++) {
			if ((*arr[j + 1]).serieCode < (*arr[j]).serieCode) {
				temp = *arr[j];
				*arr[j] = *arr[j + 1];
				*arr[j + 1] = temp;
				flag = 1;
			}
		}
	}
}

void print_series_sortedbyrank(serie*arr[1000], int nums) { //option6:
	int i, j = 0, t, rank;
	bubble_sort_rank(arr, nums);
	rank = (*arr[0]).rank; // rank=the max rank in the array
	for (i = rank;i >= 0;i--) { 
		printf("RANK %d\n", i);
		for (;(*arr[j]).rank == i && j < nums;j++) { //for this rank print untill the EOF or untill series with another rank
			printf("%03d-%s\n", arr[j]->serieCode, arr[j]->serieName);
			for (t = 0;t < (*arr[j]).numSeasons;t++) {
				printf("Season %d:%d\n", t + 1, arr[j]->watchingDetails[t]); //print all the season
			}
		}
	}

}

void Make_Series_File_Sorted_By_Rank(serie*arr[1000], int nums) { //option7:
	FILE *fp;
	int  i;
	bubble_sort_rank(arr, nums);  //Arrange the array by rank
	fp = fopen("seriesRank.txt", "w");//new file
	if (fp == NULL) exit(1);
	for (i = 0;i < nums;i++) {//print all theseries in the array to the file
		fprintf(fp,"%03d(Rank:%d)-%s\n", arr[i]->serieCode, arr[i]->rank, arr[i]->serieName);
	}

	if (fclose(fp) == EOF) exit(1);
}

void Exit(serie*arr[1000], int nums) {
	int i;
	for (i = 0;i < nums;i++) {
		free(arr[i]->watchingDetails); //free the memory 
		free(arr[i]);
	}
	printf("End Of The Program...\n");
}