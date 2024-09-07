#include "member.h"

void MemberMain() {				// Main menu of Member
	Member_log memberData;
	char alphachoice = ' ', mainchoice = ' ';
	int numchoice;

	while (1) {
		MemberMenu();
		numchoice = Member_NumChoice();
		if (numchoice == 1) {
			Search_Member(&memberData);				// Log in sessions
			Modify_MemberRequest(&memberData);		// If Account exsist
			// Ask user input choice
			alphachoice = Member_AlphaChoice();
			if (alphachoice == 'Y') {
				Modify_MemberVerification(&memberData);
				do {
					Modify_MemberMenu();
					numchoice = Member_NumChoice();
					switch (numchoice) {
					case 1:
						Report_Member(&memberData);
						break;
					case 2:
						Delete_Member(&memberData);
						exit(1);
						break;
					case 3:
						Display_Member(&memberData);
						Modify_DetailsMember(&memberData);
						break;
					}
					BacktoMemberMenu();
					alphachoice = Member_AlphaChoice();
				} while (alphachoice == 'Y');
			}
		}
		else if (numchoice == 2) {
			AddNew_Member();
		}
		else {
			break;
		}
	}
	system("pause");
}

void MemberMenu() {
	system("cls");
	printf("\n             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :                                  WELCOME TO MEMBER MENU.                                    :\n");
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n\n");
	printf("\n\t\t\t\t   +                                                    +\n");
	printf("\t\t\t\t                     [1] LOG IN                         \n\n");
	printf("\t\t\t\t                     [2] SIGN UP                         \n\n");
	printf("\t\t\t\t                     [3] BACK TO MAIN MENU                         \n\n");
	printf("\t\t\t\t   +                                                    +\n");
	printf("\t\t\t\t\t       ENTER YOUR DESIRED CHOICE : ");
}

void Search_Member(Member_log* member_data) {	//Function of member log in 
	char temp_memberID[LOG_ID + FORMAT_TXT];
	FILE* file_memberRead = NULL;
	system("cls");
	printf("\n\t\t\t\t                         LOG IN                         \n\n");
	printf("             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :                                    Enter your member ID                                     :\n");
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n\n");
	printf("                                                          :");
	do {
		scanf("%[^\n]", temp_memberID);
		strcat(temp_memberID, ".txt");
		rewind(stdin);
		if (Read_MemberFile(&file_memberRead, temp_memberID, member_data) == 0) {
			system("cls");
			printf("\n\n\t\t\t\t\t\tMember ID not found!\n\n");
			printf("\t\t\t\t\t    Please try again : ");
		}
	} while (file_memberRead == NULL);
}

void Modify_MemberRequest(Member_log* member_data) {

	system("cls");
	printf("\n\t\t\t\t                         Results                         \n\n");
	printf("             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :             Member ID : %-10s\t\t Name : %-20s\t           :\n", member_data->member_id, member_data->details.name);
	printf("             :                                                                                             :\n");
	printf("             :             IC Number : %-15s\t\t         Gender : %-2c\t                   :\n", member_data->details.nric, member_data->details.gender);
	printf("             :                                                                                             :\n");
	printf("             :             \t\t\t  Phone Number : %-15s\t\t\t   :\n", member_data->details.contact);
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n\n");
	printf("\t\t\t\t   +                                                    +\n");
	printf("\t\t\t\t                  [Y] Modify Profile\n\n");
	printf("\t\t\t\t                  [N] Back to Member Menu\n");
	printf("\t\t\t\t   +                                                    +\n\n");
	printf("\t\t\t\t             Do you want to make changes on your profile? >  ");

}

void Modify_MemberVerification(Member_log* member_data) {
	int valid_Pass = 1, valid_Recovery = 1, valid_Choice = 1;

	do {
		printf("             +.............................................................................................+\n");
		printf("             :                                                                                             :\n");
		printf("             :                                 Please enter your password.                                 :\n");
		printf("             :                                                                                             :\n");
		printf("             +.............................................................................................+\n\n");
		printf("                                                          :");
		valid_Pass = Verification_MemberPass(member_data);
		if (!valid_Pass) {
			printf("\n\n\n");
			printf("                                             Do you want to recover your password?                                  \n");
			printf("\n\n");
			printf("\t\t\t\t                  [Y] YES\n");
			printf("\t\t\t\t                  [N] NO \n\n");
			if (Member_AlphaChoice() == 'Y') {
				printf("             +.............................................................................................+\n");
				printf("             :                                                                                             :\n");
				printf("             :                                 Please enter your recovery password.                        :\n");
				printf("             :                                                                                             :\n");
				printf("             +.............................................................................................+\n\n");
				printf("                                                          :");
				do {
					valid_Recovery = Verification_MemberRecovery(member_data);
				} while (!valid_Recovery);
				printf("\n\n\n \t\t\t\t\t\t Your Password : %s \n", member_data->member_password);
			}
			else {
				continue;
			}
		}
	} while (valid_Pass != 1);
}

