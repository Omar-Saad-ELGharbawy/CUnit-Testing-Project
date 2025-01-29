#include "DB_Manager.h"

// Global variable that holds the current user id 
static int Current_user=0;
current_user_test=0;

struct Course ListofCourse[MAX_COURSES] =
{
	{1,"Standard_Diploma",0,100},
	{2,"AUTOSAR_Diploma",0,200},
	{3,"ARM_Diploma",0,300},
	{4,"RTOS_Diploma",0,400},
	{5,"Testing_Diploma",0,500},
	{6,"EmbeddedLinux_Diploma",0,600}
};






/* Local Functions Used by the Data Base Manager Only*/
static const char* get_Educational_Status_String(unsigned short id) 
{
	switch (DB_info[id].educational_status)
	{
		case DEFAULT_Status:     return "default";          break;
		case Student:            return "Student";          break;
		case Faculty_Student:    return "Faculty_Student";  break;
		case Graduate:           return "Graduate";         break;
		case Masters_Student:    return "Masters_Student";  break;
		case PHD_Student:        return "THURSDAY";         break;
		case PHD_Holder:         return "PHD_Holder";       break;
		default:                 return "UNKNOWN";          break;
	}
}

static const char* get_Gender_String(unsigned short id)
{
	switch (DB_info[id].gender)
	{
		case DEFAULT_Gender:   return "default"; break;
		case Male:             return "Male";    break;
		case Female:           return "Female";  break;
		default:               return "UNKNOWN"; break;
	}
}

/* Global Functions To be used by any one who includes Data Base Manager */

/* Function to add the recieved form from the back end to the Database */
unsigned char DBM_Add_User(struct User_Input_Type* Form)
{
	unsigned char RET = 0;
	if (Current_user == MAX_USERS)
	{
		RET = 0;
	}
	else
	{
		DB_info[Current_user].id = Current_user;
		strcpy(DB_info[Current_user].name, Form->PersonalInfo_Form.name);
		DB_info[Current_user].Age = Form->PersonalInfo_Form.Age;
		DB_info[Current_user].DOB_day = Form->PersonalInfo_Form.DOB_day;
		DB_info[Current_user].DOB_month = Form->PersonalInfo_Form.DOB_month;
		DB_info[Current_user].DOB_year = Form->PersonalInfo_Form.DOB_year;
		DB_info[Current_user].educational_status = Form->PersonalInfo_Form.educational_status;
		DB_info[Current_user].gender = Form->PersonalInfo_Form.gender;
		strcpy(DB_LoginCredentials[Current_user].User_Name, Form->LoginCredentials_Form.LoginCredentials.User_Name);
		strcpy(DB_LoginCredentials[Current_user].Password, Form->LoginCredentials_Form.LoginCredentials.Password);
		Current_user++;
		current_user_test++;
		RET = 1;
	}
	return RET;
}

/* Function to delete user by id from the Database */
unsigned char DBM_Delete_User(unsigned short user_id)
{
	unsigned char RET = 0;
	unsigned user_to_delete_index = user_id;
	unsigned int course_id;

	// checking the validity of the usr id 
	if (user_id < 0 || user_id > MAX_USERS)
	{
		RET = FALSE;
	}
	else
	{
		// Remove all the reservations of the Deleted User
		for (course_id = 1; course_id <= MAX_COURSES; course_id++)
		{
			if (Enrollments[user_id][course_id - 1] == TRUE)
			{
				RET = DBM_DeleteReservation(course_id, user_id);
				if (RET == FALSE)
				{
					return RET;
				}
			}
		}

		/* shifting all users to the left starting from the user you want to delete so it is overwritten now */
		for (; user_to_delete_index < MAX_USERS - 1; user_to_delete_index++)
		{
			DB_info[user_to_delete_index] = DB_info[user_to_delete_index + 1];
			DB_LoginCredentials[user_to_delete_index] = DB_LoginCredentials[user_to_delete_index + 1];
			for (course_id = 0; course_id < MAX_COURSES; course_id++)
			{
				Enrollments[user_to_delete_index][course_id] = Enrollments[user_to_delete_index + 1][course_id];
			}
		}
		/* 
		*  deleting the last user after shift to handle if the DB was Maximum and all users shifted left
		*  so the last user will be duplicated
		*  also deleting the last user enrollments due to the same reason
		*/
		DB_info[MAX_USERS-1].Age = 0;
		DB_info[MAX_USERS-1].DOB_day = 0;
		DB_info[MAX_USERS-1].DOB_month = 0;
		DB_info[MAX_USERS-1].DOB_year = 0;
		DB_info[MAX_USERS-1].educational_status = 0;
		DB_info[MAX_USERS-1].gender = 0;
		strcpy(DB_info[MAX_USERS-1].name, "");
		strcpy(DB_LoginCredentials[MAX_USERS-1].User_Name, "");
		strcpy(DB_LoginCredentials[MAX_USERS-1].Password, "");
		Current_user--;
		current_user_test--;
		for (course_id = 0; course_id < MAX_COURSES; course_id++)
		{
			Enrollments[MAX_USERS-1][course_id] = FALSE;
		}
		RET = TRUE;
	}
	return RET;
}

