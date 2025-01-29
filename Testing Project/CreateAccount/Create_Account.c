#include "Create_Account.h"
#include "string.h"
#include "../DB/DB_Manager.h"

/* Local Function To return the number of days for a specific month in a specific year */
static unsigned char Get_Number_OfDays(unsigned char Month, unsigned short Year)
{
	switch (Month)
	{
	case 1:  // January
	case 3:  // March
	case 5:  // May
	case 7:  // July
	case 8:  // August
	case 10: // October
	case 12: // December
		return 31;
	case 4:  // April
	case 6:  // June
	case 9:  // September
	case 11: // November
		return 30;
	case 2:  // February
		return (Year % 4 == 0 && (Year % 100 != 0 || Year % 400 == 0)) ? 29 : 28;
	default:
		// Handle invalid month input
		return 0;
	}
}

/* Function to add a registration Form to Database after verifiying correct data */
unsigned char Add_Account(struct User_Input_Type* Form)
{
	// the variable to hold the return value
	unsigned char RET = FALSE;

	/* Check the name length is bigger than 32 or less than 3 */
	if (strlen(Form->PersonalInfo_Form.name) > 32 || strlen(Form->PersonalInfo_Form.name)<3)
	{
		RET = FALSE;
	}

	/* Check the Age is in Acceptable range 0 - 100 */
	else if (Form->PersonalInfo_Form.Age < 0 || Form->PersonalInfo_Form.Age > 100)
	{
		RET = FALSE;
	}

	/* Check consistancy in the age and date of birth */
	else if 
		(
		      ((CURRENT_YEAR - (Form->PersonalInfo_Form.DOB_year)) < (Form->PersonalInfo_Form.Age)) 
		   || ((CURRENT_YEAR - (Form->PersonalInfo_Form.DOB_year)) > (Form->PersonalInfo_Form.Age+1))
		)
	{
		RET = FALSE;
	}

	/* Check consistancy in the Number of days and months */
	else if (Form->PersonalInfo_Form.DOB_day > Get_Number_OfDays(Form->PersonalInfo_Form.DOB_month, Form->PersonalInfo_Form.DOB_year))
	{
		RET = FALSE;
	}

	/* Check the DOB_day is in Acceptable range 1 - 31 */
	else if (Form->PersonalInfo_Form.DOB_day < 1 || Form->PersonalInfo_Form.DOB_day > 31)
	{
		RET = FALSE;
	}

	/* Check the DOB_month is in Acceptable range 1 - 12 */
	else if (Form->PersonalInfo_Form.DOB_month < 1 || Form->PersonalInfo_Form.DOB_month > 12)
	{
		RET = FALSE;
	}

	/* Check the DOB_year is in Acceptable range 1924 - 2024 */
	else if (Form->PersonalInfo_Form.DOB_year < 1924 || Form->PersonalInfo_Form.DOB_year > 2024)
	{
		RET = FALSE;
	}

	/* Check the edeucational status is accepted one */
	else if (Form->PersonalInfo_Form.educational_status != Student && Form->PersonalInfo_Form.educational_status != Faculty_Student && Form->PersonalInfo_Form.educational_status != Graduate &&
		Form->PersonalInfo_Form.educational_status != Masters_Student && Form->PersonalInfo_Form.educational_status != PHD_Student && Form->PersonalInfo_Form.educational_status != PHD_Holder)
	{
		RET = FALSE;
	}

	/* Check the gender is accepted one */
	else if (Form->PersonalInfo_Form.gender != Male && Form->PersonalInfo_Form.gender != Female)
	{
		RET = FALSE;
	}


	// User Name Must Be From 8 to 32 Character
	else if (strlen(Form->LoginCredentials_Form.LoginCredentials.User_Name) > 32 || strlen(Form->LoginCredentials_Form.LoginCredentials.User_Name) < 8)
	{
		RET = FALSE;
	}

	// Password Must Be From 8 to 32 Character
	else if (strlen(Form->LoginCredentials_Form.LoginCredentials.Password) > 32 || strlen(Form->LoginCredentials_Form.LoginCredentials.Password) < 8)
	{
		RET = FALSE;
	}

	// Password Recheck Must Be From 8 to 32 Character
	else if (strlen(Form->LoginCredentials_Form.Password_Recheck) > 32 || strlen(Form->LoginCredentials_Form.Password_Recheck) < 8)
	{
		RET = FALSE;
	}

	// Password Missmatch 
	else if (strcmp(Form->LoginCredentials_Form.LoginCredentials.Password, Form->LoginCredentials_Form.Password_Recheck) != 0)
	{
		RET = FALSE;
	}

	// Every thing is okay 
	else
	{
		DBM_Add_User(Form);
		RET = TRUE;
	}

	return RET;
}

/* Function to Delete A specific user bu ID */
unsigned char Delete_Account(unsigned short user_id)
{
	unsigned char RET = FALSE;

	// Check if the user id is invalid
	if (user_id < 0 || user_id > MAX_USERS)
	{
		RET = FALSE;
	}
	else
	{
		DBM_Delete_User(user_id);
		RET = TRUE;
	}
	return RET;
}