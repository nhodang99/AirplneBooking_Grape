#include<stdio.h>

struct Date {
	int d, m, y;
};
struct TicketForm {
	int id;
	int seat;
	int totalPrice;
	char purchaseDate[15];
	char flightDate[15];
	char name[30];
	char identity[30];
	char route[30];
	char class[10];
	char time[10];
};
struct Flight
{
	int seat;
	char route[30];
	char flightDate[15];
};