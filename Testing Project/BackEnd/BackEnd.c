#include "BackEnd.h"

/* variable to hold the user input with the interactive console*/
static char user_choice;

/* variable to hold the user id input to be used in any command */
static unsigned short user_id_input;

/* variable to hold the return value for any function */
static unsigned char RET = 0;

/* variable to hold the form filled by user to add a new user */
static struct User_Input_Type Input_User;

/* variable to hold the form filled by user to Login to his account */
static struct LoginCredentials_Type LoginRequest;

/* variable to hold the form filled by user to Change his Password */
static struct LoginCredentials_Form_Type ChangePasswordRequests;

/* Variable to Hold The id of the user currently logged in to the system*/
static int Session_User_id = -1;

/* String to hold the current password of the user */
char Current_Password[32];

/* itterative variable to Loop on all courses*/
unsigned char Course_id;

/* Local Function to Scan an input Form from the User when requesting CreatingAccount[Customer]/Adding User[Admin]*/
static void Scan_User(void)
{
	printf("Please Enter Your First Name \n");
	scanf("%s", &Input_User.PersonalInfo_Form.name);
	printf("Please Enter Your Age \n");
	scanf("%d", &Input_User.PersonalInfo_Form.Age);
	printf("Please Enter Your Date of birth in the format:\n(Days -> enter -> Mont -> Enter -> Year -> Enter)\n");
	scanf("%d", &Input_User.PersonalInfo_Form.DOB_day);
	scanf("%d", &Input_User.PersonalInfo_Form.DOB_month);
	scanf("%d", &Input_User.PersonalInfo_Form.DOB_year);
	printf("Please Enter Your Educational Status from the Following:\n");
	printf("Student = 1\nFaculty_Student=2\nGraduate=3\nMasters_Student=4\nPHD_Student=5\nPHD_Holder=6\n");
	scanf("%d", &Input_User.PersonalInfo_Form.educational_status);
	printf("Please Enter Your Gender from the Following:\n");
	printf("Male = 1\nFemale=2\n");
	scanf("%d", &Input_User.PersonalInfo_Form.gender);
	printf("Please Enter Your UserName without any spaces and From 8 to 32 characters only \n");
	scanf("%s", &Input_User.LoginCredentials_Form.LoginCredentials.User_Name);
	printf("Please Enter Your Password without any spaces and From 8 to 32 characters only \n");
	scanf("%s", &Input_User.LoginCredentials_Form.LoginCredentials.Password);
	printf("Please ReEnter Your Password\n");
	scanf("%s", &Input_User.LoginCredentials_Form.Password_Recheck);
}

