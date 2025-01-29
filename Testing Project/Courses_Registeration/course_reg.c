#include "course_reg.h"

unsigned char AddStudentToCourse(unsigned int Course_id, unsigned int Student_id)
{
	unsigned char RET = FALSE;
	// Check if already enrolled
	if (Enrollments[Student_id][Course_id-1] == TRUE)
	{
		RET = AlreadyEnrolled;
	}
	else
	{
		// Check if User is added succesfully to the course
		RET = DBM_AddToCourse(Course_id, Student_id);
		if (RET == TRUE)
		{
			RET = Enrolled;
		}
		// User not added the capacity is completed
		else
		{
			RET = CapacityCompleted;
		}
	}
	return RET;
}

/* Function that display list of all available courses */
void ShowListOfCourses()
{
	DBM_DisplayAllCourses();
}

/* Function that shows the Courses enrolled in for a specific Student */
void ShowStudentCourses(unsigned int User_ID)
{
	if (User_ID < 0 || User_ID >= MAX_USERS)
	{
		printf("Invalid User Id \n");
	}
	else
	{
		printf("You Are Currently Enrolled in:\n");
		DBM_ShowCourse(User_ID);
	}
}