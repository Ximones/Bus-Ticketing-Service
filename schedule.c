#include "schedule.h"

void ScheduleMain() {
	char alphaChoice = ' ';
	int numChoice = 0;
	int totalAddedSchedules = 0;
	int totalDeletedSchedules = 0;
	int totalModifiedSchedules = 0;

	do {
		ScheduleMenu();
		numChoice = numberChoice();

		switch (numChoice) {
		case 1:
			do {
				addScheduleMenu();
				add_Schedule(&totalAddedSchedules);
				display_Schedule();
				backtoScheduleMenu();
				alphaChoice = alphabetChoice();
			} while (alphaChoice == 'Y'); system("cls");
			break;
		case 2:
			do {
				deleteHeader();
				display_Schedule();
				delete_Schedule(&totalDeletedSchedules);
				deleteHeader();
				display_Schedule();
				backtoScheduleMenu();
				alphaChoice = alphabetChoice();
			} while (alphaChoice == 'Y'); system("cls");
			break;
		case 3:
			do {
				search_Schedule();
				backtoScheduleMenu();
				alphaChoice = alphabetChoice();
			} while (alphaChoice == 'Y'); system("cls");
			break;
		case 4:
			do {
				modifyHeader();
				display_Schedule();
				modify_Schedule(&totalModifiedSchedules);
				backtoScheduleMenu();
				alphaChoice = alphabetChoice();
			} while (alphaChoice == 'Y'); system("cls");
			break;
		case 5:
			do {
				report_Schedule(&totalAddedSchedules, &totalDeletedSchedules, &totalModifiedSchedules);
				backtoScheduleMenu();
				alphaChoice = alphabetChoice();
			} while (alphaChoice == 'Y'); system("cls");
			break;
		case 6:
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t           Thank You for use our Service !!     ");
			printf("\n\n\n\n\n\n\n\n\n");
			exit(1);
		}
	} while (numChoice != 6);
}

void dateTime() {
	time_t now;
	time(&now);
	struct tm* local = localtime(&now);

	printf("\tDate: %02d-%02d-%04d\t\t\t\t\t\t\t\t\t   Time: %02d:%02d:%02d\n",
		local->tm_mday, local->tm_mon + 1, local->tm_year + 1900
		, local->tm_hour, local->tm_min, local->tm_sec);
}

