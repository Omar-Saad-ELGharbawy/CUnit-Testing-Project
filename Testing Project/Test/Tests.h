#pragma once

// Before including standard headers, remove any macro definitions
#undef snprintf
// Include standard headers
#include <stdio.h>

/* Includes to use CUnit Framework */
#include <CUnit.h>	   // ASSERT macros for use in test cases, and includes other framework headers.

#include <Automated.h> // Automated interface with xml output.
#include <Basic.h>     // Basic interface with non-interactive output to stdout.
#include <Console.h>   // Interactive console interface.


/* this is our software under test */
#include "../App/App.h"

// #include "../DB/DB_info.h"
/* Prototype Function to Run the Tests */
void Main_Test_Runner(void);
