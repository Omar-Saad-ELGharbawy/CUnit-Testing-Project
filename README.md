# CUnit-Testing-Project

## Project Overview
This project focuses on testing the **EDGES Reservation Software**, a C-based application, using the **CUnit framework**. The goal is to ensure software reliability by designing, executing, and documenting **test cases** and **test suites** while achieving high coverage across various testing techniques.

## Features
- **Automated testing** of key functionalities such as user login, account creation, course registration, and database operations.
- **Test suite execution** covering multiple test cases for different software modules.
- **Coverage analysis** including **Statement Coverage, Branch Coverage, MC/DC, State Transition, and Boundary Value Analysis**.
- **Bug reporting and tracking** for failed test cases.


## Technologies Used
- **C Programming Language**
- **CUnit Testing Framework**

## Test Execution Summary
- **Test Suites Executed:** 21  
  - **Failed Suites:** 0
- **Total Tests Executed:** 63  
  - **Failed Tests:** 8
- **Total Asserts Executed:** 112  
  - **Failed Asserts:** 9

## Coverage Metrics
| Module              | Statement Coverage | Branch Coverage | MC/DC Coverage | BVA Coverage | State Transition Coverage |
|---------------------|-------------------|----------------|---------------|-------------|----------------------|
| App                | ~100%             | ~100%          | N/A           | N/A         | ~100%               |
| Back End           | ~20%              | ~20%           | N/A           | N/A         | ~20%                |
| Course Registration| ~50%              | ~50%           | ~50%          | N/A         | N/A                 |
| Create Account     | ~100%             | ~100%          | ~100%         | ~100%       | N/A                 |
| DB Manager        | ~90%              | ~90%           | ~90%          | N/A         | N/A                 |
| Login              | ~100%             | ~100%          | ~100%         | N/A         | ~100%               |

## Setup & Running Tests
### **Prerequisites**
- Install **CUnit** (CUnit Testing Framework)
- Ensure a **C compiler** (GCC recommended) is installed


## Deliverables
- **Test case report**: Detailed test steps, inputs, outputs, and techniques used.
- **Bug report**: Identified defects, expected vs actual results, and root cause analysis.
- **Test completion report**: Summary of test execution and achieved coverage.

## Author
**Omar Saad Elgharbawy**



