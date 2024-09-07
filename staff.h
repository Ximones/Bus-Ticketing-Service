#ifndef staff_header
#define staff_header
#include "common.h"

#define NAME 50+1
#define NRIC 15+1
#define CONTACT_NO 13+1
#define LOG_ID 15+1
#define PASSWORD 15+1
#define PASS_RECOVERY 15+1
#define JOB_DETAILS 25+1 //2 job titles, Manager > Admin
#define FORMAT_REPORT 5
#define FORMAT_TXT 5
#define MAX_STAFF 20 //Maximum number of staff possible

typedef struct staff_details {
	char name[NAME], gender, nric[NRIC], contact[CONTACT_NO];
}staff_details;

typedef struct {
	staff_details details;
	char staff_id[LOG_ID], staff_password[PASSWORD],
		staff_recovery[PASS_RECOVERY], staff_job[JOB_DETAILS];
}staff;

void StaffMain();
void Staff_Menu();
void Search_Staff(staff* Staff_data);
void Modify_StaffRequest(staff* Staff_data);
void Modify_StaffVerification(staff* Staff_data);
void Modify_ManagerMenu();
void Modify_AdminMenu();
int Verification_StaffPass(staff* Staff_data);
int Verification_StaffRecovery(staff* Staff_data);
char Staff_AlphabetChoice();
int Staff_NumChoice();
void Report_Staff();
void Remove_Staff(staff* Staff_data);
void Add_NewStaff();
int Validate_StaffName(const char* staff_Name);
int Validate_StaffPass(const char* staff_Pass);
int Validate_StaffNric(const char* staff_Nric);
int Validate_StaffContact(const char* staff_Contact);
char* Format_StaffNric(const char* staff_Nric);
char* Format_StaffContact(const char* staff_Contact);
void Display_Staff(staff* Staff_data);
void BackToManagerMenu();
void Modify_StaffDetails(staff* Staff_data);
void currentDateTime();
void exitMenu();
void Modify_Gender(staff* Staff_data);
void Modify_Contact(staff* Staff_data);
void Modify_Password(staff* Staff_data);
void Modify_RecoveryPassword(staff* Staff_data);

#endif