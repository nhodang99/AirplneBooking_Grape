#pragma once

int Menu(void);
int Choice(int*);
void ChangePrice();
int ChangeFightDate();
void ReservedTicket(int);
int TotalPrice();
void Booking(int*, int, int);
void Cancel();
void Ticket(int, int, int, int, int, int, int, int);

//other small function
void RouteList(void);
void GetSystemDate(int*, int*, int*);
int Weekday(int, int, int);
int DateDifference();
int ValidateTime(int, int, int);
int CompareTime(int, int, int, int, int, int);