/* The Admin Version of printing User Data by id */
unsigned char DBM_PrintUserData_Admin(unsigned short user_id)
{
	unsigned char RET = FALSE;
	if (user_id < 0 || user_id > MAX_USERS)
	{
		RET = FALSE;
	}
	else
	{
		char* str_toPrint;
		printf("\nThe Data Of User %d is the following: \n", user_id);
		printf("Name              : %s \n", DB_info[user_id].name);
		printf("Date of birth     : %d/%d/%d \n", DB_info[user_id].DOB_day, DB_info[user_id].DOB_month, DB_info[user_id].DOB_year);
		printf("Age               : %d \n", DB_info[user_id].Age);
		str_toPrint = get_Educational_Status_String(user_id);
		printf("Educational Status: %s \n", str_toPrint);
		str_toPrint = get_Gender_String(user_id);
		printf("Gender            : %s \n", str_toPrint);
		printf("Account user name : %s \n", DB_LoginCredentials[user_id].User_Name);
		printf("Account Password  : %s \n", DB_LoginCredentials[user_id].Password);
		RET = TRUE;
	}
	return RET;
}

/* The Customer Version of printing User Data by id */
unsigned char DBM_PrintUserData_User(unsigned short user_id)
{
	unsigned char RET = FALSE;
	if (user_id < 0 || user_id > MAX_USERS)
	{
		RET = FALSE;
	}
	else
	{
		char* str_toPrint;
		printf("\nThe Data Of User %d is the following: \n", user_id);
		printf("Name              : %s \n", DB_info[user_id].name);
		printf("Date of birth     : %d/%d/%d \n", DB_info[user_id].DOB_day, DB_info[user_id].DOB_month, DB_info[user_id].DOB_year);
		printf("Age               : %d \n", DB_info[user_id].Age);
		str_toPrint = get_Educational_Status_String(user_id);
		printf("Educational Status: %s \n", str_toPrint);
		str_toPrint = get_Gender_String(user_id);
		printf("Gender            : %s \n", str_toPrint);
		RET = TRUE;
	}
	return RET;
}

/* Function To Add a specific user to a specific course */
unsigned char DBM_AddToCourse(int Course_ID, int User_Id)
{
	unsigned char RET = FALSE;
	if (ListofCourse[Course_ID-1].NumberOfEnrolledStudents >= MAX_STUDENTS_PER_COURSE)
	{
		RET = FALSE;
	}
	else
	{
		ListofCourse[Course_ID - 1].NumberOfEnrolledStudents++;
		Enrollments[User_Id][Course_ID - 1] = TRUE;
		RET = TRUE;
	}
	return RET;
}

