#pragma once
/* Structure containing login info */
struct LoginCredentials_Type
{
	char User_Name[32];
	char Password[32];
};

/* structure contains login info + password confirmation*/
struct LoginCredentials_Form_Type
{
	struct LoginCredentials_Type LoginCredentials;
	char Password_Recheck[32];
};

/* enum for the gender types */
enum Gender
{
    DEFAULT_Gender,
    Male,
    Female
};

/* Enum for the Educational Status */
enum Educational_Status
{
    DEFAULT_Status,
    Student,
    Faculty_Student,
    Graduate,
    Masters_Student,
    PHD_Student,
    PHD_Holder
};

/* The Form contains personal info of the User*/
struct PersonalInfo_Form_Type
{
    unsigned int id;
    char name[32];
    int Age;
    unsigned char DOB_day;
    unsigned char DOB_month;
    unsigned short DOB_year;
    enum Gender gender;
    enum Educational_Status educational_status;
};

// Structure that contains the user input Form
struct User_Input_Type
{
    struct PersonalInfo_Form_Type PersonalInfo_Form;
    struct LoginCredentials_Form_Type LoginCredentials_Form;
};

/* Enum for the functions return types */
enum ReturnType
{
    FALSE,
    TRUE,
    ERROR
};

/* Structure for course Data */
struct Course
{
    unsigned int CourseID;
    char CourseName[50];
    unsigned int NumberOfEnrolledStudents;
    unsigned int Cost;
};

/* Enum for the Add Course Function Return */
enum AddCourseReturn {Enrolled,AlreadyEnrolled,CapacityCompleted};