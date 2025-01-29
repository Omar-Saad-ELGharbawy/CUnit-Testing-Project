#pragma once

#include "../Login/Login.h"
#include "../CreateAccount/Create_Account.h"
#include "../Courses_Registeration/course_reg.h"

/* Prototype for the function to Be Run if the SW is dealing with a Customer */
void Customer_Runner();

/* Prototype for the function to Be Run if the SW is Dealing with an Admin */
void Admin_Runner();

/* Prototype for the Home Page image after a successfull login */
void Home_Page_Runner();