//add
void add_Schedule(int* totalAddedSchedules) {
	Schedule tempSchedule, readSchedule[MAX_SCHEDULES_PER_LOCATION];
	int fromChoice, toChoice, scheduleIndex;
	char alphaChoice = ' ';
	int scheduleCount = 0;
	FILE* add_Schedulefile;
	char prefix[4];
	int insertionPoint = 0;

	add_Schedulefile = fopen("schedule.bin", "rb+");
	if (add_Schedulefile == NULL) {
		printf("Error to open.\n");
		exit(1); // If the file doesn't exist or is empty, start IDs from 1
	}
	while (fread(&readSchedule[scheduleCount], sizeof(Schedule), 1, add_Schedulefile)) {
		scheduleCount++;
	}
	fclose(add_Schedulefile);

	do {
		addScheduleMenu();
		printf("\n\t\t\t\tFrom : ");
		fromChoice = add_ScheduleChoice();
		switch (fromChoice) {
		case 1:strcpy(tempSchedule.fromLocation, "PUCHONG");
			strcpy(tempSchedule.scheduleID, "PUC");	break;
		case 2:strcpy(tempSchedule.fromLocation, "SUBANG JAYA");
			strcpy(tempSchedule.scheduleID, "SUJ");	break;
		case 3:strcpy(tempSchedule.fromLocation, "KL CENTRAL");
			strcpy(tempSchedule.scheduleID, "KLC");	break;
		case 4:strcpy(tempSchedule.fromLocation, "SEREMBAN");
			strcpy(tempSchedule.scheduleID, "SRB");	break;
		case 5:strcpy(tempSchedule.fromLocation, "SETAPAK");
			strcpy(tempSchedule.scheduleID, "STP");	break;
		case 6:strcpy(tempSchedule.fromLocation, "CHERAS");
			strcpy(tempSchedule.scheduleID, "CHS");	break;
		}

		scheduleIndex = get_ScheduleIndex(tempSchedule.scheduleID);
		sprintf(tempSchedule.scheduleID, "%s%03d", tempSchedule.scheduleID, scheduleIndex);

		addScheduleMenu();
		printf("\n\t\t\t\tTo : ");
		do {
			toChoice = add_ScheduleChoice();
			switch (toChoice) {
			case 1:strcpy(tempSchedule.toLocation, "PUCHONG");	   break;
			case 2:strcpy(tempSchedule.toLocation, "SUBANG JAYA"); break;
			case 3:strcpy(tempSchedule.toLocation, "KL CENTRAL");  break;
			case 4:strcpy(tempSchedule.toLocation, "SEREMBAN");    break;
			case 5:strcpy(tempSchedule.toLocation, "SETAPAK");     break;
			case 6:strcpy(tempSchedule.toLocation, "CHERAS");      break;
			}
			if (fromChoice == toChoice) {
				printf("\t\t\t\tDestination cannot be the same , please try again > ");
			}
		} while (fromChoice == toChoice);

		addDepartureTimeHeader();
		printf("\n\t\t\t\t     (Format HH MM) : ");
		do {
			scanf("%d %d", &tempSchedule.depatureTime.hours, &tempSchedule.depatureTime.minutes);
			rewind(stdin);
			if (tempSchedule.depatureTime.hours < 6 || tempSchedule.depatureTime.hours > 23
				|| tempSchedule.depatureTime.minutes < 0 || tempSchedule.depatureTime.minutes > 59) {
				printf("\t\t\t\t     Please enter a valid time > ");
			}
		} while (tempSchedule.depatureTime.hours < 6 || tempSchedule.depatureTime.hours > 23
			|| tempSchedule.depatureTime.minutes < 0 || tempSchedule.depatureTime.minutes > 59);

		addDurationHeader();
		printf("\n\t\t\t\t     (Format HH MM) : ");
		do {
			scanf("%d %d", &tempSchedule.duration.hours, &tempSchedule.duration.minutes);
			rewind(stdin);
			if (tempSchedule.duration.hours < 0 || tempSchedule.duration.hours > 4
				|| tempSchedule.duration.minutes < 0 || tempSchedule.duration.minutes > 59) {
				printf("\t\t\t\t     Please enter a valid time > ");
			}
		} while (tempSchedule.duration.hours < 0 || tempSchedule.duration.hours > 4
			|| tempSchedule.duration.minutes < 0 || tempSchedule.duration.minutes > 59);

		addHeader();
		scheduleHeader();
		printf("\t|      %-8s          %-13s      %-13s   \t     %02d:%02d\t       %d Hrs %02d mins    |\n",
			tempSchedule.scheduleID, tempSchedule.fromLocation, tempSchedule.toLocation,
			tempSchedule.depatureTime.hours, tempSchedule.depatureTime.minutes,
			tempSchedule.duration.hours, tempSchedule.duration.minutes);
		scheduleFooter();

		printf("\n\tAre you sure to add this schedule (Y/N) > ");
		alphaChoice = alphabetChoice();

		if (alphaChoice == 'Y')
			(*totalAddedSchedules)++;

	} while (alphaChoice != 'Y');

	addHeader();
	printf("\tNew schedule added with ID: %s\n\n", tempSchedule.scheduleID);

	// Determine the last index for schedules with the same prefix
	strncpy(prefix, tempSchedule.scheduleID, 3);
	for (int i = 0; i < scheduleCount; i++) {
		if (strncmp(readSchedule[i].scheduleID, prefix, 3) == 0) {
			insertionPoint = i + 1;
		}
	}
	// Shift schedules down from the insertion point
	for (int i = scheduleCount; i > insertionPoint; i--) {
		readSchedule[i] = readSchedule[i - 1];
	}

	// Insert the new schedule
	readSchedule[insertionPoint] = tempSchedule;
	scheduleCount++;
	writeFile(readSchedule, scheduleCount, "schedule.bin");
}

