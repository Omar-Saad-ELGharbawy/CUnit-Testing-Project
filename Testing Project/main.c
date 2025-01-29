// Before including standard headers, remove any macro definitions
#undef snprintf
#define _CRT_SECURE_NO_WARNINGS

// Include standard headers
#include <stdio.h>

#include "CreateAccount/Create_Account.h"
#include "DB/DB_Manager.h"
#include "App/App.h"
#include "Test/Tests.h"


// Main test runner
int main()
{
	/* initialize The DB with some initial Data */
	DBM_initDB();
	/* Variable to hold the status of the Main Application */
	//unsigned char Status;
	///* Super Loop To keep the App Active */
	//do
	//{
	//	 Status = Main_App_Runner();
	//} 
	//while (Status != ERROR);


	/* 
	* if you want to start your tests uncomment the following function 
	* then comment the previous Do-While Loop
	*/
	 Main_Test_Runner();
	return 0;
}
