#ifndef schedule_header
#define schedule_header

#include "common.h"
#include "schedule.h"

#define MAX_LOCATIONS 6
#define MAX_SCHEDULES_PER_LOCATION 100
#define LOCATION_NAME_LENGTH 20
#define SCHEDULE_ID 8+1

typedef struct {
	int hours;
	int minutes;
} StartTime, Duration;

typedef struct {
	char scheduleID[SCHEDULE_ID];
	char fromLocation[LOCATION_NAME_LENGTH];
	char toLocation[LOCATION_NAME_LENGTH];
	StartTime depatureTime;// Nested by StartTime Structure
	Duration duration;// Nested by Duration Structure
} Schedule;

//main function
void ScheduleMain();
void delete_Schedule(int* totalDeletedSchedules);
void add_Schedule(int* totalAddedSchedules);
void display_Schedule();
void search_Schedule();
void modify_Schedule(int* totalModifiedSchedules);
void report_Schedule(int* totalAddedSchedules, int* totalDeletedSchedules, int* totalModifiedSchedules);

//sub function
int get_ScheduleIndex(const char* location);
int add_ScheduleChoice();
char alphabetChoice();
int numberChoice();
int searchOption();
int modify_ScheduleChoice();
void modifyScheduleInfo(const Schedule* schedule);
void dateTime(); //display current date and time
int readFile(Schedule schedules[], int maxSchedules, const char* filename);// read the file into structure array
void writeFile(const Schedule schedules[], int scheduleCount, const char* filename);// write the structure array into file 

// AllHeader.c
void ScheduleMenu();// Main Menu Design
void scheduleHeader();// Display Schedule Design
void scheduleFooter();
void addScheduleMenu();// Add Schedule Design
void addHeader();
void addDepartureTimeHeader();
void addDurationHeader();
void deleteHeader();// Delete Schedule Design
void searchHeader();//Search Schedule Design;
void searchMenu();
void searchLocationHeader();
void searchDepartureTimeHeader();
void modifyHeader();// Modify Schedule Design
void modifyMenu();
void modifyDepartureTimeHeader();
void modifyDurationHeader();
void reportHeader();// Report Schedule Design
void backtoScheduleMenu();// Back to Menu Design


#endif // !SCHEDULE_HEADER