/* 
* function to Be Run if the SW is dealing with a Customer 
* the user has the option to login if he pressed L
* the user has the option to Create account if he pressed C
* the user has the option to Quit if he pressed Q
*/
void Customer_Runner()
{
	printf("Welcome To Edges Software \n");
	printf("Enter your choice and enter Q for Quit\n");
	printf("Enter L to Login to your account\n");
	printf("Enter C to Create a new account\n");
	printf("Enter H for Help\n");
	scanf(" %c", &user_choice);
	while (user_choice != 'Q' && user_choice != 'q')
	{
		switch (user_choice)
		{
		case 'C':
		case 'c':
			Scan_User();
			RET = Add_Account(&Input_User);
			if (RET == 1)
				printf("**************** User Added Successfully ****************\n");
			else
				printf("**************** Wrong inputs ****************\n");
			break;

		case 'H':
		case 'h':
			printf("Enter your choice and enter Q for Quit\n");
			printf("Enter L to Login to your account\n");
			printf("Enter C to Create a new account\n");
			printf("Enter H for Help\n");
			break;

		case 'L':
		case 'l':
			printf("Enter Your user name \n");
			scanf(" %s", &LoginRequest.User_Name);
			printf("Enter Your Password \n");
			scanf(" %s", &LoginRequest.Password);
			RET = Verify_User(LoginRequest.User_Name,LoginRequest.Password,&Session_User_id);
			if (RET == Login_Successful)
			{
				printf("Welcome %s\n", LoginRequest.User_Name);
				Home_Page_Runner();
			}
			else if (RET == UserName_NotFound)
			{
				printf("User Name Doesn't Exist Try Again\n");
			}
			else if (RET == Password_incorrect)
			{
				printf("Password inccorect, Enter Your Password again\n2 Trails Left\n");
				scanf(" %s",&LoginRequest.Password);
				RET = Verify_User(LoginRequest.User_Name, LoginRequest.Password, &Session_User_id);
				if (RET == Login_Successful)
				{
					printf("Welcome %s\n", LoginRequest.User_Name);
					Home_Page_Runner();
				}
				else if (RET == Password_incorrect)
				{
					printf("Password inccorect, Enter Your Password again\n1Trails Left\n");
					scanf(" %s", &LoginRequest.Password);
					RET = Verify_User(LoginRequest.User_Name, LoginRequest.Password, &Session_User_id);
					if (RET == Login_Successful)
					{
						printf("Welcome %s\n", LoginRequest.User_Name);
						Home_Page_Runner();
					}
					else if (RET == Password_incorrect)
					{
						printf("Your session is Terminated\nUser Will Be Deleted, Contact Admin to return it\n");
						DBM_Delete_User(Session_User_id);
						return;
					}
				}
			}
			/* Cleaning the Login request form to be ready for the next session */
			strcpy(LoginRequest.Password, "");
			strcpy(LoginRequest.User_Name, "");
			break;

		default:
			printf("Wrong input try again or use H for Help\n");
			break;
		}
		printf("Enter your choice use H for Help\n");
		scanf(" %c",&user_choice);
	}
}

/* 
* function to Be Run if the SW is Dealing with an Admin 
* Admin has the option to Add user if he pressed A
* Admin has the option to Delete user if he pressed D
* Admin has the option to Check all the course Registrations if he pressed C
* Admin has the option to print all the user info if he pressed P
* Admin has the option to print a specific user id info if he pressed U
* Admin has the option to see all his options if he pressed H
*/
void Admin_Runner()
{
	printf("Welcome To Edges Software \n");
	printf("Enter your choice and enter Q for Quit\n");
	printf("Enter A to add a new user\n");
	printf("Enter D to Delete user\n");
	printf("Enter C to Check Courses Registrations \n");
	printf("Enter P to Print all users\n");
	printf("Enter U to Print one user\n");
	printf("Enter H for Help\n");
	scanf(" %c", &user_choice);

	while (user_choice != 'Q' && user_choice != 'q')
	{
		switch (user_choice)
		{
		case 'A':
		case 'a':
			Scan_User();
			RET = Add_Account(&Input_User);
			if (RET == 1)
				printf("**************** User Added Successfully ****************\n");
			else
				printf("**************** Wrong inputs ****************\n");
			break;

		case 'C':
		case 'c':
			DBM_CheckReservations();
			break;

		case 'H':
		case 'h':
			printf("Enter your choice and enter Q for Quit\n");
			printf("Enter A to add a new user\n");
			printf("Enter D to Delete user\n");
			printf("Enter C to Check Courses Registrations \n");
			printf("Enter P to Print all users\n");
			printf("Enter U to Print one user\n");
			printf("Enter H for Help\n");
			break;

		case 'D':
		case 'd':
			printf("Enter the user id you want to delete \n");
			scanf("%d", &user_id_input);
			RET = Delete_Account(user_id_input);
			if (RET == TRUE)
			{
				printf("User %d Deleted \n", user_id_input);
			}
			else
			{
				printf("User ID Doesn't Exist \n");
			}
			break;

		case 'P':
		case 'p':
			DBM_PrintUsers();
			break;

		case 'U':
		case 'u':
			printf("Enter the user id you want to print \n");
			scanf("%d", &user_id_input);
			RET = DBM_PrintUserData_Admin(user_id_input);
			if (RET == TRUE)
			{
				printf("User %d Printed\n", user_id_input);
			}
			else
			{
				printf("User ID Doesn't Exist \n");
			}
			break;

		default:
			printf("Wrong input try again or use H for Help\n");
			break;
		}
		printf("Enter your choice use H for Help\n");

		scanf(" %c", &user_choice);
	}
}