int get_ScheduleIndex(const char* location) {
	int scheduleIndex = 0, currentIndex = 0;; // Start from 0, increment based on existing IDs
	FILE* read_schedule;
	Schedule temp_schedule;
	char prefix[4], temp_scheduleID[SCHEDULE_ID] = " "; // To store the three-letter prefix

	// Generate the prefix based on the location
	strncpy(prefix, location, 3);

	read_schedule = fopen("schedule.bin", "rb");
	if (read_schedule == NULL) {
		printf("No existing schedules. Starting from ID 001.\n");
		return 1; // If the file doesn't exist or is empty, start IDs from 1
	}

	// Read through each schedule in the file
	while (fread(&temp_schedule, sizeof(Schedule), 1, read_schedule)) {
		if (strncmp(temp_schedule.scheduleID, prefix, 3) == 0) {
			sscanf(temp_schedule.scheduleID + 3, "%d", &currentIndex); // Extract the numeric part of the ID
			if (currentIndex > scheduleIndex) {
				scheduleIndex = currentIndex; // Update to keep track of the highest ID
			}
		}
	}
	fclose(read_schedule);
	return scheduleIndex + 1; // Return the next available ID
}

int add_ScheduleChoice() {
	int choice = 0;
	do {
		scanf("%d", &choice);
		rewind(stdin);
		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6) {
			printf("\t\t\t\tInvalid Choice , Please try again > ");
		}
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6);
	return choice;
}

//display
void display_Schedule() {
	FILE* file;
	Schedule schedule;
	file = fopen("schedule.bin", "rb+");
	if (file == NULL) {
		printf("Error to open the file\n");
		exit(1);
	}
	else {
		scheduleHeader();
		while (fread(&schedule, sizeof(Schedule), 1, file)) {
			printf("\t|      %-8s          %-13s      %-13s   \t     %02d:%02d\t       %d Hrs %02d mins    |\n",
				schedule.scheduleID, schedule.fromLocation, schedule.toLocation,
				schedule.depatureTime.hours, schedule.depatureTime.minutes,
				schedule.duration.hours, schedule.duration.minutes);
		}
		scheduleFooter();
	}
}

//delete
void delete_Schedule(int* totalDeletedSchedules) {
	char tempScheduleID[SCHEDULE_ID];
	char choice = ' ';
	FILE* filename;
	Schedule schedules[MAX_SCHEDULES_PER_LOCATION];
	int scheduleCount = 0;
	int scheduleFound = -1;
	int indexCount = 0;
	char prefix[4] = " ";

	filename = fopen("schedule.bin", "rb+");
	while (fread(&schedules[scheduleCount], sizeof(Schedule), 1, filename)) {
		scheduleCount++;
	}
	fclose(filename);

	printf("\n\tEnter the schedule ID to delete : ");
	do {
		scanf("%[^\n]", tempScheduleID);
		rewind(stdin);
		for (int i = 0; tempScheduleID[i]; i++) {
			tempScheduleID[i] = toupper(tempScheduleID[i]);
		}
		for (int i = 0; i < scheduleCount; i++) {
			if (strcmp(schedules[i].scheduleID, tempScheduleID) == 0) {
				scheduleFound = i;
			}
		}
		if (scheduleFound == -1) {
			printf("\tSchedule ID not found ,please try again > ");
		}
	} while (scheduleFound == -1);

	printf("\n\tAre you sure you want to delete (Y/N) > ");
	choice = alphabetChoice();
	if (choice == 'Y') {
		(*totalDeletedSchedules)++;
		for (int j = scheduleFound; j < scheduleCount; j++) {
			schedules[j] = schedules[j + 1];
		}
		scheduleCount--;
		strncpy(prefix, tempScheduleID, 3);
		for (int index = 0; index < scheduleCount; index++) {
			if (strncmp(schedules[index].scheduleID, prefix, 3) == 0) {
				indexCount++;
				sprintf(schedules[index].scheduleID, "%s%03d", prefix, indexCount);
				printf("\n\n%s", schedules[index].scheduleID);
			}
		}
		writeFile(schedules, scheduleCount, "schedule.bin");
	}
}

//search
int searchOption() {
	int option;
	system("cls");
	searchMenu();
	printf("\n\t\t\t\t       Enter your choice : ");
	do {
		scanf("%d", &option);
		rewind(stdin);
		if (option < 1 || option > 4) {
			printf("\t\t\t\t       Invalid choice, Enter the Valid Choice > ");
		}
	} while (option < 1 || option > 4);
	return(option);
}

