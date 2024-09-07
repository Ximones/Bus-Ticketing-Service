#include "staff.h"

//c
void StaffMain() {
	staff staff_Data;
	char alphabetChoice = ' ';
	int numChoice;

	while (1) {
		Staff_Menu(); //DONE
		numChoice = Staff_NumChoice();//DONE
		if (numChoice == 1) {
			Search_Staff(&staff_Data);//DONE BUT CANNOT QUIT MAYBE NEED STAFF ID VERIFICATION
			Modify_StaffRequest(&staff_Data);//DONE
			alphabetChoice = Staff_AlphabetChoice();//DONE
			if (alphabetChoice == 'Y') {
				Modify_StaffVerification(&staff_Data);//DONE
				if (strcmp(staff_Data.staff_job, "MANAGER") == 0) {
					do {
					Modify_ManagerMenu();//DONE
						numChoice = Staff_NumChoice();
						switch (numChoice) {
						case 1:
							Add_NewStaff();//DONE
							break;
						case 2:
							Remove_Staff(&staff_Data);//DONE
							break;
						case 3:
							Modify_StaffDetails(&staff_Data); //DONE
							break;
						case 4:
							Report_Staff();//DONE
							break;
						case 5:
							system("cls");
							break;
						}
					} while (numChoice != 5 );
				}
				else {
					Modify_AdminMenu();
					numChoice = Staff_NumChoice();
					switch (numChoice) {
					case 1:
						Modify_StaffDetails(&staff_Data);
						break;
					case 2:
						system("cls");
						exitMenu();
						exit(1);
					}
				}
			}
		}
		else {
			system("cls");
			exitMenu();
			break;
		}
	}
}

void Staff_Menu() {
	printf("             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :                             GREETINGS. WELCOME TO STAFF MENU.                               :\n");
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n\n");
	currentDateTime();
	printf("\n\t\t\t\t   +                                                    +\n");
	printf("\t\t\t\t                     [1] SEARCH ID                         \n\n");
	printf("\t\t\t\t                     [2] BACK TO MAIN MENU                         \n\n");
	printf("\t\t\t\t   +                                                    +\n");
	printf("\t\t\t\t\t       ENTER YOUR DESIRED CHOICE : ");
}

void Search_Staff(staff* Staff_data) {
	char temp_staffID[LOG_ID + FORMAT_TXT];
	char staff_Choice = ' ';
	FILE* file_staffRead = NULL;

	system("cls");
	printf("             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :                                 PLEASE INPUT YOUR STAFF ID.                                 :\n");
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n\n");
	printf("                                                          :");
	do {
		scanf("%[^\n]", temp_staffID);
		strcat(temp_staffID, ".txt");
		rewind(stdin);
		if (Read_StaffFile(&file_staffRead, temp_staffID, Staff_data) == 0) {
			printf("\n\n\n\n\t\t\t\t\t\t!!!ADMIN ID NOT FOUND!!!                 \n\n");
			printf("\t\t\t\t\t      PLEASE TRY AGAIN?\n\n");
			printf("                                                          :");
		}
	} while (file_staffRead == NULL);
	system("cls");
}

void Modify_StaffRequest(staff* Staff_data) {
	printf("             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :             ADMIN ID : %-10s\t\t NAME : %-20s\t           :\n", Staff_data->staff_id, Staff_data->details.name);
	printf("             :                                                                                             :\n");
	printf("             :             IC : %-15s\t\t         GENDER : %-2c\t                           :\n", Staff_data->details.nric, Staff_data->details.gender);
	printf("             :                                                                                             :\n");
	printf("             :             CONTACT NUMBER : %-15s\t JOB : %-20s\t           :\n", Staff_data->details.contact, Staff_data->staff_job);
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n\n");
	printf("\t\t\t\t   +                                                    +\n");
	printf("\t\t\t\t                  [Y] LOG IN\n\n");
	printf("\t\t\t\t                  [N] GO BACK ONE PAGE\n");
	printf("\t\t\t\t   +                                                    +\n\n");
	printf("\t\t\t\t             ENTER YOUR DESIRED CHOICE :  ");
}

