#pragma once
#include "../DB/DB_Manager.h"

/* Prototype for the funftion that Adds A specific Student to a specific course */
unsigned char AddStudentToCourse(unsigned int Student_id, unsigned int Course_id);

/* Prototype for the function that displays the list of courses */
void ShowListOfCourses();

/* Prototype for the function that displays the list of courses for a specific student */
void ShowStudentCourses(unsigned int User_ID);