void search_Schedule() {
	char fromSearchString[LOCATION_NAME_LENGTH] = { 0 };
	char toSearchString[LOCATION_NAME_LENGTH] = { 0 };
	char tempFrom[LOCATION_NAME_LENGTH];
	char tempTo[LOCATION_NAME_LENGTH];
	int matchFrom, matchTo, matchTime;
	int searchHour = -1, searchMinute = -1;
	FILE* file;
	Schedule schedule;
	int found = 0;
	char choice = ' ';
	int option;

	option = searchOption();

	if (option == 1) {
		system("cls");
		searchLocationHeader();
		printf("\t\t\t\tKey in the from location : ");
		scanf("%[^\n]", fromSearchString);
		rewind(stdin);
		for (int i = 0; fromSearchString[i]; i++) {
			fromSearchString[i] = toupper(fromSearchString[i]);
		}
	}
	if (option == 2) {
		system("cls");
		searchLocationHeader();
		printf("\t\t\t\tKey in the to location : ");
		scanf("%[^\n]", toSearchString);
		rewind(stdin);
		for (int i = 0; toSearchString[i]; i++) {
			toSearchString[i] = toupper(toSearchString[i]);
		}
	}
	if (option == 3) {
		system("cls");
		searchHeader();
		searchDepartureTimeHeader();
		printf("\n\t\t\t\t     (Format HH MM): ");
		do {
			scanf("%d %d", &searchHour, &searchMinute);
			rewind(stdin);
			if (searchHour < 6 || searchHour > 23 || searchMinute < 0 || searchMinute > 59) {
				printf("\t\t\t\t     Enter a valid time > ");
			}
		} while (searchHour < 6 || searchHour > 23 || searchMinute < 0 || searchMinute > 59);
	}

	do {
		if (option == 4) {
			//Request from location
			system("cls");
			searchLocationHeader();
			printf("\t\t\t\tKey in the from location : ");
			scanf("%[^\n]", fromSearchString);
			rewind(stdin);
			for (int i = 0; fromSearchString[i]; i++) {
				fromSearchString[i] = toupper(fromSearchString[i]);
			}
			//Request to location
			printf("\t\t\t\tKey in the to location : ");
			scanf("%[^\n]", toSearchString);
			rewind(stdin);
			for (int i = 0; toSearchString[i]; i++) {
				toSearchString[i] = toupper(toSearchString[i]);
			}

			// Request departure time
			system("cls");
			searchHeader();
			printf("\t\t\t\tFrom:%s                             To:%s", fromSearchString, toSearchString);
			searchDepartureTimeHeader();
			printf("\n\t\t\t\t     (Format HH MM): ");

			do {
				scanf("%d %d", &searchHour, &searchMinute);
				rewind(stdin);
				if (searchHour < 6 || searchHour > 23 || searchMinute < 0 || searchMinute > 59) {
					printf("\t\t\t\t     Enter a valid time > ");
				}
			} while (searchHour < 6 || searchHour > 23 || searchMinute < 0 || searchMinute > 59);

			system("cls");
			searchHeader();
			printf("\n\n\n\t\t\t\t   +                                                    +\n");
			printf("\t\t\t\t              From\t\t:%s\n", fromSearchString);
			printf("\t\t\t\t              To\t\t:%s\n", toSearchString);
			printf("\t\t\t\t              Departure Time\t:%02d:%02d\n", searchHour, searchMinute);
			printf("\t\t\t\t   +                                                    +\n\n\n");
			printf("\t\t\t\t   Are you sure want to search these details ? > ");
			choice = alphabetChoice();
		}
	} while (choice == 'N');

	file = fopen("schedule.bin", "rb");
	if (file == NULL) {
		printf("Error opening file.\n");
		return;
	}

	system("cls");
	searchHeader();
	printf("\tMatching Schedules:\n\n");
	scheduleHeader();
	while (fread(&schedule, sizeof(Schedule), 1, file)) {

		strcpy(tempFrom, schedule.fromLocation);
		strcpy(tempTo, schedule.toLocation);

		for (int i = 0; tempFrom[i]; i++) {
			tempFrom[i] = toupper(tempFrom[i]);
		}
		for (int i = 0; tempTo[i]; i++) {
			tempTo[i] = toupper(tempTo[i]);
		}

		matchFrom = strstr(tempFrom, fromSearchString) != NULL || option != 1 && option != 4;
		matchTo = strstr(tempTo, toSearchString) != NULL || option != 2 && option != 4;
		matchTime = (searchHour == -1 && searchMinute == -1) || (schedule.depatureTime.hours < searchHour) ||
			(schedule.depatureTime.hours == searchHour && schedule.depatureTime.minutes <= searchMinute);

		if (matchFrom && matchTo && matchTime) {
			printf("\t|      %-8s          %-13s      %-13s   \t     %02d:%02d\t       %d Hrs %02d mins    |\n",
				schedule.scheduleID, schedule.fromLocation, schedule.toLocation,
				schedule.depatureTime.hours, schedule.depatureTime.minutes,
				schedule.duration.hours, schedule.duration.minutes);
			found++;

		}
	}
	if (found == 0) {
		system("cls");
		searchHeader();
		scheduleHeader();
		printf("\n\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t           No Schedule is match with the search     ");
		printf("\n\n\n\n\n\n\n\n\n");
		scheduleFooter();
	}
	else {
		scheduleFooter();
		printf("\n\tFound %d schedule(s).\n", found);
	}
	fclose(file);
}

