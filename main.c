#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include "Declaration.h"
#include "Struct.c"


// To store number of days in all months from January to Dec
int monthDays[12] = { 31, 28, 31, 30, 31, 30,
						31, 31, 30, 31, 30, 31 };

char fRoute[10][30];

struct TicketForm person[300];

int num = 0, id2 = 1000;

//Main
int main() {
	int choice1, choice2, ** seat, i, price = 0;
	seat = (int**)calloc(49, sizeof(int*));
	for (i = 0;i < 6;i++)
		*(seat + i) = (int*)calloc(49, sizeof(int));
	int x = 0;
	char idc[30];
	RouteList();

	while (x != 6) {
		choice1 = Menu();
		switch (choice1)
		{
			case 1: ChangePrice();
				break;
			case 3:
				ReservedTicket(price);
				break;
			case 4:
				choice2= Choice(&price);
				Booking(seat[choice2 - 1], choice2, price);
				num++;
				break;
			case 5:
				printf("Enter your ticket ID: ");
				scanf("%s", &idc);
				Cancel(idc);
				break;
			case 6: x = 6;
				printf("Thank you for using our service!");
				printf("\n        ______________\n");
				break;
			default:
				printf("Choice not available\n");
				break;
		}
	}
	free(seat);
}


//Print choices
int Menu()
{
	int choice1=0;
	printf("Please choose your option: ");
	printf("\n                 Simple Flight Ticket Booking System\n");
	printf(" ==================================================================\n");
	printf("||             1- To edit price of ticket (only admin):           ||\n");
	printf("||             2- To edit flight schedule (only admin):           ||\n");
	printf("||             3- To view reserved tickets(only admin):           ||\n");
	printf("||             4- To book ticket:                                 ||\n");
	printf("||             5- To cancel the ticket:                           ||\n");
	printf("||             6- Exit system:                                    ||\n");
	printf("||================================================================||\n");
	printf("  Enter your choice: ");
	fflush(stdin);
	scanf("%d", &choice1);
	return choice1;
}


//Change price
void ChangePrice()
{
	int set = 0, j=0;
	FILE* f;
	FILE* fTemp;
	char buffer[100], nPrice[10];
	char path[20] = "FlightSchedule.txt";
	int line = 0, count = 0;
	char pass[20], pak[20] = "pass";

	printf("Enter the password:  ");
	scanf("%s", &pass);
	if (strcmp(pass, pak) == 0)
	{
		printf("Choose the route you want to change original price of ticket: \n");
		for (j = 0;j < 6;j = j + 2) {
			printf("\t%d. %-30s %d. %-30s\n", j + 1, fRoute[j], j + 2, fRoute[j + 1]);
		}
		scanf("%d", &set);
		while (set < 1 || set>6) {
			printf("\nChoice is invalid, please choose another option: ");
			scanf("%d", &set);
		}
		strcat(fRoute[set - 1], "\n");
		f = fopen(path, "r");
		if (!f) printf("cannot open file");
		fTemp = fopen("replace.tmp", "w");
		printf("Set the new price for the route: ");
		fflush(stdin);
		scanf("%s", &nPrice);
		while (strcmp(fRoute[set-1], fgets(buffer, sizeof(buffer), f)) != 0)
		{
			line++;
		}
		rewind(f);
		while (fgets(buffer, sizeof(buffer), f))
		{
			count++;
			if (count == line + 2)
			{
				fputs(nPrice, fTemp);
				fputs("\n", fTemp);
			}
			else
				fputs(buffer, fTemp);
		}
		fclose(f);
		fclose(fTemp);
		remove(path);
		rename("replace.tmp", path);
		fRoute[set-1][strcspn(fRoute[set-1], "\n")] = 0;
		printf("Price of the flight '%s' has been change to %s\n", fRoute[set - 1], nPrice);
		system("pause");
		system("cls");
	}
	else
		printf("The entered password is wrong!\n\n");
}



//Route choice
int Choice(int* price) {
	int  i = 0, count = 0, j = 0, choice=0;
	char line[50];

	//choose route
	printf("Please choose the route: \n");
	for (j = 0;j < 6;j = j + 2) {
		printf("\t%d. %-30s %d. %-30s\n", j + 1, fRoute[j], j + 2, fRoute[j + 1]);
	}
	printf("\nType in your option: ");
	scanf("%d", &choice);
	while (choice < 1 || choice>6) {
		printf("\nChoice is invalid, please choose another option: ");
		scanf("%d", &choice);
	}
	strcpy(person[num].route, fRoute[choice - 1]);


	//Get price of the route
	FILE* f;
	f = fopen("FlightSchedule.txt", "r");
	if (!f) printf("cannot open file");
	while (fgets(line, sizeof(line), f)) {
		count++;
		if (count == (3 + (choice - 1) * 5))
		{
			fscanf(f, "%d", &*price);
		}
	}
	fclose(f);

	//Get flight schedule
	count = 0;
	f = fopen("FlightSchedule.txt", "r");
	if (!f) printf("cannot open file");
	while (fgets(line, sizeof(line), f)) {
		count++;
		if (count == (5 + (choice - 1) * 5))
		{
			line[strcspn(line, "\n")] = 0;
			sprintf(person[num].time, line);
		}
	}
	printf("flight time: %s", person[num].time);
	fclose(f);
	return choice;
}