void Modify_StaffVerification(staff* Staff_data) {
	int valid_Pass = 1, valid_Recovery = 1, valid_Choice = 1;

	do {
		printf("             +.............................................................................................+\n");
		printf("             :                                                                                             :\n");
		printf("             :                                 PLEASE INPUT YOUR PASSWORD.                                 :\n");
		printf("             :                                                                                             :\n");
		printf("             +.............................................................................................+\n\n");
		printf("                                                          :");
		valid_Pass = Verification_StaffPass(Staff_data);
		if (!valid_Pass) {
			printf("\n\n\n                                             DO YOU WANT TO RECOVER YOUR PASSWORD?                                  \n\n\n");
			printf("\t\t\t\t                  [Y] YES\n\n");
			printf("\t\t\t\t                  [N] NO ");
			printf("(REALLY?)\n\n");
			printf("                                                          :");
			if (Staff_AlphabetChoice() == 'Y') {
				printf("             +.............................................................................................+\n");
				printf("             :                                                                                             :\n");
				printf("             :                                 PLEASE INPUT YOUR RECOVERY PASSWORD.                        :\n");
				printf("             :                                                                                             :\n");
				printf("             +.............................................................................................+\n\n");
				printf("                                                          :");
				do {
					valid_Recovery = Verification_StaffRecovery(Staff_data);
				} while (!valid_Recovery);
				printf("\n\n\n\t\t\t\t\t\t PASSWORD : %s\n\n", Staff_data->staff_password);
			}
			else {
				continue;
			}
		}
	} while (valid_Pass != 1);
}

int Verification_StaffPass(staff* Staff_data) {
	char verify_pass[PASSWORD] = " ";

	scanf("%[^\n]", verify_pass); //4456
	rewind(stdin);
	if (strcmp(verify_pass, Staff_data->staff_password) == 0) {
		return 1;
	}
	else {
		system("cls");
		printf("\n\n\t\t\t\t\t\t    WRONG PASSWORD.\n\n");
		return 0;
	}
}

int Verification_StaffRecovery(staff* Staff_data) {
	char verify_recovery[PASS_RECOVERY] = " ";

	scanf("%[^\n]", verify_recovery); //numbers
	rewind(stdin);
	if (strcmp(verify_recovery, Staff_data->staff_recovery) == 0) {
		return 1;
	}
	else {
		printf("\n\n\t\t\t\t    WRONG RECOVERY PASSWORD. PLEASE INPUT ONCE AGAIN.\n\n");
		printf("\t\t\t\t\t\t\t  :");
		return 0;
	}
}

void Report_Staff() {
	int count = 0;
	FILE* file_readReport;
	staff check_data, staff_data[MAX_STAFF];

	file_readReport = fopen("AllStaffs.txt", "r");
	if (file_readReport == NULL) {
		printf("\n\n\t\t\t\t    !!!ERROR OPENING THE FILE!!!\n\n");
	}
	else {
		while (fscanf(file_readReport, "%[^|]|%[^|]|%[^|]|%[^|]|%s\n", check_data.staff_id, check_data.details.name
			, check_data.details.nric, check_data.details.contact, check_data.staff_job) != EOF) {
			staff_data[count] = check_data;
			count++;
		}
		system("cls");
		printf("+......................................................................................................................+\n\n");
		printf("\t  STAFF ID    NAME\t\t          NRIC\t\t    CONTACT NUMBER  JOB\t    \n");
		printf("\t  ........... ..........................  ................. ............... ............... \n");
		for (int i = 0; i < count; i++) {
			printf("\t  %-11s %-26s %-17s %-15s %-15s\n\n", staff_data[i].staff_id, staff_data[i].details.name,
				staff_data[i].details.nric, staff_data[i].details.contact, staff_data[i].staff_job);
		}
		printf("\n\n\t  TOTAL STAFF : %d \n\n", count);
		fclose(file_readReport);
	}

}

