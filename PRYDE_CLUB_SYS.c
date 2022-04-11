/*
Program Name : PRYDE_CLUB_SYS.c
written by : Leong Kuan Fei, Chang Ching We, Chong Ye Seng, Eric Chee Wei Jiat, Desmond Lim Chi Ven
Date : 11/2/2022
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<Windows.h>
#include<stdbool.h>
#pragma warning (disable : 4996)

// - FUNCTION DECLARATION -
// - CCW - Function declaration
// - CCW - Logo functions declaration
void mainLogoWord();
void mainLogoLine();

// - CCW - System header & footer declaration
void systemHeader();
void systemFooter();

// - CCW - Report header & footer declaration
void reportHeader();
void reportFooter();

// - CCW - Validation declaration
bool verifyAdminPassword(char* loginPassword);
bool verifyStaffPassword(char* loginPassword);
bool verifyName(char* name);
bool verifyIC(char* iC);

// - CCW - Login functions declaration
int loginMenu();
void mainStaffLogin();
void mainAdminLogin();
void exitMenu();

// - CCW - Staff menu declaration
int mainStaffMenu();
int staffFunction();

// - CCW - Staff function declaration
//staffAbbre() already declare in report
void resetPassword();
void searchStaff();
int facilityMgmtMenu();
void facilityMgmtFunction();

// - CCW - Admin menu declaration
int mainAdminMenu();
int adminFunction();

// - CCW - Admin function declaration
void addStaff();
int getStaffID();
void modifyStaff();
void displayStaff();
void removeStaff();
int displayStaffReport();

// - CCW - Staff report declaration
int staffReportMenu();
void staffAbbre();
void staffIndividualProfile();
void staffListPersonal();
void staffListAddress();
void staffListEmployment();
void staffListEmergency();

//================================================================================================

// - CYS - Fuction declaration
// - CYS - Club facility function declaration
void facilityInfo();
void addFacilty();
void searchFacility();
void modifyFacility();
void displayFacility();
void removeFacility();
void displayFacilityReport();


//================================================================================================

// - ERIC - Function declaration
// - ERIC - Code Test
void displayBooking();

// - ERIC - Member Menu Declaration
void memberInformationMenu();
int addUserInformation();
int searchUserInformation();
int modifyUserInformation();
int displayUserInformation();

// - ERIC - Member delete declaration
int deleteVipInformation();
int deleteMemberInformation();

// - ERIC - Member Information Report
int memberInformationReport();

// - ERIC - Member Function Validation
int checkingName(char alphabet[40]);
int checkingGender(char alphabet[3]);
int checkingVipID(char vipID[6], int limit);
int checkingMemberID(char memberID[6], int limit);
int checkingBirthDate(char digit[9], int limit);
int checkingIC(char digit[13], int limit);
int checkingContactNum(char digit[11], int limit);
int checkUserAvailable(char alphabet[40]);

//================================================================================================

// - LKF - Function declaration
// - LKF - Club facility booking menu function declaration
void bookingMenu();
void facilityBooking();

// - LKF - Club facility booking function declaration
void displayBooking();
void addBooking();
void removeBooking();
void displayBookingReport();

// - LKF - Club booking id auto generate function declaration
void generateBookId(int*);

// - LKF - Check date booking function declaration
void checkBookDate(int, int, int*);

// - LKF - Club member booking function declaration
void memberType(char*);
int  memberMenu();

// - LKF - Search booking function declaration
void searchBookingMenu();
void searchBooking();

// - LKF - Modify booking menu function declaration
void modifyBookingMenu();
void modifyBooking();

// - LKF - Display horizontal line function declaration
void horizontalLine();

//================================================================================================

// - DESMOND - Function declaration
// - DESMOND - Read LKF binary file function declaration
void readBinary();

// - DESMOND - Faclitiy usage management menu function declaration
int facilityUsage();

// - DESMOND - Add facility usage function declaration
void addUsage();

// - DESMOND - Search facility usage function declaration
void searchFacilityUsage();

// - DESMOND - Modify facility usage function declaration
void modifyFacilityUsage();

// - DESMOND - Display facility usage function declaration
void displayFacilityUsage();

// - DESMOND - Remove facility usage function declaration
void removeFacilityUsage();

// - DESMOND - Display Report
void displayReport();

//================================================================================================

// - STRUCTURE -
// - CCW - Struct
// - CCW - Struct for Date
typedef struct {
	int day, month, year;
} Date;

// - CCW - Struct for Staff Profile information
typedef struct {
	// Employee information
	char staffID[6], staffName[30];
	Date birthday;
	char gender;
	char maritalStatus, iC[15], staffContact[13], address[80];

	// Job information
	Date joinedDate;
	char department[6], position[6], jobLevel[3], officeEmail[20];
	double salary;

	// Emergency contact information
	char emergencyPerson[30], emergencyPhone[13], relationship[20];

	// Staff login password - 6 digit numeric password for fast access
	char password[7];
} StaffProfile;

// - CCW - Struct for Admin Profile information
typedef struct {
	char adminID[6];
	char adminPassword[15];
} AdminProfile;

//================================================================================================

// - CYS - Struct
// - CYS - Struct for facility
typedef struct {
	char facilityID[6];
	char faciltyType[7];
	char facilityDescription[30];
	char venue;
	char venueDescription[10];
	int maxUser;
	int startTime;
	int endTime;
}Facility;

//================================================================================================

// - ERIC - Struct
// - ERIC - Structure for membership
typedef struct {
	char memberID[30], memberName[40], gender[3], memberIC[15], memberContactNum[15], memberBirthDate[9];
}Membership;

//================================================================================================

// - LKF - Struct
// - LKF - Structure for time
typedef struct {

	int startHours;
	int startMin;
	int endHours;
	int endMin;

}Time;

// - LKF - Struct for booking
typedef struct {

	char bookingId[6];
	Facility fac;
	StaffProfile emp;
	Date date;
	Time time;
	char remarks[100];
	Membership member;
	int	numOfPax;

}Booking;

//================================================================================================

// - DESMOND - Struct
// - DESMOND - Structure for facility Usage
typedef struct {

	int day;
	int month;
	int year;
	Time time;
	char memberId[6];
	char facilityId[5];
	char staffId[6];
	char choice[5];
	int durationHour;
	int durationMin;

}Usage;

//================================================================================================

// ************
// MAIN PROGRAM
void main() {
	int choice;

	// display main menu logo
	mainLogoLine();
	mainLogoWord();
	mainLogoLine();

	do {
		//calling Login Menu & Functions
		choice = loginMenu();
		system("cls");
		switch (choice) {
		case 1: mainStaffLogin(); break;
		case 2: mainAdminLogin(); break;
		case 3: exitMenu(); break;
		default:
			mainLogoLine();
			mainLogoWord();
			mainLogoLine();
			printf("%s\n", "Error message:");
			printf("%s\n", "Oops\! you have have entered invalid character.");
			printf("%s\n\n", "Please proceed to enter correct character.");
		}
	} while (choice != 3);

	return 0;
}
// ***********

//================================================================================================

// - CCW - Program
// - CCW - Main Logo
void mainLogoLine() {

	int row, col;

	// diaplay above sub-line
	for (row = 1; row <= 1; row++) {
		printf(" ");
		for (col = 1; col <= 137; col++) {
			printf("-");
		}
		printf("\n");
	}

	// diaplay line
	for (row = 1; row <= 5; row++) {
		printf("|");

		for (col = 1; col <= 68; col++) {
			printf("~");
			printf(".");
		}
		printf("~");
		printf("|");
		printf("\n");
	}

	// diaplay below sub-line
	for (row = 1; row <= 1; row++) {
		printf(" ");
		for (col = 1; col <= 137; col++) {
			printf("-");
		}
		printf("\n");
	}
	printf("\n");
}

void mainLogoWord() {

	//5 characters empty spaces, then display PRYDE
	printf("                       /#######  /#######  /##     /## /#######  /########\n");
	printf("                      | ##__  ##| ##__  ##|  ##   /##/| ##__  ##| ##_____/\n");
	printf("                      | ##  \\ ##| ##  \\ ## \\  ## /##/ | ##  \\ ##| ##\n");
	printf("                      | #######/| #######/  \\  ####/  | ##  | ##| #####\n");
	printf("                      | ##____/ | ##__  ##   \\  ##/   | ##  | ##| ##__/\n");
	printf("                      | ##      | ##  \\ ##    | ##    | ##  | ##| ##\n");
	printf("                      | ##      | ##  | ##    | ##    | #######/| ########\n");
	printf("                      |__/      |__/  |__/    |__/    |_______/ |________/\n\n\n");

	//65 characters empty spaces, then display CLUB
	printf("                                                                         /######  /##       /##   /## /#######\n");
	printf("                                                                        /##__  ##| ##      | ##  | ##| ##__  ##\n");
	printf("                                                                       | ##  \\__/| ##      | ##  | ##| ##  \\ ##\n");
	printf("                                                                       | ##      | ##      | ##  | ##| #######\n");
	printf("                                                                       | ##      | ##      | ##  | ##| ##__  ##\n");
	printf("                                                                       | ##    ##| ##      | ##  | ##| ##  \\ ##\n");
	printf("                                                                       |  ######/| ########|  ######/| #######/\n");
	printf("                                                                        \\______/ |________/ \\______/ |_______/\n\n\n");

	//display system name
	printf("%82s\n\n", "<<-- Facility Management System -->>");

}

// - CCW - System Header & Footer
void systemHeader() {
	// structure for date and time
	SYSTEMTIME t;
	// get date & time from OS
	GetLocalTime(&t);

	int row, col;

	// display system header logo & address
	printf("%90s\n", " ___ _____   _____  ___    ___ _   _   _ ___ ");
	printf("%90s\n", "| _ \\ _ \\ \\ / /   \\| __|  / __| | | | | | _ )");
	printf("%90s\n", "|  _/   /\\ V /| |) | _|  | (__| |_| |_| | _ \\");
	printf("%90s\n", "|_| |_|_\\ |_| |___/|___|  \\___|____\\___/|___/");
	printf("%82s\n", "~.Facility Management System.~");
	printf("%125s %.2d-%.2d-%.2d\n", "Date: ", t.wDay, t.wMonth, t.wYear);
	printf("%125s %.2d:%.2d\n", "Time: ", t.wHour, t.wMinute);

	// diaplay separated line
	for (row = 1; row <= 2; row++) {

		for (col = 1; col <= 137; col++) {
			printf("_");
		}
		printf("\n");
	}
	printf("\n");
}

void systemFooter() {

	int row, col;

	// diaplay separated line
	for (row = 1; row <= 2; row++) {

		for (col = 1; col <= 137; col++) {
			printf("_");
		}
		printf("\n");
	}
	printf("%88s\n", "Copyright (C)| 2022 | PRYDE CLUB SDN.BHD.");
	printf("\n");
}

// - CCW - Report Header & Footer
void reportHeader() {

	int row, col;

	// display report header logo & address
	printf("%90s\n", " ___ _____   _____  ___    ___ _   _   _ ___ ");
	printf("%90s\n", "| _ \\ _ \\ \\ / /   \\| __|  / __| | | | | | _ )");
	printf("%90s\n", "|  _/   /\\ V /| |) | _|  | (__| |_| |_| | _ \\");
	printf("%90s\n", "|_| |_|_\\ |_| |___/|___|  \\___|____\\___/|___/");
	printf("%82s\n", "~.Facility Management System.~");
	printf("\n%78s\n", "PRYDE CLUD SDN. BHD.");
	printf("%88s\n", "No. 100, Jalan Angkasa 1, Galaxy Height,");
	printf("%84s\n", "53300 Setapak K.L.W.P., Malaysia");
	printf("%92s\n", "Registration No.: 202201008888 SST.no: 100100/2022");
	printf("%77s\n", "www.prydeclub.com.my");
	printf("%135s\n", "Tel: +603-311 3111");
	printf("%135s\n", "Fax: +603-311 3110");

	// diaplay report line
	for (row = 1; row <= 2; row++) {

		for (col = 1; col <= 137; col++) {
			printf("_");
		}
		printf("\n");
	}
	printf("\n");
}

void reportFooter() {

	int row, col;

	// diaplay report line
	for (row = 1; row <= 2; row++) {

		for (col = 1; col <= 137; col++) {
			printf("_");
		}
		printf("\n");
	}
	printf("%74s\n", "End of Report");
	printf("\n");
}

// - CCW - Validation
bool verifyStaffPassword(char* loginPassword)
{
	// Verifies that the password confirms to the following requirements:
	//
	// must be 6 characters long
	// consist only digit
	// 
	// returns true if password confirms to these requirements and false otherwise

	// check if the length is insufficient or exceed range
	int length = strlen(loginPassword);

	bool notDigit = false;

	// check for each of the required character classes
	for (int i = 0; i < length; i++)
	{
		if (!isdigit(loginPassword[i])) notDigit = true;
	}

	// return false if any required character class is not present
	if (length != 6 || notDigit) {
		printf("\n%s\n", "Error message :");
		printf("%s\n", "Invalid password. Please ensure password must contained 6 numeric digits.");
		return false;
	}
	return true;
}

bool verifyAdminPassword(char* loginPassword)
{
	// Verifies that the password confirms to the following requirements:
	//
	// at least 8 characters long
	// at least 1 uppercase letter
	// at least 1 lowercase letter
	// at least 1 digit
	// at least 1 symbol
	//
	// returns true if password confirms to these requirements and false otherwise

	// check if the length is insufficient or exceed range
	int length = strlen(loginPassword);

	bool hasDigit = false;
	bool hasUppercase = false;
	bool hasLowercase = false;
	bool hasSymbol = false;

	// check for each of the required character classes
	for (int i = 0; i < length; i++)
	{
		if (isdigit(loginPassword[i])) hasDigit = true;
		if (isupper(loginPassword[i])) hasUppercase = true;
		if (islower(loginPassword[i])) hasLowercase = true;
		if (ispunct(loginPassword[i])) hasSymbol = true;
	}

	// return false if any required character class is not present
	if (length < 8 || length > 14 || !hasDigit || !hasUppercase || !hasLowercase || !hasSymbol) {
		printf("\n%s\n", "Error message :");
		printf("%s\n", "Invalid password. Please ensure password length 8 - 14 characters.");
		printf("%s\n", "Note: Please include at least 1 digit, 1 uppercase, 1 lowercase, 1 symbol.");
		return false;
	}

	return true;
}

bool verifyName(char* name)
{
	// Verifies that the name confirms to the following requirements:
	//
	// at least 5 characters long
	// no digit
	//
	// returns true if name confirms to these requirements and false otherwise

	// check if the length is insufficient or exceed range
	int length = strlen(name);

	bool hasDigit = false;

	// check for each of the required character classes
	for (int i = 0; i < length; i++)
	{
		if (isdigit(name[i]))
			hasDigit = true;
	}

	// return false if detected name is not no digit = means there is digit
	if (length < 5 || length > 29 || hasDigit) {
		printf("\n%s\n", "Error message :");
		printf("%s\n", "Invalid name. Please ensure name is not too short or long.");
		printf("%s\n\n", "Note: Please ensure name contained alphabetical characters only.");
		return false;
	}
	return true;
}

bool verifyIC(char* iC)
{
	// Verifies that the IC confirms to the following requirements:
	//
	// at least 14 characters long, including 2 '-'
	// no alpha character
	//
	// returns true if IC confirms to these requirements and false otherwise

	// check if the length is insufficient or exceed range
	int length = strlen(iC);

	bool notDigit = false;
	bool notDash = false;

	// check for each of the required character classes
	for (int i = 0; i < length; i++)
	{
		if ((i >= 0 && i <= 5) || (i >= 7 && i <= 8) || (i >= 10 && i <= 13)) {
			if (!isdigit(iC[i]))
				notDigit = true;
		}
		else if ((i == 6) || (i == 9)) {
			if (iC[i] != '-')
				notDash = true;
		}
	}

	// return false if any required character class is not present
	if (length != 14 || notDigit || notDash) {
		printf("\n%s\n", "Error message :");
		printf("%s\n", "Invalid IC number. Please try again.");
		return false;
	}

	return true;
}

// - CCW - Login Menu
int loginMenu() {

	int choice;

	printf("%s\n", "=========================================");
	printf("%32s\n", "Welcome User, please select: ");
	printf("%s\n", "=========================================");
	printf("%s\n", "1. Staff Login");
	printf("%s\n", "2. Admin Login");
	printf("%s\n", "3. Exit program");
	printf("%s\n\n", "=========================================");
	printf("Enter your selection: ");
	scanf("%d", &choice);
	rewind(stdin);
	return(choice);
}

// - CCW - Staff Login
void mainStaffLogin() {
	StaffProfile displayStaffInfo[50];

	// staff ID - max 5 characters, password - max - 6 characters
	char userID[6], userPassword[7];
	int i = 0, pCount = 0, found = 0, count = 0, leftCount = 3;
	bool isPwdValid = false;

	FILE* fPtr1;

	// open for read binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	//read records from binary file into array
	//read one record successfully into array displayStaffInfo[50] till EOF
	while (fread(&displayStaffInfo[i], sizeof(displayStaffInfo[i]), 1, fPtr1) && i < 50)
		i++;

	//keep track how many actual records read from file (can be less than 50)
	pCount = i;

	fclose(fPtr1);

	//display main menu logo
	system("cls");
	mainLogoLine();
	mainLogoWord();
	mainLogoLine();

	do {
		printf("%s\n", "=========================================");
		printf("%25s\n", "Staff Login");
		printf("%s\n", "=========================================");
		//display staff login
		printf("%14s %2s ", "Staff ID", ":");
		scanf("%s", &userID);
		rewind(stdin);

		do {
			count++;
			leftCount--;
			printf("%14s %2s ", "Password", ":");
			scanf("%s", &userPassword);
			rewind(stdin);
			isPwdValid = verifyStaffPassword(&userPassword);

			if (!isPwdValid) {
				printf("%s %d %s\n\n", "Please try again. You have left", leftCount, "attempts");
			}
		} while (!isPwdValid && count < 3);
		printf("%s\n\n", "=========================================");

		if (count <= 3 && isPwdValid) {
			count--;
			leftCount++;

			// Initialize a value when nothing is found
			found = 0;

			// Loop as long as less than pCount and not found the code
			for (i = 0; i < pCount && found == 0; i++) {

				//check password validity
				if (strcmp(userID, displayStaffInfo[i].staffID) == 0 && strcmp(userPassword, displayStaffInfo[i].password) == 0) {
					// use to stop the loop to continue searching when record matched
					found = 1;
					system("cls");
					// call staff login
					staffFunction();
					break;
				}
			}

			if (found == 0) {
				count++;
				leftCount--;
				if (count < 3) {
					system("cls");
					mainLogoLine();
					mainLogoWord();
					mainLogoLine();
					printf("\n%14s\n", "Access Denied :");
					printf("%14s\n", "Invalid User ID or Password entered.");
					printf("%14s %d %s\n\n", "Please try again. You have left", leftCount, "attempts");
				}
				else {
					system("cls");
					mainLogoLine();
					mainLogoWord();
					mainLogoLine();
					printf("\n%s\n", "Login failed: ");
					printf("%s\n\n", "You have reached maximum attempts. Please contact Manager/ System Admin for further assistance...");
					break;
				}
			}
		}
		else {
			count++;
			system("cls");
			mainLogoLine();
			mainLogoWord();
			mainLogoLine();
			printf("\n%s\n", "Login failed: ");
			printf("%s\n\n", "You have reached maximum attempts. Please contact Manager /System Admin for further assistance...");
			break;
		}
	} while (found == 0 && count < 3);
}

void mainAdminLogin() {
	AdminProfile addAdminLogin[1];

	// admin ID - max 5 characters, password - min length 8 - 14 (inlcude at least 1 digit, 1 uppercase, 1 lowercase, 1 symbol)
	char adminID[6], adminPassword[15];
	int i = 0, pCount = 0, found = 0, count = 0, leftCount = 3;
	bool isPwdValid = false;

	FILE* fPtr1;

	// open for read binary file
	fPtr1 = fopen("admin_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	//read records from binary file into array
	//read one record successfully into array addAdminLogin till EOF
	while (fread(&addAdminLogin[i], sizeof(addAdminLogin[i]), 1, fPtr1))
		i++;

	//keep track how many actual records read from file (can be less than 50)
	pCount = i;

	fclose(fPtr1);

	//display main menu logo
	mainLogoLine();
	mainLogoWord();
	mainLogoLine();

	do {
		printf("%s\n", "=========================================");
		printf("%25s\n", "Admin Login");
		printf("%s\n", "=========================================");
		//display staff login
		printf("%14s %2s ", "Admin ID", ":");
		scanf("%s", &adminID);
		rewind(stdin);

		do {
			count++;
			leftCount--;
			printf("%14s %2s ", "Password", ":");
			scanf("%s", &adminPassword);
			rewind(stdin);
			isPwdValid = verifyAdminPassword(&adminPassword);

			if (!isPwdValid) {
				printf("%s %d %s\n\n", "Please try again. You have left", leftCount, "attempts");
			}
		} while (!isPwdValid && count < 3);
		printf("%s\n\n", "=========================================");

		if (count <= 3 && isPwdValid) {
			count--;
			leftCount++;
			// Initialize a value when nothing is found
			found = 0;

			// Loop as long as less than pCount and not found the code
			for (i = 0; i < pCount && found == 0; i++) {

				//check password validity
				if (strcmp(adminID, addAdminLogin[i].adminID) == 0 && strcmp(adminPassword, addAdminLogin[i].adminPassword) == 0) {
					// use to stop the loop to continue searching when record matched
					found = 1;
					system("cls");
					// call admin login
					adminFunction();
					break;
				}
			}

			if (found == 0) {
				count++;
				leftCount--;
				if (count < 3) {
					system("cls");
					mainLogoLine();
					mainLogoWord();
					mainLogoLine();
					printf("\n%14s\n", "Access Denied :");
					printf("%14s\n", "Invalid User ID or Password entered.");
					printf("%14s %d %s\n\n", "Please try again. You have left", leftCount, "attempts");
				}
				else {
					system("cls");
					mainLogoLine();
					mainLogoWord();
					mainLogoLine();
					printf("\n%s\n", "Login failed: ");
					printf("%s\n\n", "You have reached maximum attempts. Please contact Manager /System Admin for further assistance...");
					break;
				}
			}
		}
		else {
			count++;
			system("cls");
			mainLogoLine();
			mainLogoWord();
			mainLogoLine();
			printf("\n%s\n", "Login failed: ");
			printf("%s\n\n", "You have reached maximum attempts. Please contact Manager /System Admin for further assistance...");
			break;
		}
	} while (found == 0 && count < 3);
}

// - CCW - Exit Menu
void exitMenu() {
	systemHeader();
	printf("%88s\n", "~~ Thank you for using the system (^_^) ~~");
	printf("\n%80s\n", "~~ Have a wonderful day! ~~");
	systemFooter();
}

// - CCW - Staff Functional Menu
int mainStaffMenu() {

	int choice;

	printf("%s\n", "=========================================");
	printf("%30s\n", "~Staff Functional Menu~");
	printf("%s\n", "=========================================");
	printf("%s\n", "1. Staff Profile - Abbreviation List");
	printf("%s\n", "2. Staff Login   - Password Reset");
	printf("%s\n", "3. Staff Search  - By Department");
	printf("%s\n", "4. Pryde Club    - Facility Management");
	printf("%s\n", "5. Logout Staff Account");
	printf("%s\n\n", "=========================================");
	printf("Enter your selection: ");
	scanf("%d", &choice);
	rewind(stdin);
	return(choice);
}

int staffFunction() {
	int choice;

	systemHeader();

	do {
		//calling Display Report Menu & Functions
		choice = mainStaffMenu();
		system("cls");

		switch (choice) {
		case 1: staffAbbre(); break;
		case 2: resetPassword(); break;
		case 3: searchStaff(); break;
		case 4: facilityMgmtFunction(); break;
		case 5: mainLogoLine(); mainLogoWord(); mainLogoLine(); break;
		default:
			system("cls");
			systemHeader();
			printf("\n%s\n", "Error message:");
			printf("%s\n", "Oops\! you have have entered invalid character.");
			printf("%s\n\n", "Please proceed to enter correct character.");
		}
	} while (choice != 5);
}

void resetPassword() {
	StaffProfile displayStaffInfo[50];

	char modifyID[6], modifyIC[15], modify, nextProfile;
	int i = 0, pCount = 0, found = 0, modifyCount = 0, modifyIdx = 0;

	// Temporary employee information
	char tempPassword[7];
	bool isICValid = false;
	bool isPwdValid = false;

	FILE* fPtr1;

	// open for read binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	//read records from binary file into array
	//read one record successfully into array displayStaffInfo[50] till EOF
	while (fread(&displayStaffInfo[i], sizeof(displayStaffInfo[i]), 1, fPtr1) && i < 50)
		i++;

	//keep track how many actual records read from file (can be less than 50)
	pCount = i;

	fclose(fPtr1);

	systemHeader();

	do {
		//Print the title
		printf("\n%-30s\n", "*******************************");
		printf("%-30s\n", "Search & Reset Login Password");
		printf("%-30s\n", "*******************************");

		printf("%-33s %-2s", "Enter Staff ID", ":");
		scanf("%[^\n]", &modifyID);
		rewind(stdin);

		do {
			printf("%-33s %-2s", "Enter IC number(XXXXXX-XX-XXXX)", ":");
			scanf("%[^\n]", &modifyIC);
			rewind(stdin);

			isICValid = verifyIC(&modifyIC);

			if (!isICValid) {
				printf("\n%s\n", "Error message :");
				printf("%s\n\n", "Invalid IC number. Please try again.");
			}
		} while (!isICValid);

		// Loop as long as less than pCount and not found the code
		if (isICValid) {
			// Initialize a value when nothing is found
			found = 0;

			for (i = 0; i < pCount && found == 0; i++) {
				// to match the code user entered with the code from array
				if (strcmp(modifyID, displayStaffInfo[i].staffID) == 0 && strcmp(modifyIC, displayStaffInfo[i].iC) == 0) {
					// use to stop the loop to continue searching when record matched
					found = 1;

					//Display the record found//
					printf("\n%-30s\n", "*******************************");
					printf("%-30s\n", "Staff Account Details");
					printf("%-30s\n", "_______________________________");
					printf("%-30s %-2s %s\n", "Staff ID", ":", displayStaffInfo[i].staffID);
					printf("%-30s %-2s %s\n", "Staff name", ":", displayStaffInfo[i].staffName);
					printf("%-30s %-2s %s\n", "Department code", ":", displayStaffInfo[i].department);
					printf("%-30s %-2s %s\n", "Position code", ":", displayStaffInfo[i].position);

					// save the index for modification found into temp variable
					modifyIdx = i;

					// Prompt user to enter new record into temp variables 
					// Input - new password information
					printf("\n\n%-30s\n", "***************************");
					printf("\n%-30s\n", "Reset Login Password");
					printf("%-30s\n", "____________________________________");
					printf("\n<<%-14s %-2s %s>>\n", "Please input", "~", "6 digit password");


					do {
						printf("%-30s %-2s", "Enter new password", ":");
						scanf("%[^\n]", &tempPassword);
						rewind(stdin);

						isPwdValid = verifyStaffPassword(&tempPassword);

					} while (!isPwdValid);

					//checking the confirmation of modify staff profile
					printf("\n%-30s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
					printf("%-30s %-2s", "Update the above details to profile? (Y/N)", ":");
					scanf("%c", &modify);
					rewind(stdin);
					printf("%-30s\n\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

					if (modify == 'Y') {
						// Update the new record (temp variables) into the array at the index (modifyIdx) saved just now
						// Use the modify index value where the record was found at the index
						strcpy(displayStaffInfo[modifyIdx].password, tempPassword);

						modifyCount++;
					}
				}
			}

			if (found == 0) {
				printf("\n%s\n", "Access Denied: ");
				printf("%s\n", "Staff ID and IC doesn't matched.");
				printf("%s\n\n", "Please try again.");
			}
		}

		//checking if user wish to modify another staff profile
		printf("%-30s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("%-30s %-2s", "Proceed next modification? (Y/N)", ":");
		scanf("%c", &nextProfile);
		rewind(stdin);
		printf("%-30s\n\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");
	} while (nextProfile == 'Y' || nextProfile == 'y');

	printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");
	printf("< %-30s %-2s %d >\n\n", "Total staff's profile record(s) modified", ":", modifyCount);

	// Write all the records from array back to file
	// Open the file for writing to put all records from array into file
	fPtr1 = fopen("staff_profile.dat", "wb");

	for (i = 0; i < pCount; i++) {
		fwrite(&displayStaffInfo[i], sizeof(displayStaffInfo[i]), 1, fPtr1);
	}
	fclose(fPtr1);
}

void searchStaff() {
	StaffProfile displayStaffInfo[50];

	char searchedDept[6], nextProfile;
	int i = 0, pCount = 0, count = 0;

	FILE* fPtr1;

	// open for read binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	//read records from binary file into array
	//read one record successfully into array displayStaffInfo[50] till EOF
	while (fread(&displayStaffInfo[i], sizeof(displayStaffInfo[i]), 1, fPtr1) && i < 50)
		i++;

	//keep track how many actual records read from file (can be less than 50)
	pCount = i;

	fclose(fPtr1);

	do {
		system("cls");
		systemHeader();
		//Print the title
		printf("%82s\n\n", "** Search Staff Record(s) **");

		printf("%-30s %-2s", "Enter Department Code", ":");
		scanf("%[^\n]", &searchedDept);
		rewind(stdin);

		//Initialize a value when nothing is found
		count = 0;

		printf("%s\n", "=========================================================================================================================================");
		printf("%-7s %-30s %-12s %-12s %-10s %-35s\n", "ID", "Name", "Joined", "Department", "Position", "Email");
		printf("%s\n", "=========================================================================================================================================");

		//Loop as long as less than pCount and not found the code
		for (i = 0; i < pCount; i++) {
			//to match the code user entered with the code from array
			if (strcmp(searchedDept, displayStaffInfo[i].department) == 0) {
				//use to continue searching when record matched
				//found < pCount;

				//Read from array and display staff profile information
				printf("%-7s %-30s %.2d-%.2d-%-6d %-12s %-10s %-35s\n", displayStaffInfo[i].staffID, displayStaffInfo[i].staffName, displayStaffInfo[i].joinedDate.day, displayStaffInfo[i].joinedDate.month, displayStaffInfo[i].joinedDate.year, displayStaffInfo[i].department, displayStaffInfo[i].position, displayStaffInfo[i].officeEmail);
				count++;
			}
		}
		printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");
		printf("< %-30s %-2s %d >\n\n", "Total staff's profile record(s)", ":", count);

		if (count == 0) {
			printf("\n%s\n", "Error message:");
			printf("No record was found with the entered Department Code %s.\n", searchedDept);
			printf("%s\n", "Please proceed to enter valid Department Code.");
		}

		//checking if user wish to add another staff profile
		printf("\n%-30s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("%-30s %-2s", "Continue search next department? (Y/N)", ":");
		scanf("%c", &nextProfile);
		rewind(stdin);
		printf("%-30s\n\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	} while (nextProfile == 'Y' || nextProfile == 'y');

	system("cls");
	systemHeader();

	fclose(fPtr1);
}

// - CCW - Admin Functional Menu
int mainAdminMenu() {

	int choice;

	printf("%s\n", "=========================================");
	printf("%30s\n", "~Admin Functional Menu~");
	printf("%31s\n", "Staff Profile Management");
	printf("%s\n", "=========================================");
	printf("%s\n", "1. Staff Profile - Add Profile");
	printf("%s\n", "2. Staff Profile - Modification");
	printf("%s\n", "3. Staff Profile - Display List");
	printf("%s\n", "4. Staff Profile - Removal");
	printf("%s\n", "5. Staff Profile - Display Report");
	printf("%s\n", "6. Logout Admin Account");
	printf("%s\n\n", "=========================================");
	printf("Enter your selection: ");
	scanf("%d", &choice);
	rewind(stdin);
	return(choice);
}

int adminFunction() {
	int choice;

	systemHeader();

	do {
		//calling Display Report Menu & Functions
		choice = mainAdminMenu();
		system("cls");
		switch (choice) {
		case 1: addStaff(); break;
		case 2: modifyStaff(); break;
		case 3: displayStaff(); break;
		case 4: removeStaff(); break;
		case 5: displayStaffReport(); break;
		case 6: mainLogoLine(); mainLogoWord(); mainLogoLine(); break;
		default:
			system("cls");
			systemHeader();
			printf("\n%s\n", "Error message:");
			printf("%s\n", "Oops\! you have have entered invalid character.");
			printf("%s\n\n", "Please proceed to enter correct character.");
		}
	} while (choice != 6);
}

void addStaff() {
	StaffProfile addStaffInfo;

	char choice;
	int newStaffID = 0;
	char newStaffIDText[50];
	bool isNameValid = false;
	bool isICValid = false;

	FILE* fPtr1;

	newStaffID = getStaffID();

	// open for appending binary file
	fPtr1 = fopen("staff_profile.dat", "ab");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	systemHeader();

	do {
		// Eg. new ID is 12 + 1 = 13
		newStaffID += 1;

		printf("%80s\n\n", "** Adding Staff Profile **");

		// prompt user for append staff profile information
		// input - employee information
		printf("\n%-30s\n", "***************************");
		printf("%-30s\n", "Enter Employee Information");
		printf("%-30s\n", "___________________________");

		//Eg. combine char & int, "ST" with 013 become ST013
		sprintf(newStaffIDText, "ST%03d", newStaffID);
		strcpy(addStaffInfo.staffID, newStaffIDText);

		printf("%-30s %-2s%s\n", "Staff ID", ":", addStaffInfo.staffID);

		do {
			printf("%-30s %-2s", "Staff name", ":");
			scanf("%[^\n]", &addStaffInfo.staffName);
			rewind(stdin);

			isNameValid = verifyName(&addStaffInfo.staffName);

		} while (!isNameValid);

		printf("%-30s %-2s", "Date of birth(dd-mm-yyyy)", ":");
		scanf("%d-%d-%d", &addStaffInfo.birthday.day, &addStaffInfo.birthday.month, &addStaffInfo.birthday.year);
		rewind(stdin);

		printf("%-30s %-2s", "Gender(M/F)", ":");
		scanf("%c", &addStaffInfo.gender);
		toupper(addStaffInfo.gender);
		rewind(stdin);

		printf("\n<<%-14s %-2s %s>>\n", "Please input by using code", "~", "(S = Single, M = Married, D = Divorced)");
		printf("%-30s %-2s", "Marital status", ":");
		scanf("%c", &addStaffInfo.maritalStatus);
		toupper(addStaffInfo.maritalStatus);
		rewind(stdin);

		do {
			printf("\n%-30s %-2s", "IC number(XXXXXX-XX-XXXX)", ":");
			scanf("%[^\n]", &addStaffInfo.iC);
			rewind(stdin);

			isICValid = verifyIC(&addStaffInfo.iC);

		} while (!isICValid);

		printf("%-30s %-2s", "Phone number(012-XXXXXXXX)", ":");
		scanf("%[^\n]", &addStaffInfo.staffContact);
		rewind(stdin);

		printf("%-30s %-2s", "Residential address", ":");
		scanf("%[^\n]", &addStaffInfo.address);
		rewind(stdin);

		// Input - job information
		printf("\n%-30s\n", "Enter Job Information");
		printf("%-30s\n", "______________________");

		printf("%-30s %-2s", "Joined date(dd-mm-yyyy)", ":");
		scanf("%d-%d-%d", &addStaffInfo.joinedDate.day, &addStaffInfo.joinedDate.month, &addStaffInfo.joinedDate.year);
		rewind(stdin);

		printf("\n<<%-14s %-2s %s>>\n", "Please input by using code", "~", "(ENG, FIN, FIT, HRD, HSK, PCS, RSD, SEC, SMD)");
		printf("%-30s %-2s", "Department code", ":");
		scanf("%[^\n]", &addStaffInfo.department);
		rewind(stdin);

		printf("\n<<%-14s %-2s %s>>\n", "Please input by using code", "~", "(OFC, EXC, SUP, AMG, MGR, DIR)");
		printf("%-30s %-2s", "Position code", ":");
		scanf("%[^\n]", &addStaffInfo.position);
		rewind(stdin);

		printf("\n<<%-14s %-2s %s>>\n", "Please input by using code", "~", "(E1, E2, E3, M1, M2, M3)");
		printf("%-30s %-2s", "Job Level code", ":");
		scanf("%[^\n]", &addStaffInfo.jobLevel);
		rewind(stdin);

		printf("\n%-30s %-2s", "Office email", ":");
		scanf("%[^\n]", &addStaffInfo.officeEmail);
		rewind(stdin);

		printf("%-30s %-2s%s ", "Monthly salary", ":", "RM");
		scanf("%lf", &addStaffInfo.salary);
		rewind(stdin);

		// Input - emergency contact information
		printf("\n%-30s\n", "Enter Emergency Contact Information");
		printf("%-30s\n", "____________________________________");

		printf("%-30s %-2s", "Contact person name", ":");
		scanf("%[^\n]", &addStaffInfo.emergencyPerson);
		rewind(stdin);

		printf("%-30s %-2s", "Phone number(012-XXXXXXXX)", ":");
		scanf("%[^\n]", &addStaffInfo.emergencyPhone);
		rewind(stdin);

		printf("%-30s %-2s", "Relationship", ":");
		scanf("%[^\n]", &addStaffInfo.relationship);
		rewind(stdin);

		// Input - login password information
		printf("\n%-30s\n", "Enter Staff Login Password");
		printf("%-30s\n", "____________________________________");
		printf("\n<<%-14s %-2s %s>>\n", "Please input", "~", "6 digits password");
		printf("%-30s %-2s", "Staff login password", ":");
		scanf("%[^\n]", &addStaffInfo.password);
		rewind(stdin);

		// Write into Binary File
		fwrite(&addStaffInfo, sizeof(StaffProfile), 1, fPtr1);

		printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");

		//display the written staff profile information
		printf("\n\n%-30s\n", "*******************************");
		printf("%-30s\n", "Staff Profile Information Added");
		printf("%-30s\n", "_______________________________");
		printf("%-30s %-2s %s\n", "Staff ID", ":", addStaffInfo.staffID);
		printf("%-30s %-2s %s\n", "Staff name", ":", addStaffInfo.staffName);
		printf("%-30s %-2s %.2d-%.2d-%.2d\n", "Date of birth", ":", addStaffInfo.birthday.day, addStaffInfo.birthday.month, addStaffInfo.birthday.year);
		printf("%-30s %-2s %c\n", "Gender", ":", addStaffInfo.gender);
		printf("%-30s %-2s %c\n", "Marital status", ":", addStaffInfo.maritalStatus);
		printf("%-30s %-2s %s\n", "IC number", ":", addStaffInfo.iC);
		printf("%-30s %-2s %s\n", "Phone number", ":", addStaffInfo.staffContact);
		printf("%-30s %-2s %s\n", "Residential address", ":", addStaffInfo.address);
		printf("%-30s %-2s %.2d-%.2d-%.2d\n", "Joined date", ":", addStaffInfo.joinedDate.day, addStaffInfo.joinedDate.month, addStaffInfo.joinedDate.year);
		printf("%-30s %-2s %s\n", "Department code", ":", addStaffInfo.department);
		printf("%-30s %-2s %s\n", "Position code", ":", addStaffInfo.position);
		printf("%-30s %-2s %s\n", "Job Level code", ":", addStaffInfo.jobLevel);
		printf("%-30s %-2s %s\n", "Office email", ":", addStaffInfo.officeEmail);
		printf("%-30s %-2s %s %.2lf\n", "Monthly salary", ":", "RM", addStaffInfo.salary);
		printf("\n%-30s\n", "***********************************");
		printf("%-30s\n", "Staff Emergency Contact Information");
		printf("%-30s\n", "___________________________________");
		printf("%-30s %-2s %s\n", "Contact person name", ":", addStaffInfo.emergencyPerson);
		printf("%-30s %-2s %s\n", "Phone number", ":", addStaffInfo.emergencyPhone);
		printf("%-30s %-2s %s\n", "Relationship", ":", addStaffInfo.relationship);
		printf("\n%-30s\n", "***********************************");
		printf("%-30s\n", "Staff Login Information");
		printf("%-30s\n", "___________________________________");
		printf("%-30s %-2s %s\n", "Staff login password", ":", addStaffInfo.password);


		// checking if user wish to add another staff profile
		printf("\n%-30s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("%-30s %-2s", "Adding next staff profile? (Y/N)", ":");
		scanf("%c", &choice);
		rewind(stdin);
		printf("%-30s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("\n%s\n\n", "_________________________________________________________________________________________________________________________________________");
	} while (choice == 'Y' || choice == 'y');

	fclose(fPtr1);
}

int getStaffID() {
	StaffProfile addStaffInfo;

	char newStaffID[6] = "";
	int value = 0;

	FILE* fPtr1;

	// open for reading binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	//Read from the binary file and store into the structure
	// auto generate ID getStaffID();
	while (fread(&addStaffInfo, sizeof(StaffProfile), 1, fPtr1)) {
		strcpy(newStaffID, addStaffInfo.staffID);
	}
	fclose(fPtr1);

	// use ASCII to check last staff ID
	// Eg. '0' = 48, '9' = 57
	// If last Id is ST012
	// value = 0 * 10 + 48 - 48, value = 0
	// value = 0 * 10 + 49 - 48, value = 1
	// value = 1 * 10 + 50 - 48, value = 12
	for (int i = 0; i < strlen(newStaffID); i++) {
		if (newStaffID[i] >= '0' && newStaffID[i] <= '9') {
			value = value * 10 + newStaffID[i] - '0';
		}
	}

	return value;
}

void modifyStaff() {
	StaffProfile displayStaffInfo[50];

	char modifyID[6], modify, nextProfile;
	int i = 0, pCount = 0, found = 0, modifyCount = 0, modifyIdx = 0;
	bool isNameValid = false;
	bool isICValid = false;

	// Temporary employee information
	char tempStaffName[30];
	int tempBirthDate, tempBirthMonth, tempBirthYear;
	char tempGender;
	char tempMaritalStatus, tempIC[15], tempStaffContact[13], tempAddress[80];

	// Temporary job information
	int tempJoinedDate, tempJoinedMonth, tempJoinedYear;
	char tempDepartment[6], tempPosition[6], tempJobLevel[3], tempOfficeEmail[20];
	double tempSalary;

	// Temporary emergency contact information
	char tempEmergencyPerson[30], tempEmergencyPhone[13], tempRelationship[20];

	FILE* fPtr1;

	// open for read binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	//read records from binary file into array
	//read one record successfully into array displayStaffInfo[50] till EOF
	while (fread(&displayStaffInfo[i], sizeof(displayStaffInfo[i]), 1, fPtr1) && i < 50)
		i++;

	//keep track how many actual records read from file (can be less than 50)
	pCount = i;

	fclose(fPtr1);

	systemHeader();

	do {
		//Print the title
		printf("\n%-30s\n", "*******************************");
		printf("%-30s\n", "Search & Modify Staff Record(s)");
		printf("%-30s\n", "*******************************");

		printf("%-30s %-2s", "Enter Staff ID", ":");
		scanf("%[^\n]", &modifyID);
		rewind(stdin);

		// Initialize a value when nothing is found
		found = 0;
		// Initialize the count before modifcation starts
		// modifyCount = 0;

		// Loop as long as less than pCount and not found the code
		for (i = 0; i < pCount && found == 0; i++) {
			// to match the code user entered with the code from array
			if (strcmp(modifyID, displayStaffInfo[i].staffID) == 0) {
				// use to stop the loop to continue searching when record matched
				found = 1;

				//Display the record found//
				printf("\n%-30s\n", "*******************************");
				printf("%-30s\n", "Staff Profile To Be Modified");
				printf("%-30s\n", "_______________________________");
				printf("%-30s %-2s %s\n", "Staff ID", ":", displayStaffInfo[i].staffID);
				printf("%-30s %-2s %s\n", "Staff name", ":", displayStaffInfo[i].staffName);
				printf("%-30s %-2s %.2d-%.2d-%.2d\n", "Date of birth", ":", displayStaffInfo[i].birthday.day, displayStaffInfo[i].birthday.month, displayStaffInfo[i].birthday.year);
				printf("%-30s %-2s %c\n", "Gender", ":", displayStaffInfo[i].gender);
				printf("%-30s %-2s %c\n", "Marital status", ":", displayStaffInfo[i].maritalStatus);
				printf("%-30s %-2s %s\n", "IC number", ":", displayStaffInfo[i].iC);
				printf("%-30s %-2s %s\n", "Phone number", ":", displayStaffInfo[i].staffContact);
				printf("%-30s %-2s %s\n", "Residential area", ":", displayStaffInfo[i].address);
				printf("%-30s %-2s %.2d-%.2d-%.2d\n", "Joined date", ":", displayStaffInfo[i].joinedDate.day, displayStaffInfo[i].joinedDate.month, displayStaffInfo[i].joinedDate.year);
				printf("%-30s %-2s %s\n", "Department code", ":", displayStaffInfo[i].department);
				printf("%-30s %-2s %s\n", "Position code", ":", displayStaffInfo[i].position);
				printf("%-30s %-2s %s\n", "Job Level code", ":", displayStaffInfo[i].jobLevel);
				printf("%-30s %-2s %s\n", "Office email", ":", displayStaffInfo[i].officeEmail);
				printf("%-30s %-2s %s %.2lf\n", "Monthly salary", ":", "RM", displayStaffInfo[i].salary);
				printf("\n%-30s\n", "***********************************");
				printf("%-30s\n", "Staff Emergency Contact Information");
				printf("%-30s\n", "___________________________________");
				printf("%-30s %-2s %s\n", "Contact person name", ":", displayStaffInfo[i].emergencyPerson);
				printf("%-30s %-2s %s\n", "Phone number", ":", displayStaffInfo[i].emergencyPhone);
				printf("%-30s %-2s %s\n", "Relationship", ":", displayStaffInfo[i].relationship);

				// save the index for modification found into temp variable
				modifyIdx = i;

				printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");

				// Prompt user to enter new record into temp variables 
				// Input - employee information
				printf("\n\n%-30s\n", "***************************");
				printf("%-30s\n", "Enter Employee Information");
				printf("%-30s\n", "___________________________");

				// Start with Employee name
				do {
					printf("%-30s %-2s", "Staff name", ":");
					scanf("%[^\n]", &tempStaffName);
					rewind(stdin);

					isNameValid = verifyName(&tempStaffName);

				} while (!isNameValid);

				printf("%-30s %-2s", "Date of birth(dd-mm-yyyy)", ":");
				scanf("%d-%d-%d", &tempBirthDate, &tempBirthMonth, &tempBirthYear);
				rewind(stdin);

				printf("%-30s %-2s", "Gender(M/F)", ":");
				scanf("%c", &tempGender);
				//toupper(tempGender);
				rewind(stdin);

				printf("\n<<%-14s %-2s %s>>\n", "Please input by using code", "~", "(S = Single, M = Married, D = Divorced)");
				printf("%-30s %-2s", "Marital status", ":");
				scanf("%c", &tempMaritalStatus);
				//toupper(tempMaritalStatus);
				rewind(stdin);

				do {
					printf("\n%-30s %-2s", "IC number(XXXXXX-XX-XXXX)", ":");
					scanf("%[^\n]", &tempIC);
					rewind(stdin);

					isICValid = verifyIC(&tempIC);

				} while (!isICValid);

				printf("%-30s %-2s", "Phone number(012-XXXXXXXX)", ":");
				scanf("%[^\n]", &tempStaffContact);
				rewind(stdin);

				printf("%-30s %-2s", "Residential address", ":");
				scanf("%[^\n]", &tempAddress);
				rewind(stdin);

				// Input - job information
				printf("\n%-30s\n", "Enter Job Information");
				printf("%-30s\n", "______________________");

				printf("%-30s %-2s", "Joined date(dd-mm-yyyy)", ":");
				scanf("%d-%d-%d", &tempJoinedDate, &tempJoinedMonth, &tempJoinedYear);
				rewind(stdin);

				printf("\n<<%-14s %-2s %s>>\n", "Please input by using code", "~", "(ENG, FIN, FIT, HRD, HSK, PCS, RSD, SEC, SMD)");
				printf("%-30s %-2s", "Department code", ":");
				scanf("%[^\n]", &tempDepartment);
				rewind(stdin);

				printf("\n<<%-14s %-2s %s>>\n", "Please input by using code", "~", "(OFC, EXC, SUP, AMG, MGR, DIR)");
				printf("%-30s %-2s", "Position code", ":");
				scanf("%[^\n]", &tempPosition);
				rewind(stdin);

				printf("\n<<%-14s %-2s %s>>\n", "Please input by using code", "~", "(E1, E2, E3, M1, M2, M3)");
				printf("%-30s %-2s", "Job Level code", ":");
				scanf("%[^\n]", &tempJobLevel);
				rewind(stdin);

				printf("\n%-30s %-2s", "Office email", ":");
				scanf("%[^\n]", &tempOfficeEmail);
				rewind(stdin);

				printf("%-30s %-2s%s ", "Monthly salary", ":", "RM");
				scanf("%lf", &tempSalary);
				rewind(stdin);

				// Input - emergency contact information
				printf("\n%-30s\n", "Enter Emergency Contact Information");
				printf("%-30s\n", "____________________________________");

				printf("%-30s %-2s", "Contact person name", ":");
				scanf("%[^\n]", &tempEmergencyPerson);
				rewind(stdin);

				printf("%-30s %-2s", "Phone number(012-XXXXXXXX)", ":");
				scanf("%[^\n]", &tempEmergencyPhone);
				rewind(stdin);

				printf("%-30s %-2s", "Relationship", ":");
				scanf("%[^\n]", &tempRelationship);
				rewind(stdin);

				//checking the confirmation of modify staff profile
				printf("\n%-30s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				printf("%-30s %-2s", "Update the above details to profile? (Y/N)", ":");
				scanf("%c", &modify);
				rewind(stdin);
				printf("%-30s\n\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

				if (modify == 'Y') {
					// Update the new record (temp variables) into the array at the index (modifyIdx) saved just now
					// Use the modify index value where the record was found at the index
					strcpy(displayStaffInfo[modifyIdx].staffName, tempStaffName);

					displayStaffInfo[modifyIdx].birthday.day = tempBirthDate;
					displayStaffInfo[modifyIdx].birthday.month = tempBirthMonth;
					displayStaffInfo[modifyIdx].birthday.year = tempBirthYear;

					displayStaffInfo[modifyIdx].gender = tempGender;
					displayStaffInfo[modifyIdx].maritalStatus = tempMaritalStatus;
					strcpy(displayStaffInfo[modifyIdx].iC, tempIC);
					strcpy(displayStaffInfo[modifyIdx].staffContact, tempStaffContact);
					strcpy(displayStaffInfo[modifyIdx].address, tempAddress);

					displayStaffInfo[modifyIdx].joinedDate.day = tempJoinedDate;
					displayStaffInfo[modifyIdx].joinedDate.month = tempJoinedMonth;
					displayStaffInfo[modifyIdx].joinedDate.year = tempJoinedYear;

					strcpy(displayStaffInfo[modifyIdx].department, tempDepartment);
					strcpy(displayStaffInfo[modifyIdx].position, tempPosition);
					strcpy(displayStaffInfo[modifyIdx].jobLevel, tempJobLevel);
					strcpy(displayStaffInfo[modifyIdx].officeEmail, tempOfficeEmail);

					displayStaffInfo[modifyIdx].salary = tempSalary;

					strcpy(displayStaffInfo[modifyIdx].emergencyPerson, tempEmergencyPerson);
					strcpy(displayStaffInfo[modifyIdx].emergencyPhone, tempEmergencyPhone);
					strcpy(displayStaffInfo[modifyIdx].relationship, tempRelationship);

					modifyCount++;
				}
			}
		}

		if (found == 0) {
			printf("\n%s\n", "Error message:");
			printf("No record was found with the entered Staff ID %s.\n", modifyID);
			printf("%s\n", "Please proceed to enter valid Staff ID.");
		}

		//checking if user wish to modify another staff profile
		printf("\n%-30s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("%-30s %-2s", "Proceed next modification? (Y/N)", ":");
		scanf("%c", &nextProfile);
		rewind(stdin);
		printf("%-30s\n\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");
	} while (nextProfile == 'Y' || nextProfile == 'y');

	printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");
	printf("< %-30s %-2s %d >\n\n", "Total staff's profile record(s) modified", ":", modifyCount);

	// Write all the records from array back to file
	// Open the file for writing to put all records from array into file
	fPtr1 = fopen("staff_profile.dat", "wb");

	for (i = 0; i < pCount; i++) {
		fwrite(&displayStaffInfo[i], sizeof(displayStaffInfo[i]), 1, fPtr1);
	}
	fclose(fPtr1);
}

void displayStaff() {
	StaffProfile displayStaffInfo;

	int count = 0, row = 0, col = 0;

	FILE* fPtr1;

	// open for read binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	systemHeader();

	//Print the title
	printf("%82s\n\n", "** All Staff Profile Records **");

	//Read from the binary file and store into the structure
	while (fread(&displayStaffInfo, sizeof(StaffProfile), 1, fPtr1)) {
		printf("\n%-10s %-2s %s\n", "ID", ":", displayStaffInfo.staffID);
		printf("%-10s %-2s %s\n", "Name", ":", displayStaffInfo.staffName);
		printf("%s\n", "=======================================================================================================");
		printf("%-12s %-12s %-18s %-18s %-16s\n", "Birthdate", "Gender", "Marital Status", "IC", "Contact");
		printf("%s\n", "=======================================================================================================");
		printf("%.2d-%.2d-%-6d %-12c %-18c %-18s %-16s\n", displayStaffInfo.birthday.day, displayStaffInfo.birthday.month, displayStaffInfo.birthday.year, displayStaffInfo.gender, displayStaffInfo.maritalStatus, displayStaffInfo.iC, displayStaffInfo.staffContact);

		printf("\n%s\n", "=======================================================================================================");
		printf("%-20s\n", "Residential Address");
		printf("%s\n", "=======================================================================================================");
		printf("%-20s\n", displayStaffInfo.address);

		printf("\n%s\n", "=======================================================================================================");
		printf("%-12s %-12s %-18s %-18s %-27s %-10s\n", "Joined", "Department", "Position", "Level", "Email", "Salary(RM)");
		printf("%s\n", "=======================================================================================================");
		printf("%.2d-%.2d-%-6d %-12s %-18s %-18s %-27s %-10.2lf\n", displayStaffInfo.joinedDate.day, displayStaffInfo.joinedDate.month, displayStaffInfo.joinedDate.year, displayStaffInfo.department, displayStaffInfo.position, displayStaffInfo.jobLevel, displayStaffInfo.officeEmail, displayStaffInfo.salary);

		printf("\n<%s>\n", "Emergency Contact");
		printf("%s\n", "=======================================================================================================");
		printf("%-25s %-18s %-20s\n", "Name", "Contact", "Relationship");
		printf("%s\n", "=======================================================================================================");
		printf("%-25s %-18s %-20s\n\n", displayStaffInfo.emergencyPerson, displayStaffInfo.emergencyPhone, displayStaffInfo.relationship);

		printf("\n<%s>\n", "Staff Login Information");
		printf("%s\n", "=======================================================================================================");
		printf("%-12s\n", "Password");
		printf("%s\n", "=======================================================================================================");
		printf("%-12s\n\n", displayStaffInfo.password);

		// diaplay below sub-line
		for (row = 1; row <= 1; row++) {
			printf(" ");
			for (col = 1; col <= 137; col++) {
				printf("-");
			}
			printf("\n");
		}
		printf("\n");

		count++;
	}

	printf("\n%s\n", "_______________________________________________________________________________________________________");
	printf("< %-30s %-2s %d >\n\n", "Total staff's profile record(s)", ":", count);

	fclose(fPtr1);
}

void removeStaff() {
	StaffProfile removeStaffInfo[50];

	int i = 0, count = 0, pCount = 0, found = 0, deleteCount = 0, deleteIdx = 0;

	char removeID[6], delete1, nextProfile;

	FILE* fPtr1;

	// open for read binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	//Read records from file into array
	//Read one record successfully into array till EOF
	while (fread(&removeStaffInfo[i], sizeof(removeStaffInfo[i]), 1, fPtr1) && i < 50)
		i++;

	//keep track how many actual records read from file
	pCount = i;

	fclose(fPtr1);

	systemHeader();

	do {
		//Print the title
		printf("%81s\n\n", "** Remove Staff Profile **");

		printf("%-30s %-2s", "Enter Staff ID", ":");
		scanf("%[^\n]", &removeID);
		rewind(stdin);

		found = 0;// Initialize a value when nothing is found

		// Loop as long as less than pCount and not found the code
		for (i = 0; i < pCount && found == 0; i++) {
			if (strcmp(removeID, removeStaffInfo[i].staffID) == 0) { // to match the code user entered with the code from array
				found = 1;// use to stop the loop to continue searching when record matched

				//Display the record found
				printf("\n%-30s\n", "*******************************");
				printf("%-30s\n", "Staff Profile To Be Remove");
				printf("%-30s\n", "_______________________________");
				printf("%-30s %-2s %s\n", "Staff ID", ":", removeStaffInfo[i].staffID);
				printf("%-30s %-2s %s\n", "Staff name", ":", removeStaffInfo[i].staffName);
				printf("%-30s %-2s %.2d-%.2d-%.2d\n", "Date of birth", ":", removeStaffInfo[i].birthday.day, removeStaffInfo[i].birthday.month, removeStaffInfo[i].birthday.year);
				printf("%-30s %-2s %c\n", "Gender", ":", removeStaffInfo[i].gender);
				printf("%-30s %-2s %c\n", "Marital status", ":", removeStaffInfo[i].maritalStatus);
				printf("%-30s %-2s %s\n", "IC number", ":", removeStaffInfo[i].iC);
				printf("%-30s %-2s %s\n", "Phone number", ":", removeStaffInfo[i].staffContact);
				printf("%-30s %-2s %s\n", "Residential address", ":", removeStaffInfo[i].address);
				printf("%-30s %-2s %.2d-%.2d-%.2d\n", "Joined date", ":", removeStaffInfo[i].joinedDate.day, removeStaffInfo[i].joinedDate.month, removeStaffInfo[i].joinedDate.year);
				printf("%-30s %-2s %s\n", "Department code", ":", removeStaffInfo[i].department);
				printf("%-30s %-2s %s\n", "Position code", ":", removeStaffInfo[i].position);
				printf("%-30s %-2s %s\n", "Job Level code", ":", removeStaffInfo[i].jobLevel);
				printf("%-30s %-2s %s\n", "Office email", ":", removeStaffInfo[i].officeEmail);
				printf("%-30s %-2s %s %.2lf\n", "Monthly salary", ":", "RM", removeStaffInfo[i].salary);
				printf("\n%-30s\n", "***********************************");
				printf("%-30s\n", "Staff Emergency Contact Information");
				printf("%-30s\n", "___________________________________");
				printf("%-30s %-2s %s\n", "Contact person name", ":", removeStaffInfo[i].emergencyPerson);
				printf("%-30s %-2s %s\n", "Phone number", ":", removeStaffInfo[i].emergencyPhone);
				printf("%-30s %-2s %s\n", "Relationship", ":", removeStaffInfo[i].relationship);

				deleteIdx = i;

				//checking the confirmation of removing staff profile
				printf("\n%-30s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				printf("%-30s %-2s", "Remove this staff profile? (Y/N)", ":");
				scanf("%c", &delete1);
				rewind(stdin);
				printf("%-30s\n\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

				if (delete1 == 'Y') {
					pCount--;

					for (i = deleteIdx; i < pCount; i++) {

						//delete function
						strcpy(removeStaffInfo[i].staffID, removeStaffInfo[i + 1].staffID);
						strcpy(removeStaffInfo[i].staffName, removeStaffInfo[i + 1].staffName);

						// staff ID to remove or retain
						removeStaffInfo[i].birthday.day = removeStaffInfo[i + 1].birthday.day;
						removeStaffInfo[i].birthday.month = removeStaffInfo[i + 1].birthday.month;
						removeStaffInfo[i].birthday.year = removeStaffInfo[i + 1].birthday.year;

						removeStaffInfo[i].gender = removeStaffInfo[i + 1].gender;
						removeStaffInfo[i].maritalStatus = removeStaffInfo[i + 1].maritalStatus;
						strcpy(removeStaffInfo[i].iC, removeStaffInfo[i + 1].iC);
						strcpy(removeStaffInfo[i].staffContact, removeStaffInfo[i + 1].staffContact);
						strcpy(removeStaffInfo[i].address, removeStaffInfo[i + 1].address);

						removeStaffInfo[i].joinedDate.day = removeStaffInfo[i + 1].joinedDate.day;
						removeStaffInfo[i].joinedDate.month = removeStaffInfo[i + 1].joinedDate.month;
						removeStaffInfo[i].joinedDate.year = removeStaffInfo[i + 1].joinedDate.year;

						strcpy(removeStaffInfo[i].department, removeStaffInfo[i + 1].department);
						strcpy(removeStaffInfo[i].position, removeStaffInfo[i + 1].position);
						strcpy(removeStaffInfo[i].jobLevel, removeStaffInfo[i + 1].jobLevel);
						strcpy(removeStaffInfo[i].officeEmail, removeStaffInfo[i + 1].officeEmail);

						removeStaffInfo[i].salary = removeStaffInfo[i + 1].salary;

						strcpy(removeStaffInfo[i].emergencyPerson, removeStaffInfo[i + 1].emergencyPerson);
						strcpy(removeStaffInfo[i].emergencyPhone, removeStaffInfo[i + 1].emergencyPhone);
						strcpy(removeStaffInfo[i].relationship, removeStaffInfo[i + 1].relationship);

						strcpy(removeStaffInfo[i].password, removeStaffInfo[i + 1].password);
					}
					deleteCount++;
				}
			}
		}

		if (found == 0) {
			printf("\n%s\n", "Error message:");
			printf("No record was found with the entered Staff ID %s.\n", removeID);
			printf("%s\n", "Please proceed to enter valid Staff ID.");
		}

		//checking if user wish to modify another staff profile
		printf("\n%-30s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("%-30s %-2s", "Proceed remove next staff profile? (Y/N)", ":");
		scanf("%c", &nextProfile);
		rewind(stdin);
		printf("%-30s\n\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");
	} while (nextProfile == 'Y' || nextProfile == 'y');

	printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");
	printf("< %-30s %-2s %d >\n\n", "Total staff's profile record(s) deleted", ":", deleteCount);

	//Write all the records from array back to file
	fPtr1 = fopen("staff_profile.dat", "wb");// open the file for writing to put all records from array into file
	for (i = 0; i < pCount; i++)
		fwrite(&removeStaffInfo[i], sizeof(removeStaffInfo[i]), 1, fPtr1);

	fclose(fPtr1);
}

// - CCW - Staff Report Menu
int staffReportMenu() {

	int choice;

	printf("%s\n", "=========================================");
	printf("%28s\n", "Staff Report Menu");
	printf("%s\n", "=========================================");
	printf("%s\n", "1. Staff Profile Abbreviation List");
	printf("%s\n", "2. Staff Profile By Individual Name");
	printf("%s\n", "3. Staff List - Personal Details");
	printf("%s\n", "4. Staff List - Residential Address");
	printf("%s\n", "5. Staff List - Employment Details");
	printf("%s\n", "6. Staff List - Emergency Contact Details");
	printf("%s\n", "7. Return to Previous Menu");
	printf("%s\n\n", "=========================================");
	printf("Enter your selection: ");
	scanf("%d", &choice);
	rewind(stdin);
	return(choice);
}

int displayStaffReport() {
	int choice;

	systemHeader();

	do {
		//calling Display Report Menu & Functions
		choice = staffReportMenu();
		system("cls");
		switch (choice) {
		case 1: staffAbbre(); break;
		case 2: staffIndividualProfile(); break;
		case 3: staffListPersonal(); break;
		case 4: staffListAddress(); break;
		case 5: staffListEmployment(); break;
		case 6: staffListEmergency(); break;
		case 7: systemHeader(); break;
		default:
			system("cls");
			systemHeader();
			printf("\n%s\n", "Error message:");
			printf("%s\n", "Oops\! you have have entered invalid character.");
			printf("%s\n\n", "Please proceed to enter correct character.");
		}
	} while (choice != 7);
}

void staffAbbre() {

	reportHeader();

	int row = 0, col = 0;

	//display report name
	printf("%86s\n\n", "~~ Staff Profile Abbreviation List ~~");
	//display department code
	printf("<%s>\n", "Department Code");
	printf("%-10s %s\n", "ENG", "Engineering Department");
	printf("%-10s %s\n", "FIN", "Finance Department");
	printf("%-10s %s\n", "FIT", "Fitness & Athletic Department");
	printf("%-10s %s\n", "HRD", "Human Resource Department");
	printf("%-10s %s\n", "HSK", "Housekeeping Department");
	printf("%-10s %s\n", "PCS", "Procurement Department");
	printf("%-10s %s\n", "RSD", "Recreation Service Department");
	printf("%-10s %s\n", "SEC", "Security Department");
	printf("%-10s %s\n", "SMD", "Sales & Marketing Department");
	//display position code
	printf("\n<%s>\n", "Position Code");
	printf("%-10s %s\n", "OFC", "Officer");
	printf("%-10s %s\n", "EXC", "Executive");
	printf("%-10s %s\n", "SUP", "Supervisor");
	printf("%-10s %s\n", "AMG", "Assistant Manager");
	printf("%-10s %s\n", "MGR", "Manager");
	printf("%-10s %s\n", "DIR", "Director");
	//display job level code
	printf("\n<%s>\n", "Job Level Code");
	printf("%-10s %s\n", "E1", "Executive Level 1");
	printf("%-10s %s\n", "E2", "Executive Level 2");
	printf("%-10s %s\n", "E3", "Executive Level 3");
	printf("%-10s %s\n", "M1", "Managerial Level 1");
	printf("%-10s %s\n", "M2", "Managerial Level 2");
	printf("%-10s %s\n\n", "M3", "Managerial Level 3");

	reportFooter();
}

void staffIndividualProfile() {

	StaffProfile displayStaffInfo[50];

	char searchedID[6], nextProfile;
	int i = 0, pCount = 0, found = 0;

	FILE* fPtr1;

	//open for read binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	//read records from binary file into array
	//read one record successfully into array displayStaffInfo[50] till EOF
	while (fread(&displayStaffInfo[i], sizeof(displayStaffInfo[i]), 1, fPtr1) && i < 50)
		i++;

	//keep track how many actual records read from file (can be less than 50)
	pCount = i;

	fclose(fPtr1);

	reportHeader();

	do {
		printf("%-30s %-2s", "Enter Staff ID", ":");
		scanf("%[^\n]", &searchedID);
		rewind(stdin);

		//Initialize a value when nothing is found
		found = 0;

		//Loop as long as less than pCount and not found the code
		for (i = 0; i < pCount && found == 0; i++) {
			//to match the code user entered with the code from array
			if (strcmp(searchedID, displayStaffInfo[i].staffID) == 0) {
				//use to stop the loop to continue searching when record matched
				found = 1;

				//Display the report name and record found
				printf("%85s\n\n", "~~ Staff Profile By Individual Name ~~");
				//Read from array and display staff profile information
				printf("%-30s\n", "*************************");
				printf("%-30s\n", "Staff Profile Information ");
				printf("%-30s\n", "________________________");
				printf("%-30s %-2s %s\n", "Staff ID", ":", displayStaffInfo[i].staffID);
				printf("%-30s %-2s %s\n", "Staff name", ":", displayStaffInfo[i].staffName);
				printf("%-30s %-2s %.2d-%.2d-%.2d\n", "Date of birth", ":", displayStaffInfo[i].birthday.day, displayStaffInfo[i].birthday.month, displayStaffInfo[i].birthday.year);
				printf("%-30s %-2s %c\n", "Gender", ":", displayStaffInfo[i].gender);
				printf("%-30s %-2s %c\n", "Marital status", ":", displayStaffInfo[i].maritalStatus);
				printf("%-30s %-2s %s\n", "IC number", ":", displayStaffInfo[i].iC);
				printf("%-30s %-2s %s\n", "Phone number", ":", displayStaffInfo[i].staffContact);
				printf("%-30s %-2s %s\n", "Residential address", ":", displayStaffInfo[i].address);
				printf("%-30s %-2s %.2d-%.2d-%.2d\n", "Joined date", ":", displayStaffInfo[i].joinedDate.day, displayStaffInfo[i].joinedDate.month, displayStaffInfo[i].joinedDate.year);
				printf("%-30s %-2s %s\n", "Department code", ":", displayStaffInfo[i].department);
				printf("%-30s %-2s %s\n", "Position code", ":", displayStaffInfo[i].position);
				printf("%-30s %-2s %s\n", "Job Level code", ":", displayStaffInfo[i].jobLevel);
				printf("%-30s %-2s %s\n", "Office email", ":", displayStaffInfo[i].officeEmail);
				printf("%-30s %-2s %s %.2lf\n", "Monthly salary", ":", "RM", displayStaffInfo[i].salary);
				printf("\n%-30s\n", "***********************************");
				printf("%-30s\n", "Staff Emergency Contact Information");
				printf("%-30s\n", "___________________________________");
				printf("%-30s %-2s %s\n", "Contact person name", ":", displayStaffInfo[i].emergencyPerson);
				printf("%-30s %-2s %s\n", "Phone number", ":", displayStaffInfo[i].emergencyPhone);
				printf("%-30s %-2s %s\n", "Relationship", ":", displayStaffInfo[i].relationship);
				printf("\n%-30s\n", "***********************************");
				printf("%-30s\n", "Staff Login Information");
				printf("%-30s\n", "___________________________________");
				printf("%-30s %-2s %s\n", "Staff login password", ":", displayStaffInfo[i].password);
				reportFooter();
			}
		}
		if (found == 0) {
			printf("\n%s\n", "Error message:");
			printf("No record was found with the entered Staff ID %s\n", searchedID);
			printf("%s\n", "Please proceed to enter valid Staff ID.");
		}

		//checking if user wish to add another staff profile
		printf("\n%-30s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("%-30s %-2s", "Continue search next staff profile? (Y/N)", ":");
		scanf("%c", &nextProfile);
		rewind(stdin);
		printf("%-30s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		system("cls");
		systemHeader();

	} while (nextProfile == 'Y' || nextProfile == 'y');
}

void staffListPersonal() {

	StaffProfile displayStaffInfo;

	int count = 0;

	FILE* fPtr1;

	//open for read binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	reportHeader();

	//Print the title
	//display report name
	printf("%87s\n\n", "~~ Staff List - Personal Details ~~");
	printf("%s\n", "=========================================================================================================================================");
	printf("%-7s %-30s %-12s %-12s %-18s %-18s %-16s\n", "ID", "Name", "Birthdate", "Gender", "Marital Status", "IC", "Contact");
	printf("%s\n", "=========================================================================================================================================");
	//Read from the binary file and store into the structure
	while (fread(&displayStaffInfo, sizeof(StaffProfile), 1, fPtr1)) {
		printf("%-7s %-30s %.2d-%.2d-%-6d %-12c %-18c %-18s %-16s\n", displayStaffInfo.staffID, displayStaffInfo.staffName, displayStaffInfo.birthday.day, displayStaffInfo.birthday.month, displayStaffInfo.birthday.year, displayStaffInfo.gender, displayStaffInfo.maritalStatus, displayStaffInfo.iC, displayStaffInfo.staffContact);
		count++;
	}

	printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");
	printf("< %-30s %-2s %d >\n\n", "Total staff's profile record(s)", ":", count);

	reportFooter();

	fclose(fPtr1);
}

void staffListAddress() {

	StaffProfile displayStaffInfo;

	int count = 0;

	FILE* fPtr1;

	//open for read binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	reportHeader();

	//Print the title
	//display report name
	printf("%88s\n\n", "~~ Staff List - Residential Address ~~");

	//display staff residential address
	printf("%s\n", "=========================================================================================================================================");
	printf("%-7s %-30s %-16s\n", "ID", "Name", "Residential Address");
	printf("%s\n", "=========================================================================================================================================");
	//Read from the binary file and store into the structure
	while (fread(&displayStaffInfo, sizeof(StaffProfile), 1, fPtr1)) {
		printf("%-7s %-30s %-16s\n", displayStaffInfo.staffID, displayStaffInfo.staffName, displayStaffInfo.address);
		count++;
	}

	printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");
	printf("< %-30s %-2s %d >\n\n", "Total staff's profile record(s)", ":", count);

	reportFooter();

	fclose(fPtr1);
}

void staffListEmployment() {

	StaffProfile displayStaffInfo;

	int count = 0;

	FILE* fPtr1;

	//open for read binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	reportHeader();

	//Print the title
	//display report name
	printf("%88s\n\n", "~~ Staff List - Employment Details ~~");
	printf("%s\n", "=========================================================================================================================================");
	printf("%-7s %-30s %-12s %-12s %-10s %-7s %-35s %-16s\n", "ID", "Name", "Joined", "Department", "Position", "Level", "Email", "Monthly Salary");
	printf("%s\n", "=========================================================================================================================================");
	//Read from the binary file and store into the structure
	while (fread(&displayStaffInfo, sizeof(StaffProfile), 1, fPtr1)) {
		printf("%-7s %-30s %.2d-%.2d-%-6d %-12s %-10s %-7s %-35s %-16.2lf\n", displayStaffInfo.staffID, displayStaffInfo.staffName, displayStaffInfo.joinedDate.day, displayStaffInfo.joinedDate.month, displayStaffInfo.joinedDate.year, displayStaffInfo.department, displayStaffInfo.position, displayStaffInfo.jobLevel, displayStaffInfo.officeEmail, displayStaffInfo.salary);
		count++;
	}
	printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");
	printf("< %-30s %-2s %d >\n\n", "Total staff's profile record(s)", ":", count);

	reportFooter();

	fclose(fPtr1);
}

void staffListEmergency() {

	StaffProfile displayStaffInfo;

	int count = 0;

	FILE* fPtr1;

	//open for read binary file
	fPtr1 = fopen("staff_profile.dat", "rb");

	if (!fPtr1) {
		printf("System cannot open file specified. Please check and retry again.\n");
		exit(-1);
	}

	reportHeader();

	//Print the title
	//display report name
	printf("%90s\n\n", "~~ Staff List - Emergency Contact Details ~~");
	printf("%s\n", "=========================================================================================================================================");
	printf("%-7s %-30s %-25s %-18s %-20s\n", "ID", "Name", "Contact Person", "Contact", "Relationship");
	printf("%s\n", "=========================================================================================================================================");
	//Read from the binary file and store into the structure
	while (fread(&displayStaffInfo, sizeof(StaffProfile), 1, fPtr1)) {
		printf("%-7s %-30s %-25s %-18s %-20s\n", displayStaffInfo.staffID, displayStaffInfo.staffName, displayStaffInfo.emergencyPerson, displayStaffInfo.emergencyPhone, displayStaffInfo.relationship);
		count++;
	}
	printf("\n%s\n", "_________________________________________________________________________________________________________________________________________");
	printf("< %-30s %-2s %d >\n\n", "Total staff's profile record(s)", ":", count);

	reportFooter();

	fclose(fPtr1);
}

//================================================================================================

// - CYS - Program
// - CYS - Club facility management menu
int facilityMgmtMenu() {

	int choice = 0;

	printf("Club Facility Management\n");
	printf("=============================\n");
	printf("1. Club Facility Information\n");
	printf("2. Club Member Information\n");
	printf("3. Club Facility Booking\n");
	printf("4. Club Facility Usage\n");
	printf("5. Back to previous menu\n");
	printf("=============================\n\n");

	printf("Enter your selection : ");
	scanf("%d", &choice);
	rewind(stdin);

	return(choice);

}

void facilityMgmtFunction() {

	int choice = 0, errorCount = 0;

	systemHeader();

	do {
		//calling Display Report Menu & Functions

		choice = facilityMgmtMenu();
		system("cls");

		switch (choice) {
		case 1: facilityInfo(); break;
		case 2: memberInformationMenu(); break;
		case 3: facilityBooking(); break;
		case 4: facilityUsage(); break;
		case 5:	systemHeader(); break;
		default:
			errorCount++;
			if (errorCount >= 5) {
				system("cls");
				systemHeader();
				printf("\nPlease contact the system admin for help !!!!\n");
				exit(-1);
				systemFooter();
			}
			else {
				system("cls");
				systemHeader();
				printf("\nPlease enter the correct menu !!!\n\n");
			}
		}
	} while (choice != 5);

}

// - CYS - Facility Menu
void facilityInfo()
{
	int choice;

	systemHeader();
	printf("%77s\n\n", "** Facility Information Menu **");

	do {
		printf("\n==============================================\n");
		printf("Facility Information\n");
		printf("==============================================\n");
		printf("1. Add Facility\n");
		printf("2. Search Facility\n");
		printf("3. Modify Facility\n");
		printf("4. Display Facility\n");
		printf("5. Remove Facility\n");
		printf("6. Display Report\n");
		printf("7. Return Preview Menu\n");
		printf("==============================================\n");
		printf("Enter your selection: ");
		scanf("%d", &choice);
		rewind(stdin);

		system("cls");
		switch (choice) {
		case 1: addFacilty(); break;
		case 2: searchFacility(); break;
		case 3: modifyFacility(); break;
		case 4: displayFacility(); break;
		case 5: removeFacility(); break;
		case 6: displayFacilityReport(); break;
		case 7: system("cls"); systemHeader(); break;
		default:
			system("cls");
			systemHeader();
			printf("Invalid Choice! Please Enter The Valid Value...");
		}
	} while (choice != 7);
}

// -CYS - Add New Facility
void addFacilty() {
	char choice;
	Facility addFac;
	FILE* fp1;
	fp1 = fopen("facility.txt", "a");
	if (!fp1) {
		printf("Can't find the file 'facility.txt'");
		exit(-1);
	}

	systemHeader();
	printf("%82s\n\n", "** Add Facility Information **");

	do
	{
		printf("The New Facility\n");
		printf("====================\n");
		printf("Facility ID         : ");
		scanf("%s", &addFac.facilityID);
		rewind(stdin);
		printf("Facility Type       : ");
		scanf("%s", &addFac.faciltyType);
		rewind(stdin);
		printf("Facility Description: ");
		scanf("%[^\n]", &addFac.facilityDescription);
		rewind(stdin);
		printf("Venue               : ");
		scanf("%c", &addFac.venue);
		rewind(stdin);
		printf("Venue Description   : ");
		scanf("%[^\n]", &addFac.venueDescription);
		rewind(stdin);
		printf("Max User            : ");
		scanf("%d", &addFac.maxUser);
		rewind(stdin);
		printf("Starting Time       : ");
		scanf("%d", &addFac.startTime);
		rewind(stdin);
		printf("Ending Time         : ");
		scanf("%d", &addFac.endTime);
		rewind(stdin);

		fprintf(fp1, "%s|%s|%s|%c|%s|%d|%d|%d\n\n", addFac.facilityID, addFac.faciltyType, addFac.facilityDescription, addFac.venue, addFac.venueDescription, addFac.maxUser, addFac.startTime, addFac.endTime);

		printf("\nContinue Add Facility? Y/N: ");
		scanf("%c", &choice);
		rewind(stdin);
		printf("\n");
	} while (toupper(choice) != 'N');

	fclose(fp1);
}

// - CYS - Search for local Facility Information
void searchFacility() {
	char facilityIdSearch[6];
	int count = 0, i = 0;

	Facility searchFac[50];

	FILE* fp2;
	fp2 = fopen("facility.txt", "r");
	if (!fp2) {
		printf("Can't find the file 'facility.txt'");
		exit(-1);
	}

	systemHeader();
	printf("%82s\n\n", "** Search Facility Information **");

	printf("Enter Facility ID: ");
	scanf("%s", &facilityIdSearch);
	rewind(stdin);

	printf("\nFacility Information\n\n");
	printf("===========================================================================================================\n");
	printf("%15s %18s %11s %13s %19s %19s\n\n", "Facility ID", "Facility Type", "Venue", "Max User", "Starting Time", "Ending Time");
	printf("===========================================================================================================\n");

	while (fscanf(fp2, "%[^|]|%[^|]|%[^|]|%c|%[^|]|%d|%d|%d\n", &searchFac[i].facilityID, &searchFac[i].faciltyType, &searchFac[i].facilityDescription, &searchFac[i].venue, &searchFac[i].venueDescription, &searchFac[i].maxUser, &searchFac[i].startTime, &searchFac[i].endTime) != EOF)
	{
		if (strcmp(searchFac[i].facilityID, facilityIdSearch) == 0) {
			printf("%11s %18s %13c %12d %17.4d %21.4d\n\n", searchFac[i].facilityID, searchFac[i].faciltyType, searchFac[i].venue, searchFac[i].maxUser, searchFac[i].startTime, searchFac[i].endTime);
			count++;
		}
	}
	printf("===========================================================================================================\n");
	printf("Have %d Record(s)\n", count);
	printf("===========================================================================================================\n");
	fclose(fp2);

	if (facilityIdSearch == 0) {
		printf("No Search Result\n");
	}

}

// - CYS - Modify local Facility Information
void modifyFacility()
{
	char modifyFCode[6], modifyF, moreRecordF, facId[6], facType[7], facDescription[30], facVenue, facVenueDescription[10];
	int modifyFCount = 0, fCount = 0, foundF = 0, modifyIdxF = 0, facMaxUser, facStartTime, facEndTime;

	Facility modifyFac[20];
	FILE* fp3;
	fp3 = fopen("facility.txt", "r");

	if (!fp3) {
		printf("Can't find the file 'facility.txt'.\n\n");
		exit(-1);
	}

	int i = 0;

	while (fscanf(fp3, "%[^|]|%[^|]|%[^|]|%c|%[^|]|%d|%d|%d\n", &modifyFac[i].facilityID, &modifyFac[i].faciltyType, &modifyFac[i].facilityDescription, &modifyFac[i].venue, &modifyFac[i].venueDescription, &modifyFac[i].maxUser, &modifyFac[i].startTime, &modifyFac[i].endTime) != EOF)
		i++;

	fCount = i;

	fclose(fp3);

	systemHeader();
	printf("%82s\n\n", "** Modify Facility Information **");

	do {
		printf("Enter Facility ID: ");
		scanf("%s", &modifyFCode);
		rewind(stdin);

		foundF = 0;
		modifyFCount = 0;


		for (i = 0; i < fCount && foundF == 0; i++) {
			if (strcmp(modifyFCode, modifyFac[i].facilityID) == 0) {
				foundF = 1;

				printf("\nSearch Result\n");
				printf("==============================================\n");
				printf("\nFacility ID             : %s\n", modifyFac[i].facilityID);
				printf("Facility Type           : %s\n", modifyFac[i].faciltyType);
				printf("Facility Description    : %s\n", modifyFac[i].facilityDescription);
				printf("Venue                   : %c\n", modifyFac[i].venue);
				printf("Venue Description       : %s\n", modifyFac[i].venueDescription);
				printf("Max User                : %d\n", modifyFac[i].maxUser);
				printf("Starting Time           : %.4d\n", modifyFac[i].startTime);
				printf("Ending Time             : %.4d\n", modifyFac[i].endTime);
				modifyIdxF = i;

				printf("\nModify Record(s)\n");
				printf("==============================================\n");
				printf("\nFacility ID         : ");
				scanf("%s", &facId);
				rewind(stdin);
				printf("Facility Type       : ");
				scanf("%s", &facType);
				rewind(stdin);
				printf("Facility Description: ");
				scanf("%[^\n]", &facDescription);
				rewind(stdin);
				printf("Venue               : ");
				scanf("%c", &facVenue);
				rewind(stdin);
				printf("Venue Description   : ");
				scanf("%[^\n]", &facVenueDescription);
				rewind(stdin);
				printf("Max User            : ");
				scanf("%d", &facMaxUser);
				rewind(stdin);
				printf("Starting Time       : ");
				scanf("%d", &facStartTime);
				rewind(stdin);
				printf("Ending Time         : ");
				scanf("%d", &facEndTime);
				rewind(stdin);
				printf("==============================================\n");
				printf("\nSure to modify? (Y/N) : ");
				scanf("%c", &modifyF);
				rewind(stdin);

				if (toupper(modifyF) == 'Y') {
					strcpy(modifyFac[modifyIdxF].facilityID, facId);
					strcpy(modifyFac[modifyIdxF].faciltyType, facType);
					strcpy(modifyFac[modifyIdxF].facilityDescription, facDescription);
					modifyFac[modifyIdxF].venue = facVenue;
					strcpy(modifyFac[modifyIdxF].venueDescription, facVenueDescription);
					modifyFac[modifyIdxF].maxUser = facMaxUser;
					modifyFac[modifyIdxF].startTime = facStartTime;
					modifyFac[modifyIdxF].endTime = facEndTime;
					modifyFCount++;
				}

			}

		}

		if (foundF == 2)
			printf("No record was found with the code enter %s\n\n", modifyFCode);
		printf("\nAny more to modify? (Y/N) : ");
		scanf("%c", &moreRecordF);
		rewind(stdin);

	} while (moreRecordF != 'N');

	printf("\n< %d record(s) are modified > \n\n", modifyFCount);

	fp3 = fopen("facility.txt", "w");
	for (i = 0; i < fCount; i++)
		fprintf(fp3, "%s|%s|%s|%c|%s|%d|%.4d|%.4d\n", modifyFac[i].facilityID, modifyFac[i].faciltyType, modifyFac[i].facilityDescription, modifyFac[i].venue, modifyFac[i].venueDescription, modifyFac[i].maxUser, modifyFac[i].startTime, modifyFac[i].endTime);

	fclose(fp3);
}

// - CYS - Display Facility Details
void displayFacility() {
	char displayID[6];
	Facility displayFac;
	FILE* fp4;
	fp4 = fopen("facility.txt", "r");
	if (!fp4) {
		printf("Can't find the file 'facility.txt'\n");
		exit(-1);
	}

	systemHeader();
	printf("%82s\n\n", "** Display Facility Information **");

	printf("=========================================================================================\n");
	printf("%15s %28s %15s %23s\n", "Facility ID", "Facility Description", "Venue", "Venue Desription");
	printf("=========================================================================================\n");


	while (fscanf(fp4, "%[^|]|%[^|]|%[^|]|%c|%[^|]|%d|%d|%d\n", &displayFac.facilityID, &displayFac.faciltyType, &displayFac.facilityDescription, &displayFac.venue, &displayFac.venueDescription, &displayFac.maxUser, &displayFac.startTime, &displayFac.endTime) != EOF) {
		printf("%11s %34s %11c %20s\n", displayFac.facilityID, displayFac.facilityDescription, displayFac.venue, displayFac.venueDescription);
	}
	printf("=========================================================================================\n");
	fclose(fp4);
}

// - CYS - Remove Facility Information
void removeFacility()
{
	char deleteFCode[6], deleteF1, moreFRecord;
	int  deleteFCount = 0, fCount = 0, foundF = 0, deleteIdxF = 0, findF = 0;

	Facility removeFac[50];
	FILE* fp5;

	fp5 = fopen("facility.txt", "r");

	if (!fp5) {
		printf("Can't find the file 'facility.txt'.\n\n");
		exit(-1);
	}

	int i = 0;

	while (fscanf(fp5, "%[^|]|%[^|]|%[^|]|%c|%[^|]|%d|%d|%d\n", &removeFac[i].facilityID, &removeFac[i].faciltyType, &removeFac[i].facilityDescription, &removeFac[i].venue, &removeFac[i].venueDescription, &removeFac[i].maxUser, &removeFac[i].startTime, &removeFac[i].endTime) != EOF)
		i++;

	fCount = i;

	systemHeader();
	printf("%82s\n\n", "** Remove Facility Information **");

	do {

		printf("Enter product code to be modified : ");
		scanf("%[^\n]", &deleteFCode);
		rewind(stdin);

		foundF = 0;
		deleteFCount = 0;


		for (i = 0; i < fCount && foundF == 0; i++) {
			if (strcmp(deleteFCode, removeFac[i].facilityID) == 0)
			{
				foundF = 1;

				printf("\nRecord to be delete : \n");
				printf("==============================================\n");
				printf("\nFacility ID             : %s\n", removeFac[i].facilityID);
				printf("Facility Type           : %s\n", removeFac[i].faciltyType);
				printf("Facility Description    : %s\n", removeFac[i].facilityDescription);
				printf("Venue                   : %c\n", removeFac[i].venue);
				printf("Venue Description       : %s\n", removeFac[i].venueDescription);
				printf("Max User                : %d\n", removeFac[i].maxUser);
				printf("Starting Time           : %.4d\n", removeFac[i].startTime);
				printf("Ending Time             : %.4d\n", removeFac[i].endTime);
				printf("\n==============================================\n");
				deleteIdxF = i;


				printf("\nSure to delete? (Y/N) : ");
				scanf("%c", &deleteF1);
				rewind(stdin);

				if (deleteF1 == 'Y') {
					fCount--;

					for (i = deleteIdxF; i < fCount; i++) {
						strcpy(removeFac[i].facilityID, removeFac[i + 1].facilityID);
						strcpy(removeFac[i].faciltyType, removeFac[i + 1].faciltyType);
						strcpy(removeFac[i].facilityDescription, removeFac[i + 1].facilityDescription);
						removeFac[i].venue, removeFac[i + 1].venue;
						strcpy(removeFac[i].venueDescription, removeFac[i + 1].venueDescription);
						removeFac[i].maxUser = removeFac[i + 1].maxUser;
						removeFac[i].startTime = removeFac[i + 1].startTime;
						removeFac[i].endTime = removeFac[i + 1].endTime;
					}

					deleteFCount++;
				}

			}

		}

		if (foundF == 1)
			printf("No record was found with the code enter %s\n\n", deleteFCode);

		printf("\nAny more to delete? (Y/N) : ");
		scanf("%c", &moreFRecord);
		rewind(stdin);

	} while (moreFRecord != 'N');

	printf("\n< %d record(s) are deleted > \n\n", deleteFCount);

	fp5 = fopen("facility.txt", "w");
	for (i = 0; i < fCount; i++)
		fprintf(fp5, "%s|%s|%s|%c|%s|%d|%.4d|%.4d\n", removeFac[i].facilityID, removeFac[i].faciltyType, removeFac[i].facilityDescription, removeFac[i].venue, removeFac[i].venueDescription, removeFac[i].maxUser, removeFac[i].startTime, removeFac[i].endTime);

	fclose(fp5);

}

// - CYS - Display Existing Facility Information
void displayFacilityReport() {
	Facility displayFac;
	FILE* fp6;
	fp6 = fopen("facility.txt", "r");
	if (!fp6) {
		printf("Can't find the file 'facility.txt'\n");
		exit(-1);
	}
	reportHeader();
	//display report name
	printf("%82s\n\n", "~~ Facility Information Report ~~");

	printf("=========================================================================================================================================\n");
	printf("%13s %16s %26s %12s %14s %14s %17s %13s\n", "Facility ID", "Facility Type", "Facility Description", "Venue", "Venue", "Max", "Starting", "Ending");
	printf("%88s %12s %13s %15s\n\n", "Description", "User", "Time", "Time");
	printf("=========================================================================================================================================\n");


	while (fscanf(fp6, "%[^|]|%[^|]|%[^|]|%c|%[^|]|%d|%d|%d\n", &displayFac.facilityID, &displayFac.faciltyType, &displayFac.facilityDescription, &displayFac.venue, &displayFac.venueDescription, &displayFac.maxUser, &displayFac.startTime, &displayFac.endTime) != EOF) {
		printf("%9s %15s %34s %7c %17s %12d %15.4d %15.4d\n\n", displayFac.facilityID, displayFac.faciltyType, displayFac.facilityDescription, displayFac.venue, displayFac.venueDescription, displayFac.maxUser, displayFac.startTime, displayFac.endTime);
	}
	reportFooter();

	fclose(fp6);
}

//================================================================================================

// - ERIC - Program
// - ERIC - Member menu
void memberInformationMenu() {

	char ch;
	int option = 0, selection = 0, confirmation = 0;

	do {
		system("cls");
		systemHeader();

		printf("=========================================\n");
		printf("-----------Member Information-----------\n");
		printf("=========================================\n");
		printf("\n1.Club Member Profile - Add");
		printf("\n2.Club Member Profile - Search");
		printf("\n3.Club Member Profile - Modify");
		printf("\n4.Club Member Profile - Display");
		printf("\n5.Club Member Profile - Delete Vip");
		printf("\n6.Club Member Profile - Delete Member");
		printf("\n7.Club Member Profile - Report");
		printf("\n8.Return to Previous Menu\n");
		printf("\nPlease select one selection above this to continue the system: ");
		scanf("%d", &selection);
		rewind(stdin);
		if (selection == 1) {
			system("cls");
			option = addUserInformation();
		}
		else if (selection == 2) {
			system("cls");
			option = searchUserInformation();
		}
		else if (selection == 3) {
			system("cls");
			option = modifyUserInformation();
		}
		else if (selection == 4) {
			system("cls");
			option = displayUserInformation();
		}
		else if (selection == 5) {
			system("cls");
			option = deleteVipInformation();
		}
		else if (selection == 6) {
			system("cls");
			option = deleteMemberInformation();
		}
		else if (selection == 7) {
			system("cls");
			option = memberInformationReport();
		}
		else if (selection == 8) {
			do {
				printf("Are you sure you want to exit?(1=Yes 2=No)\n");
				rewind(stdin);
				scanf("%d", &confirmation);
				if (confirmation == 1) {
					system("cls");
					systemHeader();
					option = 2;
				}
				else if (confirmation == 2) {
					option = 1;
					printf("Press enter to continue...");
					scanf("%c", &ch);
					rewind(stdin);
				}
				else {
					system("cls");
					systemHeader();
					printf("Please try again with a correct input...\n");
					printf("Press enter to continue...");
					scanf("%c", &ch);
					rewind(stdin);
				}
			} while (confirmation > 2 || confirmation < 1);
		}
		else {
			printf("Please try again with a correct input...\n");
			printf("Press enter to continue...\n");
			scanf("%c", &ch);
			rewind(stdin);
			option = 1;
		}
	} while (option != 2);

}

int addUserInformation() {
	int option, vipCount = 0, memberCount = 0, newVipCount = 1, newMemberCount = 1, selection, confirmation, check, i = 0, u = 0, valid;
	char ch;

	Membership member, vip;
	FILE* vipUser, * memberUser, * countVip, * countMember;

	countVip = fopen("vipUserfile.dat", "rb");
	countMember = fopen("memberUserfile.dat", "rb");
	do {
		if (countVip == NULL)
		{
			printf("Cannot open vipUserfile.dat!!");
		}
		else {
			while (fread(&vip, sizeof(Membership), 1, countVip))
			{
				vipCount++;
			}
			fclose(countVip);
		}
		if (countMember == NULL)
		{
			printf("Cannot open memberUserfile.dat!!");
		}
		else {
			while (fread(&member, sizeof(Membership), 1, countMember))
			{
				memberCount++;
			}
			fclose(countMember);
		}
		system("cls");
		systemHeader();
		printf("%82s\n\n", "** Member Adding Module **");
		printf("%d user(s) are added in the system\n", vipCount + memberCount);
		printf("Please choose either one to continue...\n");
		printf("1. Vip\n2. Member\n3. Exit\n");
		scanf("%d", &selection);
		rewind(stdin);
		system("cls");
		if (selection == 1) {
			vipUser = fopen("vipUserfile.dat", "ab");
			systemHeader();
			printf("New vip User count . %d\n", newVipCount);
			//vip NAME
			do {
				printf("Please enter the user name\n");
				printf("Name: ");
				scanf("%s", &vip.memberName);
				rewind(stdin);
				check = checkingName(vip.memberName);
			} while (check != 0);
			valid = checkUserAvailable(vip.memberName);
			if (valid == 0) {
				do {
					printf("This input has been registered \n");
					printf("Please try again...\n");
					printf("Name: ");
					scanf("%s", &vip.memberName);
					rewind(stdin);
					check = checkingName(vip.memberName);
					if (check == 1) {
						do {
							printf("Please enter the correct input...\n");
							printf("Name: ");
							scanf("%s", &vip.memberName);
							rewind(stdin);
							check = checkingName(vip.memberName);
						} while (check == 1);
					}
					valid = checkUserAvailable(vip.memberName);
				} while (valid == 0);
			}
			//user GENDER
			do {
				printf("\nPlease enter the user gender\n");
				printf("Gender: ");
				scanf("%[^\n]", &vip.gender);
				rewind(stdin);
				check = checkingGender(vip.gender);
			} while (check != 0);
			//user ID
			do {
				printf("\nPlease enter the user ID(eg.VXXXX)\n");
				printf("ID: ");
				scanf("%s", &vip.memberID);
				rewind(stdin);
				check = checkingVipID(vip.memberID, 6);
			} while (check != 0);
			valid = checkUserAvailable(vip.memberID);
			if (valid == 0) {
				do {
					printf("This input has been registered \n");
					printf("Please try again...\n");
					printf("ID: ");
					scanf("%s", &vip.memberID);
					rewind(stdin);
					check = checkingVipID(vip.memberID, 6);
					if (check == 1) {
						do {
							printf("Please enter the correct input...\n");
							printf("ID: ");
							scanf("%s", &vip.memberID);
							rewind(stdin);
							check = checkingVipID(vip.memberID, 6);
						} while (check == 1);
					}
					valid = checkUserAvailable(vip.memberID);
				} while (valid == 0);
			}
			//user BirthDate
			do
			{
				printf("\nPlease enter the user birth date (xx-xx-xxxx)\n");
				printf("Birth Date: ");
				scanf("%s", &vip.memberBirthDate);
				rewind(stdin);
				check = checkingBirthDate(vip.memberBirthDate, 9);
			} while (check != 0);
			valid = checkUserAvailable(vip.memberBirthDate);
			if (valid == 0) {
				do {
					printf("This input has been registered \n");
					printf("Please try again...\n");
					printf("Birth Date: ");
					scanf("%s", &vip.memberBirthDate);
					rewind(stdin);
					check = checkingBirthDate(vip.memberBirthDate, 9);
					if (check == 1) {
						do {
							printf("Please enter the correct input...\n");
							printf("Birth Date: ");
							scanf("%s", &vip.memberBirthDate);
							check = checkingBirthDate(vip.memberBirthDate, 9);
							rewind(stdin);
						} while (check == 1);
					}
					valid = checkUserAvailable(vip.memberBirthDate);
				} while (valid == 0);
			}
			//user IC
			do
			{
				printf("\nPlease enter the user IC (without 'space' and '-')\n");
				printf("IC: ");
				scanf("%s", &vip.memberIC);
				rewind(stdin);
				check = checkingIC(vip.memberIC, 13);
			} while (check != 0);
			valid = checkUserAvailable(vip.memberIC);
			if (valid == 0) {
				do {
					printf("This input has been registered \n");
					printf("Please try again...\n");
					printf("IC: ");
					scanf("%s", &vip.memberIC);
					rewind(stdin);
					check = checkingIC(vip.memberIC, 13);
					if (check == 1) {
						do {
							printf("Please enter the correct input...\n");
							printf("IC: ");
							scanf("%s", &vip.memberIC);
							rewind(stdin);
							check = checkingIC(vip.memberIC, 13);
						} while (check == 1);
					}
					valid = checkUserAvailable(vip.memberIC);
				} while (valid == 0);
			}
			//user CONTACT NUMBER
			do {
				printf("\nPlease enter the user contact number\n");
				printf("Contact Number: ");
				scanf("%s", &vip.memberContactNum);
				rewind(stdin);
				check = checkingContactNum(vip.memberContactNum, 11);
			} while (check != 0);
			valid = checkUserAvailable(vip.memberContactNum);
			if (valid == 0) {
				do {
					printf("This input has been registered \n");
					printf("Please try again...\n");
					printf("Contact Number: ");
					scanf("%s", &vip.memberContactNum);
					rewind(stdin);
					check = checkingContactNum(vip.memberContactNum, 11);
					if (check == 1) {
						do {
							printf("Please enter the correct input...\n");
							printf("Contact Number: ");
							scanf("%s", &vip.memberContactNum);
							rewind(stdin);
							check =
								checkingContactNum(vip.memberContactNum, 11);
						} while (check == 1);
					}
					valid = checkUserAvailable(vip.memberContactNum);
				} while (valid == 0);
			}
			do {
				system("cls");
				systemHeader();
				printf("==============================================================================================================\n");
				printf("\tName\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
				printf("==============================================================================================================\n");
				printf("\t%-14s%3c\t\t%-16s%-24s%-16s%-20s\n", vip.memberName, toupper(vip.gender[0]), vip.memberID, vip.memberBirthDate, vip.memberIC, vip.memberContactNum);
				printf("\nDo you confirm to add this user in to the system? (1 = Yes 2 = No)");
				scanf("%d", &confirmation);
				rewind(stdin);
				if (confirmation == 1) {
					fwrite(&vip, sizeof(Membership), 1, vipUser);
					vipCount++;
					newVipCount++;
					option = 2;
					fclose(vipUser);
				}
				else if (confirmation == 2) {
					system("cls");
					systemHeader();
					printf("You have cancel to add the user's information to the system...\n");
					fclose(vipUser);
					option = 2;
				}
				else {
					system("cls");
					systemHeader();
					printf("Please try again with a correct input...\n");
					printf("Press enter to continue...\n");
					scanf("%c", &ch);
					rewind(stdin);
					option = 1;
				}
			} while (option != 2);
			printf("\nDo you want to add new user again?(1=Yes 2=No) : ");
			scanf("%d", &option);
			rewind(stdin);
			if (option == 2) {
				return option = 1;
			}
		}
		else if (selection == 2)
		{
			memberUser = fopen("memberUserfile.dat", "ab");
			systemHeader();
			printf("New member User count . %d\n", newMemberCount);
			//member NAME
			do {
				printf("\nPlease enter the user name\n");
				printf("Name: ");
				scanf("%s", &member.memberName);
				rewind(stdin);
				check = checkingName(member.memberName); //check if input is correct
			} while (check != 0); //continue if return 1
			valid = checkUserAvailable(member.memberName); //check if there is registered name
			if (valid == 0) {
				do {
					printf("This input has been registered \n");
					printf("Please try again...\n");
					printf("Name: ");
					scanf("%s", &member.memberName);
					rewind(stdin);
					check = checkingName(member.memberName);
					if (check == 1) {
						do {
							printf("Please enter the correct input...\n");
							printf("Name: ");
							scanf("%s", &member.memberName);
							rewind(stdin);
							check = checkingName(member.memberName);
						} while (check == 1);
					}
					valid = checkUserAvailable(member.memberName);
				} while (valid == 0);
			}
			//member GENDER
			do {
				printf("\nPlease enter the user gender\n");
				printf("Gender: ");
				scanf("%[^\n]", &member.gender);
				rewind(stdin);
				check = checkingGender(member.gender);
			} while (check != 0);
			//member ID
			do {
				printf("\nPlease enter the user ID\n");
				printf("ID: ");
				scanf("%s", &member.memberID);
				rewind(stdin);
				check = checkingMemberID(member.memberID, 6);
			} while (check != 0);
			valid = checkUserAvailable(member.memberID);
			if (valid == 0) {
				do
				{
					printf("This input has been registered \n");
					printf("Please try again...\n");
					printf("ID: ");
					scanf("%s", &member.memberID);
					rewind(stdin);
					check = checkingMemberID(member.memberID, 6);
					if (check == 1) {
						do {
							printf("Please enter the correct input...\n");
							printf("ID: ");
							scanf("%s", &member.memberID);
							rewind(stdin);
							check = checkingMemberID(member.memberID, 6);
						} while (check == 1);
					}
					valid = checkUserAvailable(member.memberID);
				} while (valid == 0);
			}
			//member Birth Date
			do {
				printf("\nPlease enter the user birth date\n");
				printf("Birth Date: ");
				scanf("%s", &member.memberBirthDate);
				rewind(stdin);
				check = checkingBirthDate(&member.memberBirthDate, 9);
			} while (check != 0);
			valid = checkUserAvailable(member.memberBirthDate);
			if (valid == 0) {
				do {
					printf("This input has been registered \n");
					printf("Please try again...\n");
					printf("Birth Date: ");
					scanf("%s", &member.memberBirthDate);
					rewind(stdin);
					check = checkingBirthDate(&member.memberBirthDate, 9);
					if (check == 1) {
						do {
							printf("Please enter the correct input...\n");
							printf("Birth Date: ");
							scanf("%s", &member.memberBirthDate);
							rewind(stdin);
							check = checkingBirthDate(&member.memberBirthDate, 9);
						} while (check == 1);
					}
					valid = checkUserAvailable(member.memberBirthDate);
				} while (valid == 0);
			}
			//member IC
			do {
				printf("\nPlease enter the user IC\n");
				printf("IC: ");
				scanf("%s", &member.memberIC);
				rewind(stdin);
				check = checkingIC(member.memberIC, 13);
			} while (check != 0);
			valid = checkUserAvailable(member.memberIC);
			if (valid == 0) {
				do {
					printf("This input has been registered \n");
					printf("Please try again...\n");
					printf("IC: ");
					scanf("%s", &member.memberIC);
					rewind(stdin);
					check = checkingIC(member.memberIC, 13);
					if (check == 1) {
						do {
							printf("Please enter the correct input...\n");
							printf("IC: ");
							scanf("%s", &member.memberIC);
							rewind(stdin);
							check = checkingIC(member.memberIC, 13);
						} while (check == 1);
					}
					valid = checkUserAvailable(member.memberIC);
				} while (valid == 0);
			}
			//member CONTACT NUMBER
			do {
				printf("\nPlease enter the user contact number\n");
				printf("Contact Number: ");
				scanf("%s", &member.memberContactNum);
				rewind(stdin);
				check = checkingContactNum(member.memberContactNum, 11);
			} while (check != 0);
			valid = checkUserAvailable(member.memberContactNum);
			if (valid == 0) {
				do {
					printf("This input has been registered \n");
					printf("Please try again...\n");
					printf("Contact Number: ");
					scanf("%s", &member.memberContactNum);
					rewind(stdin);
					check = checkingContactNum(member.memberContactNum, 11);
					if (check == 1) {
						do {
							printf("Please enter the correct input...\n");
							printf("Contact Number: ");
							scanf("%s", &member.memberContactNum);
							rewind(stdin);
							check = checkingContactNum(member.memberContactNum, 11);
						} while (check == 1);
					}
					valid = checkUserAvailable(member.memberContactNum);
				} while (valid == 0);
			}
			do {
				system("cls");
				systemHeader();
				printf("==============================================================================================================\n");
				printf("\tName\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
				printf("==============================================================================================================\n");
				printf("\t%-14s%3c\t\t%-16s%-24s%-16s%-20s\n", member.memberName, toupper(member.gender[0]), member.memberID, member.memberBirthDate, member.memberIC, member.memberContactNum);
				printf("\nDo you confirm to add this user in to the system? (1 = Yes 2 = No) : ");
				scanf("%d", &confirmation);
				rewind(stdin);
				if (confirmation == 1) {
					fwrite(&member, sizeof(Membership), 1, memberUser);
					memberCount++;
					newMemberCount++;
					option = 2;
					fclose(memberUser);
				}
				else if (confirmation == 2) {
					system("cls");
					systemHeader();
					printf("You have cancel to add the user's information to the system...\n");
					fclose(memberUser);
					option = 2;
				}
				else {
					system("cls");
					systemHeader();
					printf("Please try again with a correct input...\n");
					printf("Press enter to continue...\n");
					scanf("%c", &ch);
					rewind(stdin);
					option = 1;
				}
			} while (option != 2);
			printf("\nDo you want to add new user again?(1=Yes 2=No) : ");
			scanf("%d", &option);
			rewind(stdin);
			if (option == 2) {
				return option = 1;
			}
		}
		else if (selection == 3)
		{
			do {
				systemHeader();
				printf("Are you sure you want to exit?(1=Yes 2=No)\n");
				scanf("%d", &confirmation);
				rewind(stdin);
				if (confirmation == 1)
					option = 2;
				else if (confirmation == 2) {
					option = 1;
					printf("Press enter to continue...");
					scanf("%c", &ch);
					rewind(stdin);
				}
				else {
					printf("Please try again with a correct input...\n");
					printf("Press enter to continue...");
					scanf("%c", &ch);
					rewind(stdin);
					system("cls");
				}
			} while (confirmation > 2 || confirmation < 1);
		}
		else
		{
			printf("Please try again with a correct input...\n");
			printf("Press enter to continue...\n");
			scanf("%c", &ch);
			rewind(stdin);
			option = 1;
		}
	} while (option != 2);
}

int searchUserInformation() {
	int option = 0, selection, confirmation, check, i, u;
	char ch;

	Membership member[100], vip[100];
	FILE* vipUser, * memberUser;

	do {
		vipUser = fopen("vipUserfile.dat", "rb");
		memberUser = fopen("memberUserfile.dat", "rb");
		systemHeader();
		printf("%82s\n\n", "** Member Search Module **");
		printf("Which type of user do you want to search?\n");
		printf("1.Vip\n");
		printf("2.Member\n");
		printf("3.Exit\n");
		scanf("%d", &selection);
		rewind(stdin);
		if (selection == 1) {
			if (vipUser == NULL) {
				printf("There is no user currently...\n");
				printf("Please try to add some user before searching...\n");
				printf("Please enter to continue..\n");
				scanf("%c", &ch);
				rewind(stdin);
				return 1;
			}
			else {
				do {
					vipUser = fopen("vipUserfile.dat", "rb");
					i = 0;
					system("cls");
					systemHeader();
					printf(" Name\n");
					while (fread(&(vip[i]), sizeof(Membership), 1, vipUser))
					{
						printf("%d. %-23s\n", i + 1, vip[i].memberName);
						i++;
					}
					printf("\n\n%d Vip user(s)' information are stored in the system.\n", i);
					printf("Which Vip user do you want to search? (Please enter the number according the list above)\n");
					scanf("%d", &u);
					rewind(stdin);
					if (u <= i && u > 0) {
						system("cls");
						systemHeader();
						u -= 1;
						printf("==============================================================================================================\n");
						printf("Name\t\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
						printf("==============================================================================================================\n");
						printf("%-22s%3c\t\t%-16s%-24s%-16s%-20s\n", vip[u].memberName, toupper(vip[u].gender[0]), vip[u].memberID, vip[u].memberBirthDate, vip[u].memberIC, vip[u].memberContactNum);
						printf("\n\nPlease enter to continue..\n");
						scanf("%c", &ch);
						rewind(stdin);
						option = 2;
						fclose(vipUser);
					}
					else {
						printf("You have enter the wrong number...\n");
						printf("Please try again...\n");
						printf("Please enter to continue..\n");
						scanf("%c", &ch);
						rewind(stdin);
						option = 1;
					}
				} while (option != 2);
			}
		}
		else if (selection == 2) {
			if (memberUser == NULL) {
				printf("There is no Member user currently...\n");
				printf("Please try to add some user before searching...\n");
				printf("Please enter to continue..\n");
				scanf("%c", &ch);
				rewind(stdin);
				return 1;
			}
			else {
				do {
					memberUser = fopen("memberUserfile.dat", "rb");
					i = 0;
					system("cls");
					systemHeader();
					printf(" Name\n");
					while (fread(&(member[i]), sizeof(Membership), 1, memberUser))
					{
						printf("%d. %-23s\n", i + 1, member[i].memberName);
						i++;
					}
					printf("\n\n%d Member user(s)' information are stored in the system.\n", i);
					printf("Which Member user do you want to search? (Please enter the number according the list above)\n");
					scanf("%d", &u);
					rewind(stdin);
					if (u <= i && u > 0) {
						system("cls");
						u -= 1;
						systemHeader();
						printf("==============================================================================================================\n");
						printf("Name\t\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
						printf("==============================================================================================================\n");
						printf("%-22s%3c\t\t%-16s%-24s%-16s%-20s\n", member[u].memberName, toupper(member[u].gender[0]), member[u].memberID, member[u].memberBirthDate, member[u].memberIC, member[u].memberContactNum);
						printf("\n\nPlease enter to continue..\n");
						scanf("%c", &ch);
						rewind(stdin);
						option = 2;
						fclose(memberUser);
					}
					else {
						printf("You have enter the wrong number...\n");
						printf("Please try again...\n");
						printf("Please enter to continue..\n");
						scanf("%c", &ch);
						rewind(stdin);
						option = 1;
					}
				} while (option != 2);
			}
		}
		else if (selection == 3) {
			do {
				systemHeader();
				printf("Are you sure you want to exit?(1=Yes 2=No)\n");
				scanf("%d", &confirmation);
				rewind(stdin);
				if (confirmation == 1)
				{
					fclose(vipUser);
					fclose(memberUser);
					option = 2;
				}
				else if (confirmation == 2)
				{
					option = 1;
					printf("Press enter to continue...");
					scanf("%c", &ch);
					rewind(stdin);
					system("cls");
					fclose(memberUser);
					fclose(vipUser);
				}
				else
				{
					printf("Please try again with a correct input...\n");
					printf("Press enter to continue...");
					scanf("%c", &ch);
					rewind(stdin);
					system("cls");
				}
			} while (confirmation > 2 || confirmation < 1);
		}
		else
		{
			printf("Please try again with a correct input...\n");
			printf("Press enter to continue...\n");
			scanf("%c", &ch);
			rewind(stdin);
			option = 1;
		}
	} while (option != 2);
}

int modifyUserInformation()
{
	int option = 0, selection, confirmation, check, i, u, valid, index;
	char ch;

	Membership member[100], vip[100];
	FILE* vipUser, * memberUser, * writeUser;

	do {
		vipUser = fopen("vipUserfile.dat", "rb");
		memberUser = fopen("memberUserfile.dat", "rb");
		systemHeader();
		printf("%82s\n\n", "** Member Modification Module **");
		printf("Which type of user do you want to modify?\n");
		printf("1.Vip\n");
		printf("2.Member\n");
		printf("3.Exit\n");
		scanf("%d", &selection);
		rewind(stdin);
		if (selection == 1) {
			if (vipUser == NULL) {
				printf("There is no user currently...\n");
				printf("Please try to add some user before modify...\n");
				printf("Please enter to continue..\n");
				scanf("%c", &ch);
				rewind(stdin);
				return 1;
			}
			else {
				do {
					vipUser = fopen("vipUserfile.dat", "rb");
					i = 0;
					system("cls");
					systemHeader();
					printf(" Name\n");
					while (fread(&(vip[i]), sizeof(Membership), 1, vipUser))
					{
						printf("%d. %-23s\n", i + 1, vip[i].memberName);
						i++;
					}
					printf("\n\n%d Vip user(s)' information are stored in the system.\n", i);
					printf("Which Vip user do you want to modify? (Please enter the number according the list above)\n");
					scanf("%d", &u);
					rewind(stdin);
					index = 0;
					if (u <= i && u > 0) {
						u -= 1;
						writeUser = fopen("vipUserfile.dat", "wb");
						while (index != i)
						{
							if (u != index) {
								fwrite(&vip[index], sizeof(Membership), 1, writeUser);
							}
							index++;
						}
						fclose(writeUser);
						system("cls");
						systemHeader();
						printf("==============================================================================================================\n");
						printf("Name\t\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
						printf("==============================================================================================================\n");
						printf("%-22s%3c\t\t%-16s%-24s%-16s%-20s\n", vip[u].memberName, toupper(vip[u].gender[0]), vip[u].memberID, vip[u].memberBirthDate, vip[u].memberIC, vip[u].memberContactNum);
						//user NAME
						do {
							printf("Please enter the user name\n");
							printf("Name: ");
							scanf("%s", &vip[u].memberName);
							rewind(stdin);
							check = checkingName(vip[u].memberName);
						} while (check != 0);
						valid = checkUserAvailable(vip[u].memberName);
						if (valid == 0) {
							do {
								printf("This input has been registered \n");
								printf("Please try again...\n");
								printf("Name: ");
								scanf("%s", &vip[u].memberName);
								rewind(stdin);
								check = checkingName(vip[u].memberName);
								if (check == 1) {
									do {
										printf("Please enter the correct input...\n");
										printf("Name: ");
										scanf("%s", &vip[u].memberName);
										rewind(stdin);
										check = checkingName(vip[u].memberName);
									} while (check == 1);
								}
								valid = checkUserAvailable(vip[u].memberName);
							} while (valid == 0);
						}
						//user GENDER
						do {
							printf("\nPlease enter the user gender(M=Male F = Female)\n");
							printf("Gender: ");
							scanf("%[^\n]", &vip[u].gender);
							rewind(stdin);
							check = checkingGender(vip[u].gender);
						} while (check != 0);
						//user ID
						do {
							printf("\nPlease enter the user ID(eg.VXXXX)\n");
							printf("ID: ");
							scanf("%s", &vip[u].memberID);
							rewind(stdin);
							check = checkingVipID(vip[u].memberID, 6);
						} while (check != 0);
						valid = checkUserAvailable(vip[u].memberID);
						if (valid == 0) {
							do {
								printf("This input has been registered \n");
								printf("Please try again...\n");
								printf("ID: ");
								scanf("%s", &vip[u].memberID);
								rewind(stdin);
								check = checkingVipID(vip[u].memberID, 6);
								if (check == 1) {
									do {
										printf("Please enter the correct input...\n");
										printf("ID: ");
										scanf("%s", &vip[u].memberID);
										rewind(stdin);
										check = checkingVipID(vip[u].memberID, 6);
									} while (check == 1);
								}
								valid = checkUserAvailable(vip[u].memberID);
							} while (valid == 0);
						}
						//user Birth Date
						do {
							printf("\nPlease enter the user birth date (xx-xx-xxxx)\n");
							printf("Birth Date: ");
							scanf("%s", &vip[u].memberBirthDate);
							rewind(stdin);
							check = checkingBirthDate(vip[u].memberBirthDate, 9);
						} while (check != 0);
						valid = checkUserAvailable(vip[u].memberBirthDate);
						if (valid == 0) {
							do {
								printf("This input has been registered \n");
								printf("Please try again...\n");
								printf("Birth Date: ");
								scanf("%s", &vip[u].memberBirthDate);
								rewind(stdin);
								check = checkingBirthDate(vip[u].memberBirthDate, 9);
								if (check == 1) {
									do {
										printf("Please enter the correct input...\n");
										printf("Birth Date: ");
										scanf("%s", &vip[u].memberBirthDate);
										rewind(stdin);
										check = checkingBirthDate(vip[u].memberBirthDate, 9);
									} while (check == 1);
								}
								valid = checkUserAvailable(vip[u].memberBirthDate);
							} while (valid == 0);
						}
						//user IC
						do {
							printf("\nPlease enter the user IC\n");
							printf("IC: ");
							scanf("%s", &vip[u].memberIC);
							rewind(stdin);
							check = checkingIC(vip[u].memberIC, 13);
						} while (check != 0);
						valid = checkUserAvailable(vip[u].memberIC);
						if (valid == 0) {
							do {
								printf("This input has been registered \n");
								printf("Please try again...\n");
								printf("IC: ");
								scanf("%s", &vip[u].memberIC);
								rewind(stdin);
								check = checkingIC(vip[u].memberIC, 13);
								if (check == 1) {
									do {
										printf("Please enter the correct input...\n");
										printf("IC: ");
										scanf("%s", &vip[u].memberIC);
										rewind(stdin);
										check = checkingIC(vip[u].memberIC, 13);
									} while (check == 1);
								}
								valid = checkUserAvailable(vip[u].memberIC);
							} while (valid == 0);
						}
						//user CONTACT NUMBER
						do {
							printf("\nPlease enter the user contact number\n");
							printf("Contact Number: ");
							scanf("%s", &vip[u].memberContactNum);
							rewind(stdin);
							check = checkingContactNum(vip[u].memberContactNum, 11);
						} while (check != 0);
						valid = checkUserAvailable(vip[u].memberContactNum);
						if (valid == 0) {
							do {
								printf("This input has been registered \n");
								printf("Please try again...\n");
								printf("Contact Number: ");
								scanf("%s", &vip[u].memberContactNum);
								rewind(stdin);
								check = checkingContactNum(vip[u].memberContactNum, 11);
								if (check == 1) {
									do {
										printf("Please enter the correct input...\n");
										printf("Contact Number: ");
										scanf("%s", &vip[u].memberContactNum);
										rewind(stdin);
										check = checkingContactNum(vip[u].memberContactNum, 11);
									} while (check == 1);
								}
								valid = checkUserAvailable(vip[u].memberContactNum);
							} while (valid == 0);
						}
						do {
							system("cls");
							systemHeader();
							printf("==============================================================================================================\n");
							printf("\tName\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
							printf("==============================================================================================================\n");
							printf("\t%-14s%3c\t\t%-16s%-24s%-16s%-20s\n", vip[u].memberName, toupper(vip[u].gender[0]), vip[u].memberID, vip[u].memberBirthDate, vip[u].memberIC, vip[u].memberContactNum);
							printf("Do you confirm to modify this user in to the system ? (1 = Yes 2 = No) : ");
							scanf("%d", &confirmation);
							rewind(stdin);
							if (confirmation == 1) {
								writeUser = fopen("vipUserfile.dat", "wb");
								u = 0;
								while (u != i)
								{
									fwrite(&vip[u],
										sizeof(Membership), 1, writeUser);
									u++;
								}
								option = 2;
								fclose(writeUser);
							}
							else if (confirmation == 2) {
								system("cls");
								systemHeader();
								printf("You have cancel to modify the user's information to the system...\n");
								option = 2;
							}
							else {
								system("cls");
								systemHeader();
								printf("Please try again with a correct input...\n");
								printf("Press enter to continue...\n");
								scanf("%c", &ch);
								rewind(stdin);
								option = 1;
							}
						} while (option != 2);
						printf("Do you want to modify user again?(1=Yes 2 = No)\n");
						scanf("%d", &option);
						rewind(stdin);
						if (option == 2) {
							fclose(vipUser);
							return option = 1;
						}
					}
					else {
						printf("You have enter the wrong number...\n");
						printf("Please try again...\n");
						printf("Please enter to continue..\n");
						scanf("%c", &ch);
						rewind(stdin);
						option = 1;
					}
				} while (option != 2);
			}
		}
		else if (selection == 2) {
			if (memberUser == NULL) {
				printf("There is no Member user currently...\n");
				printf("Please try to add some user before searching...\n");
				printf("Please enter to continue..\n");
				scanf("%c", &ch);
				rewind(stdin);
				return 1;
			}
			else {
				do {
					memberUser = fopen("memberUserfile.dat", "rb");
					i = 0;
					system("cls");
					systemHeader();
					printf(" Name\n");
					while (fread(&(member[i]), sizeof(Membership), 1, memberUser))
					{
						printf("%d. %-23s\n", i + 1,
							member[i].memberName);
						i++;
					}
					printf("\n\n%d Member user(s)' information are stored in the system.\n", i);
					printf("Which Member user do you want to modify? (Please enter the number according the list above)\n");
					scanf("%d", &u);
					rewind(stdin);
					index = 0;
					if (u <= i && u > 0)
					{
						u -= 1;
						writeUser = fopen("memberUserfile.dat", "wb");
						while (index != i)
						{
							if (u != index)
							{
								fwrite(&member[index],
									sizeof(Membership), 1, writeUser);
							}
							index++;
						}
						fclose(writeUser);
						system("cls");
						systemHeader();
						printf("==============================================================================================================\n");
						printf("Name\t\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
						printf("==============================================================================================================\n");
						printf("%-22s%3c\t\t%-16s%-24s%-16s%-20s\n\n", member[u].memberName, toupper(member[u].gender[0]), member[u].memberID, member[u].memberBirthDate, member[u].memberIC, member[u].memberContactNum);
						//user NAME
						do {
							printf("Please enter the user name\n");
							printf("Name: ");
							scanf("%s", &member[u].memberName);
							rewind(stdin);
							check = checkingName(member[u].memberName);
						} while (check != 0);
						valid = checkUserAvailable(member[u].memberName);
						if (valid == 0) {
							do {
								printf("This input has been registered \n");
								printf("Please try again...\n");
								printf("Name: ");
								scanf("%s", &member[u].memberName);
								rewind(stdin);
								check = checkingName(member[u].memberName);
								if (check == 1) {
									do {
										printf("Please enter the correct input...\n");
										printf("Name: ");
										scanf("%s", &member[u].memberName);
										rewind(stdin);
										check = checkingName(member[u].memberName);
									} while (check == 1);
								}
								valid = checkUserAvailable(member[u].memberName);
							} while (valid == 0);
						}
						//user GENDER
						do {
							printf("\nPlease enter the user gender(M=Male F = Female)\n");
							printf("Gender: ");
							scanf("%[^\n]", &member[u].gender);
							rewind(stdin);
							check = checkingGender(member[u].gender);
						} while (check != 0);
						//user ID
						do {
							printf("\nPlease enter the user ID(eg.MXXXX)\n");
							printf("ID: ");
							scanf("%s", &member[u].memberID);
							rewind(stdin);
							check = checkingMemberID(member[u].memberID, 6);
						} while (check != 0);
						valid = checkUserAvailable(member[u].memberID);
						if (valid == 0) {
							do {
								printf("This input has been registered \n");
								printf("Please try again...\n");
								printf("ID: ");
								scanf("%s", &member[u].memberID);
								rewind(stdin);
								check = checkingMemberID(member[u].memberID, 6);
								if (check == 1) {
									do {
										printf("Please enter the correct input...\n");
										printf("ID: ");
										scanf("%s", &member[u].memberID);
										rewind(stdin);
										check = checkingMemberID(member[u].memberID, 6);
									} while (check == 1);
								}
								valid = checkUserAvailable(member[u].memberID);
							} while (valid == 0);
						}
						//user Birth Date
						do {
							printf("\nPlease enter the user birth date (xx-xx-xxxx)\n");
							printf("Birth Date: ");
							scanf("%s", &member[u].memberBirthDate);
							rewind(stdin);
							check = checkingBirthDate(member[u].memberBirthDate, 9);
						} while (check != 0);
						valid = checkUserAvailable(member[u].memberBirthDate);
						if (valid == 0) {
							do {
								printf("This input has been registered \n");
								printf("Please try again...\n");
								printf("Birth Date: ");
								scanf("%s", &member[u].memberBirthDate);
								rewind(stdin);
								check = checkingBirthDate(member[u].memberBirthDate, 9);
								if (check == 1) {
									do {
										printf("Please enter the correct input...\n");
										printf("BirthDate: ");
										scanf("%s", &member[u].memberBirthDate);
										rewind(stdin);
										check = checkingBirthDate(member[u].memberBirthDate, 9);
									} while (check == 1);
								}
								valid = checkUserAvailable(member[u].memberBirthDate);
							} while (valid == 0);
						}
						//user IC
						do {
							printf("\nPlease enter the user IC (without 'space' and '-')\n");
							printf("IC: ");
							scanf("%s", &member[u].memberIC);
							rewind(stdin);
							check = checkingIC(member[u].memberIC, 13);
						} while (check == 1);
						valid = checkUserAvailable(member[u].memberIC);
						if (valid == 0) {
							do {
								printf("This input has been registered \n");
								printf("Please try again...\n");
								printf("IC: ");
								scanf("%s", &member[u].memberIC);
								rewind(stdin);
								check = checkingIC(member[u].memberIC, 13);
								if (check == 1) {
									do {
										printf("Please enter the correct input...\n");
										printf("IC: ");
										scanf("%s", &member[u].memberIC);
										rewind(stdin);
										check = checkingIC(member[u].memberIC, 13);
									} while (check == 1);
								}
								valid = checkUserAvailable(member[u].memberIC);
							} while (valid == 0);
						}
						//user CONTACT NUMBER
						do {
							printf("\nPlease enter the user contact number\n");
							printf("Contact Number: ");
							scanf("%s", member[u].memberContactNum);
							rewind(stdin);
							check = checkingContactNum(member[u].memberContactNum, 11);
						} while (check != 0);
						valid = checkUserAvailable(member[u].memberContactNum);
						if (valid == 0) {
							do {
								printf("This input has been registered \n");
								printf("Please try again...\n");
								printf("Contact Number: ");
								scanf("%s", member[u].memberContactNum);
								rewind(stdin);
								check = checkingContactNum(member[u].memberContactNum, 11);
								if (check == 1) {
									do {
										printf("Please enter the correct input...\n");
										printf("Contact Number: ");
										scanf("%s", member[u].memberContactNum);
										rewind(stdin);
										check = checkingContactNum(member[u].memberContactNum, 11);
									} while (check == 1);
								}
								valid = checkUserAvailable(member[u].memberContactNum);
							} while (valid == 0);
						}
						do {
							system("cls");
							systemHeader();
							printf("==============================================================================================================\n");
							printf("\tName\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
							printf("==============================================================================================================\n");
							printf("\t%-14s%3c\t\t%-16s%-24s%-16s%-20s\n", member[u].memberName, toupper(member[u].gender[0]), member[u].memberID, member[u].memberBirthDate, member[u].memberIC, member[u].memberContactNum);
							printf("Do you confirm to modify this user in to the system ? (1 = Yes 2 = No) : ");
							scanf("%d", &confirmation);
							rewind(stdin);
							if (confirmation == 1) {
								writeUser = fopen("memberUserfile.dat", "wb");
								u = 0;
								while (u != i)
								{
									fwrite(&member[u], sizeof(Membership), 1, writeUser);
									u++;
								}
								option = 2;
								fclose(writeUser);
							}
							else if (confirmation == 2) {
								system("cls");
								systemHeader();
								printf("You have cancel to modify the user's information to the system...\n");
								option = 2;
							}
							else {
								system("cls");
								systemHeader();
								printf("Please try again with a correct input...\n");
								printf("Press enter to continue...\n");
								scanf("%c", &ch);
								rewind(stdin);
								option = 1;
							}
						} while (option != 2);
						printf("Do you want to modify user again?(1=Yes 2 = No)\n");
						scanf("%d", &option);
						rewind(stdin);
						if (option == 2) {
							fclose(memberUser);
							return option = 1;
						}
					}
					else {
						printf("You have enter the wrong number...\n");
						printf("Please try again...\n");
						printf("Please enter to continue..\n");
						scanf("%c", &ch);
						rewind(stdin);
						option = 1;
					}
				} while (option != 2);
			}
		}
		else if (selection == 3) {
			do {
				system("cls");
				systemHeader();
				printf("Are you sure you want to exit?(1=Yes 2=No)\n");
				scanf("%d", &confirmation);
				rewind(stdin);
				if (confirmation == 1) {
					fclose(vipUser);
					fclose(memberUser);
					option = 2;
				}
				else if (confirmation == 2) {
					option = 1;
					system("cls");
					systemHeader();
					printf("Press enter to continue...");
					scanf("%c", &ch);
					rewind(stdin);
					system("cls");
					fclose(memberUser);
					fclose(vipUser);
				}
				else {
					system("cls");
					systemHeader();
					printf("Please try again with a correct input...\n");
					printf("Press enter to continue...");
					scanf("%c", &ch);
					rewind(stdin);
					system("cls");
				}
			} while (confirmation > 2 || confirmation < 1);
		}
		else {
			system("cls");
			systemHeader();
			printf("Please try again with a correct input...\n");
			printf("Press enter to continue...\n");
			scanf("%c", &ch);
			rewind(stdin);
			option = 1;
		}
	} while (option != 2);
}

int displayUserInformation()
{
	int option = 0, i = 0, selection, confirmation;
	char ch;

	Membership member[100], vip[100];
	FILE* vipUser, * memberUser;
	do {
		vipUser = fopen("vipUserfile.dat", "rb");
		memberUser = fopen("memberUserfile.dat", "rb");
		systemHeader();
		printf("%82s\n\n", "** Member Detail Display **");
		printf("Which type of user do you want to display?\n");
		printf("1.Vip\n");
		printf("2.Member\n");
		printf("3.Exit\n");
		scanf("%d", &selection);
		rewind(stdin);
		if (selection == 1) {
			if (vipUser == NULL) {
				printf("There is no user currently...\n");
				printf("Please try to add some user before displaying...\n");
				printf("Please enter to continue..\n");
				scanf("%c", &ch);
				rewind(stdin);
				return 1;
			}
			else {
				printf("======================================================================================================\n");
				printf(" Name\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
				printf("======================================================================================================\n");
				while (fread(&(vip[i]), sizeof(Membership), 1, vipUser))
				{
					printf("%d. %-13s%c\t\t%-16s%-24s%-16s%-20s\n", i + 1, vip[i].memberName, toupper(vip[i].gender[0]), vip[i].memberID, vip[i].memberBirthDate, vip[i].memberIC, vip[i].memberContactNum);
					i++;
				}
				printf("\n\n%d Vip user(s)' information are stored in the system.\n", i);
				printf("Please enter to continue..\n");
				scanf("%c", &ch);
				rewind(stdin);
				option = 2;
				fclose(vipUser);
			}
		}
		else if (selection == 2) {
			if (memberUser == NULL) {
				printf("There is no Member user currently...\n");
				printf("Please try to add some user before displaying...\n");
				printf("Please enter to continue..\n");
				scanf("%c", &ch);
				rewind(stdin);
				return 1;
			}
			else {
				printf("======================================================================================================\n");
				printf(" Name\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
				printf("======================================================================================================\n");
				while (fread(&(member[i]), sizeof(Membership), 1, memberUser))
				{
					printf("%d. %-13s%c\t\t%-16s%-24s%-16s%-20s\n", i + 1, member[i].memberName, toupper(member[i].gender[0]), member[i].memberID, member[i].memberBirthDate, member[i].memberIC, member[i].memberContactNum);
					i++;
				}
				printf("\n\n%d Member user(s)' information are stored in the system.\n", i);
				printf("Please enter to continue..\n");
				scanf("%c", &ch);
				rewind(stdin);
				option = 2;
				fclose(memberUser);
			}
		}
		else if (selection == 3) {
			do {
				printf("Are you sure you want to exit?(1=Yes 2=No)\n");
				scanf("%d", &confirmation);
				rewind(stdin);
				if (confirmation == 1) {
					fclose(vipUser);
					fclose(memberUser);
					option = 2;
				}
				else if (confirmation == 2) {
					option = 1;
					printf("Press enter to continue...");
					scanf("%c", &ch);
					rewind(stdin);
					fclose(memberUser);
					fclose(vipUser);
				}
				else {
					printf("Please try again with a correct input...\n");
					printf("Press enter to continue...");
					scanf("%c", &ch);
					rewind(stdin);
					system("cls");
				}
			} while (confirmation > 2 || confirmation < 1);
		}
		else {
			printf("Please try again with a correct input...\n");
			printf("Press enter to continue...\n");
			scanf("%c", &ch);
			rewind(stdin);
			option = 1;
		}
	} while (option != 2);
}

// - ERIC - Member delete
int deleteVipInformation() {
	Membership removeMemberInfo[50];
	Booking book[100];

	char deleteCode[6], delete1, moreRecord;
	int   i = 0, deleteCount = 0, pCount = 0, bCount = 0, found = 0, deleteIdx = 0, find = 0, noFound = 0, bookFound = 0;// Initialize the count before modifcation starts
	//char confirm;

	FILE* vipUser, * booking;

	vipUser = fopen("vipUserfile.dat", "rb");
	booking = fopen("booking.dat", "rb");

	if (vipUser == NULL) {
		printf("Cannot open vipUserfile.dat!!");
		exit(-1);
	}
	if (booking == NULL) {
		printf("Cannot open booking.dat!!");
		exit(-1);
	}

	while (fread(&removeMemberInfo[i], sizeof(removeMemberInfo[i]), 1, vipUser) && i < 50)
		i++;

	pCount = i;

	fclose(vipUser);

	i = 0;

	while (fread(&book[i], sizeof(book[i]), 1, booking) && i < 100)
		i++;

	bCount = i;

	fclose(booking);


	do {
		system("cls");
		systemHeader();
		printf("Enter VIP Member ID to be deleted : ");
		scanf("%[^\n]", &deleteCode);
		rewind(stdin);

		found = 0;// Initialize a value when nothing is found
		deleteCount = 0;

		// Loop as long as less than pCount and not found the code
		for (i = 0; i < pCount && found == 0; i++) {
			if (strcmp(deleteCode, removeMemberInfo[i].memberID) == 0) { // to match the code user entered with the code from array
				found = 1;// use to stop the loop to continue searching when record matched

				//Display the record found
				printf("\n%-30s\n", "-------------------------------");
				printf("%-30s\n", "Member Profile To Be Removed");
				printf("%-30s\n", "_____");
				printf("%-30s %s\n", "Member name: ", removeMemberInfo[i].memberName);
				printf("%-30s %s\n", "Member Gender: ", removeMemberInfo[i].gender);
				printf("%-30s %s\n", "Member ID: ", removeMemberInfo[i].memberID);
				printf("%-30s %s\n", "Member Date of birth: ", removeMemberInfo[i].memberBirthDate);
				printf("%-30s %s\n", "Member IC number: ", removeMemberInfo[i].memberIC);
				printf("%-30s %s\n", "Member Contact number: ", removeMemberInfo[i].memberContactNum);

				deleteIdx = i;

				printf("Sure to delete? (Y/N) : ");
				scanf("%c", &delete1);
				rewind(stdin);



				if (delete1 == 'Y') {
					pCount--;

					for (i = deleteIdx; i <= pCount; i++) {

						//delete function
						strcpy(removeMemberInfo[i].memberName, removeMemberInfo[i + 1].memberName);
						strcpy(removeMemberInfo[i].gender, removeMemberInfo[i + 1].gender);
						strcpy(removeMemberInfo[i].memberID, removeMemberInfo[i + 1].memberID);
						strcpy(removeMemberInfo[i].memberBirthDate, removeMemberInfo[i + 1].memberBirthDate);
						strcpy(removeMemberInfo[i].memberIC, removeMemberInfo[i + 1].memberIC);
						strcpy(removeMemberInfo[i].memberContactNum, removeMemberInfo[i + 1].memberContactNum);

						deleteCount++;
					}

					//delete multiple records from file
					do {

						bookFound = 0;

						for (i = 0; i < bCount && bookFound == 0 && noFound == 0; i++)
							if (strcmp(deleteCode, book[i].member.memberID) == 0) { //if found the member id that entered by the user is same in the file
								bookFound = 1; // found = 1
								deleteIdx = i; // deleteIdx = i
								bCount--; //bCount
							}
							else {
								noFound = 1;
							}
						

						if (bookFound == 1)
							for (i = deleteIdx; i < bCount; i++) {
								//delete function
								strcpy(book[i].bookingId, book[i + 1].bookingId);
								strcpy(book[i].fac.facilityID, book[i + 1].fac.facilityID);
								strcpy(book[i].emp.staffName, book[i + 1].emp.staffName);
								strcpy(book[i].emp.staffID, book[i + 1].emp.staffID);
								book[i].date.day = book[i + 1].date.day;
								book[i].date.month = book[i + 1].date.month;
								book[i].date.year = book[i + 1].date.year;
								book[i].time.startHours = book[i + 1].time.startHours;
								book[i].time.startMin = book[i + 1].time.startMin;
								book[i].time.endHours = book[i + 1].time.endHours;
								book[i].time.endMin = book[i + 1].time.endMin;
								strcpy(book[i].remarks, book[i + 1].remarks);
								strcpy(book[i].member.memberID, book[i + 1].member.memberID);
								book[i].numOfPax = book[i + 1].numOfPax;
						}

						if(noFound == 0)
							for (i = 0; i < bCount && found == 1; i++)
								if (strcmp(deleteCode, book[i].member.memberID) == 0) { //if found the member id that entered by the user is same in the file
									bookFound = 0; //found = 0
								}

					} while (bookFound == 0 && noFound == 0); //continue loop when found = 0 or noFound = 0

				}
			}
		}

		if (found == 0) {
			printf("\n%s\n", "Error message:");
			printf("No record was found with the entered Member ID %s.\n", deleteCode);
			printf("%s\n", "Please proceed to enter valid Member ID.");
		}

		printf("Any more to delete? (Y/N) : ");
		scanf("%c", &moreRecord);
		rewind(stdin);

	} while (moreRecord != 'N');

	printf("\n%s\n", "_________________");
	printf("< %-30s %-2s %d >\n\n", "Total member's profile record(s) deleted", ":", deleteCount);

	//Write all the records from array back to file
	vipUser = fopen("vipUserfile.dat", "wb");// open the file for writing to put all records from array into file
	for (i = 0; i < pCount; i++)
		fwrite(&removeMemberInfo[i], sizeof(removeMemberInfo[i]), 1, vipUser);

	fclose(vipUser);

	booking = fopen("booking.dat", "wb");
	for (i = 0; i < bCount; i++)
		fwrite(&book[i], sizeof(book[i]), 1, booking);

	fclose(booking);
}

int deleteMemberInformation() {
	Membership removeMemberInfo[50];
	Booking book[100];

	char deleteCode[6], delete1, moreRecord;
	int   i = 0, deleteCount = 0, pCount = 0, bCount = 0, found = 0, deleteIdx = 0, find = 0;// Initialize the count before modifcation starts
	//char confirm;

	FILE* memberUser, * booking;

	memberUser = fopen("memberUserfile.dat", "rb");
	booking = fopen("booking.dat", "rb");

	if (memberUser == NULL) {
		printf("Cannot open memberUserfile.dat!!");
		exit(-1);
	}
	if (booking == NULL) {
		printf("Cannot open booking.dat!!");
		exit(-1);
	}

	while (fread(&removeMemberInfo[i], sizeof(removeMemberInfo[i]), 1, memberUser) && i < 50)
		i++;

	pCount = i;

	fclose(memberUser);

	i = 0;

	while (fread(&book[i], sizeof(book[i]), 1, booking) && i < 100)
		i++;

	bCount = i;

	fclose(booking);


	do {
		system("cls");
		systemHeader();

		printf("Enter Member ID to be deleted : ");
		scanf("%[^\n]", &deleteCode);
		rewind(stdin);

		found = 0;// Initialize a value when nothing is found
		deleteCount = 0;

		// Loop as long as less than pCount and not found the code
		for (i = 0; i < pCount && found == 0; i++) {
			if (strcmp(deleteCode, removeMemberInfo[i].memberID) == 0) { // to match the code user entered with the code from array
				found = 1;// use to stop the loop to continue searching when record matched

				//Display the record found
				printf("\n%-30s\n", "-------------------------------");
				printf("%-30s\n", "Member Profile To Be Removed");
				printf("%-30s\n", "_____");
				printf("%-30s %s\n", "Member name: ", removeMemberInfo[i].memberName);
				printf("%-30s %s\n", "Member Gender: ", removeMemberInfo[i].gender);
				printf("%-30s %s\n", "Member ID: ", removeMemberInfo[i].memberID);
				printf("%-30s %s\n", "Member Date of birth: ", removeMemberInfo[i].memberBirthDate);
				printf("%-30s %s\n", "Member IC number: ", removeMemberInfo[i].memberIC);
				printf("%-30s %s\n", "Member Contact number: ", removeMemberInfo[i].memberContactNum);

				deleteIdx = i;

				printf("Sure to delete? (Y/N) : ");
				scanf("%c", &delete1);
				rewind(stdin);



				if (delete1 == 'Y') {
					pCount--;

					for (i = deleteIdx; i < pCount; i++) {

						//delete function
						strcpy(removeMemberInfo[i].memberName, removeMemberInfo[i + 1].memberName);
						strcpy(removeMemberInfo[i].gender, removeMemberInfo[i + 1].gender);
						strcpy(removeMemberInfo[i].memberID, removeMemberInfo[i + 1].memberID);
						strcpy(removeMemberInfo[i].memberBirthDate, removeMemberInfo[i + 1].memberBirthDate);
						strcpy(removeMemberInfo[i].memberIC, removeMemberInfo[i + 1].memberIC);
						strcpy(removeMemberInfo[i].memberContactNum, removeMemberInfo[i + 1].memberContactNum);


						deleteCount++;
					}

					//delete multiple records from file
					do {

						found = 0;

						for (i = 0; i < bCount && found == 0; i++)
							if (strcmp(deleteCode, book[i].member.memberID) == 0) { //if found the member id that entered by the user is same in the file
								found = 1; // found = 1
								deleteIdx = i; // deleteIdx = i
								bCount--; //bCount
							}

						for (i = deleteIdx; i < bCount; i++) {
							//delete function
							strcpy(book[i].bookingId, book[i + 1].bookingId);
							strcpy(book[i].fac.facilityID, book[i + 1].fac.facilityID);
							strcpy(book[i].emp.staffName, book[i + 1].emp.staffName);
							strcpy(book[i].emp.staffID, book[i + 1].emp.staffID);
							book[i].date.day = book[i + 1].date.day;
							book[i].date.month = book[i + 1].date.month;
							book[i].date.year = book[i + 1].date.year;
							book[i].time.startHours = book[i + 1].time.startHours;
							book[i].time.startMin = book[i + 1].time.startMin;
							book[i].time.endHours = book[i + 1].time.endHours;
							book[i].time.endMin = book[i + 1].time.endMin;
							strcpy(book[i].remarks, book[i + 1].remarks);
							strcpy(book[i].member.memberID, book[i + 1].member.memberID);
							book[i].numOfPax = book[i + 1].numOfPax;

						}

						for (i = 0; i < bCount && found == 1; i++)
							if (strcmp(deleteCode, book[i].member.memberID) == 0) { //if found the member id that entered by the user is same in the file
								found = 0; //found = 0
							}

					} while (found == 0); //continue loop when found = 0

				}
			}
		}

		if (found == 0) {
			printf("\n%s\n", "Error message:");
			printf("No record was found with the entered Member ID %s.\n", deleteCode);
			printf("%s\n", "Please proceed to enter valid Member ID.");
		}

		printf("Any more to delete? (Y/N) : ");
		scanf("%c", &moreRecord);
		rewind(stdin);

	} while (moreRecord != 'N');

	printf("\n%s\n", "_________________");
	printf("< %-30s %-2s %d >\n\n", "Total member's profile record(s) deleted", ":", deleteCount);

	//Write all the records from array back to file
	memberUser = fopen("memberUserfile.dat", "wb");// open the file for writing to put all records from array into file
	for (i = 0; i < pCount; i++)
		fwrite(&removeMemberInfo[i], sizeof(removeMemberInfo[i]), 1, memberUser);

	fclose(memberUser);

	booking = fopen("booking.dat", "wb");
	for (i = 0; i < bCount; i++)
		fwrite(&book[i], sizeof(book[i]), 1, booking);

	fclose(booking);
}

// - ERIC - Member information report
int memberInformationReport() {
	Membership member[100], vip[100];

	int i = 0, counter = 0;
	char choice;

	FILE* vipUser, * memberUser;

	vipUser = fopen("vipUserfile.dat", "rb");
	memberUser = fopen("memberUserfile.dat", "rb");

	if (vipUser == NULL) {
		printf("Unable to open vipUserfile.dat\n");
		exit(-1);
	}
	else if (memberUser == NULL) {
		printf("Unable to open memberUserfile.dat\n");
		exit(-1);
	}
	reportHeader();
	do {
		printf("List of Members: \n");
		printf("======================================================================================================\n");
		printf(" Name\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
		printf("======================================================================================================\n");
		while (fread(&(member[i]), sizeof(Membership), 1, memberUser))
		{
			printf("%d. %-13s%c\t\t%-16s%-24s%-16s%-20s\n", i + 1, member[i].memberName, toupper(member[i].gender[0]), member[i].memberID, member[i].memberBirthDate, member[i].memberIC, member[i].memberContactNum);
			i++;
			counter++;
		}
		fclose(memberUser);
		printf("\n");
		printf("List of VIPs: \n");
		printf("======================================================================================================\n");
		printf(" Name\t\tGender\t\tID\t\tBirth Date\t\tIC\t\tContact Number\n");
		printf("======================================================================================================\n");
		while (fread(&(vip[i]), sizeof(Membership), 1, vipUser))
		{
			printf("%d. %-13s%c\t\t%-16s%-24s%-16s%-20s\n", i + 1, vip[i].memberName, toupper(vip[i].gender[0]), vip[i].memberID, vip[i].memberBirthDate, vip[i].memberIC, vip[i].memberContactNum);
			i++;
			counter++;
		}
		fclose(vipUser);
		printf("\n\t\t\t\t< Total% d Members & VIPs listed >\n", counter);

		printf("\nPress to continue...\n");
		scanf("%c", &choice);
		rewind(stdin);
		system("cls");
		systemHeader();
		return 1;
	} while (choice != 2);
}

// - ERIC - Member function
int checkingName(char alphabet[40]) {
	int check = 0;
	for (int i = 0; alphabet[i] != '\0'; i++) {
		if (alphabet[0] == '\n') {
			check++;
		}
		else if (isalpha(alphabet[i]) == 0)
			if (alphabet[i] == ' ' || alphabet[i] == '\n')
			{
			}
			else {
				check++;
			}
	}
	if (check > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkingGender(char alphabet[3]) {
	int check = 0;
	for (int i = 0; alphabet[i] != '\0'; i++) {
		if (toupper(alphabet[i]) == 'F' || toupper(alphabet[i]) == 'M')
			check++;
		else {
			check = 2;
		}
	}
	if (check >= 2) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkingVipID(char vipID[6], int limit) {
	int wrongCount = 0, lengthCount = 0;
	if (vipID[0] != '\n') {
		if (toupper(vipID[0]) != 'V') {
			wrongCount++;
		}
	}
	else {
		wrongCount++;
	}
	for (int i = 1; vipID[i] != '\0'; i++) {
		if (vipID[i] != '\n') {
			if (isalpha(vipID[i]) == 1) {
				wrongCount++;
			}
			else {
				lengthCount++;
			}
		}
		else {
			lengthCount++;
			wrongCount++;
		}
	}
	if (lengthCount < limit && lengthCount > limit) {
		wrongCount++;
	}
	if (wrongCount > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkingMemberID(char memberID[6], int limit) {
	int wrongCount = 0, lengthCount = 0;
	if (memberID[0] != '\n') {
		if (toupper(memberID[0]) != 'M') {
			wrongCount++;
		}
	}
	else {
		wrongCount++;
	}
	for (int i = 1; memberID[i] != '\0'; i++) {
		if (memberID[i] != '\n') {
			if (isalpha(memberID[i]) == 1) {
				wrongCount++;
			}
			else {
				lengthCount++;
			}
		}
		else {
			lengthCount++;
			wrongCount++;
		}
	}
	if (lengthCount < limit && lengthCount > limit) {
		wrongCount++;
	}
	if (wrongCount > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkingBirthDate(char digit[9], int limit) {
	int wrongCount = 0, lengthCount = 0;
	for (int i = 0; digit[i] != '\0'; i++) {
		if (digit[i] != '\n') {
			if (isalpha(digit[i]) == 1) {
				wrongCount++;
			}
			else {
				lengthCount++;
			}
		}
		else {
			lengthCount++;
			wrongCount++;
		}
	}

	if (lengthCount < limit && lengthCount>limit) {
		wrongCount++;
	}

	if (wrongCount > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkingIC(char digit[13], int limit) {
	int wrongCount = 0, lengthCount = 0;
	for (int i = 0; digit[i] != '\0'; i++) {
		if (digit[i] != '\n') {
			if (isalpha(digit[i]) == 1) {
				wrongCount++;
			}
			else {
				lengthCount++;
			}
		}
		else {
			lengthCount++;
		}
	}
	if (lengthCount < limit && lengthCount > limit) {
		wrongCount++;
	}
	if (wrongCount > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkingContactNum(char digit[11], int limit) {
	int wrongCount = 0, lengthCount = 0;
	for (int i = 0; digit[i] != '\0'; i++) {
		if (digit[i] != '\n') {
			if (isalpha(digit[i]) == 1) {
				wrongCount++;
			}
			else {
				lengthCount++;
			}
		}
		else {
			lengthCount++;
		}
	}
	if (lengthCount < limit && lengthCount > limit) {
		wrongCount++;
	}
	if (wrongCount > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkUserAvailable(char alphabet[40]) {
	int i = 0, valid1, valid2, valid3, valid4, valid5, check = 0;

	Membership vip[100], member[100];
	FILE* vipUser, * memberUser;

	vipUser = fopen("vipUserfile.dat", "rb");
	memberUser = fopen("memberUserfile.dat", "rb");
	if (vipUser == NULL)
	{
		printf("Cannot open vipUserfile.dat!!");
	}
	else {
		while (fread(&(vip[i]), sizeof(Membership), 1, vipUser))
		{
			valid1 = strcmp(alphabet, vip[i].memberName);
			valid2 = strcmp(alphabet, vip[i].memberIC);
			valid3 = strcmp(alphabet, vip[i].memberID);
			valid4 = strcmp(alphabet, vip[i].memberBirthDate);
			valid5 = strcmp(alphabet, vip[i].memberContactNum);
			i++;
			if (valid1 == 0 || valid2 == 0 || valid3 == 0 || valid4 == 0 || valid5 == 0) {
				check++;
			}
		}
	}
	fclose(vipUser);
	if (memberUser == NULL)
	{
		printf("Cannot open memberUserfile.dat!!");
	}
	else {
		while (fread(&(member[i]), sizeof(Membership), 1, memberUser))
		{
			valid1 = strcmp(alphabet, member[i].memberName);
			valid2 = strcmp(alphabet, member[i].memberIC);
			valid3 = strcmp(alphabet, member[i].memberID);
			valid4 = strcmp(alphabet, member[i].memberBirthDate);
			valid5 = strcmp(alphabet, member[i].memberContactNum);
			i++;
			if (valid1 == 0 || valid2 == 0 || valid3 == 0 || valid4 == 0 || valid5 == 0)
			{
				check++;
			}
		}
	}
	fclose(memberUser);
	if (check >= 1) {
		return 0;
	}
	else {
		return 1;
	}
}

//================================================================================================

// - LKF - Program
// - LKF - Club facility booking menu
void facilityBooking() {

	int choose = 0, errorCount = 0;

	system("cls");
	systemHeader();
	printf("%77s\n\n", "** Facility Booking Menu **");

	do {

		bookingMenu();
		scanf("%d", &choose);
		rewind(stdin);

		system("cls");

		switch (choose) {
		case 1:
			displayBooking();
			break;
		case 2:
			addBooking();
			break;
		case 3:
			searchBooking();
			break;
		case 4:
			modifyBooking();
			break;
		case 5:
			removeBooking();
			break;
		case 6:
			displayBookingReport();
			break;
		case 7:
			system("cls");
			systemHeader();
			break;
		default:
			errorCount++;
			if (errorCount >= 5) {
				system("cls");
				systemHeader();
				printf("%77s\n\n", "** Facility Booking Menu **");
				printf("\n\nPlease contact the system admin for help !!!!\n\n");
				systemFooter();
				exit(-1);
			}
			else {
				system("cls");
				systemHeader();
				printf("%77s\n\n", "** Facility Booking Menu **");
				printf("\nPlease enter the correct menu !!!\n\n");

			}
		}


	} while (choose != 7);

}

void bookingMenu() {

	printf("Facility Booking Menu\n");
	printf("=========================\n");
	printf("1. Facility booking - Display\n");
	printf("2. Facility booking - Add\n");
	printf("3. Facility booking - Search\n");
	printf("4. Facility booking - Modification\n");
	printf("5. Facility booking - Delete\n");
	printf("6. Facility booking - Report\n");
	printf("7. Back to previous menu\n");
	printf("\nPlease select : ");

}

// - LKF - Club facility booking information
void displayBooking() {

	int count = 0;

	Booking book;

	//open file
	FILE* displayBooking;

	displayBooking = fopen("booking.dat", "rb");

	if (!displayBooking) {

		printf("Couldn't find the file : booking.dat\n\n");
		exit(-1);

	}

	systemHeader();

	printf("%-13s%-12s%-30s%-13s%-12s%-8s%-15s%-10s\n", "Facility Id", "Booking Id", "Employees Name", "Date", "Time", "Member", "Number of pax", "Remarks");
	printf("=======================================================================================================================\n");

	while (fread(&book, sizeof(book), 1, displayBooking)) {
		printf("%-13s%-12s%-30s%-2.2d-%-2.2d-%-7d%.02d%.02d-%-.02d%-5.02d%-8s%-15d%s\n", book.fac.facilityID, book.bookingId, book.emp.staffName, book.date.day, book.date.month, book.date.year, book.time.startHours, book.time.startMin, book.time.endHours, book.time.endMin, book.member.memberID, book.numOfPax, book.remarks);
		count++;
	}

	horizontalLine();
	printf("\n< %d booking listed >\n", count);
	horizontalLine();
	printf("\n");

	fclose(displayBooking);

}

void addBooking() {

	char comfirm, nextBooking, facilityId[30], staffId[30], memberId[30], selectMem, facId[6], bookingId[6];
	int bookingCount = 0, i = 0, id = 0, facCount = 0, staffCount = 0, find = 0, right = 0, day = 0, month = 0, year = 0, checkBook = 0, startHours = 0, startMin = 0, endHours = 0, endMin = 0, numOfPax = 0, maxPax = 0, stop = 0, recordDay = 0, recordMonth = 0, recordYear = 0, timeCount = 0, days = 0, bookId = 0, totalDays = 0;

	//struct 
	Facility fac[50];
	StaffProfile staff[50];
	Booking book;
	Booking timeBook[100];

	// structure for date and time
	SYSTEMTIME t;
	// get date & time from OS
	GetLocalTime(&t);

	do {

		find = 0;
		i = 0;

		//open file
		//add booking to file
		FILE* addBookingToFile;

		addBookingToFile = fopen("booking.dat", "ab");

		if (!addBookingToFile) {

			printf("Couldn't find the file : booking.dat\n\n");
			exit(-1);

		}

		//read booking time from file
		FILE* readBookingTime;

		readBookingTime = fopen("booking.dat", "rb");

		if (!readBookingTime) {

			printf("Couldn't find the file : booking.dat\n\n");
			exit(-1);

		}

		//read staff info
		FILE* staffInfo;

		staffInfo = fopen("staff_profile.dat", "rb");

		if (!staffInfo) {
			printf("\nCan't find the file \"staff_profile.dat\"!\n");
			exit(-1);
		}

		//read facility info
		FILE* readFacility;

		readFacility = fopen("facility.txt", "r");

		if (!readFacility) {
			printf("\nCan't find the file \"facility.txt\"!\n");
			exit(-1);
		}

		system("cls");
		systemHeader();

		printf("\nPlease Enter Booking Information\n");
		printf("================================\n");

		//booking id 
		generateBookId(&bookId); //return int
		//to combine the string and int value to one variable, for example "B" with "0001" become "B0001"
		snprintf(bookingId, 6, "B%.04d", bookId);
		strcpy(book.bookingId, bookingId);
		printf("Booking Id  : %s\n", book.bookingId);

		//facility information
		do {

			printf("Facility Id : ");
			scanf("%[^\n]", &facilityId);
			rewind(stdin);

			//search facility information
			while (fscanf(readFacility, "%[^|]|%[^|]|%[^|]|%c|%[^|]|%d|%d|%d\n", &fac[i].facilityID, &fac[i].faciltyType, &fac[i].facilityDescription, &fac[i].venue, &fac[i].venueDescription, &fac[i].maxUser, &fac[i].startTime, &fac[i].endTime) != EOF && i < 50)
				i++;

			facCount = i;

			for (i = 0; i < facCount; i++) {
				if (strcmp(fac[i].facilityID, facilityId) == 0) {
					printf("\nFacility information\n");
					printf("====================\n");
					printf("Facility Id          : %s\n", fac[i].facilityID);
					strcpy(book.fac.facilityID, fac[i].facilityID);
					printf("Facility Type        : %s\n", fac[i].faciltyType);
					printf("Facility Description : %s\n", fac[i].facilityDescription);
					printf("Facility Venue       : %c\n", fac[i].venue);
					printf("Max User             : %d\n", fac[i].maxUser);
					maxPax = fac[i].maxUser;
					strcpy(facId, fac[i].facilityID);
					find = 1;
				}
			}

			if (find == 0)
				printf("Can't find %s! Please enter the correct facility id!\n", facilityId);

		} while (find != 1);

		//close the file
		fclose(readFacility);

		find = 0;

		//add employees information

		do {
			printf("\nStaff Id : ");
			scanf("%[^\n]", &staffId);
			rewind(stdin);

			//search staff information
			while (fread(&staff[i], sizeof(staff[i]), 1, staffInfo) && i < 50)
				i++;

			staffCount = i;

			for (i = 0; i < staffCount; i++) {
				if (strcmp(staff[i].staffID, staffId) == 0) {
					printf("\nEmployees information\n");
					printf("=====================\n");
					printf("Staff Name : %s\n", staff[i].staffName);
					strcpy(book.emp.staffName, staff[i].staffName);
					printf("Staff Id   : %s\n", staff[i].staffID);
					strcpy(book.emp.staffID, staffId);
					find = 1;
				}
			}

			if (find == 0)
				printf("Can't find %s! Please enter the correct staff id!\n", staffId);

		} while (find != 1);

		//close the file
		fclose(staffInfo);

		printf("\n< Note: The next available booking date from: ");
		if (t.wMonth == 1 || t.wMonth == 3 || t.wMonth == 5 || t.wMonth == 7 || t.wMonth == 8 || t.wMonth == 10 || t.wMonth == 12) {
			if (t.wDay + 1 > 31) {
				totalDays = 1;
				t.wMonth += 1;
				printf("%.2d-%.2d-%.4d >\n", totalDays, t.wMonth, t.wYear);
			}
			else {
				printf("%.2d-%.2d-%.4d >\n", t.wDay + 1, t.wMonth, t.wYear);
			}
		}
		else if (t.wMonth == 4 || t.wMonth == 6 || t.wMonth == 9 || t.wMonth == 11) {
			if (t.wDay + 1 > 30) {
				totalDays = 1;
				t.wMonth += 1;
				printf("%.2d-%.2d-%.4d >\n", totalDays, t.wMonth, t.wYear);
			}
			else {
				printf("%.2d-%.2d-%.4d >\n", t.wDay + 1, t.wMonth, t.wYear);
			}
		}
		else if (t.wMonth == 2) {
			if (t.wYear % 4 == 0) {
				totalDays = 29;
				if (t.wDay + 1 > totalDays) {
					totalDays = 1;
					t.wMonth += 1;
					printf("%.2d-%.2d-%.4d >\n", totalDays, t.wMonth, t.wYear);
				}
				else {
					printf("%.2d-%.2d-%.4d >\n", t.wDay + 1, t.wMonth, t.wYear);
				}
			}
			else {
				totalDays = 28;
				if (t.wDay + 1 > totalDays) {
					totalDays = 1;
					t.wMonth += 1;
					printf("%.2d-%.2d-%.4d >\n", totalDays, t.wMonth, t.wYear);
				}
				else {
					printf("%.2d-%.2d-%.4d >\n", t.wDay + 1, t.wMonth, t.wYear);
				}
			}
		}

		do {

			right = 0;

			printf("Booking date (dd mm yyyy) : ");
			scanf("%d %d %d", &day, &month, &year);
			rewind(stdin);

			if (year >= t.wYear && month >= t.wMonth && month >= 1 && month <= 12) {	//if the date is correct, continue to check
				checkBookDate(month, year, &days);
				//if the month that user enter is error, days will become 0 and print the error message
				if (days == 0) {
					printf("Please contact the system admin for help! \n");
					exit(-1);
				}
				else if (day <= days) { //to check the days by month, for example feb only have 28 or 29 days, if user enter month is 2, day is over 28 or 29, it will print error message
					if (day <= t.wDay && month == t.wMonth) {
						printf("Please enter the correct day! (Number of days of year %d, month %d is %d)\n", year, month, days);
					}
					else {
						recordDay = day;
						recordMonth = month;
						recordYear = year;
						book.date.day = day;
						book.date.month = month;
						book.date.year = year;
						right = 1;
					}
				}
				else {
					printf("Please enter the correct day! (Number of days of year %d, month %d is %d)\n", year, month, days);
				}
			}

			//display error message by the part that user enter wrongly
			else if (year < t.wYear)
				printf("Please enter the correct year!\n");
			else if (month < t.wMonth || month < 1 || month > 12)
				printf("Please enter the correct month!\n");
			else
				printf("Please enter the correct date!\n");

		} while (right != 1);

		i = 0;

		while (fread(&timeBook[i], sizeof(timeBook[i]), 1, readBookingTime))
			i++;

		timeCount = i;

		//time
		printf("\n< Notes : Facility operating hours is 0600 - 2300 >\n");
		//booking start time
		do {

			right = 0;
			stop = 0;

			printf("Booking start time (hh mm) : ");
			scanf("%d %d", &startHours, &startMin);
			rewind(stdin);

			for (i = 0; i < timeCount && stop == 0; i++) {
				if (strcmp(facId, timeBook[i].fac.facilityID) == 0 && recordDay == timeBook[i].date.day && recordMonth == timeBook[i].date.month && recordYear == timeBook[i].date.year && startHours >= timeBook[i].time.startHours && startHours <= timeBook[i].time.endHours && startMin == timeBook[i].time.endMin) {
					printf("The time that you enter is already been book by other people! Please select another time slot!\n");
					stop = 1;
				}
			}

			if (stop != 1) {
				if (startHours < 6 || startHours >= 23) {
					printf("Invalid time entered! (Our club operating hours is 0600 - 2300)\n");
				}
				else if (startMin != 15 && startMin != 30 && startMin != 45 && startMin != 0) {
					printf("Invalid minutes entered ! (Booking minutes only accept 15, 30, 45 or 00)\n");
				}
				else {
					book.time.startHours = startHours;
					book.time.startMin = startMin;
					right = 1;
				}
			}

		} while (right == 0);

		//booking end time
		do {

			stop = 0;
			right = 0;

			printf("Booking end time (hh mm)   : ");
			scanf("%d %d", &endHours, &endMin);
			rewind(stdin);

			for (i = 0; i < timeCount && stop == 0; i++) {
				if (strcmp(facId, timeBook[i].fac.facilityID) == 0 && recordDay == timeBook[i].date.day && recordMonth == timeBook[i].date.month && recordYear == timeBook[i].date.year && endHours <= timeBook[i].time.startHours && endMin == timeBook[i].time.startMin) {
					printf("The time that you enter is already been book by other people! Please select another time slot!\n");
					stop = 1;
				}
			}
			if (stop != 1) {
				if (endHours > 23 || endHours == startHours) {
					printf("Invalid hours entered! (Our club operating hours is 0600 - 2300)\n");
				}
				else if (endHours < startHours) {
					printf("Invalid end hours! (Mininum usage time is 1 hour and above)\n");
				}
				else if (endMin != 15 && endMin != 30 && endMin != 45 && endMin != 0) {
					printf("Invalid minutes entered ! (Booking minutes only accept 15, 30, 45 or 00)\n");
				}
				else {
					book.time.endHours = endHours;
					book.time.endMin = endMin;
					right = 1;
				}
			}

		} while (right == 0);

		//close the file
		fclose(readBookingTime);

		printf("\nRemarks : ");
		scanf("%[^\n]", book.remarks);
		rewind(stdin);

		find = 0;

		//add member 
		memberType(&memberId);
		strcpy(book.member.memberID, memberId);

		do {

			printf("\nNumber of pax : ");
			scanf("%d", &numOfPax);
			rewind(stdin);

			if (numOfPax > maxPax)
				printf("The number of pax that you enter is more than the facility's max user!\n");
			else {
				book.numOfPax = numOfPax;
				find = 1;
			}

		} while (find != 1);

		printf("Confirm to add booking? (Y/N) : ");
		scanf("%c", &comfirm);
		rewind(stdin);

		if (toupper(comfirm) == 'Y') {
			fwrite(&book, sizeof(book), 1, addBookingToFile);
			bookingCount++;
			fclose(addBookingToFile); //To avoid user enter wrong data cause the true data that has been entered don't save into the file
		}

		printf("Add next booking? (Y/N) :");
		scanf("%c", &nextBooking);
		rewind(stdin);

	} while (toupper(nextBooking) != 'N');


	horizontalLine();
	printf("\n< %d booking record(s) has been added >\n", bookingCount);
	horizontalLine();
	printf("\n");

}

void removeBooking() {

	char deleteId[30], confirm, moreDelete;
	int deleteCount = 0, i = 0, dCount = 0, found = 0, totalDelete = 0, deleteIdx = 0, bookFound = 0;

	Booking book[100];

	FILE* deleteBooking;

	deleteBooking = fopen("booking.dat", "rb");

	if (!deleteBooking) {
		printf("Can't find the file \"booking.dat\"");
		exit(-1);
	}

	while (fread(&book[i], sizeof(book[i]), 1, deleteBooking) && i < 100)
		i++;

	dCount = i;

	fclose(deleteBooking);

	do {

		system("cls");
		systemHeader();

		printf("Enter the booking id to be deleted : ");
		scanf("%[^\n]", &deleteId);
		rewind(stdin);

		found = 0;
		totalDelete = 0;

		for (i = 0; i < dCount && found == 0; i++) {
			if (strcmp(deleteId, book[i].bookingId) == 0) {

				found = 1;

				printf("\nBooking record to be modified : \n");
				printf("Booking Id  : %s\n", book[i].bookingId);
				printf("Facility Id : %s\n", book[i].fac.facilityID);
				printf("Booking date and time : \n");
				printf("Date        : %.2d-%.2d-%-2d\n", book[i].date.day, book[i].date.month, book[i].date.year);
				printf("Start time  : %.02d%.02d\n", book[i].time.startHours, book[i].time.startMin);
				printf("End time    : %.02d%.02d\n", book[i].time.endHours, book[i].time.endMin);
				printf("Remarks     : %s\n", book[i].remarks);
				printf("Member      : %s\n", book[i].member.memberID);
				printf("Num of pax  : %d\n\n", book[i].numOfPax);

				deleteIdx = i;

				printf("Sure to delete? (Y/N) : ");
				scanf("%c", &confirm);
				rewind(stdin);

				if (toupper(confirm) == 'Y') {
					do {

						dCount--;

						for (i = deleteIdx; i < dCount; i++) {

							strcpy(book[i].bookingId, book[i + 1].bookingId);
							strcpy(book[i].fac.facilityID, book[i + 1].fac.facilityID);
							strcpy(book[i].emp.staffName, book[i + 1].emp.staffName);
							strcpy(book[i].emp.staffID, book[i + 1].emp.staffID);
							book[i].date.day = book[i + 1].date.day;
							book[i].date.month = book[i + 1].date.month;
							book[i].date.year = book[i + 1].date.year;
							book[i].time.startHours = book[i + 1].time.startHours;
							book[i].time.startMin = book[i + 1].time.startMin;
							book[i].time.endHours = book[i + 1].time.endHours;
							book[i].time.endMin = book[i + 1].time.endMin;
							strcpy(book[i].remarks, book[i + 1].remarks);
							strcpy(book[i].member.memberID, book[i + 1].member.memberID);
							book[i].numOfPax = book[i + 1].numOfPax;
						}

						totalDelete++;
						found = 1;
						for (i = 0; i < dCount && found == 1; i++)
							if (strcmp(deleteId, book[i].bookingId) == 0) {
								found = 0;
							}

					} while (found == 0);

				} //if else confirm startement
			}//if else strcmp statement
		}//for loop dCount

		if (found == 0)
			printf("\nNo record was found with the booking Id %s! \n\n", deleteId);

		printf("Any more to delete? (Y/N) : ");
		scanf("%c", &moreDelete);
		rewind(stdin);

	} while (toupper(moreDelete) != 'N');

	printf("\n< %d booking record(s) are deleted > \n\n", totalDelete);

	deleteBooking = fopen("booking.dat", "wb");

	for (i = 0; i < dCount; i++)
		fwrite(&book[i], sizeof(book[i]), 1, deleteBooking);

	fclose(deleteBooking);

}

void displayBookingReport() {

	int count = 0;

	// structure for date and time
	SYSTEMTIME t;
	// get date & time from OS
	GetLocalTime(&t);

	Booking book;

	//open file
	FILE* reportBooking;

	reportBooking = fopen("booking.dat", "rb");

	if (!reportBooking) {

		printf("Couldn't find the file : booking.dat\n\n");
		exit(-1);

	}

	reportHeader();

	printf("%78s\n\n", "~~ Booking Report ~~");
	printf("%s %d-%d-%d\n", "Date: ", t.wDay, t.wMonth, t.wYear);
	printf("%s %.2d:%.2d\n", "Time: ", t.wHour, t.wMinute);
	printf("================================================================================================================\n");
	printf("%-13s%-12s%-10s%-30s%-13s%-12s%-8s%-15s\n", "Facility Id", "Booking Id", "Staff Id", "Employees Name", "Date", "Time", "Member", "Number of pax");
	printf("================================================================================================================\n");

	while (fread(&book, sizeof(book), 1, reportBooking)) {
		printf("%-13s%-12s%-10s%-30s%-2.2d-%-2.2d-%-7d%.02d%.02d-%-.02d%-5.02d%-8s%-15d\n", book.fac.facilityID, book.bookingId, book.emp.staffID, book.emp.staffName, book.date.day, book.date.month, book.date.year, book.time.startHours, book.time.startMin, book.time.endHours, book.time.endMin, book.member.memberID, book.numOfPax); 
		count++;
	}
	printf("================================================================================================================\n");
	printf("Total booking: %d\n", count);
	printf("==================\n");

	reportFooter();

	fclose(reportBooking);

}

// - LKF - Club booking id auto generate
void generateBookId(int *bookId) {

	Booking booking[100];

	int i = 0, id = 0;
	char bookingId[6] = "";

	//read booking from file
	FILE* readBooking;

	readBooking = fopen("booking.dat", "rb");

	if (!readBooking) {

		printf("Couldn't find the file : booking.dat\n\n");
		exit(-1);

	}

	//Booking id
	//Read from the binary file and store into the structure
	while (fread(&booking[i], sizeof(booking[i]), 1, readBooking) && i < 100) {
		strcpy(bookingId, booking[i].bookingId);
	}

	// use ASCII to check last staff ID
	// Eg. '0' = 48, '9' = 57
	// If last Id is ST012
	// value = 0 * 10 + 48 - 48, value = 0
	// value = 0 * 10 + 49 - 48, value = 1
	// value = 1 * 10 + 50 - 48, value = 12
	for (int i = 0; i < strlen(bookingId); i++) {
		if (bookingId[i] >= '0' && bookingId[i] <= '9') {
			id = id * 10 + bookingId[i] - '0';
		}
	}

	// Eg. new ID is 12 + 1 = 13
	id += 1;

	//pass by address, because is string
	*bookId = id;

	//close the file
	fclose(readBooking);

}

// - LKF - Check date booking information
void checkBookDate(int month, int year, int* days) {

	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		*days = 31;
		break;

	case 4:
	case 6:
	case 9:
	case 11:
		*days = 30;
		break;

	case 2:
		if (year % 4 == 0)
			*days = 29;
		else
			*days = 28;
		break;
	default:
		*days = 0;
	}

}

// - LKF - Club member booking information
void memberType(char* type[6]) { //pass array

	char memberId[6];
	int choose = 0, errorCount = 0, i = 0, memCount = 0, vipCount = 0, found = 0;

	//struct
	Membership mem[100];
	Membership vip[100];

	//file
	//read member info
	FILE* readMember;
	FILE* readVip;

	readMember = fopen("memberUserfile.dat", "rb");
	readVip = fopen("vipUserfile.dat", "rb");

	if (!readMember) {
		printf("\nCan't find the file \"memberUserfile.dat\"!\n");
		exit(-1);
	}

	if (!readVip) {
		printf("\nCan't find the file \"vipUserfile.dat\"!\n");
		exit(-1);
	}

	//search member information
	while (fread(&mem[i], sizeof(mem[i]), 1, readMember) && i < 50)
		i++;

	memCount = i;

	fclose(readMember);

	i = 0;

	//search member information
	while (fread(&vip[i], sizeof(vip[i]), 1, readVip) && i < 50)
		i++;

	vipCount = i;

	fclose(readVip);

	do {

		found = 0;

		choose = memberMenu();

		switch (choose) {
		case 1:

			printf("\nPrimary Member Id : ");
			scanf("%[^\n]", &memberId);
			rewind(stdin);

			for (i = 0; i < memCount && found == 0; i++) {
				if (strcmp(mem[i].memberID, memberId) == 0) {
					printf("\nMembership information\n");
					printf("======================\n");
					printf("Member Name : %s\n", mem[i].memberName);
					printf("Member Id   : %s\n", mem[i].memberID);
					//type is a pointer
					strcpy(type, memberId); //copy the id into array
					found = 1;
				}
			}

			break;

			//vip
		case 2:

			printf("\nVIP Member Id : ");
			scanf("%[^\n]", &memberId);
			rewind(stdin);

			for (i = 0; i < vipCount && found == 0; i++) {
				if (strcmp(vip[i].memberID, memberId) == 0) {
					printf("\nMembership information\n");
					printf("======================\n");
					printf("Vip Name    : %s\n", vip[i].memberName);
					printf("Vip Id      : %s\n", vip[i].memberID);
					//type is a pointer
					strcpy(type, memberId); //copy the id into array
					found = 1;
				}
			}

			break;

		default:
			errorCount++;
			if (errorCount >= 5) {
				system("cls");
				systemHeader();
				printf("\n\nPlease contact the system admin for help !!!!\n\n");
				systemFooter();
				exit(-1);
			}
			else {
				printf("\nPlease enter the correct menu !!!\n");
			}
		}

		if (found == 0)
			printf("Can't find %s! Please enter the correct member id!\n", memberId);


	} while (found != 1);

}

int memberMenu() {

	int choose = 0;

	printf("\nSelect membership categories\n");
	printf("============================\n");
	printf("1. Primary Member\n");
	printf("2. VIP Member\n");
	printf("Enter your selection : ");
	scanf("%d", &choose);
	rewind(stdin);

	return choose;
}

// - LKF - Search booking information
void searchBookingMenu() {

	printf("Search Menu\n");
	printf("===================\n");
	printf("1. Facility Id\n");
	printf("2. Booking Id\n");
	printf("3. Member\n");
	printf("4. Time\n");
	printf("5. Date\n");
	printf("6. Back to previous menu\n");

}

void searchBooking() {

	char facilityId[30], bookingId[30], confirm, memberId[30];
	int search = 0, count = 0, searchCount = 0, startHrs = 0, startMin = 0, endHrs = 0, endMin = 0, day = 0, month = 0, year = 0, errorCount = 0, error = 0, member = 0, startTime = 0, endTime = 0, checkStartTime = 0, checkEndTime = 0, exitSearch = 0;

	Booking book[100];

	FILE* searchBooking;

	searchBooking = fopen("booking.dat", "rb");

	if (!searchBooking) {
		printf("Can't find the file \"booking.dat\"");
		exit(-1);
	}

	int i = 0;

	while (fread(&book[i], sizeof(book[i]), 1, searchBooking) && i < 100)
		i++;

	count = i;

	system("cls");
	systemHeader();

	do {

		searchCount = 0;
		member = 0;
		error = 0;
		exitSearch = 0;

		searchBookingMenu();

		printf("Search by : ");
		scanf("%d", &search);
		rewind(stdin);

		system("cls");
		systemHeader();

		switch (search) {

		case 1:
			printf("\nSearch by Facility Id : ");
			scanf("%[^\n]", facilityId);
			rewind(stdin);

			printf("\n%-13s%-12s%-30s%-13s%-12s%-8s%-15s%-10s\n", "Facility Id", "Booking Id", "Employees Name", "Date", "Time", "Member", "Number of pax", "Remarks");
			printf("=======================================================================================================================\n");
			for (int i = 0; i < count; i++)
				if (strcmp(facilityId, book[i].fac.facilityID) == 0) {
					printf("%-13s%-12s%-30s%-2.2d-%-2.2d-%-7d%.02d%.02d-%-.02d%-5.02d%-8s%-15d%s\n", book[i].fac.facilityID, book[i].bookingId, book[i].emp.staffName, book[i].date.day, book[i].date.month, book[i].date.year, book[i].time.startHours, book[i].time.startMin, book[i].time.endHours, book[i].time.endMin, book[i].member.memberID, book[i].numOfPax, book[i].remarks);
					searchCount++;
				}
			printf("=======================================================================================================================\n");

			break;

		case 2:
			printf("\nSearch by Booking Id : ");
			scanf("%[^\n]", bookingId);
			rewind(stdin);

			printf("\n%-13s%-12s%-30s%-13s%-12s%-8s%-15s%-10s\n", "Facility Id", "Booking Id", "Employees Name", "Date", "Time", "Member", "Number of pax", "Remarks");
			printf("=======================================================================================================================\n");
			for (int i = 0; i < count; i++)
				if (strcmp(bookingId, book[i].bookingId) == 0) {
					printf("%-13s%-12s%-30s%-2.2d-%-2.2d-%-7d%.02d%.02d-%-.02d%-5.02d%-8s%-15d%s\n", book[i].fac.facilityID, book[i].bookingId, book[i].emp.staffName, book[i].date.day, book[i].date.month, book[i].date.year, book[i].time.startHours, book[i].time.startMin, book[i].time.endHours, book[i].time.endMin, book[i].member.memberID, book[i].numOfPax, book[i].remarks);
					searchCount++;
				}
			printf("=======================================================================================================================\n");

			break;

		case 3:
			do {
				printf("\nSearch by Member : \n");
				printf("\n============================\n");
				printf("Select membership categories\n");
				printf("============================\n");
				printf("1. Primary Member\n");
				printf("2. VIP Member\n");
				printf("3. Back to previous menu\n");
				printf("Please enter your choice : ");
				scanf("%d", &member);
				rewind(stdin);

				if (member == 1) {
					printf("\n< Notes : (MXXXX) for primer member >\n");
					printf("Primary Member Id : ");
					scanf("%[^\n]", memberId);
					rewind(stdin);
				}
				else if (member == 2) {
					printf("\n< Notes : (VXXXX) for vip member >\n");
					printf("VIP Member Id : ");
					scanf("%[^\n]", memberId);
					rewind(stdin);
				}
				else if (member == 3) {
					confirm = 'Y';
				}
				else {
					system("cls");
					systemHeader();
					printf("\nPlease enter the correct choice !!\n");
				}

			} while (member != 1 && member != 2 && member != 3);

			if (member == 1 || member == 2) {
				printf("\n%-13s%-12s%-30s%-13s%-12s%-8s%-15s%-10s\n", "Facility Id", "Booking Id", "Employees Name", "Date", "Time", "Member", "Number of pax", "Remarks");
				printf("=======================================================================================================================\n");
				for (int i = 0; i < count; i++)
					if (strcmp(memberId, book[i].member.memberID) == 0) {
						printf("%-13s%-12s%-30s%-2.2d-%-2.2d-%-7d%.02d%.02d-%-.02d%-5.02d%-8s%-15d%s\n", book[i].fac.facilityID, book[i].bookingId, book[i].emp.staffName, book[i].date.day, book[i].date.month, book[i].date.year, book[i].time.startHours, book[i].time.startMin, book[i].time.endHours, book[i].time.endMin, book[i].member.memberID, book[i].numOfPax, book[i].remarks);
						searchCount++;
					}
				printf("=======================================================================================================================\n");
			}
			break;

		case 4:
			printf("\nSearch by Time (start time (hh mm)) : ");
			scanf("%d %d", &startHrs, &startMin);
			rewind(stdin);
			printf("Search by Time (end time (hh mm))   : ");
			scanf("%d %d", &endHrs, &endMin);
			rewind(stdin);

			//To combine the hours and minutes, we are using 24 hours clock format to find the time range
			//for example user want to find 1230 until 1500 records, it will combine the hours and minutes to search the range
			startTime = startHrs * 100 + startMin;
			endTime = endHrs * 100 + endMin;

			printf("\n%-13s%-12s%-30s%-13s%-12s%-8s%-15s%-10s\n", "Facility Id", "Booking Id", "Employees Name", "Date", "Time", "Member", "Number of pax", "Remarks");
			printf("=======================================================================================================================\n");
			for (int i = 0; i < count; i++) {

				//To combine the hours and minutes, we are using 24 hours clock format to find the time range
				//for example user want to find 1230 until 1500 records, it will combine the hours and minutes to search the range
				checkStartTime = book[i].time.startHours * 100 + book[i].time.startMin;
				checkEndTime = book[i].time.endHours * 100 + book[i].time.endMin;

				if (checkStartTime >= startTime && checkEndTime <= endTime) {
					printf("%-13s%-12s%-30s%-2.2d-%-2.2d-%-7d%.02d%.02d-%-.02d%-5.02d%-8s%-15d%s\n", book[i].fac.facilityID, book[i].bookingId, book[i].emp.staffName, book[i].date.day, book[i].date.month, book[i].date.year, book[i].time.startHours, book[i].time.startMin, book[i].time.endHours, book[i].time.endMin, book[i].member.memberID, book[i].numOfPax, book[i].remarks);
					searchCount++;
					//}
				}
			}
			printf("=======================================================================================================================\n");

			break;

		case 5:
			printf("\nSearch by Date (dd mm yyyy) : ");
			scanf("%d %d %d", &day, &month, &year);
			rewind(stdin);

			printf("\n%-13s%-12s%-30s%-13s%-12s%-8s%-15s%-10s\n", "Facility Id", "Booking Id", "Employees Name", "Date", "Time", "Member", "Number of pax", "Remarks");
			printf("=======================================================================================================================\n");
			for (int i = 0; i < count; i++)
				if (day == book[i].date.day && month == book[i].date.month && year == book[i].date.year) {
					printf("%-13s%-12s%-30s%-2.2d-%-2.2d-%-7d%.02d%.02d-%-.02d%-5.02d%-8s%-15d%s\n", book[i].fac.facilityID, book[i].bookingId, book[i].emp.staffName, book[i].date.day, book[i].date.month, book[i].date.year, book[i].time.startHours, book[i].time.startMin, book[i].time.endHours, book[i].time.endMin, book[i].member.memberID, book[i].numOfPax, book[i].remarks);
					searchCount++;
				}
			printf("=======================================================================================================================\n");

			break;

		case 6:
			confirm = 'N';
			exitSearch = 1;
			break;

		default:
			errorCount++;
			if (errorCount >= 5) {
				system("cls");
				systemHeader();
				printf("\n\nPlease contact the system admin for help !!!!\n\n");
				systemFooter();
				exit(-1);
			}
			else {
				system("cls");
				systemHeader();
				printf("\nPlease enter the correct menu !!!\n\n");
				error = 1;
			}
		}

		if (search != 6 && member != 3 && error != 1) {
			horizontalLine();
			printf("\n< %d booking record(s) has been search >\n", searchCount);
			horizontalLine();
			printf("\n");
			printf("Any more to search? (Y/N) : ");
			scanf("%c", &confirm);
			rewind(stdin);
		}
		else if(exitSearch != 1)
			confirm = 'Y';

	} while (toupper(confirm) != 'N' || error == 1);

	system("cls");
	systemHeader();

	fclose(searchBooking);

}

// - LKF - Modify booking menu 
void modifyBookingMenu() {

	printf("Modify Menu\n");
	printf("========================\n");
	printf("1. Facility Id\n");
	printf("2. Booking date\n");
	printf("3. Booking start Time\n");
	printf("4. Booking end Time\n");
	printf("5. Remarks\n");
	printf("6. Member\n");
	printf("7. Num of pax\n");
	printf("8. Back to previous menu\n");
	printf("========================\n");

}

void modifyBooking() {

	char modifyId[30], modifyFacility[30], modifyRemark[100], modifyMember[30], confirm, moreBooking, memberId[6];
	int  pCount = 0, found = 0, modifyCount = 0, modifyIdx = 0, modify = 0, modifyDay = 0, modifyMonth = 0, modifyYear = 0, modifyStartHours = 0, modifyStartMin = 0, modifyEndHours = 0, modifyEndMin = 0, modifyNum = 0, errorCount = 0, days = 0, right = 0, error = 0, stop = 0, find = 0, facCount = 0;

	Booking book[100];
	Facility fac[50];

	// structure for date and time
	SYSTEMTIME t;
	// get date & time from OS
	GetLocalTime(&t);

	FILE* modifyBook;

	modifyBook = fopen("booking.dat", "rb");

	if (!modifyBook) {
		printf("\nCan't open the file 'booking.dat!!\n\n");
		exit(-1);
	}

	int i = 0;

	//read facility 
	FILE* readFacility;

	readFacility = fopen("facility.txt", "r");

	if (!readFacility) {
		printf("\nCan't find the file \"facility.txt\"!\n");
		exit(-1);
	}

	while (fread(&book[i], sizeof(book[i]), 1, modifyBook) && i < 100)
		i++;

	pCount = i;

	system("cls");
	systemHeader();

	do {

		printf("Enter the booking Id to be modified : ");
		scanf("%[^\n]", &modifyId);
		rewind(stdin);

		found = 0;
		modifyCount = 0;
		error = 0;
		right = 0;

		for (i = 0; i < pCount && found == 0; i++) {

			if (strcmp(modifyId, book[i].bookingId) == 0) {

				found = 1;
				printf("\nBooking record to be modified : \n");
				printf("Booking Id  : %s\n", book[i].bookingId);
				printf("Facility Id : %s\n", book[i].fac.facilityID);
				printf("Booking date and time : \n");
				printf("Date        : %.2d-%.2d-%-2d\n", book[i].date.day, book[i].date.month, book[i].date.year);
				printf("Start time  : %.02d%.02d\n", book[i].time.startHours, book[i].time.startMin);
				printf("End time    : %.02d%.02d\n", book[i].time.endHours, book[i].time.endMin);
				printf("Remarks     : %s\n", book[i].remarks);
				printf("Member      : %s\n", book[i].member.memberID);
				printf("Num of pax  : %d\n\n", book[i].numOfPax);

				modifyIdx = i;

				modifyBookingMenu();
				printf("Please choose the record have to modified : ");
				scanf("%d", &modify);
				rewind(stdin);

				switch (modify) {

				case 1:
					
					do {

						printf("Enter new facility Id : ");
						scanf("%[^\n]", modifyFacility);
						rewind(stdin);

						//search facility information
						while (fscanf(readFacility, "%[^|]|%[^|]|%[^|]|%c|%[^|]|%d|%d|%d\n", &fac[i].facilityID, &fac[i].faciltyType, &fac[i].facilityDescription, &fac[i].venue, &fac[i].venueDescription, &fac[i].maxUser, &fac[i].startTime, &fac[i].endTime) != EOF && i < 50)
							i++;

						facCount = i;

						for (i = 0; i < facCount; i++) {
							if (strcmp(fac[i].facilityID, modifyFacility) == 0) {
								printf("\nFacility information\n");
								printf("====================\n");
								printf("Facility Id          : %s\n", fac[i].facilityID);
								printf("Facility Type        : %s\n", fac[i].faciltyType);
								printf("Facility Description : %s\n", fac[i].facilityDescription);
								printf("Facility Venue       : %c\n", fac[i].venue);
								printf("Max User             : %d\n", fac[i].maxUser);
								find = 1;
							}
						}

						if (find == 0)
							printf("Can't find %s! Please enter the correct facility id!\n", modifyFacility);

					} while (find != 1);

					break;

				case 2:

					do {

						right = 0;

						printf("Enter new booking date (dd/mm/yyyy) : ");
						scanf("%d %d %d", &modifyDay, &modifyMonth, &modifyYear);
						rewind(stdin);

						if (modifyYear >= t.wYear && modifyMonth >= t.wMonth && modifyMonth >= 1 && modifyMonth <= 12) {	//if the date is correct, continue to check
							checkBookDate(modifyMonth, modifyYear, &days);
							//if the month that user enter is error, days will become 0 and print the error message
							if (days == 0) {
								printf("Please contact the system admin for help!\n");
								exit(-1);
							}
							else if (modifyDay <= days) { //to check the days by month, for example feb only have 28 or 29 days, if user enter month is 2, day is over 28 or 29, it will print error message
								if (modifyDay <= t.wDay && modifyMonth == t.wMonth) {
									printf("Please enter the correct day! (Number of days of year %d, month %d is %d)\n", modifyYear, modifyMonth, days);
								}
								else {
									right = 1;
								} //to check the days by month, for example feb only have 28 or 29 days, if user enter month is 2, day is over 28 or 29, it will print error message
							}
							else {
								printf("Please enter the correct day!\n");
							}
						}

						//display error message by the part that user enter wrongly
						else if (modifyYear < t.wYear)
							printf("Please enter the correct year!\n");
						else if (modifyMonth < t.wMonth || modifyMonth < 1 || modifyMonth > 12)
							printf("Please enter the correct month!\n");
						else
							printf("Please enter the correct date!\n");

					} while (right != 1);

					break;

				case 3:

					//time
					printf("\nOur club operating hours is 0600 - 2300\n");
					printf("(Min only can put 15, 30, 45 and 00)\n");

					//booking start time
					do {

						right = 0;
						stop = 0;

						printf("Enter new booking start time (hhmm) : ");
						scanf("%d %d", &modifyStartHours, &modifyStartMin);
						rewind(stdin);

						for (i = 0; i < pCount && stop == 0; i++) {
							if (strcmp(book[modifyIdx].fac.facilityID, book[i].fac.facilityID) == 0 && book[modifyIdx].date.day == book[i].date.day && book[modifyIdx].date.month == book[i].date.month && book[modifyIdx].date.year == book[i].date.year && modifyStartHours <= book[i].time.startHours && modifyStartHours <= book[i].time.endHours && modifyStartMin == book[i].time.endMin) {
								printf("The time that you enter is already been book by other people! Please select another time slot!\n");
								stop = 1;
							}
						}

						if (stop != 1) {
							if (modifyStartHours < 6 || modifyStartHours >= 23) {
								printf("Invalid hours entered! (Our club operating hours is 0600 - 2300)\n");
							}
							else if (modifyStartMin != 15 && modifyStartMin != 30 && modifyStartMin != 45 && modifyStartMin != 0) {
								printf("Invalid minutes entered ! (Min only can set 15, 30, 45 and 00)\n)");
							}
							else if (modifyStartHours > book[modifyIdx].time.endHours || modifyStartHours == book[modifyIdx].time.endHours) {
								printf("The start time cannot more than end time!\n");
							}
							else {
								right = 1;
							}
						}

					} while (right == 0);

					break;

				case 4:

					//booking end time

					do {

						right = 0;

						printf("Enter new booking end time (hhmm) : ");
						scanf("%d %d", &modifyEndHours, &modifyEndMin);
						rewind(stdin);

						for (i = 0; i < pCount && stop == 0; i++) {
							if (strcmp(book[modifyIdx].fac.facilityID, book[i].fac.facilityID) == 0 && book[modifyIdx].date.day == book[i].date.day && book[modifyIdx].date.month == book[i].date.month && book[modifyIdx].date.year == book[i].date.year && modifyEndHours >= book[i].time.startHours && modifyEndMin == book[i].time.startMin) {
								printf("The time that you enter is already been book by other people! Please select another time slot!\n");
								stop = 1;
							}
						}

						if (stop != 1) {
							if (modifyEndHours > 23) {
								printf("Invalid hours entered! (Our club operating hours is 0600 - 2300)\n");
							}
							else if (modifyEndHours <= book[modifyIdx].time.startHours) {
								printf("Invalid end hours! (All the facility must book more than 1 hour)\n");
							}
							else if (modifyEndHours != 15 && modifyEndHours != 30 && modifyEndHours != 45 && modifyEndHours != 0) {
								printf("Invalid minutes entered ! (Min only can set 15, 30, 45 and 00)\n)");
							}
							else {
								right = 1;
							}
						}

					} while (right == 0);

					break;

				case 5:
					printf("Enter new remark : ");
					scanf("%[^\n]", &modifyRemark);
					rewind(stdin);
					break;

				case 6:

					memberType(&memberId);
					strcpy(modifyMember, memberId);

					break;

				case 7:
				
					do {

						printf("Enter new num of pax : ");
						scanf("%d", &modifyNum);
						rewind(stdin);

						//search facility information
						while (fscanf(readFacility, "%[^|]|%[^|]|%[^|]|%c|%[^|]|%d|%d|%d\n", &fac[i].facilityID, &fac[i].faciltyType, &fac[i].facilityDescription, &fac[i].venue, &fac[i].venueDescription, &fac[i].maxUser, &fac[i].startTime, &fac[i].endTime) != EOF && i < 50)
							i++;

						facCount = i;

						for (i = 0; i < facCount; i++) {
							if (strcmp(fac[i].facilityID, book[i].fac.facilityID) == 0) {
								if (modifyNum > fac[i].maxUser) {
									printf("The number of pax that you enter is more than the facility's max user! (The max user for facility %s is %d)\n", book[i].fac.facilityID, fac[i].maxUser);
								}
								else
									find = 1;
							}
						}

					} while (find != 1);

					break;

				case 8:
					printf("\n");
					break;

				default:
					errorCount++;
					if (errorCount >= 5) {
						system("cls");
						systemHeader();
						printf("\n\nPlease contact the system admin for help !!!!\n\n");
						systemFooter();
						exit(-1);
					}
					else {
						printf("\nPlease enter the correct menu !!!\n\n");
						error = 1;
					}
				}

				if (modify != 8 && error == 0) {
					printf("Sure to modify? (Y/N) : ");
					scanf("%c", &confirm);
					rewind(stdin);

					if (confirm == 'Y') {
						switch (modify) {

						case 1:
							strcpy(book[modifyIdx].fac.facilityID, modifyFacility);
							break;

						case 2:
							book[modifyIdx].date.day = modifyDay;
							book[modifyIdx].date.month = modifyMonth;
							book[modifyIdx].date.year = modifyYear;
							break;

						case 3:
							book[modifyIdx].time.startHours = modifyStartHours;
							book[modifyIdx].time.startMin = modifyStartMin;
							break;

						case 4:
							book[modifyIdx].time.endHours = modifyEndHours;
							book[modifyIdx].time.endMin = modifyEndMin;
							break;

						case 5:
							strcpy(book[modifyIdx].remarks, modifyRemark);
							break;

						case 6:
							strcpy(book[modifyIdx].member.memberID, modifyMember);
							break;

						case 7:
							book[modifyIdx].numOfPax = modifyNum;
							break;

						default:
							errorCount++;
							if (errorCount >= 5) {
								system("cls");
								systemHeader();
								printf("\n\nPlease contact the system admin for help !!!!\n\n");
								systemFooter();
								exit(-1);
							}
							else {
								printf("\nPlease enter the correct menu !!!\n\n");
							}
						}
						modifyCount++;
					}

			
				}

			}
		}

		if (found == 0) {
			system("cls");
			systemHeader();
			printf("\nNo record was found with the booking Id %s! \n\n", modifyId);
			error = 1;
		}

		if (modify != 8 && error == 0) {
			printf("Any more to modified? (Y/N) : ");
			scanf("%c", &moreBooking);
			rewind(stdin);
			if (moreBooking == 'Y') {
				system("cls");
				systemHeader();
			}
		}
		else if (modify == 8)
			moreBooking = 'N';
		else
			moreBooking = 'Y';

	} while (toupper(moreBooking) != 'N' || error == 1);

	fclose(readFacility);
	fclose(modifyBook);

	if (modify != 8 && confirm == 'Y') {
		printf("\n< %d booking record(s) are modified > \n\n", modifyCount);

		modifyBook = fopen("booking.dat", "wb");

		if (!modifyBook) {
			printf("\nCan't open the file 'booking.dat!!\n\n");
			exit(-1);
		}

		for (i = 0; i < pCount; i++)
			fwrite(&book[i], sizeof(book[i]), 1, modifyBook);

		fclose(modifyBook);
	}
	else {
		system("cls");
		systemHeader();
	}


}

// - LKF - Display horizontal line
void horizontalLine() {

	int row = 0, col = 0;

	// diaplay separated line
	for (row = 1; row <= 2; row++) {

		for (col = 1; col <= 137; col++) {
			printf("_");
		}
		printf("\n");
	}
}

//================================================================================================

// - DESMOND - Program
// - DESMOND - Read LKF Binary
void readBinary()
{
	Booking bookDisplay;
	int durationHour = 0, durationMin = 0;
	FILE* fp1;
	FILE* fp2;

	fp1 = fopen("booking.dat", "rb");
	fp2 = fopen("usage.txt", "w+");

	if (!fp1) {
		printf("Can't found the file 'booking.dat'\n");
		exit(-1);
	}

	if (!fp2) {
		printf("Can't found the file 'usage.txt'\n");
		exit(-1);
	}

	while (fread(&bookDisplay, sizeof(Booking), 1, fp1))
	{
		durationHour = bookDisplay.time.endHours - bookDisplay.time.startHours;

		//1245, 1315
		if (bookDisplay.time.startMin > bookDisplay.time.endMin)
			durationMin = bookDisplay.time.startMin - bookDisplay.time.endMin;
		else if (bookDisplay.time.endMin > bookDisplay.time.startMin)
			durationMin = bookDisplay.time.endMin - bookDisplay.time.startMin;

		fprintf(fp2, "%d|%d|%d|%d|%d|%d|%d|%s|%s|%s|%s|%d|%d\n", bookDisplay.date.day, bookDisplay.date.month, bookDisplay.date.year, bookDisplay.time.startHours, bookDisplay.time.startMin, bookDisplay.time.endHours, bookDisplay.time.endMin, bookDisplay.member.memberID, bookDisplay.fac.facilityID, bookDisplay.emp.staffID, bookDisplay.bookingId, durationHour, durationMin);
	}

	fclose(fp1);
	fclose(fp2);
}

// - DESMOND - Faclitiy Usage Management Menu
int facilityUsage(){
	int choice;

	systemHeader();
	readBinary();

	printf("%86s\n\n", "** Facility Usage Management Menu **");

	do {
		printf("\n==============================================\n");
		printf("Facility Usage Management\n");
		printf("==============================================\n");
		printf("1. Facility Usage - Add\n");
		printf("2. Facility Usage - Search\n");
		printf("3. Facility Usage - Modify\n");
		printf("4. Facility Usage - Display\n");
		printf("5. Facility Usage - Remove\n");
		printf("6. Facility Usage - Report\n");
		printf("7. Return Preview Menu\n");
		printf("==============================================\n");
		printf("Enter your selection: ");
		scanf("%d", &choice);
		rewind(stdin);

		system("cls");
		switch (choice) {
		case 1: addUsage(); break;
		case 2: searchFacilityUsage(); break;
		case 3: modifyFacilityUsage(); break;
		case 4: displayFacilityUsage(); break;
		case 5: removeFacilityUsage(); break;
		case 6: displayReport(); break;
		case 7: system("cls"); systemHeader(); break;
		default:
			system("cls");
			systemHeader();
			printf("Invalid Choice! Please Enter The Valid Choice...");
		}
	} while (choice != 7);

}

// - DESMOND - Add Facility Usage
void addUsage()
{
	char choice;
	Usage usa;
	FILE* fp1;
	fp1 = fopen("usage.txt", "a");
	if (!fp1) {
		printf("Can't found the file 'usage.txt'");
		exit(-1);
	}

	do
	{
		system("cls");
		systemHeader();
		printf("%81s\n\n", "** The New Usage detail **");
		printf("The New Usage detail\n");
		printf("====================\n");
		printf("Day                      : ");
		scanf("%d", &usa.day);
		rewind(stdin);

		printf("Month                    : ");
		scanf("%d", &usa.month);
		rewind(stdin);

		printf("Year                     : ");
		scanf("%d", &usa.year);
		rewind(stdin);

		printf("Time(Start Hour)         : ");
		scanf("%d", &usa.time.startHours);
		rewind(stdin);

		printf("Time(Start Minute)       : ");
		scanf("%d", &usa.time.startMin);
		rewind(stdin);

		printf("Time(End Hour)           : ");
		scanf("%d", &usa.time.endHours);
		rewind(stdin);

		printf("Time(End Minute)         : ");
		scanf("%d", &usa.time.endMin);
		rewind(stdin);

		printf("Member ID                : ");
		scanf("%s", &usa.memberId);
		rewind(stdin);

		printf("Facility ID              : ");
		scanf("%s", &usa.facilityId);
		rewind(stdin);

		printf("Staff ID                 : ");
		scanf("%s", &usa.staffId);
		rewind(stdin);

		printf("Walk-in/ Booking ID(W001): ");
		scanf("%s", &usa.choice);
		rewind(stdin);

		usa.durationHour = usa.time.endHours - usa.time.startHours;

		//1245, 1315
		if (usa.time.startMin > usa.time.endMin)
			usa.durationMin = usa.time.startMin - usa.time.endMin;
		else if (usa.time.endMin > usa.time.startMin)
			usa.durationMin = usa.time.endMin - usa.time.startMin;

		fprintf(fp1, "%.2d|%.2d|%d|%.2d|%.2d|%.2d|%.2d|%s|%s|%s|%s|%d|%d\n", usa.day, usa.month, usa.year, usa.time.startHours, usa.time.startMin, usa.time.endHours, usa.time.endMin, usa.memberId, usa.facilityId, usa.staffId, usa.choice, usa.durationHour, usa.durationMin);


		printf("Continue Add Usage? Y/N: ");
		scanf("%c", &choice);
		rewind(stdin);
	} while (toupper(choice) != 'N');

	fclose(fp1);
}

// - DESMOND - Search Facility Usage
void searchFacilityUsage()
{
	char memberIdSearch[6];
	int count = 0, i = 0;
	Usage susa;
	FILE* fp2;
	fp2 = fopen("usage.txt", "r");

	if (!fp2) {
		printf("Can't found the file 'usage.txt'\n");
		exit(-1);
	}

	systemHeader();
	printf("%78s\n\n", "** Search Details **");

	printf("Enter Member ID: ");
	scanf("%s", &memberIdSearch);
	rewind(stdin);

	printf("=========================================================================================================================================\n");
	printf("%15s %18s %22s %18s %15s %17s %25s\n", "Booked Date", "Booked Time", "Member ID", "Facility ID", "Staff ID", "Usage Type", "Duration(hour)");
	printf("=========================================================================================================================================\n");

	while (fscanf(fp2, "%d|%d|%d|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d\n", &susa.day, &susa.month, &susa.year, &susa.time.startHours, &susa.time.startMin, &susa.time.endHours, &susa.time.endMin, &susa.memberId, &susa.facilityId, &susa.staffId, &susa.choice, &susa.durationHour, &susa.durationMin) != EOF)
	{
		if (strcmp(susa.memberId, memberIdSearch) == 0)
		{
			printf("%6.2d-%.2d-%d %11.2d%.2d-%.2d%.2d %21s %16s %18s %16s %19d.%.2d\n", susa.day, susa.month, susa.year, susa.time.startHours, susa.time.startMin, susa.time.endHours, susa.time.endMin, susa.memberId, susa.facilityId, susa.staffId, susa.choice, susa.durationHour, susa.durationMin);
			count++;
		}
	}
	printf("=========================================================================================================================================\n");
	printf("%59d Record(s) Found\n", count);
	printf("=========================================================================================================================================\n");

	fclose(fp2);

	if (memberIdSearch == 0) {
		printf("No Search Result\n");
	}
}

// - DESMOND - Modify Facility Usage
void modifyFacilityUsage()
{
	char id[6], modify, moreRecord, facilityId[6], staffId[6], choice[6];
	int i = 0, count = 0, pCount = 0, found = 0, idX = 0, day = 0, month = 0, year = 0, startHour = 0, startMin = 0, endHour = 0, endMin = 0, durationHour = 0, durationMin = 0;
	Usage modifyFacUsage[20];

	FILE* fp3;
	fp3 = fopen("usage.txt", "r");

	if (!fp3) {
		printf("Can't found the file 'usage.txt'.\n\n");
		exit(-1);
	}

	while (fscanf(fp3, "%d|%d|%d|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d\n", &modifyFacUsage[i].day, &modifyFacUsage[i].month, &modifyFacUsage[i].year, &modifyFacUsage[i].time.startHours, &modifyFacUsage[i].time.startMin, &modifyFacUsage[i].time.endHours, &modifyFacUsage[i].time.endMin, &modifyFacUsage[i].memberId, &modifyFacUsage[i].facilityId, &modifyFacUsage[i].staffId, &modifyFacUsage[i].choice, &modifyFacUsage[i].durationHour, &modifyFacUsage[i].durationMin) != EOF)
		i++;

	fclose(fp3);

	pCount = i;

	do {

		system("cls");
		systemHeader();
		printf("%82s\n\n", "** Modify Facility Usage **");

		printf("Enter Member ID To Modified : ");
		scanf("%s", &id);
		rewind(stdin);

		found = 0;
		count = 0;


		for (i = 0; i < pCount && found == 0; i++) {
			if (strcmp(id, &modifyFacUsage[i].memberId) == 0)
			{

				found = 1;

				printf("\nDisplay Current Facility Usage Information\n");
				printf("============================================\n");
				printf("Member ID   : %s\n", modifyFacUsage[i].memberId);
				printf("Facility ID : %s\n", modifyFacUsage[i].facilityId);
				printf("Date        : %.2d-%.2d-%d\n", modifyFacUsage[i].day, modifyFacUsage[i].month, modifyFacUsage[i].year);
				printf("Time        : %.2d%.2d-%.2d%.2d\n", modifyFacUsage[i].time.startHours, modifyFacUsage[i].time.startMin, modifyFacUsage[i].time.endHours, modifyFacUsage[i].time.endMin);
				printf("Duration    : %d.%.2d\n", modifyFacUsage[i].durationHour, modifyFacUsage[i].durationMin);
				printf("Staff ID    : %s\n", modifyFacUsage[i].staffId);
				printf("Usage Type  : %s\n", modifyFacUsage[i].choice);
				idX = i;

				printf("\nEnter Information To Be Modify\n");
				printf("================================\n");
				printf("Enter Day                : ");
				scanf("%d", &day);
				rewind(stdin);

				printf("Enter Month              : ");
				scanf("%d", &month);
				rewind(stdin);

				printf("Enter Year               : ");
				scanf("%d", &year);
				rewind(stdin);

				printf("Enter Facility ID        : ");
				scanf("%s", &facilityId);
				rewind(stdin);

				printf("Enter Time(Start Hour)   : ");
				scanf("%d", &startHour);
				rewind(stdin);

				printf("Enter Time(Start Minute) : ");
				scanf("%d", &startMin);
				rewind(stdin);

				printf("Enter Time(End Hour)     : ");
				scanf("%d", &endHour);
				rewind(stdin);

				printf("Enter Time(End Minute)   : ");
				scanf("%d", &endMin);
				rewind(stdin);

				printf("Enter Staff ID           : ");
				scanf("%s", &staffId);
				rewind(stdin);

				printf("Walk-in/ Booking ID(W0001): ");
				scanf("%s", &choice);
				rewind(stdin);

				durationHour = (endHour - startHour);
				if (startMin > endMin)
					durationMin = startMin - endMin;
				else if (endMin > startMin)
					durationMin = endMin - startMin;

				printf("Sure to modify? (Y/N) : ");
				scanf("%c", &modify);
				rewind(stdin);

				if (toupper(modify) == 'Y') {
					strcpy(modifyFacUsage[idX].facilityId, facilityId);
					modifyFacUsage[idX].day = day;
					modifyFacUsage[idX].month = month;
					modifyFacUsage[idX].year = year;
					modifyFacUsage[idX].time.startHours = startHour;
					modifyFacUsage[idX].time.startMin = startMin;
					modifyFacUsage[idX].time.endHours = endHour;
					modifyFacUsage[idX].time.endMin = endMin;
					strcpy(modifyFacUsage[idX].staffId, staffId);
					strcpy(modifyFacUsage[idX].choice, choice);
					modifyFacUsage[idX].durationHour = durationHour;
					modifyFacUsage[idX].durationMin = durationMin;

				}

			}
			count++;
		}

		if (found == 2)
			printf("No record was found with the ID enter %s\n\n", id);

		printf("Continue Modify? (Y/N) : ");
		scanf("%c", &moreRecord);
		rewind(stdin);

	} while (toupper(moreRecord) != 'N');

	printf("\n< %d records are modified > \n\n", count);

	fp3 = fopen("usage.txt", "w");
	for (i = 0; i < pCount; i++)
	{
		fprintf(fp3, "%d|%d|%d|%d|%d|%d|%d|%s|%s|%s|%s|%d|%d\n", modifyFacUsage[i].day, modifyFacUsage[i].month, modifyFacUsage[i].year, modifyFacUsage[i].time.startHours, modifyFacUsage[i].time.startMin, modifyFacUsage[i].time.endHours, modifyFacUsage[i].time.endMin, modifyFacUsage[i].memberId, modifyFacUsage[i].facilityId, modifyFacUsage[i].staffId, modifyFacUsage[i].choice, modifyFacUsage[i].durationHour, modifyFacUsage[i].durationMin);
	}
	fclose(fp3);

}

// - DESMOND - Display Facility UsagE
void displayFacilityUsage()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	Usage displayFacUsa;
	FILE* fp4;
	fp4 = fopen("usage.txt", "r");

	if (!fp4) {
		printf("Can't found the file 'usage.txt'\n");
		exit(-1);
	}

	systemHeader();
	printf("%83s\n\n", "** Facility Usage Details **");

	printf("=========================================================================================================================================\n");
	printf("%15s %18s %22s %18s %15s %17s %25s\n", "Booked Date", "Booked Time", "Member ID", "Facility ID", "Staff ID", "Usage Type", "Duration(hour)");
	printf("=========================================================================================================================================\n");

	while (fscanf(fp4, "%d|%d|%d|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d\n", &displayFacUsa.day, &displayFacUsa.month, &displayFacUsa.year, &displayFacUsa.time.startHours, &displayFacUsa.time.startMin, &displayFacUsa.time.endHours, &displayFacUsa.time.endMin, &displayFacUsa.memberId, &displayFacUsa.facilityId, &displayFacUsa.staffId, &displayFacUsa.choice, &displayFacUsa.durationHour, &displayFacUsa.durationMin) != EOF)
	{
		if (displayFacUsa.day == t.wDay && displayFacUsa.month == t.wMonth && displayFacUsa.year == t.wYear)

			printf("%6.2d-%.2d-%d %11.2d%.2d-%.2d%.2d %21s %16s %18s %16s %19d.%.2d\n", displayFacUsa.day, displayFacUsa.month, displayFacUsa.year, displayFacUsa.time.startHours, displayFacUsa.time.startMin, displayFacUsa.time.endHours, displayFacUsa.time.endMin, displayFacUsa.memberId, displayFacUsa.facilityId, displayFacUsa.staffId, displayFacUsa.choice, displayFacUsa.durationHour, displayFacUsa.durationMin);
	}

	printf("\n");
	printf("\n%78s\n\n", "** Today Report **");

	fclose(fp4);
}

// - DESMOND - Remove Facility Usage
void removeFacilityUsage()
{
	char deleteUsage[6], deleteA, moreRecord;
	int  count = 0, pCount = 0, found = 0, deleteId = 0, find = 0;
	Usage removeFacUsage[20];
	FILE* fp5;
	fp5 = fopen("usage.txt", "r");

	if (!fp5) {
		printf("Can't found the file 'usage.txt'.\n\n");
		exit(-1);
	}

	systemHeader();
	printf("%82s\n\n", "** Delete Facility Usage **");

	int i = 0;

	while (fscanf(fp5, "%d|%d|%d|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d\n", &removeFacUsage[i].day, &removeFacUsage[i].month, &removeFacUsage[i].year, &removeFacUsage[i].time.startHours, &removeFacUsage[i].time.startMin, &removeFacUsage[i].time.endHours, &removeFacUsage[i].time.endMin, &removeFacUsage[i].memberId, &removeFacUsage[i].facilityId, &removeFacUsage[i].staffId, &removeFacUsage[i].choice, &removeFacUsage[i].durationHour, &removeFacUsage[i].durationMin) != EOF)
		i++;

	pCount = i;

	fclose(fp5);

	do {

		printf("Enter Member ID To Delete : ");
		scanf("%[^\n]", &deleteUsage);
		rewind(stdin);

		found = 0;
		count = 0;


		for (i = 0; i < pCount && found == 0; i++) {
			if (strcmp(deleteUsage, &removeFacUsage[i].memberId) == 0)
			{
				found = 1;

				printf("\nRecord to be delete : \n");
				printf("========================\n");
				printf("Member ID   : %s\n", removeFacUsage[i].memberId);
				printf("Date        : %.2d-%.2d-%d\n", removeFacUsage[i].day, removeFacUsage[i].month, removeFacUsage[i].year);
				printf("Facility ID : %s\n", removeFacUsage[i].facilityId);

				deleteId = i;


				printf("Sure to delete? (Y/N) : ");
				scanf("%c", &deleteA);
				rewind(stdin);

				if (toupper(deleteA) == 'Y') {
					pCount--;

					for (i = deleteId; i < pCount; i++) {
						strcpy(&removeFacUsage[i].memberId, removeFacUsage[i + 1].memberId);
						&removeFacUsage[i].day, & removeFacUsage[i].month, & removeFacUsage[i].year == removeFacUsage[i + 1].day, removeFacUsage[i + 1].month, removeFacUsage[i + 1].year;
						strcpy(&removeFacUsage[i].facilityId, removeFacUsage[i + 1].facilityId);

					}

				}

			}
			count++;
		}

		if (found == 0)
			printf("No record was found with the ID enter %s\n\n", deleteUsage);

		printf("Continue Delete? (Y/N) : ");
		scanf("%c", &moreRecord);
		rewind(stdin);

	} while (toupper(moreRecord) != 'N');

	printf("\n< %d records are deleted > \n\n", count);

	fp5 = fopen("usage.txt", "w");
	for (i = 0; i < pCount; i++)
	{
		fprintf(fp5, "%d|%d|%d|%d|%d|%d|%d|%s|%s|%s|%s|%d|%d\n", removeFacUsage[i].day, removeFacUsage[i].month, removeFacUsage[i].year, removeFacUsage[i].time.startHours, removeFacUsage[i].time.startMin, removeFacUsage[i].time.endHours, removeFacUsage[i].time.endMin, removeFacUsage[i].memberId, removeFacUsage[i].facilityId, removeFacUsage[i].staffId, removeFacUsage[i].choice, removeFacUsage[i].durationHour, removeFacUsage[i].durationMin);

	}

	fclose(fp5);

}

// - DESMOND - Display Report
void displayReport()
{
	Usage displayUsa;
	FILE* fp6;
	fp6 = fopen("usage.txt", "r");

	if (!fp6) {
		printf("Can't found the file 'usage.txt'\n");
		exit(-1);
	}

	reportHeader();

	printf("%81s\n\n", "** Facility Usage Report **");
	printf("=========================================================================================================================================\n");
	printf("%15s %18s %22s %18s %15s %17s %25s\n", "Booked Date", "Booked Time", "Member ID", "Facility ID", "Staff ID", "Booking ID", "Duration(hour)");
	printf("=========================================================================================================================================\n");

	while (fscanf(fp6, "%d|%d|%d|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d\n", &displayUsa.day, &displayUsa.month, &displayUsa.year, &displayUsa.time.startHours, &displayUsa.time.startMin, &displayUsa.time.endHours, &displayUsa.time.endMin, &displayUsa.memberId, &displayUsa.facilityId, &displayUsa.staffId, &displayUsa.choice, &displayUsa.durationHour, &displayUsa.durationMin) != EOF)
	{
		printf("%6.2d-%.2d-%d %11.2d%.2d-%.2d%.2d %21s %16s %18s %16s %19d.%.2d\n", displayUsa.day, displayUsa.month, displayUsa.year, displayUsa.time.startHours, displayUsa.time.startMin, displayUsa.time.endHours, displayUsa.time.endMin, displayUsa.memberId, displayUsa.facilityId, displayUsa.staffId, displayUsa.choice, displayUsa.durationHour, displayUsa.durationMin);
	}

	fclose(fp6);

	reportFooter();
}

//================================================================================================