//modify
void modifyScheduleInfo(const Schedule* schedule) {
	scheduleHeader();
	printf("\t|      %-8s          %-13s      %-13s   \t     %02d:%02d\t       %d Hrs %02d mins    |\n",
		schedule->scheduleID, schedule->fromLocation, schedule->toLocation,
		schedule->depatureTime.hours, schedule->depatureTime.minutes,
		schedule->duration.hours, schedule->duration.minutes);
	scheduleFooter();
}

int modify_ScheduleChoice() {
	int option = 0;
	do {
		scanf("%d", &option);
		rewind(stdin);
		if (option != 1 && option != 2) {
			printf("\t\t\t\t       Invalid Option , Please try again > ");
		}
	} while (option != 1 && option != 2);
	return option;
}

void modify_Schedule(int* totalModifiedSchedules) {
	char scheduleID[SCHEDULE_ID];
	char choice = ' ';
	Schedule schedules[MAX_SCHEDULES_PER_LOCATION];
	int found = 0, option, scheduleCount = 0;

	scheduleCount = readFile(schedules, MAX_SCHEDULES_PER_LOCATION * MAX_LOCATIONS, "schedule.bin");

	printf("\n\tEnter Schedule ID to modify: ");
	do {
		scanf("%[^\n]", &scheduleID);
		rewind(stdin);
		for (int i = 0; scheduleID[i]; i++) {
			scheduleID[i] = toupper(scheduleID[i]);
		}

		for (int i = 0; i < scheduleCount; i++) {
			if (strcmp(schedules[i].scheduleID, scheduleID) == 0) {
				found = 1;
				modifyHeader();
				printf("\n\tSchedule found:\n\n");
				modifyScheduleInfo(&schedules[i]);

				printf("\n\tAre you sure you want to modify (%s) (Y/N) > ", schedules[i].scheduleID);
				choice = alphabetChoice();
				if (choice == 'Y') {
					(*totalModifiedSchedules)++;
					modifyScheduleInfo(&schedules[i]);
					modifyMenu();
					printf("\t\t\t\t       Enter your choice: ");
					option = modify_ScheduleChoice();

					if (option == 1) {
						modifyDepartureTimeHeader();
						printf("\t\t\t\t     (Format HH MM): ");
						do {
							scanf("%d %d", &schedules[i].depatureTime.hours, &schedules[i].depatureTime.minutes);
							rewind(stdin);
							if (schedules[i].depatureTime.hours < 6 || schedules[i].depatureTime.hours > 23
								|| schedules[i].depatureTime.minutes < 0 || schedules[i].depatureTime.minutes > 59) {
								printf("\t\t\t\t     Please enter a valid time > ");
							}
						} while (schedules[i].depatureTime.hours < 6 || schedules[i].depatureTime.hours > 23
							|| schedules[i].depatureTime.minutes < 0 || schedules[i].depatureTime.minutes > 59);
					}
					if (option == 2) {
						modifyDurationHeader();
						printf("\t\t\t\t     (Format HH MM) : ");
						do {
							scanf("%d %d", &schedules[i].duration.hours, &schedules[i].duration.minutes);
							rewind(stdin);
							if (schedules[i].duration.hours < 0 || schedules[i].duration.hours > 4
								|| schedules[i].duration.minutes < 0 || schedules[i].duration.minutes > 59) {
								printf("\t\t\t\t     Please enter a valid time > ");
							}
						} while (schedules[i].duration.hours < 0 || schedules[i].duration.hours > 4
							|| schedules[i].duration.minutes < 0 || schedules[i].duration.minutes > 59);
					}

					modifyHeader();
					modifyScheduleInfo(&schedules[i]);
					printf("\n\tSchedule updated successfully.\n\n");
					break;
				}
			}
		}

		if (!found) {
			printf("\tSchedule ID not found. Enter again > ");
		}
	} while (!found);

	writeFile(schedules, scheduleCount, "schedule.bin");
}

