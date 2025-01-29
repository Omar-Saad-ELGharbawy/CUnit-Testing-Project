#include "Login.h"

static unsigned int User_Type;
static unsigned int Token;

/* Function to check on the user input type Admin / Customer / Terminate the SW */
unsigned char Detect_User_Type() 
{
	printf("Hello Are You Admin Mohamed Tarek ? \nif yes please Enter 0 \nif No Please Enter 1\nOther Input will close the SW\n");
	scanf("%d", &User_Type);
	if (User_Type == AdminMohamedTarek)
	{
		return AdminMohamedTarek;
	}
	else if (User_Type == NormalUser)
	{
		return NormalUser;
	}
	else
	{
		return IncorrectLogin;
	}
}

/* Function to verify the admin token if input user type is chossen as an admin */
unsigned char Verify_Admin()
{
	printf("Hello Admin Mohamed Tarek\nPlease Enter Your Secret Token\n");
	scanf("%d", &Token);
	if (SECRET_ADMIN_TOKEN == Token)
	{
		return TRUE;
	}
	else
	{
		printf("Wrong Token please Enter Again you have 2 Trials left \n");
		scanf("%d", &Token);
		if (SECRET_ADMIN_TOKEN == Token)
		{
			return TRUE;
		}
		else
		{
			printf("Wrong Token please Enter Again you have 1 Trial left \n");
			scanf("%d", &Token);
			if (SECRET_ADMIN_TOKEN == Token)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
	}
}

/* 
* Function to check the credentials of the login requrest 
* the id_ptr is an output parameter to store the id of Logged in User in case of sucessfull login
*/
unsigned char Verify_User(char* UserName, char* Password,int* id_ptr)
{
	unsigned int Customer;
	for (Customer = 0; Customer < MAX_USERS; Customer++)
	{
		if (0 == strcmp(UserName, DB_LoginCredentials[Customer].User_Name))
		{
			if (0 == strcmp(Password, DB_LoginCredentials[Customer].Password))
			{
				*id_ptr = Customer;
				return Login_Successful;
			}
			else
			{
				*id_ptr = -1;
				return Password_incorrect;
			}
		}
	}
	*id_ptr = -1;
	return UserName_NotFound;
}
