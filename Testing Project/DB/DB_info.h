#pragma once
#include "../Generic/System_info.h"
#include "../Generic/Data_Types.h"

// this array is of structures Accout
// each element is the Login Credentials of one user 
struct LoginCredentials_Type DB_LoginCredentials[MAX_USERS];

// this array is of structures Accout
// each element is the info of one user 
struct PersonalInfo_Form_Type DB_info[MAX_USERS];

// 2D array 
// array of users each array is an array of booleans with the number of courses
//  each element represents if the student is enrroled in this course or not
int Enrollments[MAX_USERS][MAX_COURSES];