//report

void report_Schedule(int* totalAddedSchedules, int* totalDeletedSchedules, int* totalModifiedSchedules) {

	int fromLocationCount[MAX_LOCATIONS] = { 0 };
	int toLocationCount[MAX_LOCATIONS] = { 0 };
	int totalDurationFrom[MAX_LOCATIONS] = { 0 };
	int totalDurationTo[MAX_LOCATIONS] = { 0 };
	const char* locations[MAX_LOCATIONS] = { "PUCHONG", "SUBANG JAYA", "KL CENTRAL", "SEREMBAN", "SETAPAK", "CHERAS" };

	Schedule* schedules = (Schedule*)malloc(MAX_SCHEDULES_PER_LOCATION * MAX_LOCATIONS * sizeof(Schedule)); //  Allocate the memory space of the certain size by a pointer

	if (!schedules) {
		printf("Memory allocation failed.\n");
		return;
	}
	int scheduleCount = readFile(schedules, MAX_SCHEDULES_PER_LOCATION * MAX_LOCATIONS, "schedule.bin");

	if (scheduleCount == 0) {
		printf("No schedules to report.\n");
		free(schedules); // Uses to release the memory
		return;
	}



	for (int i = 0; i < scheduleCount; i++) {
		for (int j = 0; j < MAX_LOCATIONS; j++) {
			if (strcmp(schedules[i].fromLocation, locations[j]) == 0) {
				fromLocationCount[j]++;
				totalDurationFrom[j] += schedules[i].duration.hours * 60 + schedules[i].duration.minutes;
			}
			if (strcmp(schedules[i].toLocation, locations[j]) == 0) {
				toLocationCount[j]++;
				totalDurationTo[j] += schedules[i].duration.hours * 60 + schedules[i].duration.minutes;
			}
		}
	}
	// Total schedule change
	reportHeader();
	display_Schedule();
	printf("\n\n");
	printf("\t+.......................................................................................................+\n");
	printf("\t|                                          Total schedule change                                        |\n");
	printf("\t+.......................................................................................................+\n");
	printf("\t|                    ADD SCHEDULE                    |                         %d                        |\n",*totalAddedSchedules);
	printf("\t+                                                                                                       +\n");
	printf("\t|                  DELETE SCHEDULE                   |                         %d                        |\n",*totalDeletedSchedules);
	printf("\t+                                                                                                       +\n");
	printf("\t|                  MODIFY SCHEDULE                   |                         %d                        |\n",*totalModifiedSchedules);
	printf("\t+.......................................................................................................+\n");
	printf("\n\n");
	printf("\t+.......................................................................................................+\n");
	printf("\t|                   From location                    |                    To location                   |\n");
	printf("\t+.......................................................................................................+\n");
	printf("\t|     The            Location          Average       |     The            Location         Average      |\n");
	printf("\t|  Location           Amount           Duration      |  Location           Amount          Duration     |\n");
	printf("\t+.......................................................................................................+\n");
	for (int i = 0; i < MAX_LOCATIONS; i++) {
		int avgDurationFrom = fromLocationCount[i] ? totalDurationFrom[i] / fromLocationCount[i] : 0;
		int avgDurationTo = toLocationCount[i] ? totalDurationTo[i] / toLocationCount[i] : 0;
		printf("\t|  %-20s %-8d    %d hrs %02d mins    |  %-20s %-8d   %d hrs %02d mins   |\n",
			locations[i], fromLocationCount[i], avgDurationFrom / 60, avgDurationFrom % 60,
			locations[i], toLocationCount[i], avgDurationTo / 60, avgDurationTo % 60);
		printf("\t+                                                    +                                                  +\n");
	}
	printf("\t+.......................................................................................................+\n");
}

