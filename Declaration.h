#pragma once

int Menu(void);
int Choice(int*);
void ChangePrice();
int ChangeFightDate();
void ReservedTicket();
float TotalPrice(int, struct Date dt1, struct Date dt2);
void Booking(int*, int, int);
void Cancel(char);
void Ticket(int, int);
void Cusfile(int);


//other small function

char** Readfile(const char*);
char* getithline(char, int);
int countLine(const char*);
void RouteList(void);
void GetSystemDate(int*, int*, int*);
int Weekday(int, int, int);
int countLeapYears(struct Date d);
int DateDifference(struct Date dt1, struct Date dt2);
int ValidateTime(int, int, int);
int CompareTime(int, int, int, int, int, int);