void Remove_Staff(staff* Staff_data) {
	int count = 0;
	FILE* file_readReport;
	staff check_data, staff_data[MAX_STAFF];
	staff currentStaff = *Staff_data;
	int choice = 0;
	char alphachoice = ' ';
	char tempID[LOG_ID] = " ", staff_deleteAcc[LOG_ID + FORMAT_TXT] = " ";

	file_readReport = fopen("AllStaffs.txt", "r+");
	if (file_readReport == NULL) {
		printf("\n\n\t\t\t\t    !!!ERROR OPENING THE FILE!!!\n\n");
	}
	else {
		while (fscanf(file_readReport, "%[^|]|%[^|]|%[^|]|%[^|]|%s\n", check_data.staff_id, check_data.details.name
			, check_data.details.nric, check_data.details.contact, check_data.staff_job) != EOF) {
			staff_data[count] = check_data;
			count++;
		}
		system("cls");
		printf("+......................................................................................................................+\n\n");
		printf("\t  STAFF ID    NAME\t\t          NRIC\t\t    CONTACT NUMBER  JOB\t    \n");
		printf("\t  ........... ..........................  ................. ............... ............... \n");
		for (int i = 0; i < count; i++) {
			printf("\t  %-11s %-26s %-17s %-15s %-15s\n\n", staff_data[i].staff_id, staff_data[i].details.name,
				staff_data[i].details.nric, staff_data[i].details.contact, staff_data[i].staff_job);
		}
		printf("\n\n\t\t\t\t\t\t  TOTAL STAFF : %d \n\n", count);
		fclose(file_readReport);

		printf("\n\t\t\t\t\t   INPUT STAFF ID TO REMOVE STAFF \n\n");
		printf("\t\t\t\t\t\t      : ");
		do {
			scanf("%[^\n]", tempID);
			rewind(stdin);
			for (int i = 0; tempID[i]; i++) {
				tempID[i] = toupper(tempID[i]);
			}
			if ((strcmp(tempID, currentStaff.staff_id) == 0)) {
				printf("\n\t\t\t\t\t    YOU CANNOT REMOVE YOURSELF ;)\n\n");
				printf("\t\t\t\t\t\t      : ");
			}
		} while (strcmp(tempID, currentStaff.staff_id) == 0);
		
		for (int i = 0; i < count; i++) {
			tempID[i] = toupper(tempID[i]); // the exact solution
			if (strcmp(tempID, staff_data[i].staff_id) == 0) {
				printf("\n\n\t\t\t\t                    ARE YOU SURE?                         \n\n");
				printf("\t\t\t\t                   [Y] REMOVE STAFF                         \n\n");
				printf("\t\t\t\t                     [N] CANCEL                         \n\n");
				printf("\t\t\t\t\t\t         : ");
				scanf("%c", &alphachoice);
				rewind(stdin);
				alphachoice = toupper(alphachoice);
				if (alphachoice == 'Y') {
					snprintf(staff_deleteAcc, sizeof(staff_deleteAcc), "%s.txt", staff_data[i].staff_id);
					if (remove(staff_deleteAcc) != 0) {
						perror("\t\t\t\t\t\t\t !!!ERROR!!!\n");
					}
					else {
						staff_data[i] = staff_data[i + 1];
						count--;
						printf("\n\t\t\t\t\t\t   STAFF IS DELETED. \n");
					}
				}
				file_readReport = fopen("AllStaffs.txt", "w+");
				if (file_readReport == NULL) {
					printf("\n\n\t\t\t\t    !!!ERROR OPENING THE FILE!!!\n\n");
				}
				else {
					for (int i = 0; i < count; i++) {
						fprintf(file_readReport, "%s|%s|%s|%s|%s\n", staff_data[i].staff_id, staff_data[i].details.name
							, staff_data[i].details.nric, staff_data[i].details.contact, staff_data[i].staff_job);
					}
					fclose(file_readReport);

				}
			}
		}

	}

}

