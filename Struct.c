#include<stdio.h>

struct Date {
	int d, m, y;
};
struct TicketForm {
	int id;
	char purchaseDate[15];
	char flightDate[15];
	char name[30];
	char identity[20];
	int seat;
	char route[30];
	char class[10];
	int price;
	char time[10];
};