/* 
* Function for the Home Page image after a successfull login 
* the user has the option to Change his password if he pressed C
* the user has the option to see his personal info if he pressed I
* the user has the option to Reserve a course from the course list if he pressed R
* the user has the option to show his enrolled courses if he pressed S
* the user has the option to see all his options if he pressed H
*/
void Home_Page_Runner()
{
	printf("Welcome To Your Home Page \n");
	printf("Enter your choice and enter O To Logout from yout current Account\n"); 
	printf("Enter C to change your password\n"); 
	printf("Enter i to see your info\n"); 
	printf("Enter R To Reserve a course\n");
	printf("Enter S To Show Your Enrolled Courses\n");
	printf("Enter H for Help\n"); 
	scanf(" %c", &user_choice);
	do
	{
		switch (user_choice)
		{
		case 'H':
		case 'h':
			printf("Enter your choice and enter O To Logout from yout current Account\n");
			printf("Enter C to change your password\n");
			printf("Enter i to see your info\n");
			printf("Enter R To Reserve a course\n");
			printf("Enter S To Show Your Enrolled Courses\n");
			printf("Enter H for Help\n");
			break;

		case 'C':
		case 'c':
			printf("Please Enter Your current Password \n");
			scanf(" %s", &Current_Password);
			printf("Please Enter New Password \n");
			scanf(" %s", &ChangePasswordRequests.LoginCredentials.Password);
			printf("Please Confirm New Password \n");
			scanf(" %s", &ChangePasswordRequests.Password_Recheck);
			if (strcmp(Current_Password, DB_LoginCredentials[Session_User_id].Password) == 0)
			{
				if (strcmp(ChangePasswordRequests.LoginCredentials.Password, ChangePasswordRequests.Password_Recheck) == 0)
				{
					strcpy(DB_LoginCredentials[Session_User_id].Password, ChangePasswordRequests.LoginCredentials.Password);
					printf("Password Changed Successfully \n");
				}
				else
				{
					printf("New Password mismatched \n");
				}
			}
			else
			{
				printf("Current Password is incorrect \n");
			}
			break;

		case 'I':
		case 'i':
			DBM_PrintUserData_User(Session_User_id);
			break;

		case 'O':
		case 'o':
			/* Ending the current session and go back to the Customer Runner */
			Session_User_id = -1;
			strcpy(Current_Password, "");
			strcpy(ChangePasswordRequests.LoginCredentials.User_Name, "");
			strcpy(ChangePasswordRequests.LoginCredentials.Password, "");
			strcpy(ChangePasswordRequests.Password_Recheck, "");
			printf("Good Bye!! see you soon \nLogged Out\n");
			return;
			break;

		case 'R':
		case 'r':
			printf("Please Choose From Our List Of Courses \n");
			ShowListOfCourses();
			scanf("%d", &Course_id);
			if (Course_id<1 || Course_id > MAX_COURSES)
			{
				printf("Out of range Course Try again \n");
			}
			else
			{
				RET= AddStudentToCourse(Course_id, Session_User_id);
				if (RET == Enrolled)
				{
					printf("You Are Added To This Course Reservation \n");
				}
				else if (RET == CapacityCompleted)
				{
					printf("Sorry, Course is Complete Try with the next wave \n");
				}
				else if (RET == AlreadyEnrolled)
				{
					printf("You Are Already Enrolled to this Course \n");
				}
			}
			break;

		case 'S':
		case 's':
			ShowStudentCourses(Session_User_id);
			break;

		default:
			printf("Wrong input try again or use H for Help\n");
			break;
		}
		printf("Enter your choice use H for Help\n");
		scanf(" %c", &user_choice);
	} 
	while (user_choice != 'Q' && user_choice != 'q');
}