char Staff_AlphabetChoice() {
	char staff_choice = ' ';
	do {
		scanf("%c", &staff_choice);
		rewind(stdin);
		staff_choice = toupper(staff_choice);

		if (staff_choice != 'Y' && staff_choice != 'N') {
			printf("\n\t\t\t\tINVALID SELECTION. PLEASE INPUT THE CORRESPONDING ALPHABET.\n\n");
			printf("\t\t\t\t\t\t\t     :");
		}
	} while (staff_choice != 'Y' && staff_choice != 'N');
	system("cls");
	return staff_choice;
}

int Staff_NumChoice() {
	int staff_choice;
	do {
		scanf("%d", &staff_choice);
		rewind(stdin);
		if (staff_choice != 1 && staff_choice != 2 && staff_choice != 3 && staff_choice != 4 && staff_choice != 5) {
			printf("\n\t\t\t\t  INVALID SELECTION. PLEASE INPUT THE CORRESPONDING NUMBER.\n\n");
			printf("\t\t\t\t\t\t\t     :");
		}
	} while (staff_choice != 1 && staff_choice != 2 && staff_choice != 3 && staff_choice != 4 && staff_choice != 5);
	return staff_choice;
}
//MANAGER
void Modify_ManagerMenu() {
	system("cls");
	printf("\n\n             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :                             GREETINGS. WELCOME TO OPTION MENU.                              :\n");
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n\n");
	printf("\t\t\t\t                  [1] ADD STAFF\n\n");
	printf("\t\t\t\t                  [2] REMOVE STAFF ACCOUNT\n\n");
	printf("\t\t\t\t                  [3] MAKE CHANGES ON STAFF ACCOUNT\n\n");
	printf("\t\t\t\t                  [4] VIEW REPORTS\n\n");
	printf("\t\t\t\t                  [5] QUIT PROGRAM\n\n");
	printf("\t\t\t\t             ENTER THE CORRESPONDING CHOICE :  ");
}
//ADMIN
void Modify_AdminMenu() {
	system("cls");
	printf("\n\n             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :                             GREETINGS. WELCOME TO OPTION MENU.                              :\n");
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n\n");
	printf("\t\t\t\t                  [1] MAKE CHANGES ON STAFF ACCOUNT\n\n");
	printf("\t\t\t\t                  [2] QUIT PROGRAM\n\n");
	printf("\t\t\t\t             ENTER THE CORRESPONDING CHOICE :  ");
}

