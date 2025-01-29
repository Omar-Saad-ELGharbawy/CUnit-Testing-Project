#pragma once
#include "DB_info.h"
#include "stdio.h"

// test code to read the current user
int current_user_test;

/* Function to tack the Form From the Back end and assign it to Database*/
unsigned char DBM_Add_User(struct User_Input_Type* Form);

/* Function to take user id and delete this user and his dependencies from the Database*/
unsigned char DBM_Delete_User(unsigned short user_id);

/* Function to take user id and print all his info including his username and password */
unsigned char DBM_PrintUserData_Admin(unsigned short user_id);

/* Function to take user id and print all his info excluding his username and password */
unsigned char DBM_PrintUserData_User(unsigned short user_id);

/* Function that takes the ID of a course and student and then assign this user to this course*/
unsigned char DBM_AddToCourse(int Course_ID,int User_Id);

/* Function to take user id and print all his enrolled courses */
void DBM_ShowCourse(int User_Id);

/* Function Displays All Courses */
void DBM_DisplayAllCourses();

/* Function Displays All Users info (Admin Version)*/
void DBM_PrintUsers();

/* Function To Initiallize the Database with initial Users */
void DBM_initDB();

/* Function To print all the courses reservation */
void DBM_CheckReservations();

/* Function to remove the reservation from a specific student to a specific course */
unsigned char DBM_DeleteReservation(unsigned int CourseID, unsigned int StudentID);