int numberChoice() {
	int choice;
	do {
		scanf("%d", &choice);
		rewind(stdin);
		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6) {
			printf("\t\t\t\t\t       Invalid Number, try again > ");
		}
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6);
	return choice;
}

char alphabetChoice() {
	char choice = ' ';
	do {
		scanf("%c", &choice);
		rewind(stdin);
		choice = toupper(choice);
		if (choice != 'Y' && choice != 'N') {
			printf("\tInvalid Choice , Please try again > ");
		}
	} while (choice != 'Y' && choice != 'N');
	return choice;
}

int readFile(Schedule schedules[], int maxSchedules, const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (!file) {
		printf("Error opening file for reading.\n");
		return 0;
	}

	int count = 0;
	while (count < maxSchedules && fread(&schedules[count], sizeof(Schedule), 1, file)) {
		count++;
	}

	fclose(file);
	return count;
}

void writeFile(const Schedule schedules[], int scheduleCount, const char* filename) {
	FILE* file = fopen(filename, "wb");
	if (!file) {
		printf("Error opening file for writing.\n");
		return;
	}

	for (int i = 0; i < scheduleCount; i++) {
		fwrite(&schedules[i], sizeof(Schedule), 1, file);
	}

	fclose(file);
}

void dateTime();

// Main Menu Design
void ScheduleMenu() {
	system("cls");
	printf("             +---------------------------------------------------------------------------------------------+\n");
	printf("             +                                                                                             +\n");
	printf("             +                             Welcome to our Train Schedule Service                           +\n");
	printf("             +                                                                                             +\n");
	printf("             +---------------------------------------------------------------------------------------------+\n\n");
	dateTime();
	printf("\n\t\t\t\t*                        Main Menu                          *\n");
	printf("\n\t\t\t\t   +                                                    +\n");
	printf("\t\t\t\t                     [1] Add Schedule                         \n");
	printf("\t\t\t\t                     [2] Delete Schedule                      \n");
	printf("\t\t\t\t                     [3] Search Schedule                      \n");
	printf("\t\t\t\t                     [4] Modify Schedule                      \n");
	printf("\t\t\t\t                     [5] Generate Report                      \n");
	printf("\t\t\t\t                     [6] Exit Program                         \n");
	printf("\t\t\t\t   +                                                    +\n");
	printf("\n  \t\t\t\t           << Select your function requirements >> \n\n");
	printf("\t\t\t\t\t       Enter your choice (1-6) > ");
}

// Display Schedule Design

void scheduleHeader() {
	dateTime();
	printf("\t+.......................................................................................................+\n");
	printf("\t|   Schedule ID\t\t  From\t\t       To\t\tDeparture Time\t\t Duration\t|\n");
	printf("\t+.......................................................................................................+\n");
}

void scheduleFooter() {
	printf("\t+.......................................................................................................+\n");
}

// Add Schedule Design

void addHeader() {
	system("cls");
	printf("             +---------------------------------------------------------------------------------------------+\n");
	printf("             +                                          ADD SCHEDULE                                       +\n");
	printf("             +---------------------------------------------------------------------------------------------+\n");
	printf("\n\n");
}

void addScheduleMenu() {
	addHeader();
	printf("\n\t\t\t\t+......................................................+\n");
	printf("\t\t\t\t:  [1] PUC (PUCHONG)\t\t[2] SUJ (SUBANG JAYA)  :\n");
	printf("\t\t\t\t:  [3] KLC (KL CENTRAL)\t\t[4] SRB (SEREMBAN)     :\n");
	printf("\t\t\t\t:  [5] STP (SETAPAK)\t\t[6] CHS (CHERAS)       :\n");
	printf("\t\t\t\t+......................................................+\n");
	printf("\n  \t\t\t\t\t        << Select a location >> \n\n");
}

void addDepartureTimeHeader() {
	addHeader();
	printf("\n\n\n\t\t\t\t     +.............................................+\n");
	printf("\t\t\t\t     :             Enter Departure time            : \n");
	printf("\t\t\t\t     +.............................................+\n\n");
	printf("\t\t\t\t\t    << Operating Hours 06:00 - 23:59 >>\n\n");
}

