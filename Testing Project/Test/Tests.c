#include "Tests.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/************************************************************************************
 *                              Help Functions
 *************************************************************************************/
// Function to simulate input for scanf
void simulate_input(const char* input) {
    // Create a temporary file to hold the simulated input
    FILE* temp_input = fopen("temp_input.txt", "w");
    if (!temp_input) {
        perror("Error creating temporary input file");
        exit(EXIT_FAILURE);
    }
    fprintf(temp_input, "%s\n", input); // Write the input string to the file
    fclose(temp_input);

    // Redirect stdin to the temporary file
    freopen("temp_input.txt", "r", stdin);
}

/************************************************************************************
 *                              Test Functions
 *************************************************************************************/

 /************************************************************************************
  * Test ID                : TC_USER_TYPE_001	
  * Description            : Testing Detect_User_Type functionality for Admin user using simulated input.
  * Pre-requisites         : Application must be initialized.
  * Test Inputs            :
  *                          User Type Input -> 0
  * Test Expected Output   : The function should return AdminMohamedTarek.
  * Reason                 : Input matches Admin user type identifier.
  *************************************************************************************/
static void TC_USER_TYPE_001(void) {
    // Simulate input
    simulate_input("0");

    // Call the function
    unsigned char result = Detect_User_Type();
    CU_ASSERT_EQUAL(result, AdminMohamedTarek);

    // Restore stdin and clean up
    freopen(NULL, "r", stdin);
    remove("temp_input.txt");
}
/************************************************************************************
 * Test ID                : TestCase_DetectUserType_Normal_Simulated
 * Description            : Testing Detect_User_Type functionality for Normal user using simulated input.
 * Pre-requisites         : Application must be initialized.
 * Test Inputs            :
 *                          User Type Input -> 1
 * Test Expected Output   : The function should return NormalUser.
 * Reason                 : Input matches Normal user type identifier.
 *************************************************************************************/
static void TC_USER_TYPE_002(void) {
    // Simulate input
    simulate_input("1");

    // Call the function
    unsigned char result = Detect_User_Type();
    CU_ASSERT_EQUAL(result, NormalUser);

    // Restore stdin and clean up
    freopen(NULL, "r", stdin);
    remove("temp_input.txt");
}

/************************************************************************************
 * Test ID                : TC_USER_TYPE_003
 * Description            : Testing Detect_User_Type functionality for incorrect user input using simulated input.
 * Pre-requisites         : Application must be initialized.
 * Test Inputs            :
 *                          User Type Input -> 99 (or any invalid input)
 * Test Expected Output   : The function should return IncorrectLogin.
 * Reason                 : Input does not match any valid user type identifier.
 *************************************************************************************/
static void TC_USER_TYPE_003(void) {
    // Simulate input
    simulate_input("99"); // Simulated incorrect input

    // Call the function
    unsigned char result = Detect_User_Type();
    CU_ASSERT_EQUAL(result, IncorrectLogin);

    // Restore stdin and clean up
    freopen(NULL, "r", stdin);
    remove("temp_input.txt");
}



/***********************************************************
 *               Test Suite 2
 **********************************************************/

 /************************************************************************************
  * Test ID                : TC_VERIFY_ADMIN_001
  * Description            : Admin login success on first attempt.
  * Prerequisites          : System initialized with the correct secret token.
  * Test Inputs            : Token -> 10203040
  * Expected Output        : TRUE
  *************************************************************************************/
static void TC_VERIFY_ADMIN_001(void) {
    simulate_input("10203040");
    unsigned char result = Verify_Admin();
    CU_ASSERT_EQUAL(result, TRUE);
    freopen(NULL, "r", stdin);
    remove("temp_input.txt");
}

/************************************************************************************
 * Test ID                : TC_VERIFY_ADMIN_002
 * Description            : Admin login success on second attempt after first failure.
 * Prerequisites          : System initialized with the correct secret token.
 * Test Inputs            : Token -> 12345678, 10203040
 * Expected Output        : TRUE
 *************************************************************************************/
static void TC_VERIFY_ADMIN_002(void) {
    simulate_input("12345678\n10203040");
    unsigned char result = Verify_Admin();
    CU_ASSERT_EQUAL(result, TRUE);
    freopen(NULL, "r", stdin);
    remove("temp_input.txt");
}
/************************************************************************************
 * Test ID                : TC_VERIFY_ADMIN_003
 * Description            : Admin login success on third attempt after two failures.
 * Prerequisites          : System initialized with the correct secret token.
 * Test Inputs            : Token -> 111111, 222222, 10203040
 * Expected Output        : TRUE
 *************************************************************************************/
static void TC_VERIFY_ADMIN_003(void) {
    simulate_input("111111\n222222\n10203040");
    unsigned char result = Verify_Admin();
    CU_ASSERT_EQUAL(result, TRUE);
    freopen(NULL, "r", stdin);
    remove("temp_input.txt");
}

/************************************************************************************
 * Test ID                : TC_VERIFY_ADMIN_004
 * Description            : Admin login failure after three incorrect attempts.
 * Prerequisites          : System initialized with the correct secret token.
 * Test Inputs            : Token -> 111111, 222222, 333333
 * Expected Output        : FALSE
 *************************************************************************************/
static void TC_VERIFY_ADMIN_004(void) {
    simulate_input("111111\n222222\n333333");
    unsigned char result = Verify_Admin();
    CU_ASSERT_EQUAL(result, FALSE);
    freopen(NULL, "r", stdin);
    remove("temp_input.txt");
}

/***********************************************************
 *               Test Suite 3
 **********************************************************/
 /************************************************************************************
  * Test ID                : TC_VERIFY_USER_001
  * Description            : User login success with valid credentials.
  * Prerequisites          : Database initialized with valid users.
  * Test Inputs            : Username -> AdminUser1, Password -> Edges123, id_ptr -> Pointer
  * Expected Output        : Login_Successful, id_ptr = 0
  *************************************************************************************/
static void TC_VERIFY_USER_001(void) {
    const char* username = "AdminUser1";
    const char* password = "Edges123";
    int id_ptr = -1;
    enum LoginStatus result = Verify_User((char*)username, (char*)password, &id_ptr);
    CU_ASSERT_EQUAL(result, Login_Successful);
    CU_ASSERT_EQUAL(id_ptr, 0);
}

/************************************************************************************
 * Test ID                : TC_VERIFY_USER_002
 * Description            : User login failure with incorrect password.
 * Prerequisites          : Database initialized with valid users.
 * Test Inputs            : Username -> AdminUser1, Password -> wrongpass, id_ptr -> Pointer
 * Expected Output        : Password_incorrect, id_ptr = -1
 *************************************************************************************/
static void TC_VERIFY_USER_002(void) {
    const char* username = "AdminUser1";
    const char* password = "wrongpass";
    int id_ptr = -1;
    enum LoginStatus result = Verify_User((char*)username, (char*)password, &id_ptr);
    CU_ASSERT_EQUAL(result, Password_incorrect);
    CU_ASSERT_EQUAL(id_ptr, -1);
}

/************************************************************************************
 * Test ID                : TC_VERIFY_USER_003
 * Description            : User login failure with nonexistent username.
 * Prerequisites          : Database initialized with valid users.
 * Test Inputs            : Username -> NonexistentUser, Password -> password, id_ptr -> Pointer
 * Expected Output        : UserName_NotFound, id_ptr = -1
 *************************************************************************************/
static void TC_VERIFY_USER_003(void) {
    const char* username = "NonexistentUser";
    const char* password = "password";
    int id_ptr = -1;
    enum LoginStatus result = Verify_User((char*)username, (char*)password, &id_ptr);
    CU_ASSERT_EQUAL(result, UserName_NotFound);
    CU_ASSERT_EQUAL(id_ptr, -1);
}

/***********************************************************
 *               Test Suite 4 APP
 **********************************************************/

 /************************************************************************************
  * Test ID                : TC_MAIN_APP_001
  * Description            : Tests the transition from Main_App_Runner to Admin_Runner and back when input is `Q`.
  * Prerequisites          : System initialized.
  * Test Inputs            : User type -> 0 (Admin), Admin token -> 10203040, Admin Runner input -> Q
  * Expected Output        : Status = 0 (returned to Main App Runner)
  *************************************************************************************/