//booking ticket
void Booking(int* array, int choice, int price)
{
	struct Date current, flight;
	int i, j, validate=0;
	GetSystemDate(&current.d, &current.m, &current.y);
	sprintf(person[num].purchaseDate, "%d/%d/%d", current.d, current.m, current.y);
	do
	{
		printf("\nFlight date (DD/MM/YYYY): ");
		scanf("%d%*c%d%*c%d", &flight.d, &flight.m, &flight.y);
		validate = ValidateTime(flight.d, flight.m, flight.y);
		while (validate == 0)
		{
			printf("\nDate invalid. Please type again");
			printf("\nFlight date (DD/MM/YYYY): ");
			scanf("%d%*c%d%*c%d", &flight.d, &flight.m, &flight.y);
			validate = ValidateTime(flight.d, flight.m, flight.y);
		}
		validate = CompareTime(flight.d, flight.m, flight.y, current.d, current.m, current.y);
		if (validate == 0) printf("\nDate invalid. Please type again");
	} 
	while (validate == 0);

	sprintf(person[num].purchaseDate, "%d/%d/%d", current.d, current.m, current.y);
	sprintf(person[num].flightDate, "%d/%d/%d", flight.d, flight.m, flight.y);

	printf("\nPlease enter your name: ");
	scanf(" %19[^\n]%*[^\n]", &person[num].name);
	printf("Please enter your identity number: ");
	scanf("%s", &person[num].identity);
	printf("\n\t\t =========");
	printf("\n\t\t| COCKPIT |");
	printf("\n\t\t =========\n\n");
	printf("\t _________Business________\n");
	for (i = 1;i <= 16;i++)
	{
		if (array[i] == 0)
			printf("\t %d", i);
		else
			printf("\t *");
		if (i % 4 == 0)
			printf("\n\n");
	};
	printf("\t _________Economy__________\n");
	for (i = 17; i <= 48; i++)
	{
		if (array[i] == 0)
			printf("\t %d", i);
		else
			printf("\t *");
		if (i % 4 == 0)
			printf("\n");
	}

	int valiseat = 0;
	do
	{
		printf("\nWhich seat number do you want? \n");
		scanf("%d", &j);
		if (j > 48 || j < 1)
			valiseat = 0;
		else valiseat = 1;
		while (valiseat==0)
		{
			printf("Sorry, this seat is unavailable! Please choose another seat.\n");
			printf("Please re-enter seat number: ");
			scanf("%d", &j);
			if (j > 48 || j < 1)
				valiseat = 0;
			else valiseat = 1;
		}
		if (array[j] == 1)
		{
			printf("Sorry, this seat is unavailable! Please choose another seat.\n");
			valiseat = 0;
		}
		else valiseat = 1;
	} while (valiseat == 0);

	array[j] = 1;

	person[num].seat = j;
	if (j >= 1 && j <= 16) strcpy(person[num].class, "Business");
	if (j >= 17 && j <= 48) strcpy(person[num].class, "Economy");

	Ticket(id2, price);
	Cusfile(id2, price);
	id2++;
	system("pause");
	system("cls");
}


//Cancel the ticket
void Cancel(char identity[30])
{
	FILE* f;
	FILE* fTemp;
	char buffer[30];
	int line = 0, count = 0;
	char path[] = "Customer.txt";
	char filename[20];
	char directory[300];
	sprintf(filename, "%s.txt", identity);
	strcpy(directory, ".\\Tickets\\");
	strcat(directory, filename);
	if (remove(directory) == 0)
		printf("Cancel ticket successfully!\n");


	f = fopen(path, "r");
	if (!f) printf("cannot open file");
	fTemp = fopen("replace.tmp", "w");

	strcat(filename, "\n");
	while (strcmp(filename, fgets(buffer, sizeof(buffer), f)) != 0)
	{
		line++;
	}
	rewind(f);
	while (fgets(buffer, sizeof(buffer), f))
	{
		count++;
		if (count == line + 1) 
		{
			fputs("", fTemp);
		}
		else
			fputs(buffer, fTemp);
	}
	fclose(f);
	fclose(fTemp);
	remove(path);
	rename("replace.tmp", path);


	
	system("pause");
	system("cls");
}