void Add_NewStaff() {
	int count;
	staff temp_staffNew;
	char temp_ID[LOG_ID + FORMAT_TXT];
	FILE* check_AdminFile = NULL, * new_AdminFile = NULL, * addToAllStaffs = NULL;

	system("cls");
	printf("\n\n             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :                             PLEASE COMPLETE THE FOLLOWING DETAILS                           :\n");
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n\n");
	printf("\t\t\t\t    STAFF ID (FORMAT IN ST0000): ");
	do {
		scanf("%[^\n]", temp_ID);
		rewind(stdin);
		for (int i = 0; temp_ID[i]; i++) {
			temp_ID[i] = toupper(temp_ID[i]);
		}
		strcpy(temp_staffNew.staff_id, temp_ID);
		strcat(temp_ID, ".txt");
		if (Read_StaffFile(&check_AdminFile, temp_ID, &temp_staffNew) != 0) {
			printf("\n\t\t\t\t                  STAFF ID IS IN USE.\n\n");
			printf("\t\t\t\t                  PLEASE INPUT A DIFFERENT STAFF ID.\n\n");
			printf("\t\t\t\t              NEW STAFF ID : ");
		}
		else {
			printf("\n\t\t\t\t                      NAME : ");
			do {
				scanf("%[^\n]", temp_staffNew.details.name);
				rewind(stdin);
				for (int i = 0; temp_staffNew.details.name[i]; i++) {
					temp_staffNew.details.name[i] = toupper(temp_staffNew.details.name[i]);
				}
				count = Validate_StaffName(temp_staffNew.details.name);
				if (!count) {
					printf("\n\t\t\t\t                  INVALID NAME AS IT CONTAINS DIGIT(S).\n\n");
					printf("\t\t\t\t                  PLEASE INPUT NAME WITHOUT DIGIT(S).\n\n");
					printf("\t\t\t\t              NEW NAME : ");
					rewind(stdin);
				}
			} while (!count); //Format check Name
			strcpy(temp_staffNew.details.name, temp_staffNew.details.name);

			printf("\n\t\t\t\t              GENDER (M/F) : ");
			do {
				scanf("%c", &temp_staffNew.details.gender);
				temp_staffNew.details.gender = toupper(temp_staffNew.details.gender);
				rewind(stdin);
				if (temp_staffNew.details.gender != 'M' && temp_staffNew.details.gender != 'F') {
					printf("\n\t\t\t\t                  INVALID GENDER SELECTION\n\n");
					printf("\t\t\t\t              GENDER (M/F): ");
					rewind(stdin);
				}
			} while (temp_staffNew.details.gender != 'M' && temp_staffNew.details.gender != 'F'); //Format check Gender

			//NRIC
			printf("\n\t\t\t\t                 IC NUMBER : ");
			do {
				scanf("%[^\n]", temp_staffNew.details.nric);
				rewind(stdin);
				count = Validate_StaffNric(temp_staffNew.details.nric);
				if (!count) {
					printf("\n\t\t\t\t                  INVALID NRIC NUMBER.\n\n");
					printf("\t\t\t\t                  FORMAT : 123456121234\n\n");
					printf("\t\t\t\t                 IC NUMBER : ");
					rewind(stdin);
				}
			} while (!count); //Format check Nric

			char* formattedNric = Format_StaffNric(temp_staffNew.details.nric);
			if (formattedNric != NULL) {
				strcpy(temp_staffNew.details.nric, formattedNric);
				free(formattedNric); //Free the dynamically allocated memory
			}

			//Contact
			printf("\n\t\t\t\t            CONTACT NUMBER : ");
			do {
				scanf("%[^\n]", temp_staffNew.details.contact);
				rewind(stdin);
				count = Validate_StaffContact(temp_staffNew.details.contact);
				if (!count) {
					printf("\n\t\t\t\t                  INVALID CONTACT NUMBER.\n\n");
					printf("\t\t\t\t                  FORMAT : 01234567890\n\n");
					printf("\t\t\t\t            CONTACT NUMBER : ");
				}
			} while (!count);

			char* formattedContact = Format_StaffContact(temp_staffNew.details.contact);

			if (formattedContact != NULL) {
				strcpy(temp_staffNew.details.contact, formattedContact);
				free(formattedContact); //Free the dynamically allocated memory
			}
			system("cls");
			strcpy(temp_staffNew.staff_password, "A10a"); //automatically assign password to new staff
			strcpy(temp_staffNew.staff_recovery, "abc123"); //automatically assign recovery password to new staff
			strcpy(temp_staffNew.staff_job, "ADMINISTRATOR"); //automatically assign admin to new staff
			new_AdminFile = fopen(temp_ID, "w");

			printf("\n\n");
			printf("             +.............................................................................................+\n");
			printf("             :                                                                                             :\n");
			printf("             :                             NEW STAFF IS REGISTERED SUCCESSFULLY!                           :\n");
			printf("             :                                                                                             :\n");
			printf("             +.............................................................................................+\n\n");
			Display_Staff(&temp_staffNew);
			/*printf("\t\t\t\t\t Is your details correct? (Y/N) : \n");
				choice = Member_AlphaChoice();
				if (choice == 'Y') {
					if (Write_MemberFile(&newMember_file, temp_id, &temp_memberNew) == 1) {
						printf("\n\t\t\t\t\t   <<< Register Successfully ! >>>\n");
						printf("\t\t\t\t\t......................................\n");
					}

					char memberReports[LOG_ID + FORMAT_REPORT + FORMAT_TXT];
					snprintf(memberReports, sizeof(memberReports), "%s_log.txt", temp_memberNew.member_id);
					newMember_file = fopen(memberReports, "w");
					fclose(newMember_file);
				}
			} while (choice == 'N');*/
			if (Write_StaffFile(&new_AdminFile, temp_ID, &temp_staffNew) ==1 && Write_ReportStaffFile(&addToAllStaffs, &temp_staffNew) == 1) {
				printf("\n\t\t\t\t\t\tREGISTERED SUCCESSFULLY\n");
				printf("\t\t\t\t\t......................................\n\n");
			}
			else {
				printf("\n\n             +.............................................................................................+\n");
				printf("             :                                                                                             :\n");
				printf("             :                                 !!!ERROR OPENING THE FILE!!!                                :\n");
				printf("             :                                                                                             :\n");
				printf("             +.............................................................................................+\n\n");
				return;
			}
		}

	} while (check_AdminFile != NULL);

}