static void TC_MAIN_APP_001(void) {
    // Simulate input for selecting admin user type, entering admin token, and quitting Admin_Runner
    simulate_input("0\n10203040\nQ");

    // Call Main_App_Runner
    int Status = Main_App_Runner();

    // Assert that Status is correctly updated after Admin_Runner terminates
    CU_ASSERT_TRUE(Status);
}
/***********************************************************
 *               Test Suite 5 Data Base ADD
 **********************************************************/

 /* Test Code to test the Add User */
static struct User_Input_Type Test1_User = {
    {
        -1, // this is to indicate the user hasn't been assigned an ID
        "Ahmed",
        26,
        23,
        10,
        1998,
        Male,
        Masters_Student
    },
    {
        {
            "EdgesAcademy",
            "Edges123"
        },
        "Edges123"
    }
};


/* Closure Function For Test Suite 1 */
static unsigned char TC_DBM_ADD_USER_001_end(void) {
    unsigned char RET = Delete_Account(current_user_test - 1); // Deleting the most recently added user
    DBM_PrintUsers(); // Print users for verification
    return !RET;
}

/************************************************************************************
* Test ID                : TC_DBM_ADD_USER_001
* Description            : Testing the Add Account Functionality
* Pre-requisites         : The database is initialized and there is at least one user assigned.
* Test inputs            :
*                          Name                         -> Ahmed
*                          Age                          -> 26
*                          DOB_day                      -> 23
*                          DOB_Month                    -> 10
*                          DOB_Year                     -> 1998
*                          Educational_Status           -> Masters_Student
*                          Gender                       -> Male
*                          UserName                     -> EdgesAcademy
*                          Password                     -> Edges123
*                          Password Recheck             -> Edges123
* Test Expected Output   : The database should be updated with the previous inputs correctly.
* Reason                 : All inputs are in correct format and meet validation criteria.
*************************************************************************************/
static void TC_DBM_ADD_USER_001(void) {
    // Add the user to the database
    unsigned char RET = DBM_Add_User(&Test1_User);

    // Assign ID to the user
    Test1_User.PersonalInfo_Form.id = current_user_test - 1;

    // Print users for debugging
    DBM_PrintUsers();

    // Assert that the function succeeded
    CU_ASSERT_EQUAL(RET, 1);

    // Verify that data is assigned correctly
    unsigned int Test_id = Test1_User.PersonalInfo_Form.id;
    CU_ASSERT_EQUAL(DB_info[Test_id].Age, Test1_User.PersonalInfo_Form.Age);
    CU_ASSERT_EQUAL(DB_info[Test_id].DOB_day, Test1_User.PersonalInfo_Form.DOB_day);
    CU_ASSERT_EQUAL(DB_info[Test_id].DOB_month, Test1_User.PersonalInfo_Form.DOB_month);
    CU_ASSERT_EQUAL(DB_info[Test_id].DOB_year, Test1_User.PersonalInfo_Form.DOB_year);
    CU_ASSERT_EQUAL(DB_info[Test_id].educational_status, Test1_User.PersonalInfo_Form.educational_status);
    CU_ASSERT_EQUAL(DB_info[Test_id].gender, Test1_User.PersonalInfo_Form.gender);
    CU_ASSERT_STRING_EQUAL(DB_info[Test_id].name, Test1_User.PersonalInfo_Form.name);
    CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].User_Name, Test1_User.LoginCredentials_Form.LoginCredentials.User_Name);
    CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[Test_id].Password, Test1_User.LoginCredentials_Form.LoginCredentials.Password);
    CU_ASSERT_EQUAL(DB_info[Test_id].id, Test1_User.PersonalInfo_Form.id);

    // Call the cleanup function
    CU_ASSERT_EQUAL(TC_DBM_ADD_USER_001_end(), 0); // Ensure cleanup was successful


}


/* End Function: Cleanup added users */
static void TC_DBM_ADD_USER_002_End(void) {
    // Remove all users added during the test, keeping the initial 3 users intact
    while (current_user_test > 3) {
        int result = DBM_Delete_User(current_user_test - 1);
        CU_ASSERT_EQUAL(result, TRUE); // Ensure each user is deleted successfully
    }

    // Verify cleanup
    CU_ASSERT_EQUAL(current_user_test, 3); // Ensure only the initial users remain
    DBM_PrintUsers(); // Print users for confirmation
}

/************************************************************************************
 * Test ID                : TC_DBM_ADD_USER_002
 * Description            : Tests the behavior of DBM_Add_User when the number of users exceeds the maximum allowed.
 * Pre-requisites         : Database initialized with 3 preloaded users.
 * Test Inputs            : User_Input_Type with valid fields.
 * Expected Output        : Returns FALSE. No new user is added. Current_user remains unchanged.
 *************************************************************************************/
static void TC_DBM_ADD_USER_002(void) {
    // Fill the database to maximum capacity starting from the 4th user
    for (unsigned int i = 3; i < MAX_USERS; i++) {
        struct User_Input_Type temp_user = {
            {
                -1,                        // ID unassigned
                "Test User",               // Name
                30 + i,                    // Age (to differentiate users)
                1,                         // DOB_day
                1,                         // DOB_month
                1990 + i,                  // DOB_year
                Male,                      // Gender
                Graduate          // Educational_Status
            },
            {
                {
                    "TestUser",            // User_Name
                    "TestPassword"         // Password
                },
                "TestPassword"             // Password recheck
            }
        };
        int result = DBM_Add_User(&temp_user);
        CU_ASSERT_EQUAL(result, TRUE); // Ensure all valid users are added successfully
    }

    // Attempt to add one more user beyond capacity
    struct User_Input_Type new_user = {
        {
            -1,                        // ID unassigned
            "Extra User",              // Name
            25,                        // Age
            15,                        // DOB_day
            5,                         // DOB_month
            1995,                      // DOB_year
            Female,                    // Gender
            Masters_Student            // Educational_Status
        },
        {
            {
                "ExtraUser",           // User_Name
                "ExtraPassword"        // Password
            },
            "ExtraPassword"            // Password recheck
        }
    };

    // Call DBM_Add_User and ensure it fails
    int result = DBM_Add_User(&new_user);
    CU_ASSERT_EQUAL(result, FALSE);

    // Assert that Current_user has not changed
    CU_ASSERT_EQUAL(current_user_test, MAX_USERS);

    // Cleanup: Print users to ensure no extra user is added
    DBM_PrintUsers();

    // Call the cleanup function
    TC_DBM_ADD_USER_002_End();
}

/***********************************************************
 *               Test Suite 5 Data Base Delete User
 **********************************************************/

 /************************************************************************************
  * Test ID                : TC_DBM_DELETE_USER_001
  * Description            : Deletes a user successfully when a valid user ID is provided and verifies data is cleared properly.
  * Pre-requisites         : Database initialized with at least one user.
  * Test Inputs            : User ID of the added user.
  * Expected Output        : Returns TRUE. User is removed from `DB_info` and `DB_LoginCredentials`. `current_user_test` is decremented. Data at deleted user's position is cleared.
  *************************************************************************************/