//Reserved ticket
void ReservedTicket(int price)
{
	int i;
	char pass[10], pak[10] = "pass";

	printf("Enter the password to see details: ");
	scanf("%s", &pass);
	if (strcmp(pass, pak) == 0)
	{
		
	}
	else
		printf("Entered password is wrong \n");
	system("PAUSE");
	system("cls");
}


//Ticket
void Ticket(int id2, int price) {
	system("cls");
	printf("\t                     Booking ticket successfully!");
	printf("\n\n");
	printf("\t        ------------------AIRPLANE TICKET-----------------\n");
	printf("\t=====================================================================\n");
	printf("\t Booking ID : %d \t\t\tRoute : %s\n", id2, person[num].route);
	printf("\t Customer  : %s\n", person[num].name);
	printf("\t\t\t                       Purchase Date    : %s\n", person[num].purchaseDate);
	printf("\t\t\t                       Flight Date      : %s\n", person[num].flightDate );
	printf("\t                                              Time      : %s\n", person[num].time);
	printf("\t Seat Class: %-12s                     Seats No. : %d  \n", person[num].class, person[num].seat);
	printf("\t                                              Price  : %d  \n\n", price);
	//person[num].id = id2;
	printf("\t=====================================================================\n");
	return;
}


//Print each ticket into a ticket file
void Cusfile(int id2, int price)
{
	FILE* C;
	FILE* D;
	char filename[20];
	char directory[300];
	char s[300];
	sprintf(filename, "%s.txt", person[num].identity);
	strcpy(directory, ".\\Tickets\\");
	strcat(directory, filename);
	C = fopen(directory, "w");
	sprintf(s, "%s\n%s\n%s\n%s\n%s\n%d\n%d", person[num].route, person[num].name, person[num].identity,
										person[num].purchaseDate, person[num].flightDate, person[num].seat, price);
	fputs(s, C);

	//Print customer list into Customer.txt
	D = fopen("Customer.txt", "a+");
	strcat(filename, "\n");
	fputs(filename, D);
	fclose(C);
	fclose(D);
}

//Get route list from file and assign to array
void RouteList() {
	int i = 0, count = 0;
	char line[50];
	FILE* f;
	f = fopen("FlightSchedule.txt", "r");
	if (!f) printf("cannot open file");
	while (fgets(line, sizeof(line), f)) {
		count++;
		for (i = 0;i < 6; i++) {
			if (count == 3 + 5 * i)
			{
				line[strcspn(line, "\n")] = 0;
				strcpy(fRoute[i], line);
			}
		}
	}
	fclose(f);
}

//Get system time
void GetSystemDate(int* d, int* m, int* y) {
	SYSTEMTIME stime;
	GetLocalTime(&stime);
	*d = stime.wDay;
	*m = stime.wMonth;
	*y = stime.wYear;
};


//find weekday of flight date using Sakamoto's method
int Weekday(int d, int m, int y)
{
	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}


//calculate date difference

// Counts number of leap years before the given date 
int countLeapYears(struct Date d)
{
	int years = d.y;
	if (d.m <= 2)
		years--;
	return years / 4 - years / 100 + years / 400;
}

//Returns number of days between two given dates 
int DateDifference(struct Date dt1, struct Date dt2)
{
	long int n1 = dt1.y * 365 + dt1.d;

	for (int i = 0; i < dt1.m - 1; i++)
		n1 += monthDays[i];

	n1 += countLeapYears(dt1);

	long int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i < dt2.m - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(dt2);

	// return difference between two counts 
	return (n2 - n1);
}


// validate date (Check date is valid or not)
int ValidateTime(int dd, int mm, int yy)
{
	int validate=0;

	//Check validation of dd, mm ,yy
	//check year
	if (yy >= 1900 && yy <=2030)
	{
		//check month
		if (mm >= 1 && mm <= 12)
		{
			//check days
			if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
				validate = 1;
			else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
				validate = 1;
			else if ((dd >= 1 && dd <= 28) && (mm == 2))
				validate = 1;
			else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
				validate = 1;
			else
				validate = 0;
		}
		else
		{
			validate = 0;
		}
	}
	else
	{
		validate = 0;
	}


	return validate;
}

//compare to current date
int CompareTime(int dd, int mm, int yy, int cd, int cm, int cy)
{
	int validate = 0;
	if (yy == cy)
	{
		if (mm > cm)
			validate = 1;
		else if (mm == cm)
		{
			if (dd >= cd)
				validate = 1;
			else validate = 0;
		}
		else
			validate = 0;
	}
	else if (yy > cy)
		validate = 1;
	else validate = 0;
	return validate;
}