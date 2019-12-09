#pragma once

int Menu(void);
int Choice(int*);
void ChangePrice();
int ChangeFightDate();
void ReservedTicket();
int TotalPrice();
void Booking(int*, int, int);
void Cancel(char);
void Ticket(int, int);
void Cusfile(int, int);


//other small function

char** Readfile(const char*);
char* getithline(char, int);
int countLine(const char*);
void RouteList(void);
void GetSystemDate(int*, int*, int*);
int Weekday(int, int, int);
int DateDifference();
int ValidateTime(int, int, int);
int CompareTime(int, int, int, int, int, int);

