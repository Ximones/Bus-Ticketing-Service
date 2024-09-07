#ifndef member_header
#define member_header

#include "common.h"

//Constant for length of variables , +1 for \0 character
#define NAME 40+1
#define NRIC 15+1
#define CONTACT_NO 13+1
#define LOG_ID 15+1
#define PASSWORD 15+1
#define PASS_RECOVERY 15+1

//Constant for format exp: .txt , _log

#define FORMAT_REPORT 5 
#define FORMAT_TXT 5

//-----------------------
//Struct Definiton 
struct member_details {
	char name[NAME], gender, nric[NRIC], contact[CONTACT_NO];
};

typedef struct {
	struct member_details details;
	char member_id[LOG_ID], member_password[PASSWORD], member_recovery[PASS_RECOVERY], ticket_id[LOG_ID];
}Member_log;

void MemberMain();
void MemberMenu();
void Search_Member(Member_log* member_data);
void Modify_MemberRequest(Member_log* member_data);
void Modify_MemberVerification(Member_log* member_data);
void Modify_MemberMenu();
void Report_Member(Member_log* member_data);
void Delete_Member(Member_log* member_data);
void Display_Member(Member_log* member_data);
void Modify_DetailsMember(Member_log* member_data);
void BacktoMemberMenu();
void AddNew_Member();

//	Verification 
int Verification_MemberPass(Member_log* member_data);

int Verification_MemberRecovery(Member_log* member_data);

//	Validation
int Validate_MemberName(const char* member_Name);

int Validate_MemberPass(const char* member_Pass);

int Validate_MemberNric(const char* member_Nric);

int Validate_MemberContact(const char* member_Contact);

//	Formatting
char* Format_MemberNric(const char* member_Nric);

char* Format_MemberContact(const char* member_Contact);

//	Choice 
char Member_AlphaChoice();
int Member_NumChoice();

int Read_MemberFile(FILE** readfile, char* memberID, Member_log* member_data);
int Write_MemberFile(FILE** writefile, char* memberID, Member_log* member_data);

#endif // !member_header