/* Function to display the courses that a specific user is enrolled in*/
void DBM_ShowCourse(int User_Id)
{
	unsigned int course_id;
	for (course_id = 0; course_id < MAX_COURSES; course_id++)
	{
		if (Enrollments[User_Id][course_id] == TRUE)
		{
			printf("************* Course %d ************** \n", course_id + 1);
			printf("Course Name: %s \n", ListofCourse[course_id].CourseName);
			printf("Course ID  : %d \n", ListofCourse[course_id].CourseID);
			printf("Course Cost: %d \n", ListofCourse[course_id].Cost);
		}
	}
}

/* Function to display all available courses*/
void DBM_DisplayAllCourses()
{
	unsigned int course_id;
	for (course_id = 0; course_id < MAX_COURSES ; course_id++)
	{
		printf("************* Course %d ************** \n", course_id + 1);
		printf("Course Name: %s \n", ListofCourse[course_id].CourseName);
		printf("Course ID  : %d \n", ListofCourse[course_id].CourseID);
		printf("Course Cost: %d \n", ListofCourse[course_id].Cost);
	}
}

/* Function to print all users info Admin Version */
void DBM_PrintUsers()
{
	unsigned short user;
	for ( user = 0; user < MAX_USERS; user++)
	{
		DBM_PrintUserData_Admin(user);
		printf("*****************************************************************\n");
	}
}

/* Function to initiallize the DB with initial users */
void DBM_initDB()
{
	
	static struct User_Input_Type First =
	{
		{
		-1,"Ahmed",23,1,2,2021,Male,Student
		},
		{
			{"AdminUser1","Edges123"},
			"Edges123"
		}
	};

	static struct User_Input_Type Second =
	{
		{
		-1,"Mohamed",25,5,11,1999,Male,Graduate
		},
		{
			{"AdminUser2", "Edges123456"},
			"Edges123456"
		}
	};

	static struct User_Input_Type Third =
	{
		{
		-1,"Nada",24,3,4,2000,Female,Graduate
		},
		{
			{"AdminUser3","Edges_123"},
			"Edges_123"
		}
	};

	DBM_Add_User(&First);
	First.PersonalInfo_Form.id = Current_user - 1;

	DBM_Add_User(&Second);
	Second.PersonalInfo_Form.id = Current_user - 1;

	DBM_Add_User(&Third);
	Third.PersonalInfo_Form.id = Current_user - 1;

	DBM_AddToCourse(5, First.PersonalInfo_Form.id);
	DBM_AddToCourse(6, First.PersonalInfo_Form.id);

	DBM_AddToCourse(5, Second.PersonalInfo_Form.id);
	DBM_AddToCourse(6, Second.PersonalInfo_Form.id);

	DBM_AddToCourse(5, Third.PersonalInfo_Form.id);
	DBM_AddToCourse(1, Third.PersonalInfo_Form.id);
}

/* Function to print all the courses reservation status */
void DBM_CheckReservations()
{
	unsigned int course_id;
	for (course_id = 0; course_id < MAX_COURSES; course_id++)
	{
		printf("************* Course %d ************** \n", course_id + 1);
		printf("Course Name      : %s \n", ListofCourse[course_id].CourseName);
		printf("Course ID        : %d \n", ListofCourse[course_id].CourseID);
		printf("Enrolled Students: %d \n", ListofCourse[course_id].NumberOfEnrolledStudents);
	}
}

/* Function To delete the reservation of a specific student to a specific course */
unsigned char DBM_DeleteReservation(unsigned int CourseID, unsigned int StudentID)
{
	unsigned char RET;
	if (ListofCourse[CourseID - 1].NumberOfEnrolledStudents == 0)
	{
		// do no thing no enrolled students
		RET = TRUE;
	}
	else if (ListofCourse[CourseID - 1].NumberOfEnrolledStudents > 0)
	{
		if (Enrollments[StudentID][CourseID - 1] == TRUE)
		{
			Enrollments[StudentID][CourseID - 1] == FALSE;
			ListofCourse[CourseID - 1].NumberOfEnrolledStudents--;
			RET = TRUE;
		}
		else
		{
			RET = ERROR;
		}
	}
	else
	{
		// error !! number of enrolled students is less than 0 !!
		RET = ERROR;
	}
	return RET;
}