static void TC_DBM_DELETE_USER_001(void) {
    // Add a user to the database
    struct User_Input_Type new_user = {
        {
            -1,                        // ID unassigned
            "Delete Me",               // Name
            30,                        // Age
            1,                         // DOB_day
            1,                         // DOB_month
            1990,                      // DOB_year
            Male,                      // Gender
            Masters_Student            // Educational_Status
        },
        {
            {
                "DeleteMe",            // User_Name
                "DeletePassword"       // Password
            },
            "DeletePassword"           // Password recheck
        }
    };

    // Add the user and assert successful addition
    int add_result = DBM_Add_User(&new_user);
    CU_ASSERT_EQUAL(add_result, TRUE);

    unsigned int user_id = current_user_test - 1;

    // Call DBM_Delete_User and assert successful deletion
    int delete_result = DBM_Delete_User(user_id);
    CU_ASSERT_EQUAL(delete_result, TRUE);

    // Assert that current_user_test is decremented
    CU_ASSERT_EQUAL(current_user_test, user_id);

    // Verify that data is cleared at the deleted user's position
    CU_ASSERT_EQUAL(DB_info[user_id].Age, 0);
    CU_ASSERT_EQUAL(DB_info[user_id].DOB_day, 0);
    CU_ASSERT_EQUAL(DB_info[user_id].DOB_month, 0);
    CU_ASSERT_EQUAL(DB_info[user_id].DOB_year, 0);
    CU_ASSERT_EQUAL(DB_info[user_id].educational_status, 0); // Assuming 0 is the default for educational_status
    CU_ASSERT_EQUAL(DB_info[user_id].gender, 0); // Assuming 0 is the default for gender
    CU_ASSERT_STRING_EQUAL(DB_info[user_id].name, ""); // Assuming an empty string is the default
    CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[user_id].User_Name, "");
    CU_ASSERT_STRING_EQUAL(DB_LoginCredentials[user_id].Password, "");
    //CU_ASSERT_EQUAL(DB_info[user_id].id, 0); // Assuming 0 is the default for id
}


/************************************************************************************
 * Test ID                : TC_DBM_DELETE_USER_002
 * Description            : Fails to delete a user when a nonexistent user ID is provided.
 * Pre-requisites         : Database initialized.
 * Test Inputs            : User ID greater than `MAX_USERS` or less than 0.
 * Expected Output        : Returns FALSE. No change in `DB_info` or `DB_LoginCredentials`. `Current_user` remains unchanged.
 *************************************************************************************/
static void TC_DBM_DELETE_USER_002(void) {
    // Call DBM_Delete_User with an invalid user ID
    int invalid_id = MAX_USERS + 1;
    int result = DBM_Delete_User(invalid_id);

    // Assert failure
    CU_ASSERT_EQUAL(result, FALSE);

    // Assert that Current_user remains unchanged
    CU_ASSERT_EQUAL(current_user_test, 3); // Assuming 3 users from initialization
}

/************************************************************************************
 * Test ID                : TC_DBM_DELETE_USER_003
 * Description            : Fails to delete a user when a user ID less than `0` is provided.
 * Pre-requisites         : Database initialized.
 * Test Inputs            : User ID less than `0`.
 * Expected Output        : Returns FALSE. No changes in `DB_info`, `DB_LoginCredentials`, or `current_user_test`.
 *************************************************************************************/
static void TC_DBM_DELETE_USER_003(void) {
    // Call DBM_Delete_User with an invalid user ID less than 0
    int invalid_id = -1;
    int result = DBM_Delete_User(invalid_id);

    // Assert failure
    CU_ASSERT_EQUAL(result, FALSE);

    // Assert that current_user_test remains unchanged
    CU_ASSERT_EQUAL(current_user_test, 3); // Assuming 3 users from initialization
}


/* End Function: Delete Added User  */
static void TC_DBM_DELETE_USER_004_End(void) {
    // Get the ID of the last user
    unsigned int user_id = current_user_test - 1;

    int delete_result = DBM_Delete_User(user_id);
    CU_ASSERT_EQUAL(delete_result, TRUE);
}

/************************************************************************************
 * Test ID                : TC_DBM_DELETE_USER_004
 * Description            : Deletes the last user in the database successfully without requiring data shifting.
 * Pre-requisites         : Database initialized and explicitly filled with users.
 * Test Inputs            : User ID of the last user.
 * Expected Output        : Returns TRUE. User is removed, and `current_user_test` is decremented.
 *************************************************************************************/
static void TC_DBM_DELETE_USER_004(void) {
    // Fill the database up to capacity if not already filled
    while (current_user_test < MAX_USERS) {
        struct User_Input_Type temp_user = {
            {
                -1,                        // ID unassigned
                "Test User",               // Name
                25 + current_user_test,    // Age
                1,                         // DOB_day
                1,                         // DOB_month
                1990 + current_user_test,  // DOB_year
                Male,                      // Gender
                Masters_Student            // Educational_Status
            },
            {
                {
                    "TestUser",            // User_Name
                    "TestPassword"         // Password
                },
                "TestPassword"             // Password recheck
            }
        };
        int result = DBM_Add_User(&temp_user);
        CU_ASSERT_EQUAL(result, TRUE); // Ensure user is added successfully
    }

    // Get the ID of the last user
    unsigned int user_id = current_user_test - 1;

    // Call DBM_Delete_User and assert successful deletion
    int delete_result = DBM_Delete_User(user_id);
    CU_ASSERT_EQUAL(delete_result, TRUE);

    // Assert that current_user_test is decremented
    CU_ASSERT_EQUAL(current_user_test, user_id);
    
	// Call the cleanup function
	TC_DBM_DELETE_USER_004_End();
}

/***********************************************************
 *               Test Suite 6 Data Base Add TO Course
 **********************************************************/

/************************************************************************************
 * Test ID                : TC_DBM_ADD_COURSE_001
 * Description            : Successfully adds a course for a valid user.
 * Pre-requisites         : Database initialized with users and courses.
 *************************************************************************************/
static void TC_DBM_ADD_COURSE_001(void) {
    unsigned int valid_user_id = 0; // User Ahmed
    unsigned int valid_course_id = 2; // AUTOSAR_Diploma

    // Add user to the course
    int result = DBM_AddToCourse(valid_course_id, valid_user_id);

    // Assert success
    CU_ASSERT_EQUAL(result, TRUE);

    // Verify enrollment in the Enrollments array
    CU_ASSERT_EQUAL(Enrollments[valid_user_id][valid_course_id - 1], TRUE);
}
/************************************************************************************
 * Test ID                : TC_DBM_ADD_COURSE_002
 * Description            : Fails to add a user to a course they are already enrolled in.
 * Pre-requisites         : User Ahmed is already enrolled in Testing_Diploma.
 *************************************************************************************/
static void TC_DBM_ADD_COURSE_002(void) {
    unsigned int user_id = 0; // User Ahmed
    unsigned int course_id = 5; // Testing_Diploma

    // Attempt to add the user again
    int result = DBM_AddToCourse(course_id, user_id);

    // Assert failure
    CU_ASSERT_EQUAL(result, FALSE);

    // Verify enrollment remains unchanged in the Enrollments array
    CU_ASSERT_EQUAL(Enrollments[user_id][course_id - 1], TRUE);
}

/************************************************************************************
 * Test ID                : TC_DBM_ADD_COURSE_003
 * Description            : Fails to add a user when the course is at full capacity.
 * Pre-requisites         : Testing_Diploma (course_id 5) is full.
 *************************************************************************************/
static void TC_DBM_ADD_COURSE_003(void) {
    unsigned int course_id = 3; // ARM_Diploma
    unsigned int user_id = 3; // New user (added for this test)

    // Simulate course being full
    for (int i = 0; i < MAX_STUDENTS_PER_COURSE; i++) {
        int result =  DBM_AddToCourse(course_id, i);
        // Assert failure
        CU_ASSERT_EQUAL(result, TRUE);
    }

    // Attempt to add another user
    int result = DBM_AddToCourse(course_id, user_id);

    // Assert failure
    CU_ASSERT_EQUAL(result, FALSE);

	// Delete the added users from the course
	for (int i = 0; i < MAX_STUDENTS_PER_COURSE; i++) {
		DBM_DeleteReservation(course_id, i);
	}
}
/************************************************************************************
 * Test ID                : TC_DBM_ADD_COURSE_004
 * Description            : Fails to add a non-existent user to a course.
 * Pre-requisites         : Database initialized with valid courses.
 *************************************************************************************/
static void TC_DBM_ADD_COURSE_004(void) {
    unsigned int invalid_user_id = MAX_USERS + 1; // Non-existent user
    unsigned int course_id = 1; // Valid course

    // Attempt to add the invalid user
    int result = DBM_AddToCourse(course_id, invalid_user_id);

    // Assert failure
    CU_ASSERT_EQUAL(result, FALSE);
}
/************************************************************************************
 * Test ID                : TC_DBM_ADD_COURSE_005
 * Description            : Fails to add a user to a non-existent course.
 * Pre-requisites         : Database initialized with valid users.
 *************************************************************************************/
