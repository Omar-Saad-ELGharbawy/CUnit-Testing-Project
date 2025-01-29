#pragma once

#include "stdio.h"
#include "string.h"
#include "../Security/Sec.h"
#include "../Generic/Data_Types.h"
#include "../DB/DB_Manager.h"

// this is to supress the error of using strcpy instead of strcpy_s
#define _CRT_SECURE_NO_WARNINGS

/* enum to detect the login type to the SW */
enum LoginType { AdminMohamedTarek, NormalUser, IncorrectLogin};

/* enum to detect the login request status */
enum LoginStatus {Login_Successful,Password_incorrect,UserName_NotFound};

/* Function that detects the User Type (Admin/Customer) */
unsigned char Detect_User_Type();

/* Function that Verifies the Admin Login */
unsigned char Verify_Admin();

/* 
* Function that verifies the credentials of the login request 
* and if successfull login it assigns the registered user id to the user active session
*/
unsigned char Verify_User(char* UserName,char* Password, int* id_ptr);