void Display_Member(Member_log* member_data) {
	printf("\n\t\t\t\t\t\t  Current Details :\n");
	printf("             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :             Member ID : %-10s\t\tName : %-20s\t           ;\n", member_data->member_id, member_data->details.name);
	printf("             :                                                                                             :\n");
	printf("             :             Password : %-10s\t\t Recovery Password : %-20s  :\n", member_data->member_password, member_data->member_recovery);
	printf("             :                                                                                             :\n");
	printf("             :             IC : %-15s\t\t         Gender : %-2c\t                           :\n", member_data->details.nric, member_data->details.gender);
	printf("             :                                                                                             :\n");
	printf("             :             \t\t\t  Phone Number : %-15s\t\t\t   :\n", member_data->details.contact);
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n");
}

void Modify_MemberMenu() {
	system("cls");
	printf("\n\n");
	printf("             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :                                  Welcome to option menu.                                    :\n");
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n\n");
	printf("\t\t\t\t                  [1] View Report\n\n");
	printf("\t\t\t\t                  [2] Remove account\n\n");
	printf("\t\t\t\t                  [3] Make changes on your account\n\n");
	printf("                                                          :");
}

void Report_Member(Member_log* member_data) {
	char member_reportID[LOG_ID + FORMAT_REPORT + FORMAT_TXT];
	FILE* file_member_reportRead;

	snprintf(member_reportID, sizeof(member_reportID), "%s_log.txt", member_data->member_id);
	file_member_reportRead = fopen(member_reportID, "r+");
	if (member_reportID == NULL) {
		printf("\n\t\t\t\t\t\tReport not found.\n\n\t\t\t\t\t\tPlease try again > ");
	}
	else {
		char member_Reports[100];
		system("cls");
		while (fgets(member_Reports, sizeof(member_Reports), file_member_reportRead)) {
			printf("\t%s", member_Reports);
		}
		printf("\n\n");
		fclose(file_member_reportRead);
	}
}

void Delete_Member(Member_log* member_data) {
	char member_deleteReport[LOG_ID + FORMAT_REPORT + FORMAT_TXT] = " ";
	char member_deleteAcc[LOG_ID + FORMAT_TXT] = " ";
	int valid = 1;

	snprintf(member_deleteReport, sizeof(member_deleteReport), "%s_log.txt", member_data->member_id);
	snprintf(member_deleteAcc, sizeof(member_deleteAcc), "%s.txt", member_data->member_id);

	printf("\nEnter again password to verify before removing account > ");
	do {
		valid = Verification_MemberPass(member_data);
	} while (valid != 1);

	if (remove(member_deleteReport) == 0 && remove(member_deleteAcc) == 0) {
		printf("\nAccount remove Successfully\n\n");
	}
	else {
		printf("\n%s\n\n", member_deleteReport);
		perror("Error: unable to delete the file\n\n");
		printf("\n%s\n\n", member_deleteAcc);
		perror("Error: unable to delete the file\n\n");
	}
}