int Validate_StaffName(const char* staff_Name) {
	int alphabet = 0, digit = 0;
	size_t name_length = strlen(staff_Name); //size_t to prevent integer overflow

	for (int i = 0; i < name_length; i++) {
		if (isalpha(staff_Name[i])) { //isalpha checks whether it is alphabet 
			alphabet = 1;			  //and return non-zero value, else 0
		}
		if (isdigit(staff_Name[i])) { //isdigit checks whether it is digit
			digit = 1;				  //and return non-zero value, else 0
		}
	}
	if (alphabet && digit) {
		return 0;
	}
	else {
		return 1;
	}
}

int Validate_StaffPass(const char* staff_Pass) {
	int digit = 0, alphabet = 0, uppercase = 0, lowercase = 0;
	size_t pass_length = strlen(staff_Pass); //size_t to prevent integer overflow

	if (pass_length < 4) {
		return 0;
	}
	for (int i = 0; i < pass_length; i++) {
		if (isdigit(staff_Pass[i])) {
			digit = 1;
		}
		if (isalpha(staff_Pass[i])) {
			alphabet = 1;
		}
		if (isupper(staff_Pass[i])) {
			uppercase = 1;
		}
		if (islower(staff_Pass[i])) {
			lowercase = 1;
		}
	}
	if (digit && alphabet && uppercase && lowercase) {
		return 1;
	}
	else {
		return 0;
	}
}

int Validate_StaffNric(const char* staff_Nric) {
	size_t nric_length = strlen(staff_Nric); //size_t to prevent integer overflow

	if (nric_length != 12) {
		return 0;
	}
	for (int i = 0; i < nric_length; i++) {
		if (!isdigit(staff_Nric[i])) {
			return 0;
		}
	}
	return 1;
}

int Validate_StaffContact(const char* staff_Contact) {
	size_t contact_length = strlen(staff_Contact); //size_t to prevent integer overflow

	if (staff_Contact[0] != '0') { //contact number must be 0 or else invalid phone number
		return 0;
	}
	if (contact_length > 11 || contact_length < 10) { // Corrected logical operator to '||' (OR)
		return 0;
	}
	for (int i = 0; i < contact_length; i++) {
		if (!isdigit(staff_Contact[i])) {
			return 0;
		}
	}
	return 1;
}

char* Format_StaffNric(const char* staff_Nric) {
	char* format_nric = malloc(NRIC); //malloc let us put 16 byte of memory for NRIC

	if (format_nric != NULL) {
		snprintf(format_nric, NRIC, "%6.6s-%2.2s-%4.4s", staff_Nric, staff_Nric + 6, staff_Nric + 8);
	}
	return format_nric;
}

char* Format_StaffContact(const char* staff_Contact) {
	char* format_contact = malloc(CONTACT_NO); //malloc let us put 14 byte of memory for contact number
	if (format_contact != NULL) {
		snprintf(format_contact, CONTACT_NO, "%3.3s-%-8.8s", staff_Contact, staff_Contact + 3);
	}
	return format_contact;
}