static void TC_DBM_ADD_COURSE_005(void) {
    unsigned int user_id = 0; // Valid user
    unsigned int invalid_course_id = MAX_COURSES + 1; // Non-existent course

    // Attempt to add the user to the invalid course
    int result = DBM_AddToCourse(20, user_id);

    // Assert failure
    CU_ASSERT_EQUAL(result, FALSE);
}
/***********************************************************
 *               Test Suite 7 Data Base DBM_DeleteReservation
 **********************************************************/

  /************************************************************************************
   * Test ID                : TC_DBM_DEL_RES_001
   * Description            : Successfully deletes a valid course reservation for a user.
   * Pre-requisites         : Database initialized with valid users and reservations.
   * Test Inputs            :
   *                          User ID    -> 0 (Ahmed)
   *                          Course ID  -> 5 (Testing_Diploma)
   * Test Expected Output   :
   *                          Function returns TRUE.
   *                          Reservation is removed from the `Enrollments` array.
   *                          `NumberOfEnrolledStudents` is decremented.
   *************************************************************************************/
// Note : Failed
// Root Cause : Enrollments[StudentID][CourseID - 1] == FALSE;

static void TC_DBM_DEL_RES_001(void) {
    unsigned int valid_user_id = 0; // User Ahmed
    unsigned int valid_course_id = 5; // Testing_Diploma

    // Delete the reservation
    int result = DBM_DeleteReservation(valid_course_id, valid_user_id);

    // Assert success
    CU_ASSERT_EQUAL(result, 1);

    // Verify the reservation is removed
    CU_ASSERT_EQUAL(Enrollments[valid_user_id][valid_course_id - 1], FALSE);

	// Re-enroll the user for future tests
	DBM_AddToCourse(valid_course_id, valid_user_id);
}

/************************************************************************************
 * Test ID                : TC_DBM_DEL_RES_002
 * Description            : Handles case where no students are enrolled in the course.
 * Pre-requisites         : Database initialized with courses having no enrollments.
 * Test Inputs            :
 *                          User ID    -> 0 (Ahmed)
 *                          Course ID  -> 4 (RTOS_Diploma)
 * Test Expected Output   :
 *                          Function returns TRUE.
 *                          No changes in `Enrollments` or `NumberOfEnrolledStudents`.
 * Reason                 : No students are enrolled in the course.
 *************************************************************************************/
static void TC_DBM_DEL_RES_002(void) {
    unsigned int user_id = 0; // User Ahmed
    unsigned int course_id = 4; // RTOS_Diploma (no enrolled students)

    // Attempt to delete reservation
    unsigned char result = DBM_DeleteReservation(course_id, user_id);

    // Assert success (no action taken)
    CU_ASSERT_EQUAL(result, TRUE);

    // Verify no changes in the reservation
    CU_ASSERT_EQUAL(Enrollments[user_id][course_id - 1], FALSE);

}

/************************************************************************************
 * Test ID                : TC_DBM_DEL_RES_003
 * Description            : Fails to delete a reservation when the user is not enrolled in the course.
 * Pre-requisites         : Database initialized with valid users and reservations.
 * Test Inputs            :
 *                          User ID    -> 3 (Nada)
 *                          Course ID  -> 2 (AUTOSAR_Diploma)
 * Test Expected Output   :
 *                          Function returns ERROR.
 *                          No changes in `Enrollments` or `NumberOfEnrolledStudents`.
 * Reason                 : User is not enrolled in the specified course.
 *************************************************************************************/
static void TC_DBM_DEL_RES_003(void) {
    unsigned int user_id = 3; // User Nada
    unsigned int course_id = 2; // AUTOSAR_Diploma (not enrolled)

    // Attempt to delete reservation
    unsigned char result = DBM_DeleteReservation(course_id, user_id);

    // Assert failure
    CU_ASSERT_EQUAL(result, ERROR);

    // Verify no changes in the reservation
    CU_ASSERT_EQUAL(Enrollments[user_id][course_id - 1], FALSE);
}
/***********************************************************
 *               Test Suite 8 Data Base AddStudentToCourse 
 **********************************************************/

 /************************************************************************************
  * Test ID                : TC_ADD_TO_COURSE_001
  * Description            : Verifies that a valid student can be added to a valid course.
  * Pre-requisites         : Database initialized with valid users and courses.
  * Test Inputs            :
  *                          Student ID -> 1 (Valid student, e.g., Mohamed)
  *                          Course ID  -> 2 (Valid course, Standard_Diploma)
  * Test Expected Output   :
  *                          - Function returns Enrolled.
  *                          - Enrollment is updated in the Enrollments array.
  *************************************************************************************/
  // Note : Failed
  // Root Cause : prototype is different from definition
  // Return AlreadyEnrolled instead of Enrolled
static void TC_ADD_TO_COURSE_001(void) {
    unsigned int valid_student_id = 1; // Valid student ID (e.g., Mohamed)
    unsigned int valid_course_id = 2; // Standard_Diploma

    // Add student to the course
    int result = AddStudentToCourse(valid_student_id, valid_course_id);

    // Assert success
    CU_ASSERT_EQUAL(result, Enrolled);

    // Verify enrollment
    CU_ASSERT_EQUAL(Enrollments[valid_student_id][valid_course_id - 1], TRUE);
}
/************************************************************************************
 * Test ID                : TC_ADD_TO_COURSE_002
 * Description            : Ensures the function prevents duplicate enrollment for a student already enrolled in a course.
 * Pre-requisites         : Database initialized with valid users and courses.
 *                          Student is already enrolled in the course.
 * Test Inputs            :
 *                          Student ID -> 1 (Valid student, already enrolled)
 *                          Course ID  -> 5 (Valid course, Testing_Diploma)
 * Test Expected Output   :
 *                          - Function returns AlreadyEnrolled.
 *                          - Enrollment remains unchanged in the Enrollments array.
 *************************************************************************************/
 // Note : Failed
 // Root Cause : prototype is different from definition
 // Return Enrolled instead of AlreadyEnrolled
 // Another user is enrolled
static void TC_ADD_TO_COURSE_002(void) {
    unsigned int student_id = 1; // Valid student ID (already enrolled)
    unsigned int course_id = 5; // Testing_Diploma

    // Attempt to add the same student again
    int result = AddStudentToCourse(student_id, course_id);

    // Assert failure
    CU_ASSERT_EQUAL(result, AlreadyEnrolled);

    // Verify user is still enrolled
    CU_ASSERT_EQUAL(Enrollments[student_id][course_id - 1], TRUE);
}


/***********************************************************
 *               Test Suite 9 Add Account Name tests
 **********************************************************/
 // Helper function to create a valid base user input
void create_valid_user_input(struct User_Input_Type* user) {
    // Reset the entire structure
    memset(user, 0, sizeof(struct User_Input_Type));

    // Set valid personal info
    strcpy(user->PersonalInfo_Form.name, "John Doe");
    user->PersonalInfo_Form.Age = 23;
    user->PersonalInfo_Form.DOB_day = 4;
    user->PersonalInfo_Form.DOB_month = 8;
    user->PersonalInfo_Form.DOB_year = 2001;
    user->PersonalInfo_Form.gender = Male;
    user->PersonalInfo_Form.educational_status = Student;

    // Set valid login credentials
    strcpy(user->LoginCredentials_Form.LoginCredentials.User_Name, "johndoe123");
    strcpy(user->LoginCredentials_Form.LoginCredentials.Password, "ValidPass123");
    strcpy(user->LoginCredentials_Form.Password_Recheck, "ValidPass123");
}

/************************************************************************************
 * Test ID                : TC_NAME_LENGTH_001
 * Description            : Verifies that Add_Account fails when the name is shorter than 3 characters.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Name: "Jo" (2 characters)
 *                          - Age: 34
 *                          - DOB: 4/8/2001
 *                          - Gender: Male
 *                          - Educational Status: Student
 *                          - Username: "johndoe123"
 *                          - Password: "ValidPass123"
 *                          - Password Recheck: "ValidPass123"
 * Expected Results       : Add_Account returns FALSE, and no user is added to the database.
 *************************************************************************************/