void Modify_DetailsMember(Member_log* member_data) {
	int member_choice, valid;
	FILE* file_member_modify;
	char member_modifyAcc[LOG_ID + FORMAT_TXT];

	snprintf(member_modifyAcc, sizeof(member_modifyAcc), "%s.txt", member_data->member_id);
	do {
		system("cls");
		Display_Member(member_data);
		printf("\n[1] Gender \n[2] Phone \n[3] Password \n[4] Recovery \n[5] Quit\n");
		printf("Which do you want to make changes ? > ");
		do {
			scanf("%d", &member_choice);
			rewind(stdin);
			if (member_choice != 1 && member_choice != 2 && member_choice != 3 && member_choice != 4 && member_choice != 5) {
				printf("Invalid Choice.Please try again > ");
			}
		} while (member_choice != 1 && member_choice != 2 && member_choice != 3 && member_choice != 4 && member_choice != 5);
		if (member_choice == 1) {
			printf("Enter Gender : ");
			do {
				scanf("%c", &member_data->details.gender);
				member_data->details.gender = toupper(member_data->details.gender);
				rewind(stdin);
				if (member_data->details.gender != 'M' && member_data->details.gender != 'F') {
					printf("\nInvalid Gender,Please enter M/F > ");
					rewind(stdin);
				}
			} while (member_data->details.gender != 'M' && member_data->details.gender != 'F'); //Format check Gender
		}
		if (member_choice == 2) {
			printf("Enter contact : ");
			do {
				scanf("%[^\n]", member_data->details.contact);
				rewind(stdin);
				valid = Validate_MemberContact(member_data->details.contact);
				if (!valid) {
					printf("\nInvalid Contact,should only have numbers.\n\tPlease try again > ");
					rewind(stdin);
				}
			} while (!valid);

			char* formattedContact = Format_MemberContact(member_data->details.contact);

			if (formattedContact != NULL) {
				strcpy(member_data->details.contact, formattedContact);
				free(formattedContact); // Again, free the dynamically allocated memory
			}
		}
		if (member_choice == 3) {
			printf("Password (Minimum 4 characters with format exp A12a) : ");
			do {
				scanf("%[^\n]", member_data->member_password);
				rewind(stdin);
				valid = Validate_MemberPass(member_data->member_password);
				if (valid) {
					printf("\nValid Password\n");
				}
				else {
					printf("\nInvalid Password.\n\tPlease try again > ");
					rewind(stdin);
				}
			} while (!valid); //Format check Password
			strcpy(member_data->member_password, member_data->member_password);
		}
		if (member_choice == 4) {
			printf("Enter recovery password : ");
			scanf("%[^\n]", member_data->member_recovery);
			rewind(stdin);
		}
		if (member_choice == 5) {

			if (Write_MemberFile(&file_member_modify, member_modifyAcc, member_data) == 1) {
				system("cls");
				printf("\n\t <<< Successfully change >>>\n");
			}
			else {
				printf("\n\t <<< Failed to modify >>> \n");
			}
		}
	} while (member_choice != 5);
}