void Display_Staff(staff* Staff_data) {
	printf("             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :             ADMIN ID : %-10s\t\t NAME : %-20s\t           ;\n", Staff_data->staff_id, Staff_data->details.name);
	printf("             :                                                                                             :\n");
	printf("             :             PASSWORD : %-10s\t\t RECOVERY PASSWORD : %-20s  :\n", Staff_data->staff_password, Staff_data->staff_recovery);
	printf("             :                                                                                             :\n");
	printf("             :             IC : %-15s\t\t         GENDER : %-2c\t                           :\n", Staff_data->details.nric, Staff_data->details.gender);
	printf("             :                                                                                             :\n");
	printf("             :             CONTACT NUMBER : %-15s\t JOB : %-20s\t           :\n", Staff_data->details.contact, Staff_data->staff_job);
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n");
}


// Simplified and secured version of Modify_StaffDetails function
void Modify_StaffDetails(staff* Staff_data) {
	int staff_Choice;
	FILE* file_Staff_Modify = NULL, * addToAllStaff = NULL;
	FILE* staffFile;
	staff tempdata[100];  // Assuming there's a reasonable upper limit of 100 staff members
	int count = 0;
	char staff_ModDetails[LOG_ID + FORMAT_TXT];

	snprintf(staff_ModDetails, sizeof(staff_ModDetails), "%s.txt", Staff_data->staff_id);
	do {
		system("cls");
		Display_Staff(Staff_data);
		printf("\t\t\t\t                  [1] PHONE\n\n");
		printf("\t\t\t\t                  [2] PASSWORD\n\n");
		printf("\t\t\t\t                  [3] RECOVERY PASSWORD\n\n");
		printf("\t\t\t\t                  [4] SAVE CHANGES\n\n");
		printf("\t\t\t\t                  ENTER YOUR CHOICE: ");
		scanf("%d", &staff_Choice);
		rewind(stdin);

		switch (staff_Choice) {
		case 1:
			Modify_Contact(Staff_data);
			break;
		case 2:
			Modify_Password(Staff_data);
			break;
		case 3:
			Modify_RecoveryPassword(Staff_data);
			break;
		case 4:
			// Re-read the file to update any changes made by other processes
			addToAllStaff = fopen("AllStaffs.txt", "r");
			if (!addToAllStaff) {
				perror("\t\t\t\t\t\t   FAILED TO OPEN FILE!\n");
				return;
			}
			while (fscanf(addToAllStaff, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
				tempdata[count].staff_id,
				tempdata[count].details.name,
				tempdata[count].details.nric,
				tempdata[count].details.contact,
				tempdata[count].staff_job) != EOF) {
				count++;
			}
			fclose(addToAllStaff);

			// Update the specific staff member in memory
			for (int i = 0; i < count; i++) {
				if (strcmp(tempdata[i].staff_id, Staff_data->staff_id) == 0) {
					tempdata[i] = *Staff_data;  // Update the record
				}
			}

			// Rewrite updated data back to file
			addToAllStaff = fopen("AllStaffs.txt", "w");
			if (!addToAllStaff) {
				perror("\t\t\t\t\t\t   FAILED TO OPEN FILE!\n");
				return;
			}
			for (int i = 0; i < count; i++) {
				fprintf(addToAllStaff, "%s|%s|%s|%s|%s",
					tempdata[i].staff_id,
					tempdata[i].details.name,
					tempdata[i].details.nric,
					tempdata[i].details.contact,
					tempdata[i].staff_job);
			}
			fclose(addToAllStaff);

			file_Staff_Modify = fopen(staff_ModDetails, "w");
			if (file_Staff_Modify == NULL) {
				printf("\n\n");
				printf("\t\t\t\t    !!!ERROR OPENING THE FILE TO SAVE CHANGES!!!\n\n");
			}
			else {
				fprintf(file_Staff_Modify, "%s\n%s\n%s\n%s\n%c\n%s\n%s\n%s",
					Staff_data->staff_id,
					Staff_data->details.name,
					Staff_data->staff_password,
					Staff_data->staff_recovery,
					Staff_data->details.gender,
					Staff_data->details.nric,
					Staff_data->details.contact,
					Staff_data->staff_job);
				fclose(file_Staff_Modify);
			}
			system("cls");
			printf("\n\t\t\t\t\t\tCHANGES SAVED SUCCESSFULLY\n\n");
			return;
		}
	} while (staff_Choice != 5);
}