void TC_NAME_LENGTH_001(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    strcpy(user.PersonalInfo_Form.name, "Jo");
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}
/************************************************************************************
 * Test ID                : TC_NAME_LENGTH_002
 * Description            : Verifies that Add_Account succeeds when the name is exactly 3 characters long.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Name: "Joe" (3 characters)
 *                          - Age: 34
 *                          - DOB: 4/8/2001
 *                          - Gender: Male
 *                          - Educational Status: Student
 *                          - Username: "johndoe123"
 *                          - Password: "ValidPass123"
 *                          - Password Recheck: "ValidPass123"
 * Expected Results       : Add_Account returns TRUE, and the user is successfully added to the database.
 *************************************************************************************/
void TC_NAME_LENGTH_002(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    strcpy(user.PersonalInfo_Form.name, "Joe");
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}
/************************************************************************************
 * Test ID                : TC_NAME_LENGTH_003
 * Description            : Verifies that Add_Account succeeds when the name is exactly 32 characters long.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Name: "JohnDoeAbcDefGhiJklMnoPqrStuvWxy" (32 characters)
 *                          - Age: 34
 *                          - DOB: 4/8/2001
 *                          - Gender: Male
 *                          - Educational Status: Student
 *                          - Username: "johndoe123"
 *                          - Password: "ValidPass123"
 *                          - Password Recheck: "ValidPass123"
 * Expected Results       : Add_Account returns TRUE, and the user is successfully added to the database.
 *************************************************************************************/
// Failed 
// Root Cause : when initializong with 32 characters name the null character(0) is calculated as 33
void TC_NAME_LENGTH_003(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    strcpy(user.PersonalInfo_Form.name, "JohnDoeAbcDefGhiJklMnoPqrStuvWxy");
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}
/************************************************************************************
 * Test ID                : TC_NAME_LENGTH_004
 * Description            : Verifies that Add_Account fails when the name exceeds 32 characters.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Name: "JohnDoeAbcDefGhiJklMnoPqrStuvWxyz" (33 characters)
 *                          - Age: 34
 *                          - DOB: 4/8/2001
 *                          - Gender: Male
 *                          - Educational Status: Student
 *                          - Username: "johndoe123"
 *                          - Password: "ValidPass123"
 *                          - Password Recheck: "ValidPass123"
 * Expected Results       : Add_Account returns FALSE, and no user is added to the database.
 *************************************************************************************/