void AddNew_Member() {

	Member_log temp_memberNew;
	int valid;
	char temp_id[LOG_ID + FORMAT_TXT];
	FILE* newMember_file = NULL;
	char choice = ' ';

	system("cls");
	printf("\n\n             +.............................................................................................+\n");
	printf("             :                                                                                             :\n");
	printf("             :                                Complete the following details                               :\n");
	printf("             :                                                                                             :\n");
	printf("             +.............................................................................................+\n\n");
	printf("\t\t\t\t                 Member ID : ");
	do {
		scanf("%[^\n]", temp_id);
		rewind(stdin);
		for (int i = 0; temp_id[i]; i++) {
			temp_id[i] = toupper(temp_id[i]);
		}
		strcpy(temp_memberNew.member_id, temp_id);
		strcat(temp_id, ".txt");
		if (Read_MemberFile(&newMember_file, temp_id, &temp_memberNew) != 0) {
			printf("\n\t\t\t\t\t\tMember ID is in use.\n\n");
			printf("\t\t\t\t\tPlease try another member ID : ");
		}
		else {
			do {
				printf("\n\t\t\t\t\t\t  NRIC NAME : ");
				do {
					scanf("%[^\n]", temp_memberNew.details.name);
					rewind(stdin);
					for (int i = 0; temp_memberNew.details.name[i]; i++) {
						temp_memberNew.details.name[i] = toupper(temp_memberNew.details.name[i]);
					}
					valid = Validate_MemberName(temp_memberNew.details.name);
					if (!valid) {
						printf("\n\t\t\t\t\tInvalid name as name should only have characters.\n\n");
						printf("\t\t\t\t\t  Please try again : ");
						rewind(stdin);
					}
				} while (!valid); //Format check Name
				printf("\t\t\t\t\t(Minimum 4 characters with format A12a)");
				printf("\n\t\t\t\t\t  Password  : ");
				do {
					scanf("%[^\n]", temp_memberNew.member_password);
					rewind(stdin);
					valid = Validate_MemberPass(temp_memberNew.member_password);
					if (valid) {
						printf("\n\t\t\t\t\t\t    Valid Password\n");
					}
					else {
						printf("\n\t\t\t\t\t\t  Invalid Password.\n");
						printf("\t\t\t\t\tPlease try again : ");
						rewind(stdin);
					}
				} while (!valid); //Format check Password
				printf("\n\t\t\t\t\tEnter recovery password : ");
				scanf("%[^\n]", temp_memberNew.member_recovery);
				rewind(stdin);

				printf("\n\t\t\t\t\t\tGender (M/F) : ");
				do {
					scanf("%c", &temp_memberNew.details.gender);
					temp_memberNew.details.gender = toupper(temp_memberNew.details.gender);
					rewind(stdin);
					if (temp_memberNew.details.gender != 'M' && temp_memberNew.details.gender != 'F') {
						printf("\n\t\t\t\t                  Invalid Gender Selection\n\n");
						printf("\t\t\t\t              Gender (M/F): ");
						rewind(stdin);
					}
				} while (temp_memberNew.details.gender != 'M' && temp_memberNew.details.gender != 'F'); //Format check Gender

				//Nric
				printf("\n\t\t\t\t           Enter IC Number : ");
				do {
					scanf("%[^\n]", temp_memberNew.details.nric);
					rewind(stdin);
					valid = Validate_MemberNric(temp_memberNew.details.nric);
					if (!valid) {
						printf("\n\t\t\t\t                  Invalid NRIC.\n\n");
						printf("\t\t\t\t                  Correct Format : 981234121111\n\n");
						printf("\t\t\t\t               Please try again : ");
						rewind(stdin);
					}
				} while (!valid); //Format check Nric

				char* formattedNric = Format_MemberNric(temp_memberNew.details.nric);

				if (formattedNric != NULL) {
					strcpy(temp_memberNew.details.nric, formattedNric);
					free(formattedNric); // Free the dynamically allocated memory
				}

				//Contact
				printf("\n\t\t\t\t           Enter Contact : ");
				do {
					scanf("%[^\n]", temp_memberNew.details.contact);
					rewind(stdin);
					valid = Validate_MemberContact(temp_memberNew.details.contact);
					if (!valid) {
						printf("\nInvalid Contact,Correct Format : 01118566866.\n\tPlease try again > ");
						printf("\n\t\t\t\t                  Invalid Contact.\n\n");
						printf("\t\t\t\t              Correct Format : 01118566866\n\n");
						printf("\t\t\t\t               Please try again : ");
						rewind(stdin);
					}
				} while (!valid);

				char* formattedContact = Format_MemberContact(temp_memberNew.details.contact);

				if (formattedContact != NULL) {
					strcpy(temp_memberNew.details.contact, formattedContact);
					free(formattedContact); // Again, free the dynamically allocated memory
				}
				system("cls");

				Display_Member(&temp_memberNew);
				printf("\t\t\t\t\t Is your details correct? (Y/N) : \n");
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
			} while (choice == 'N');
		}

	} while (newMember_file != NULL);
}

void BacktoMemberMenu() {
	printf("\t\t\t\t                  Back to :\n\n");
	printf("\t\t\t\t                  [Y] Yes - Modify Menu\n\n");
	printf("\t\t\t\t                  [N] No  - Main Menu\n\n");
	printf("\t\t\t\t              Do you still want to make changes?\n\n");
	printf("\t\t\t\t\t\t\t   >");
}

//	Verification 

int Verification_MemberPass(Member_log* member_data) {
	char verify_pass[PASSWORD] = " ";

	scanf("%[^\n]", verify_pass); //4456
	rewind(stdin);
	if (strcmp(verify_pass, member_data->member_password) == 0) {
		return 1;
	}
	else {
		system("cls");
		printf("\n\n");
		printf("\t\t\t\t\t\t<<< Wrong Password >>>\n");
		printf("\n");
		return 0;
	}
}

int Verification_MemberRecovery(Member_log* member_data) {
	Member_log memberData = *member_data;
	char verify_recovery[PASS_RECOVERY] = " ";

	scanf("%[^\n]", verify_recovery); //numbers
	rewind(stdin);
	if (strcmp(verify_recovery, memberData.member_recovery) == 0) {
		return 1;
	}
	else {
		printf("Invalid Recovery. Please try again > ");
		printf("\n\n");
		printf("\t\t\t\t    Invalid recovery password. Please try again.\n\n");
		printf("\t\t\t\t\t\t\t  >");
		return 0;
	}
}

//	Validation