void currentDateTime() {
	time_t now;
	time(&now);
	struct tm* local = localtime(&now);

	printf("\t\t\tDate: %02d-%02d-%04d\t\t\t\t\t   Time: %02d:%02d:%02d\n",
		local->tm_mday, local->tm_mon + 1, local->tm_year + 1900
		, local->tm_hour, local->tm_min, local->tm_sec);
}

void exitMenu() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t       RETURNING TO LAST PAGE...");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
}

int Read_StaffFile(FILE** readfile, char* staffID, staff* Staff_data) {
	*readfile = fopen(staffID, "r");
	if (*readfile == NULL) {
		perror("Error opening the file");
		return 0;
	}
	while (fscanf(*readfile, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n%[^\n]\n%[^\n]\n%[^\n]",
		Staff_data->staff_id,
		Staff_data->details.name,
		Staff_data->staff_password,
		Staff_data->staff_recovery,
		&Staff_data->details.gender,
		Staff_data->details.nric,
		Staff_data->details.contact,
		Staff_data->staff_job
	) != EOF) {
	}
	fclose(*readfile);
	return 1;
}

int Write_StaffFile(FILE** writefile, char* staffID, staff* Staff_data) {
	*writefile = fopen(staffID, "w");

	if (*writefile == NULL) {
		return 0;
	}
	fprintf(*writefile, "%s\n%s\n%s\n%s\n%c\n%s\n%s\n%s",
		Staff_data->staff_id,
		Staff_data->details.name,
		Staff_data->staff_password,
		Staff_data->staff_recovery,
		Staff_data->details.gender,
		Staff_data->details.nric,
		Staff_data->details.contact,
		Staff_data->staff_job);
	fclose(*writefile);
	return 1;
}

int Write_ReportStaffFile(FILE** writefile, staff* Staff_data) {
	*writefile = fopen("AllStaffs.txt", "a");

	if (*writefile == NULL) {
		return 0;
	}
	fprintf(*writefile, "%s|%s|%s|%s|%s\n",
		Staff_data->staff_id,
		Staff_data->details.name,
		Staff_data->details.nric,
		Staff_data->details.contact,
		Staff_data->staff_job);
	fclose(*writefile);
	return 1;
}

void Modify_Contact(staff* Staff_data) {
	char formattedContact[CONTACT_NO];
	printf("\n\t\t\t\t            CONTACT NUMBER : ");
	do {
		scanf("%[^\n]", Staff_data->details.contact);
		rewind(stdin);
		if (!Validate_StaffContact(Staff_data->details.contact)) {
			printf("\n\t\t\t\t                  INVALID CONTACT NUMBER.\n\n");
			printf("\t\t\t\t                  FORMAT : 01234567890\n\n");
			printf("\t\t\t\t            CONTACT NUMBER : ");
		}
	} while (!Validate_StaffContact(Staff_data->details.contact));

	// Optionally format the contact number before saving
	snprintf(formattedContact, sizeof(formattedContact), "%s", Format_StaffContact(Staff_data->details.contact));
	strcpy(Staff_data->details.contact, formattedContact);
}

void Modify_Password(staff* Staff_data) {
	printf("\n\t\t\t\t       PASSWORD (MINIMUM 4 CHARACTERS WITH FORMAT A12a) : ");
	do {
		scanf("%[^\n]", Staff_data->staff_password);
		rewind(stdin);
		if (!Validate_StaffPass(Staff_data->staff_password)) {
			printf("\n\t\t\t\t                  INVALID PASSWORD FORMAT.\n\n");
			printf("\t\t\t\t                  FORMAT : A10a\n\n");
			printf("\t\t\t\t            PASSWORD : ");
		}
	} while (!Validate_StaffPass(Staff_data->staff_password));
}

void Modify_RecoveryPassword(staff* Staff_data) {
	printf("\n\t\t\t\t         RECOVERY PASSWORD : ");
	scanf("%[^\n]", Staff_data->staff_recovery);
	rewind(stdin);
}