void TC_NAME_LENGTH_004(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    strcpy(user.PersonalInfo_Form.name, "JohnDoeAbcDefGhiJklMnoPqrStuvWxyz");
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/***********************************************************
 *               Test Suite 10 Add Account Age tests
 **********************************************************/

 /************************************************************************************
  * Test ID                : TC_AGE_BOUNDARY_001
  * Description            : Verifies that Add_Account fails when the age is below 0.
  * Pre-requisites         : Database initialized.
  * Test Inputs            :
  *                          - Age: -1
  *                          - DOB_year: 2025 (calculated to match valid age logic)
  *                          - Name: "John Doe"
  *                          - Gender: Male
  *                          - Educational Status: Student
  *                          - Username: "johndoe123"
  *                          - Password: "ValidPass123"
  *                          - Password Recheck: "ValidPass123"
  * Expected Results       : Add_Account returns FALSE, and no user is added to the database.
  *************************************************************************************/
void TC_AGE_BOUNDARY_001(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.Age = -1;
    user.PersonalInfo_Form.DOB_year = 2025; // Consistent with age
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/************************************************************************************
 * Test ID                : TC_AGE_BOUNDARY_002
 * Description            : Verifies that Add_Account succeeds when the age is exactly 0 (newborn baby).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Age: 0
 *                          - DOB_year: 2024 (calculated to match age logic)
 *                          - Name: "John Doe"
 *                          - Gender: Male
 *                          - Educational Status: Student
 *                          - Username: "johndoe123"
 *                          - Password: "ValidPass123"
 *                          - Password Recheck: "ValidPass123"
 * Expected Results       : Add_Account returns TRUE, and the user is successfully added to the database.
 *************************************************************************************/
void TC_AGE_BOUNDARY_002(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.Age = 0;           // Set age to 0
    user.PersonalInfo_Form.DOB_year = 2024;  // Match current year for newborn
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}


/************************************************************************************
 * Test ID                : TC_AGE_BOUNDARY_003
 * Description            : Verifies that Add_Account succeeds when the age is exactly 100.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Age: 100
 *                          - DOB_year: 1924 (calculated to match valid age logic)
 *                          - Name: "John Doe"
 *                          - Gender: Male
 *                          - Educational Status: Student
 *                          - Username: "johndoe123"
 *                          - Password: "ValidPass123"
 *                          - Password Recheck: "ValidPass123"
 * Expected Results       : Add_Account returns TRUE, and the user is successfully added to the database.
 *************************************************************************************/
void TC_AGE_BOUNDARY_003(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.Age = 100;
    user.PersonalInfo_Form.DOB_year = 1924; // Consistent with age
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}
/************************************************************************************
 * Test ID                : TC_AGE_BOUNDARY_004
 * Description            : Verifies that Add_Account fails when the age is above 100.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Age: 101
 *                          - DOB_year: 1923 (calculated to match valid age logic)
 *                          - Name: "John Doe"
 *                          - Gender: Male
 *                          - Educational Status: Student
 *                          - Username: "johndoe123"
 *                          - Password: "ValidPass123"
 *                          - Password Recheck: "ValidPass123"
 * Expected Results       : Add_Account returns FALSE, and no user is added to the database.
 *************************************************************************************/
void TC_AGE_BOUNDARY_004(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.Age = 101;
    user.PersonalInfo_Form.DOB_year = 1923; // Consistent with age
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}
/***********************************************************
 *               Test Suite 11 Add Account Age tests
 **********************************************************/

/************************************************************************************
 * Test ID                : TC_AGE_YEAR_CONSISTENCY_001
 * Description            : Verifies that Add_Account fails when the age and year are inconsistent (too young).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Age: 5
 *                          - DOB: 1990
 *                          - Name: "John Doe"
 *                          - Gender: Male
 *                          - Educational Status: Student
 *                          - Username: "johndoe123"
 *                          - Password: "ValidPass123"
 *                          - Password Recheck: "ValidPass123"
 * Expected Results       : Add_Account returns FALSE, and no user is added to the database.
 *************************************************************************************/
void TC_AGE_YEAR_CONSISTENCY_001(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.Age = 5;
    user.PersonalInfo_Form.DOB_year = 1990;
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/************************************************************************************
 * Test ID                : TC_AGE_YEAR_CONSISTENCY_002
 * Description            : Verifies that Add_Account fails when the age and year are inconsistent (too old).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Age: 50
 *                          - DOB: 2020
 *                          - Name: "John Doe"
 *                          - Gender: Male
 *                          - Educational Status: Student
 *                          - Username: "johndoe123"
 *                          - Password: "ValidPass123"
 *                          - Password Recheck: "ValidPass123"
 * Expected Results       : Add_Account returns FALSE, and no user is added to the database.
 *************************************************************************************/
void TC_AGE_YEAR_CONSISTENCY_002(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.Age = 50;
    user.PersonalInfo_Form.DOB_year = 2020;
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/***********************************************************
 *               Test Suite 12 Add Account Age tests
 **********************************************************/
 /************************************************************************************
  * Test ID                : TC_DOB_DAY_001
  * Description            : Verifies that Add_Account fails when the day is below the minimum (0).
  * Pre-requisites         : Database initialized.
  * Test Inputs            :
  *                          - DOB_day: 0
  *                          - DOB_month: 8
  *                          - DOB_year: 2001
  * Expected Results       : Add_Account returns FALSE.
  *************************************************************************************/
void TC_DOB_DAY_001(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_day = 0;
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/************************************************************************************
 * Test ID                : TC_DOB_DAY_002
 * Description            : Verifies that Add_Account succeeds when the day is at the minimum (1).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - DOB_day: 1
 *                          - DOB_month: 8
 *                          - DOB_year: 2001
 * Expected Results       : Add_Account returns TRUE.
 *************************************************************************************/
void TC_DOB_DAY_002(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_day = 1;
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}

/************************************************************************************
 * Test ID                : TC_DOB_DAY_003
 * Description            : Verifies that Add_Account succeeds when the day is at the maximum for 31-day months.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - DOB_day: 31
 *                          - DOB_month: 8
 *                          - DOB_year: 2001
 * Expected Results       : Add_Account returns TRUE.
 *************************************************************************************/
void TC_DOB_DAY_003(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_day = 31;
    user.PersonalInfo_Form.DOB_month = 7; // July (31 days)
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}

/************************************************************************************
 * Test ID                : TC_DOB_DAY_004
 * Description            : Verifies that Add_Account fails when the day exceeds the maximum for specific months.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - DOB_day: 31
 *                          - DOB_month: 4
 *                          - DOB_year: 2001
 * Expected Results       : Add_Account returns FALSE.
 *************************************************************************************/
void TC_DOB_DAY_004(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_day = 31;
    user.PersonalInfo_Form.DOB_month = 4; // April (30 days)
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/***********************************************************
 *               Test Suite 13 Add Account Age tests
 **********************************************************/

/************************************************************************************
 * Test ID                : TC_DOB_MONTH_001
 * Description            : Verifies that Add_Account fails when the month is below the minimum (0).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - DOB_month: 0
 * Expected Results       : Add_Account returns FALSE.
 *************************************************************************************/
void TC_DOB_MONTH_001(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_month = 0;
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/************************************************************************************
 * Test ID                : TC_DOB_MONTH_002
 * Description            : Verifies that Add_Account succeeds when the month is at the minimum (1).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - DOB_month: 1
 * Expected Results       : Add_Account returns TRUE.
 *************************************************************************************/
void TC_DOB_MONTH_002(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_month = 1;
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}

/************************************************************************************
 * Test ID                : TC_DOB_MONTH_003
 * Description            : Verifies that Add_Account succeeds when the month is at the maximum (12).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - DOB_month: 12
 * Expected Results       : Add_Account returns TRUE.
 *************************************************************************************/
void TC_DOB_MONTH_003(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_month = 12;
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}

/************************************************************************************
 * Test ID                : TC_DOB_MONTH_004
 * Description            : Verifies that Add_Account fails when the month exceeds the maximum (13).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - DOB_month: 13
 * Expected Results       : Add_Account returns FALSE.
 *************************************************************************************/
void TC_DOB_MONTH_004(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_month = 13;
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/***********************************************************
 *               Test Suite 14 Add Account Age tests
 **********************************************************/

/************************************************************************************
 * Test ID                : TC_DOB_YEAR_001
 * Description            : Verifies that Add_Account fails when the year is below the minimum (1923).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - DOB_year: 1923
 *                          - Age: 101
 * Expected Results       : Add_Account returns FALSE.
 *************************************************************************************/
void TC_DOB_YEAR_001(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_year = 1923; // Below minimum year
    user.PersonalInfo_Form.Age = 101;       // Age consistent with year
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/************************************************************************************
 * Test ID                : TC_DOB_YEAR_002
 * Description            : Verifies that Add_Account succeeds when the year is at the minimum (1924).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - DOB_year: 1924
 *                          - Age: 100
 * Expected Results       : Add_Account returns TRUE.
 *************************************************************************************/
void TC_DOB_YEAR_002(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_year = 1924; // Minimum valid year
    user.PersonalInfo_Form.Age = 100;       // Age consistent with year
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}

/************************************************************************************
 * Test ID                : TC_DOB_YEAR_003
 * Description            : Verifies that Add_Account succeeds when the year is at the maximum (2024).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - DOB_year: 2024
 *                          - Age: 0
 * Expected Results       : Add_Account returns TRUE.
 *************************************************************************************/
void TC_DOB_YEAR_003(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_year = 2024; // Maximum valid year
    user.PersonalInfo_Form.Age = 0;         // Age consistent with year (newborn)
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}

/************************************************************************************
 * Test ID                : TC_DOB_YEAR_004
 * Description            : Verifies that Add_Account fails when the year exceeds the maximum (2025).
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - DOB_year: 2025
 *                          - Age: -1
 * Expected Results       : Add_Account returns FALSE.
 *************************************************************************************/
void TC_DOB_YEAR_004(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.DOB_year = 2025; // Above maximum year
    user.PersonalInfo_Form.Age = -1;        // Age consistent with year
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}


/***********************************************************
 *               Test Suite 15 Add Account USERNAME tests
 **********************************************************/

 /************************************************************************************
  * Test ID                : TC_USERNAME_001
  * Description            : Verifies that Add_Account fails when the username is too short.
  * Pre-requisites         : Database initialized.
  * Test Inputs            :
  *                          - Username: "short"
  * Expected Results       : Add_Account returns FALSE.
  *************************************************************************************/
void TC_USERNAME_001(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    strcpy(user.LoginCredentials_Form.LoginCredentials.User_Name, "short");
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/************************************************************************************
 * Test ID                : TC_USERNAME_002
 * Description            : Verifies that Add_Account succeeds when the username is at minimum length.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Username: "validuse"
 * Expected Results       : Add_Account returns TRUE.
 *************************************************************************************/
void TC_USERNAME_002(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    strcpy(user.LoginCredentials_Form.LoginCredentials.User_Name, "validuse");
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}

/************************************************************************************
 * Test ID                : TC_USERNAME_003
 * Description            : Verifies that Add_Account succeeds when the username is at maximum length.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Username: "validusernamelengthmaximum123456"
 * Expected Results       : Add_Account returns TRUE.
 *************************************************************************************/
void TC_USERNAME_003(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    strcpy(user.LoginCredentials_Form.LoginCredentials.User_Name, "validusernamelengthmaximum123456");
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}

/************************************************************************************
 * Test ID                : TC_USERNAME_004
 * Description            : Verifies that Add_Account fails when the username exceeds the maximum length.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Username: "validusernamelengthmaximumexceede"
 * Expected Results       : Add_Account returns FALSE.
 *************************************************************************************/
void TC_USERNAME_004(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    strcpy(user.LoginCredentials_Form.LoginCredentials.User_Name, "validusernamelengthmaximumexceede");
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}


/***********************************************************
 *               Test Suite 16 Add Account ASSWORD_MISMATCH tests
 **********************************************************/

/************************************************************************************
 * Test ID                : TC_PASSWORD_MISMATCH_001
 * Description            : Verifies that Add_Account fails when passwords do not match.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Password: "ValidPass123"
 *                          - Password_Recheck: "differentpassword"
 * Expected Results       : Add_Account returns FALSE.
 *************************************************************************************/
void TC_PASSWORD_MISMATCH_001(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    strcpy(user.LoginCredentials_Form.Password_Recheck, "differentpassword");
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}


/***********************************************************
 *               Test Suite 17 Add Account Gender tests
 **********************************************************/

 /************************************************************************************
  * Test ID                : TC_GENDER_001
  * Description            : Verifies that Add_Account fails when the gender is invalid.
  * Pre-requisites         : Database initialized.
  * Test Inputs            :
  *                          - Gender: DEFAULT_Gender
  * Expected Results       : Add_Account returns FALSE.
  *************************************************************************************/
void TC_GENDER_001(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.gender = DEFAULT_Gender; // Invalid gender
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/************************************************************************************
 * Test ID                : TC_GENDER_002
 * Description            : Verifies that Add_Account succeeds when the gender is Female.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Gender: Female
 * Expected Results       : Add_Account returns TRUE.
 *************************************************************************************/
void TC_GENDER_002(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.gender = Female; // Valid gender
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}

/***********************************************************
 *               Test Suite 17 Add Account Educational tests
 **********************************************************/
 /************************************************************************************
  * Test ID                : TC_EDUC_STATUS_001
  * Description            : Verifies that Add_Account fails when the educational status is invalid.
  * Pre-requisites         : Database initialized.
  * Test Inputs            :
  *                          - Educational Status: DEFAULT_Status
  * Expected Results       : Add_Account returns FALSE.
  *************************************************************************************/
void TC_EDUC_STATUS_001(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.educational_status = DEFAULT_Status; // Invalid status
    CU_ASSERT_EQUAL(Add_Account(&user), FALSE);
}

/************************************************************************************
 * Test ID                : TC_EDUC_STATUS_002
 * Description            : Verifies that Add_Account succeeds when the educational status is PHD_Student.
 * Pre-requisites         : Database initialized.
 * Test Inputs            :
 *                          - Educational Status: PHD_Student
 * Expected Results       : Add_Account returns TRUE.
 *************************************************************************************/
void TC_EDUC_STATUS_002(void) {
    struct User_Input_Type user;
    create_valid_user_input(&user);
    user.PersonalInfo_Form.educational_status = PHD_Student; // Valid status
    CU_ASSERT_EQUAL(Add_Account(&user), TRUE);
}
/***********************************************************
 *               Test Suite 18 delete Account
 **********************************************************/
 /************************************************************************************
  * Test ID                : TC_DELETE_ACCOUNT_001
  * Description            : Verifies that deleting a valid user ID works.
  * Pre-requisites         : Database initialized with user ID 1.
  * Test Inputs            : user_id = 1
  * Expected Results       : Function returns TRUE, user is removed.
  *************************************************************************************/
void TC_DELETE_ACCOUNT_001(void) {
    unsigned char result = Delete_Account(1);
    CU_ASSERT_EQUAL(result, TRUE);
}

/************************************************************************************
 * Test ID                : TC_DELETE_ACCOUNT_002
 * Description            : Verifies that deleting the first user ID (0) works.
 * Pre-requisites         : Database initialized with user ID 0.
 * Test Inputs            : user_id = 0
 * Expected Results       : Function returns TRUE, user is removed.
 *************************************************************************************/
void TC_DELETE_ACCOUNT_002(void) {
    unsigned char result = Delete_Account(0);
    CU_ASSERT_EQUAL(result, TRUE);
}

/************************************************************************************
 * Test ID                : TC_DELETE_ACCOUNT_003
 * Description            : Verifies that deleting the last user ID works.
 * Pre-requisites         : Database initialized with the last user ID.
 * Test Inputs            : user_id = MAX_USERS - 1
 * Expected Results       : Function returns TRUE, user is removed.
 *************************************************************************************/
void TC_DELETE_ACCOUNT_003(void) {
    unsigned char result = Delete_Account(MAX_USERS - 1);
    CU_ASSERT_EQUAL(result, TRUE);
}

/************************************************************************************
 * Test ID                : TC_DELETE_ACCOUNT_004
 * Description            : Verifies that deleting a user ID less than 0 fails.
 * Pre-requisites         : Database initialized.
 * Test Inputs            : user_id = -1
 * Expected Results       : Function returns FALSE.
 *************************************************************************************/
void TC_DELETE_ACCOUNT_004(void) {
    unsigned char result = Delete_Account(-1);
    CU_ASSERT_EQUAL(result, FALSE);
}

/************************************************************************************
 * Test ID                : TC_DELETE_ACCOUNT_005
 * Description            : Verifies that deleting a user ID greater than MAX_USERS fails.
 * Pre-requisites         : Database initialized.
 * Test Inputs            : user_id = MAX_USERS
 * Expected Results       : Function returns FALSE.
 *************************************************************************************/
//Failed
//Root Cause : must not accept id MAX_USERS (condition needs to be user_id >= MAX_USERS)
void TC_DELETE_ACCOUNT_005(void) {
    unsigned char result = Delete_Account(MAX_USERS);
    CU_ASSERT_EQUAL(result, FALSE);
}


/************************************************************************************
 * Test Runner
 *************************************************************************************/
void Main_Test_Runner(void) {
    /* Initialize the Registry */
    CU_initialize_registry();

    /* Adding Test Suite to the Registry */
    CU_pSuite suite_detect_user_type = CU_add_suite("Detect User Type Tests", NULL, NULL);

    /* Adding Test Cases to the Test Suite */
    CU_add_test(suite_detect_user_type, "Test Detect_User_Type Admin Input ", TC_USER_TYPE_001);
    CU_add_test(suite_detect_user_type, "Test Detect_User_Type NormalUser Input", TC_USER_TYPE_002);
    CU_add_test(suite_detect_user_type, "Test Detect_User_Type Incorrect User Input", TC_USER_TYPE_003);

    CU_pSuite suite_verify_admin = CU_add_suite("Verify Admin Login Tests", NULL, NULL);

    CU_add_test(suite_verify_admin, "Test Admin Login Success on First Attempt", TC_VERIFY_ADMIN_001);
    CU_add_test(suite_verify_admin, "Test Admin Login Success on Second Attempt", TC_VERIFY_ADMIN_002);
    CU_add_test(suite_verify_admin, "Test Admin Login Success on Third Attempt", TC_VERIFY_ADMIN_003);
    CU_add_test(suite_verify_admin, "Test Admin Login Failure After Three Attempts", TC_VERIFY_ADMIN_004);

    CU_pSuite suite_verify_user = CU_add_suite("Verify User Login Tests", NULL, NULL);

    CU_add_test(suite_verify_user, "TC_VERIFY_USER_001: Test User Login Success", TC_VERIFY_USER_001);
    CU_add_test(suite_verify_user, "TC_VERIFY_USER_002: Test User Login Failure - Incorrect Password", TC_VERIFY_USER_002);
    CU_add_test(suite_verify_user, "TC_VERIFY_USER_003: Test User Login Failure - Nonexistent Username", TC_VERIFY_USER_003);

    CU_pSuite suite_main_app_runner = CU_add_suite("Main App Runner Tests", NULL, NULL);

    CU_add_test(suite_main_app_runner, "Test Transition from Main_App_Runner to Admin_Runner and Back", TC_MAIN_APP_001);

    CU_pSuite suite_dbm_add_user = CU_add_suite("DBM_Add_User Tests", NULL, NULL);

    CU_add_test(suite_dbm_add_user, "TC_DBM_ADD_USER_001: Test Add Valid User", TC_DBM_ADD_USER_001);
    CU_add_test(suite_dbm_add_user, "TC_DBM_ADD_USER_002: Test Add User Beyond Max Capacity", TC_DBM_ADD_USER_002);

    CU_pSuite suite_dbm_delete_user = CU_add_suite("DBM_Delete_User Tests", NULL, NULL);

    CU_add_test(suite_dbm_delete_user, "TC_DBM_DELETE_USER_001: Test Delete Valid User", TC_DBM_DELETE_USER_001);
    CU_add_test(suite_dbm_delete_user, "TC_DBM_DELETE_USER_002: Test Delete User Greater Than Max Users", TC_DBM_DELETE_USER_002);
    CU_add_test(suite_dbm_delete_user, "TC_DBM_DELETE_USER_003: Test Delete User Less Than Zero", TC_DBM_DELETE_USER_003);
    CU_add_test(suite_dbm_delete_user, "TC_DBM_DELETE_USER_004: Test Delete Last User", TC_DBM_DELETE_USER_004);

    /* Add a Suite for DBM_AddToCourse Tests */
    CU_pSuite suite_DB_add_to_course = CU_add_suite("DBM_AddToCourse Tests", NULL, NULL);

    /* Add Test Cases to the Suite */
    CU_add_test(suite_DB_add_to_course, "TC_DBM_ADD_COURSE_001: Add Valid User to Valid Course", TC_DBM_ADD_COURSE_001);
    CU_add_test(suite_DB_add_to_course, "TC_DBM_ADD_COURSE_002: Add User Already Enrolled in the Course", TC_DBM_ADD_COURSE_002);
    CU_add_test(suite_DB_add_to_course, "TC_DBM_ADD_COURSE_003: Add User to Full Course", TC_DBM_ADD_COURSE_003);
    CU_add_test(suite_DB_add_to_course, "TC_DBM_ADD_COURSE_004: Add Non-Existent User to a Course", TC_DBM_ADD_COURSE_004);
    CU_add_test(suite_DB_add_to_course, "TC_DBM_ADD_COURSE_005: Add User to Non-Existent Course", TC_DBM_ADD_COURSE_005);

    /* Add a Suite for DBM_DeleteReservation Tests */
    CU_pSuite suite_del_reservation = CU_add_suite("DBM_DeleteReservation Tests", NULL, NULL);

    /* Add Test Cases to the Suite */
    CU_add_test(suite_del_reservation, "TC_DBM_DEL_RES_001: Delete Valid Reservation", TC_DBM_DEL_RES_001);
    CU_add_test(suite_del_reservation, "TC_DBM_DEL_RES_002: No Enrolled Students", TC_DBM_DEL_RES_002);
    CU_add_test(suite_del_reservation, "TC_DBM_DEL_RES_003: No Reservation for Use", TC_DBM_DEL_RES_003);

    /* Add a Suite for AddStudentToCourse  Tests */
    CU_pSuite suite_add_to_course = CU_add_suite("AddStudentToCourse Tests", NULL, NULL);

	/* Add Test Cases to the Suite */
    CU_add_test(suite_add_to_course, "TC_ADD_TO_COURSE_001: Add Valid Student to Valid Course", TC_ADD_TO_COURSE_001);
    CU_add_test(suite_add_to_course, "TC_ADD_TO_COURSE_002: Add Already Enrolled Student to Course", TC_ADD_TO_COURSE_002);

    // Add a suite for Name Length Boundary Tests
    CU_pSuite suite_name_length = CU_add_suite("Name Length Boundary Tests", NULL, NULL);

    // Add test cases to the suite
    CU_add_test(suite_name_length, "TC_NAME_LENGTH_001: Name Too Short", TC_NAME_LENGTH_001);
    CU_add_test(suite_name_length, "TC_NAME_LENGTH_002: Name at Minimum Length", TC_NAME_LENGTH_002);
    CU_add_test(suite_name_length, "TC_NAME_LENGTH_003: Name at Maximum Length", TC_NAME_LENGTH_003);
    CU_add_test(suite_name_length, "TC_NAME_LENGTH_004: Name Too Long", TC_NAME_LENGTH_004);
       
    // Add Test Suite for AGE_BOUNDARY Tests
    CU_pSuite suite_age_boundary = CU_add_suite("AGE_BOUNDARY Tests", NULL, NULL);

    // Add Test Cases to the AGE_BOUNDARY Test Suite
    CU_add_test(suite_age_boundary, "TC_AGE_BOUNDARY_001: Age Below Minimum", TC_AGE_BOUNDARY_001);
    CU_add_test(suite_age_boundary, "TC_AGE_BOUNDARY_002: Age at Minimum", TC_AGE_BOUNDARY_002);
    CU_add_test(suite_age_boundary, "TC_AGE_BOUNDARY_003: Age at Upper Boundary", TC_AGE_BOUNDARY_003);
    CU_add_test(suite_age_boundary, "TC_AGE_BOUNDARY_004: Age Above Maximum", TC_AGE_BOUNDARY_004);

    // Add Test Suite for Age-Year Consistency Tests with NULL for init_suite and clean_suite
    CU_pSuite suite_age_year_consistency = CU_add_suite("Age-Year Consistency Tests", NULL, NULL);

    // Add Test Cases to the Age-Year Consistency Test Suite
    CU_add_test(suite_age_year_consistency, "TC_AGE_YEAR_CONSISTENCY_001: Age Too Young", TC_AGE_YEAR_CONSISTENCY_001);
    CU_add_test(suite_age_year_consistency, "TC_AGE_YEAR_CONSISTENCY_002: Age Too Old", TC_AGE_YEAR_CONSISTENCY_002);


    // Add Test Suite for Days
    CU_pSuite suite_days = CU_add_suite("DOB Day Boundary Tests", NULL, NULL);
    CU_add_test(suite_days, "TC_DOB_DAY_001: Day Below Minimum", TC_DOB_DAY_001);
    CU_add_test(suite_days, "TC_DOB_DAY_002: Day at Minimum", TC_DOB_DAY_002);
    CU_add_test(suite_days, "TC_DOB_DAY_003: Day at Maximum", TC_DOB_DAY_003);
    CU_add_test(suite_days, "TC_DOB_DAY_004: Day Above Maximum", TC_DOB_DAY_004);

     //Add Test Suite for Months
    CU_pSuite suite_months = CU_add_suite("DOB Month Boundary Tests", NULL, NULL);
    CU_add_test(suite_months, "TC_DOB_MONTH_001: Month Below Minimum", TC_DOB_MONTH_001);
    CU_add_test(suite_months, "TC_DOB_MONTH_002: Month at Minimum", TC_DOB_MONTH_002);
    CU_add_test(suite_months, "TC_DOB_MONTH_003: Month at Maximum", TC_DOB_MONTH_003);
    CU_add_test(suite_months, "TC_DOB_MONTH_004: Month Above Maximum", TC_DOB_MONTH_004);

    // Add Test Suite for Years
    CU_pSuite suite_years = CU_add_suite("DOB Year Boundary Tests", NULL, NULL);
    CU_add_test(suite_years, "TC_DOB_YEAR_001: Year Below Minimum", TC_DOB_YEAR_001);
    CU_add_test(suite_years, "TC_DOB_YEAR_002: Year at Minimum", TC_DOB_YEAR_002);
    CU_add_test(suite_years, "TC_DOB_YEAR_003: Year at Maximum", TC_DOB_YEAR_003);
    CU_add_test(suite_years, "TC_DOB_YEAR_004: Year Above Maximum", TC_DOB_YEAR_004);

    // Add Test Suite for Username Boundary Tests
    CU_pSuite suite_username = CU_add_suite("Username Boundary Tests", NULL, NULL);
    CU_add_test(suite_username, "TC_USERNAME_001: Username Too Short", TC_USERNAME_001);
    CU_add_test(suite_username, "TC_USERNAME_002: Username at Minimum Length", TC_USERNAME_002);
    CU_add_test(suite_username, "TC_USERNAME_003: Username at Maximum Length", TC_USERNAME_003);
    CU_add_test(suite_username, "TC_USERNAME_004: Username Too Long", TC_USERNAME_004);

    // Add Test Suite for Password Mismatch Tests
    CU_pSuite suite_password_mismatch = CU_add_suite("Password Mismatch Tests", NULL, NULL);
    CU_add_test(suite_password_mismatch, "TC_PASSWORD_MISMATCH_001: Password Mismatch", TC_PASSWORD_MISMATCH_001);

    // Add Test Suite for Gender Tests
    CU_pSuite suite_gender = CU_add_suite("Gender Tests", NULL, NULL);
    CU_add_test(suite_gender, "TC_GENDER_001: Invalid Gender", TC_GENDER_001);
    CU_add_test(suite_gender, "TC_GENDER_002: Valid Gender (Female)", TC_GENDER_002);

    // Add Test Suite for Educational Status Tests
    CU_pSuite suite_educ_status = CU_add_suite("Educational Status Tests", NULL, NULL);
    CU_add_test(suite_educ_status, "TC_EDUC_STATUS_001: Invalid Educational Status", TC_EDUC_STATUS_001);
    CU_add_test(suite_educ_status, "TC_EDUC_STATUS_002: Valid Educational Status (PHD)", TC_EDUC_STATUS_002);


    // Add Test Suite for Valid User Tests
    CU_pSuite suite_valid_users = CU_add_suite("Valid User Tests", NULL, NULL);
    CU_add_test(suite_valid_users, "TC_DELETE_ACCOUNT_001: Delete Valid User", TC_DELETE_ACCOUNT_001);
    CU_add_test(suite_valid_users, "TC_DELETE_ACCOUNT_002: Delete First User (Boundary)", TC_DELETE_ACCOUNT_002);
    CU_add_test(suite_valid_users, "TC_DELETE_ACCOUNT_003: Delete Last User (Boundary)", TC_DELETE_ACCOUNT_003);

    // Add Test Suite for Invalid User Tests
    CU_pSuite suite_invalid_users = CU_add_suite("Invalid User Tests", NULL, NULL);
    CU_add_test(suite_invalid_users, "TC_DELETE_ACCOUNT_004: Delete User ID < 0", TC_DELETE_ACCOUNT_004);
    CU_add_test(suite_invalid_users, "TC_DELETE_ACCOUNT_005: Delete User ID > MAX_USERS", TC_DELETE_ACCOUNT_005);



    // Return error if any test case addition failed
    if (CU_get_error() != CUE_SUCCESS) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Running the Test Suite through Basic Console */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    /* Clear the registry after test finished */
    CU_cleanup_registry();
}