int Validate_MemberName(const char* member_Name) {
	int alpha = 0, digit = 0;
	size_t name_length = strlen(member_Name);

	for (int i = 0; i < name_length; i++) {
		if (isalpha(member_Name[i])) {
			alpha = 1;
		}
		if (isdigit(member_Name[i])) {
			digit = 1;
		}
	}
	if (alpha && digit) {
		return 0;
	}
	else {
		return 1;
	}
}

int Validate_MemberPass(const char* member_Pass) {
	int digit = 0, alpha = 0, upper = 0, lower = 0;
	size_t pass_length = strlen(member_Pass);

	if (pass_length < 4) {
		return 0;
	}
	for (int i = 0; i < pass_length; i++) {
		if (isdigit(member_Pass[i])) {
			digit = 1;
		}
		if (isalpha(member_Pass[i])) {
			alpha = 1;
		}
		if (isupper(member_Pass[i])) {
			upper = 1;
		}
		if (islower(member_Pass[i])) {
			lower = 1;
		}
	}
	if (digit && alpha && upper && lower) {
		return 1;
	}
	else {
		return 0;
	}
}

int Validate_MemberNric(const char* member_Nric) {
	size_t nric_length = strlen(member_Nric);

	if (nric_length != 12) {
		return 0;
	}
	for (int i = 0; i < nric_length; i++) {
		if (!isdigit(member_Nric[i])) {
			return 0;
		}
	}
	return 1;
}

int Validate_MemberContact(const char* member_Contact) {
	size_t contact_length = strlen(member_Contact);

	if (member_Contact[0] != '0') {
		return 0;
	}
	if (contact_length > 12 || contact_length < 10) { // Corrected logical operator to '||' (OR)
		return 0;
	}
	for (int i = 0; i < contact_length; i++) {
		if (!isdigit(member_Contact[i])) {
			return 0;
		}
	}
	return 1;
}

//	Formatting

char* Format_MemberNric(const char* member_Nric) {
	char* format_nric = malloc(NRIC);

	if (format_nric != NULL) {
		snprintf(format_nric, NRIC, "%6.6s-%2.2s-%4.4s", member_Nric, member_Nric + 6, member_Nric + 8);
	}
	return format_nric;
}

char* Format_MemberContact(const char* member_Contact) {
	char* format_contact = malloc(CONTACT_NO);
	if (format_contact != NULL) {
		snprintf(format_contact, CONTACT_NO, "%3.3s-%-8.8s", member_Contact, member_Contact + 3);
	}
	return format_contact;
}

//	Choice 
char Member_AlphaChoice() {
	char member_choice = ' ';
	do {
		scanf("%c", &member_choice);
		rewind(stdin);
		member_choice = toupper(member_choice);
		if (member_choice != 'Y' && member_choice != 'N') {
			printf("\n\t\t\t\t\t   Invalid. Please try again (Y/N).\n\n");
			printf("\t\t\t\t\t\t\t   >");
		}
		// if invalid is true printf else valid 
	} while (member_choice != 'Y' && member_choice != 'N');
	return member_choice;
}

int Member_NumChoice() {
	int member_choice;
	do {
		scanf("%d", &member_choice);
		rewind(stdin);
		if (member_choice != 1 && member_choice != 2 && member_choice != 3) {
			printf("\n\t\t\t\t\t   Invalid. Please try again (1/2/3).\n\n");
			printf("\t\t\t\t\t\t\t   >");
		}
	} while (member_choice != 1 && member_choice != 2 && member_choice != 3);
	return member_choice;
}

int Read_MemberFile(FILE** readfile, char* memberID, Member_log* member_data) {
	*readfile = fopen(memberID, "r");
	if (*readfile == NULL) {
		return 0;
	}
	while (fscanf(*readfile, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n%[^\n]\n%[^\n]\n",
		member_data->member_id,
		member_data->details.name,
		member_data->member_password,
		member_data->member_recovery,
		&member_data->details.gender,
		member_data->details.nric,
		member_data->details.contact) != EOF) {
	}
	fclose(*readfile);
	return 1;
}

int Write_MemberFile(FILE** writefile, char* memberID, Member_log* member_data) {
	*writefile = fopen(memberID, "w");

	if (*writefile == NULL) {
		return 0;
	}
	fprintf(*writefile, "%s\n%s\n%s\n%s\n%c\n%s\n%s\n",
		member_data->member_id,
		member_data->details.name,
		member_data->member_password,
		member_data->member_recovery,
		member_data->details.gender,
		member_data->details.nric,
		member_data->details.contact);
	fclose(*writefile);
	return 1;
}

