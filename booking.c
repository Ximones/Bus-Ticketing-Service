#include "booking.h"
#include "schedule.h"
#include "member.h"

void bookingMain(Member_log* member_data) {
    char scheduleID[10];
    int totalModify = 0;
    int totalRefunds = 0;
    int ticketCount = 0;
    Schedule schedule;
    TicketDetail ticket;
    int choice = 0;

    bookingMenu();
    scanf("%d", &choice);
    rewind(stdin);
    switch (choice) {
        case 1:
            searchBooking(&schedule, scheduleID);
            if (!bookingValidation(member_data->member_id)) {
                printf("You have to refund your existing record before you can book another ticket.\n");
                break;
            }
            addBooking(scheduleID, &ticket,member_data);
            break;
        case 2: //member
            displayBooking(&ticket);
            break;
        case 3: //staff
            reportBooking(&totalRefunds, &totalModify);
            break;
        case 4: //member
            modifyBooking(scheduleID, &totalModify, &ticket,member_data);
            break;
        case 5: //member
            deleteBooking(&ticket, &totalRefunds,member_data);
            break;
    }
}

void searchBooking(Schedule* scheduleDetail,char *scheduleID) {

    FILE* file;
    Schedule temp;
    int found = 0;

    file = fopen("schedule.bin", "rb");
    if (!file) {
        perror("Unable to open schedule file");
        return;
    }

    printf("Enter the schedule ID to search: ");
    do {
        scanf("%[^\n]", scheduleID);
        rewind(stdin);
        
        for (int i = 0; i < scheduleID[i]; i++) {
            scheduleID[i] = toupper(scheduleID[i]);
        }
        //Move back to the beginning of the file
        fseek(file, 0, SEEK_SET);

        while (fread(&temp, sizeof(Schedule), 1, file)) {
            if (strcmp(temp.scheduleID, scheduleID) == 0) {
                *scheduleDetail = temp;
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Schedule ID not found, please try again. > ");
        }
        else {
            printf("Schedule found: %s - From: %s To: %s\n", scheduleDetail->scheduleID, scheduleDetail->fromLocation, scheduleDetail->toLocation);
        }

    } while (!found);
    fclose(file);
}

void addBooking(char* scheduleID, TicketDetail *ticket, Member_log* member_data) {

    printf("Booking for Schedule ID: %s\n", scheduleID);
    char filename[20];
    int seats[MAX_SEATS] = { 0 };
    int seatNo;
    double price = TICKET_PRICE;
    
    sprintf(filename, "%s.bin", scheduleID);
    FILE* file = fopen(filename, "rb+");
    if (!readSeatData(filename, seats, MAX_SEATS)) {
        writeSeatData(filename, seats, MAX_SEATS);
    }
    displaySeats(seats);

    printf("\nWhich seat do you want to book? ");
    do {
        scanf("%d", &seatNo);
        rewind(stdin);

        if (!isSeatAvailable(seats, seatNo)) {
            printf("Seat already booked.\n");
        }
        else {
            seats[seatNo - 1] = 1; // Mark seat as booked
            break;
        }
    } while (!isSeatAvailable(seats, seatNo));

    writeSeatData(filename, seats, MAX_SEATS);

    strcpy(ticket->scheduleID, scheduleID);
    bookTime(ticket->date); // Assuming bookTime fills date buffer
    ticket->seatNum = seatNo;
    ticket->ticketPrice = TICKET_PRICE;
    strcpy(ticket->ticketStatus, "Booked");

    if (writelogTicketDetails(member_data->member_id, ticket) == 1) {
        printf("Seat %d booked successfully with price RM%.2lf.\n", seatNo, price);
    }

    displaySeats(seats);
}

void displaySeats(int seats[]) {
    int seatsPerRow = 10; // You can adjust this based on your specific requirements
    int numRows = (MAX_SEATS + seatsPerRow - 1) / seatsPerRow;

    printf("Current seat bookings:\n\n");
    printf("     "); // Space for row labels

    // Print column headers
    for (int i = 1; i <= seatsPerRow; i++) {
        printf("\t%-2d", i);
    }
    printf("\n");

    // Print each row
    for (int row = 0; row < numRows; row++) {
        printf("Row %-2d", row + 1);
        for (int col = 0; col < seatsPerRow; col++) {
            int index = row * seatsPerRow + col;
            if (index < MAX_SEATS) {
                printf("\t%-2s", seats[index] ? "X" : ".");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void displayBooking(TicketDetail* ticket) {
    
    char filename[25];
    char memberID[10] = " ";
    sprintf(filename, "%s.txt", memberID);
   // char memberReports[LOG_ID + FORMAT_REPORT + FORMAT_TXT];
   // snprintf(memberReports, sizeof(memberReports), "%s_log.txt", memberID);

  if (!readlogTicketDetails(filename, ticket)) {
      perror("Unable to open the file");
      return;
  }

    printf("Ticket Details\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("%-15s | %-10s | %-6s | %-7s  | %-8s\n", "Ticket ID", "Date", "SeatNo", "Price", "Status");
    printf("--------------------------------------------------------------------------------\n");
    printf("%-15s | %-10s | %-6d |RM %-6.2f | %-8s\n",
        ticket->scheduleID, ticket->date, ticket->seatNum,
        ticket->ticketPrice, ticket->ticketStatus);

    printf("--------------------------------------------------------------------------------\n");
}

void modifyBooking(char* scheduleID, int* totalModify, TicketDetail* ticket,Member_log* member_data) {
    char filename[25];
    int seats[14];
    int currentSeat, newSeat;

    sprintf(filename, "%s.bin", scheduleID);
    if (!readSeatData(filename, seats, MAX_SEATS)) {
        perror("Unable to open the file");
        return;
    }

    if (!readlogTicketDetails(filename, ticket)) {
        perror("Unable to open the file");
        return;
    }

    displaySeats(seats);

    currentSeat = ticket->seatNum;
    printf("Your current booked seat is %d \n", currentSeat);

    printf("Enter new seat number you want to change (1-14): ");
    do {
        scanf("%d", &newSeat);
        rewind(stdin);

        if (!isSeatAvailable(seats, newSeat)) {
            printf("Invalid new seat number or seat already booked > \n");
        }
        else {
            seats[currentSeat - 1] = 0;
            seats[newSeat - 1] = 1;
            ticket->seatNum = newSeat;
            break;
        }
    } while (!isSeatAvailable(seats, newSeat));

    writeSeatData(filename, seats, MAX_SEATS);
    if (writelogTicketDetails(member_data->member_id, ticket) == 1) {
        printf("Modified booking from seat A-%02d to seat A-%02d successfully.\n", currentSeat, newSeat);
        (*totalModify)++; // Increment the count of modifications
    }
    displaySeats(seats);

}

void deleteBooking(TicketDetail *ticket, int* totalRefund,Member_log *member_data) {
    FILE* file;
    char filename[20];
    int seats[14] = { 0 }; // Represents seat bookings
    
    if (!readlogTicketDetails(filename, ticket)) {
        perror("Unable to open the file");
        exit(1);
    }

    sprintf(filename, "%s.bin", ticket->scheduleID);
    if (!readSeatData(filename, seats, MAX_SEATS)) {
        perror("Unable to open the file");
        return;
    }
    displaySeats(seats);

    printf("Refunding for Ticket ID: %s\n", ticket->scheduleID);
    
    seats[ticket->seatNum - 1] = 0;
 
    displaySeats(seats);

    writeSeatData(filename, seats, MAX_SEATS);

    sprintf(filename, "%s_log.txt", member_data->member_id);
    file = fopen("filename", "w"); //clear data of the history
    if (!file) {
        perror("Failed to open log file");
        return;
    } 
    fclose(file);

    printf("Refund successfully\n\n");
    (*totalRefund)++;
}

void bookTime(char* buffer) {
    time_t now;
    struct tm* local;

    time(&now);
    local = localtime(&now);
    sprintf(buffer, "%02d/%02d/%04d", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
}

void reportBooking(int* totalRefunds, int* totalModify) {
    Schedule schedule;
    FILE* file = fopen("schedule.bin", "rb");
    char filename[25];
    int seats[14] = { 0 };
    int totalBooked, totalAmountBooked = 0;
    double totalSales = 0.0;
    int countSchedules = 0;

    if (!file) {
        perror("Unable to open schedule file");
        return;
    }

    printf("Booking Report by Location\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("%-12s | %-20s | %-20s | %-13s\n", "Schedule ID", "From", "To", "Total Booked");
    printf("--------------------------------------------------------------------------------\n");
    while (fread(&schedule, sizeof(Schedule), 1, file)) {
        sprintf(filename, "%s.bin", schedule.scheduleID);
        FILE* seatFile = fopen(filename, "rb");
        if (!seatFile) {
            continue;  // If no file, skip to next schedule
        }

        fread(seats, sizeof(int), 14, seatFile);
        fclose(seatFile);

        totalBooked = 0;
        for (int i = 0; i < 14; i++) {
            if (seats[i]) {
                totalBooked++;
            }
        }

        if (totalBooked > 0) {
            totalAmountBooked += totalBooked;
            totalSales += totalBooked * 20;  // Assuming $20 per ticket
            countSchedules++;
            printf("%-12s | %-20s | %-20s | %13d\n", schedule.scheduleID, schedule.fromLocation, schedule.toLocation, totalBooked);
        }
    }
    fclose(file);

    printf("--------------------------------------------------------------------------------\n");
    if (countSchedules > 0) {
        printf("Total Schedules with Bookings: %d\n", countSchedules);
        printf("Total Booked Seats Across All Schedules: %d\n", totalAmountBooked);
        printf("Total Sales: $%.2f\n", totalSales);
        printf("Average Sales per Schedule: $%.2f\n", totalSales / countSchedules);
    }
    else {
        printf("No bookings found.\n");
    }

    printf("\nAdditional Metrics:\n");
    printf("Total Refunds Processed: %d\n", *totalRefunds);
    printf("Total Seat Modifications: %d\n", *totalModify);
    printf("--------------------------------------------------------------------------------\n");
}

int readSeatData(const char* filename, int seats[], int size) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return 0;  // Indicate failure
    }
    fread(seats, sizeof(int), size, file);
    fclose(file);
    return 1;  // Indicate success
}

// Writes seat data to a file
int writeSeatData(const char* filename, const int seats[], int size) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;  // Indicate failure
    }
    fwrite(seats, sizeof(int), size, file);
    fclose(file);
    return 1;  // Indicate success
}

// Checks if a seat is available; returns 1 if available, 0 otherwise
int isSeatAvailable(const int seats[], int seatNo) {
    if (seatNo < 1 || seatNo > MAX_SEATS || seats[seatNo - 1] != 0) {
        return 0;
    }
    return 1;
}


// Writes ticket details to log file
int writelogTicketDetails(const char* memberID, const TicketDetail* ticket) {
   
    char filename[25];

    sprintf(filename, "%s._log.txt", memberID);
    FILE* file = fopen(filename, "w");  // Append mode
    if (!file) {
        perror("Failed to open log file");
        return 0;
    }
    fprintf(file, "%s\n%s\n%d\n%.2lf\n%s", ticket->scheduleID, ticket->date, ticket->seatNum, ticket->ticketPrice, ticket->ticketStatus);
    fclose(file);
    return 1;
}

int readlogTicketDetails(const char* memberID,TicketDetail* ticket) {

    char filename[25];

    sprintf(filename, "%s._log.txt", memberID);
    FILE* file = fopen(filename, "r");  // Append mode
    if (!file) {
        perror("Failed to open log file");
        return 0;
    }
    while (fscanf(file, "%s\n%s\n%d\n%lf\n%s", ticket->scheduleID, ticket->date,&ticket->seatNum,
        &ticket->ticketPrice, ticket->ticketStatus) != EOF) {

    }
    fclose(file);
    return 1;
}

void bookingMenu() {
    system("cls");
    printf("             +---------------------------------------------------------------------------------------------+\n");
    printf("             +                                                                                             +\n");
    printf("             +                              Welcome to our Train Booking Service                           +\n");
    printf("             +                                                                                             +\n");
    printf("             +---------------------------------------------------------------------------------------------+\n\n");
    dateTime();
    printf("\n\t\t\t\t*                        Main Menu                          *\n");
    printf("\n\t\t\t\t   +                                                    +\n");
    printf("\t\t\t\t                     [1] Search Booking                         \n");
    printf("\t\t\t\t                     [2] Add Booking                         \n");
    printf("\t\t\t\t                     [3] Refund Booking                      \n");
    printf("\t\t\t\t                     [4] Modify Booking                      \n");
    printf("\t\t\t\t                     [5] Generate Report                      \n");
    printf("\t\t\t\t                     [6] Exit Program                         \n");
    printf("\t\t\t\t   +                                                    +\n");
    printf("\n  \t\t\t\t           << Select your function requirements >> \n\n");
    printf("\t\t\t\t\t       Enter your choice (1-5) > ");
}

int hasExistingBooking(const char* memberID) {
    FILE* file;
    char filename[50];
    sprintf(filename, "%s_log.txt", memberID);
    printf("%s", filename);
    file = fopen(filename, "r");
    if (!file) {
        // If the file doesn't open, it might not exist which implies no bookings yet
        return 0;
    }

    // Check for at least one entry in the file to confirm an existing booking
    TicketDetail temp;
    while(fscanf(file, "%s\n%s\n%d\n%lf\n%s",
        temp.scheduleID, temp.date, &temp.seatNum,
        &temp.ticketPrice, temp.ticketStatus) > 0 ) {
        fclose(file);
        return 1;  // Found an existing booking
    }

    fclose(file);
    return 0;  // No bookings found
}


// Function to integrate booking validation in your booking process
int bookingValidation(const char* memberID) {
    if (hasExistingBooking(memberID)) {
        printf("You have already booked a ticket. Only one ticket is allowed per member.\n");
        return 0;  // Invalid to book more
    }
    return 1;  // Valid to proceed with booking
}