void addDurationHeader() {
	addHeader();
	printf("\n\n\n\t\t\t\t     +.............................................+\n");
	printf("\t\t\t\t     :              Enter Duration time            : \n");
	printf("\t\t\t\t     +.............................................+\n\n");
	printf("\t\t\t\t\t        <<  No More than 5 hours >>\n\n");
}

// Delete Schedule Design

void deleteHeader() {
	system("cls");
	printf("             +---------------------------------------------------------------------------------------------+\n");
	printf("             +                                       DELETE SCHEDULE                                       +\n");
	printf("             +---------------------------------------------------------------------------------------------+\n");
	printf("\n\n");
}

// Search Schedule Design

void searchHeader() {
	printf("             +---------------------------------------------------------------------------------------------+\n");
	printf("             +                                       SEARCH SCHEDULE                                       +\n");
	printf("             +---------------------------------------------------------------------------------------------+\n");
	printf("\n\n");
}

void searchMenu() {
	searchHeader();
	printf("\n\t\t\t\t       +..........................................+\n");
	printf("\t\t\t\t       :      [1] From Location                   :\n");
	printf("\t\t\t\t       :      [2] To Location                     :\n");
	printf("\t\t\t\t       :      [3] Departure Time (HH MM)          :\n");
	printf("\t\t\t\t       :      [4] Details (From + To + HHMM)      :\n");
	printf("\t\t\t\t       +..........................................+\n");
	printf("\n  \t\t\t\t\t   << Select your search requirements >> \n\n");
}

void searchLocationHeader() {
	searchHeader();
	printf("\n\t\t\t\t+......................................................+\n");
	printf("\t\t\t\t:      PUCHONG (PUC)\t\t    SUBANG JAYA (SUJ)  :\n");
	printf("\t\t\t\t:      KL CENTRAL (KLC)\t\t    SEREMBAN (SRB)     :\n");
	printf("\t\t\t\t:      SETAPAK (STP)\t\t    CHERAS (CHS)       :\n");
	printf("\t\t\t\t+......................................................+\n");
	printf("\n  \t\t\t\t\t        << Select a location >> \n");
	printf("\t\t\t\t\t      (Please Key in as Full Name)  \n\n");

}

void searchDepartureTimeHeader() {
	printf("\n\n\n\t\t\t\t     +.............................................+\n");
	printf("\t\t\t\t     :             Enter Departure time            : \n");
	printf("\t\t\t\t     +.............................................+\n\n");
	printf("\t\t\t\t\t    << Operating Hours 06:00 - 23:59 >>\n\n");
}

// Modify Schedule Design

void modifyHeader() {
	system("cls");
	printf("             +---------------------------------------------------------------------------------------------+\n");
	printf("             +                                       MODIFY SCHEDULE                                       +\n");
	printf("             +---------------------------------------------------------------------------------------------+\n");
	printf("\n\n");
}

void modifyMenu() {
	modifyHeader();
	printf("\n\t\t\t\t       +..........................................+\n");
	printf("\t\t\t\t       :             [1] Departure Time           :\n");
	printf("\t\t\t\t       :             [2] Duration                 :\n");
	printf("\t\t\t\t       +..........................................+\n");
	printf("\n  \t\t\t\t\t<< Choose a option you want to modify : >> \n\n");
}

void modifyDepartureTimeHeader() {
	modifyHeader();
	printf("\n\n\n\t\t\t\t     +.............................................+\n");
	printf("\t\t\t\t     :             Enter Departure time            : \n");
	printf("\t\t\t\t     +.............................................+\n\n");
	printf("\t\t\t\t\t    << Operating Hours 06:00 - 23:59 >>\n\n");
}

void modifyDurationHeader() {
	modifyHeader();
	printf("\n\n\n\t\t\t\t     +.............................................+\n");
	printf("\t\t\t\t     :              Enter Duration time            : \n");
	printf("\t\t\t\t     +.............................................+\n\n");
	printf("\t\t\t\t\t        <<  No More than 5 hours >>\n\n");
}

// Report Schedule Design

void reportHeader() {
	system("cls");
	printf("             +---------------------------------------------------------------------------------------------+\n");
	printf("             +                                            REPORT                                           +\n");
	printf("             +---------------------------------------------------------------------------------------------+\n");
	printf("\n\n");
}

// Back to Menu Design

void backtoScheduleMenu() {
	printf("\n\tDo you want to continue (Y/N) > ");
}