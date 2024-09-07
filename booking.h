#ifndef booking_header
#define booking_header

#include "common.h"
#include "schedule.h"
#include "member.h"

#define MAX_SEATS 14
#define TICKET_PRICE 20


typedef struct {
    char scheduleID[10];
    char date[20]; // Assuming date format "dd/mm/yyyy"
    int seatNum;
    double ticketPrice;
    char ticketStatus[15];
} TicketDetail;


// Function Prototypes
void bookingMenu();
void bookingMain(Member_log* member_data);
void searchBooking(Schedule* scheduleDetail,char* scheduleID);
void addBooking(char* scheduleID, TicketDetail* ticket, Member_log* member_data);
void displaySeats(const int seats[]);
void displayBooking(TicketDetail *ticket);
void modifyBooking(char* scheduleID, int* totalModify, TicketDetail* ticket, Member_log* member_data);
void deleteBooking(TicketDetail* ticket, int* totalRefund, Member_log* member_data);
void reportBooking(int* totalRefunds, int* totalModify);
void bookTime(char* buffer);
int writeSeatData(const char* filename, const int seats[], int size);
int isSeatAvailable(const int seats[], int seatNo);
int writelogTicketDetails(const char* filename, const TicketDetail* ticket);
int readlogTicketDetails(const char* filename, TicketDetail* ticket);
int bookingValidation(const char* memberID);
int hasExistingBooking(const char* memberID);

#endif