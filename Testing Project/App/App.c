#include "App.h"



unsigned char Main_App_Runner()
{
	unsigned char User_Type;
	unsigned char Admin_Verification;
	unsigned char RET = FALSE;

	// Detecting the user Login Type
	User_Type = Detect_User_Type();
	if (User_Type == AdminMohamedTarek)
	{
		Admin_Verification = Verify_Admin();
		if (TRUE == Admin_Verification)
		{
			printf("Welcome Mohamed Tarek \n");
			Admin_Runner();
			RET = TRUE;
		}
		else if (FALSE == Admin_Verification)
		{
			printf("You Are a Thief and not Mohamed Tarek\nSoftware Will Close\n");
			RET = FALSE;
		}
	}
	else if (User_Type == NormalUser)
	{
		Customer_Runner();
		RET = TRUE;
	}
	else 
	{
		printf("Wrong Entry you will quit\n");
		// this indicates we want to terminate the software 
		RET = ERROR;
	}
	return RET;
}