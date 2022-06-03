/********************************************************************
 *
 * hospitalDB.h
 *
 *      This header file defines data structures and declares functions
 *   	that are located in several programs used for Hospital Database.
 *		These functions add, display, validate, read and writing data
 *		in the file, search and modify the patient's data.
 *
 *      Created by Sonia Gautam (Sonia) ID 63070503410
 *      06 December 2020
 *
 ********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "dateFunctions.h"

#define FILENAME "database.dat"		/* Hospital Database's file name */
#define MAXLEN 128					/* maximum length for stringInput */

typedef struct
	{
	char passportNum[32];		/* patient's Passport number */
	char name[64];				/* patient's name */
	char dateOfBirth[16];		/* patient's date of birth */
	char dateToday[16];			/* patient's admission date */
	char phoneNum[32];			/* patient's international phone number */
	char gender[4];				/* patient's gender */
	} HOSPITALDB_T;


/* Declarations of functions in addObject program */

/**************************************************************
 *
 * This function is the major function for adding new object
 * to the database file.
 *
 * This function will call responsible functions to ask
 * the patient's information and add it into the
 * database file which contains
 *
 *      -   Passport number
 *      -   Name
 *      -   Date of Birth
 *      -   Today's date
 *      -   International phone
 *      -   Gender
 *
 * No argument.
 *
 *************************************************************/
void addData();


/**************************************************************
 *
 * This function is responsible for asking the patient's
 * Passport number and checking if it is valid or not by
 * calling 'validatePassport' function.
 *
 * pPassport is a pointer to get the address and store the
 * Passport number to the variable in that address.
 *
 *************************************************************/
void addPassportNum(char* pPassport);


/**************************************************************
 *
 * This function is responsible for asking the patient's
 * name and checking if it is valid or not by calling
 * 'validateName' function.
 *
 * pName is a pointer to get the address and store the
 * name to the variable in that address.
 *
 *************************************************************/
void addName(char* pName);


/**************************************************************
 *
 * This function is responsible for asking the patient's
 * date of birth and checking if it is valid or not by
 * calling 'validateDate' function.
 *
 * pBirth is a pointer to get the address and store the
 * date of birth to the variable in that address.
 *
 *************************************************************/
void addDateOfBirth(char* pBirth);


/**************************************************************
 *
 * This function is responsible for asking the patient's
 * international phone number and checking if it is valid or
 * not by calling 'validatePhoneNum' function.
 *
 * pPhoneNum is a pointer to get the address and store the
 * international phone number to the variable in that address.
 *
 *************************************************************/
void addPhoneNum(char* pPhoneNum);


/**************************************************************
 *
 * This function is responsible for asking the patient's
 * gender and checking if it is valid or not by calling
 * 'validateGender' function.
 *
 * pGender is a pointer to get the address and store the
 * gender to the variable in that address.
 *
 *************************************************************/
void addGender(char* pGender);


/* Declarations of functions in displayObject program */

/**************************************************************
 *
 * This function is the major function for displaying all
 * objects in the database file on the screen.
 *
 * This function checks the file if it exists or not and
 * gets the number of objects in the file. Then, allocates
 * enough memory for all objects, reads and prints each
 * patient's data on the screen.
 *
 * No argument.
 *
 *************************************************************/
void readToDisplay();


/* Declarations of functions in readWriteData program */

/**************************************************************
 *
 * This function reads the number of objects in the database
 * file and returns it to the calling function.
 *
 * No argument.
 *
 * This function returns 'objectCount' which is the number
 * of objects in the database file.
 *
 *************************************************************/
int readToCount();


/**************************************************************
 *
 * This function reads all data from the file and store each
 * patient's data in the array of structure.
 *
 * patientData[] is array of structure to store each
 * patient's data.
 *
 *************************************************************/
void readData(HOSPITALDB_T patientData[]);


/**************************************************************
 *
 * This function adds new data into the database file and
 * updates number of object in the file at the top of
 * the file.
 *
 * newData is a structure variable storing new patient's data.
 * objectCount is the number of objects in the file.
 *
 *************************************************************/
void addNewData(HOSPITALDB_T newData, int objectCount);


/**************************************************************
 *
 * This function writes the number of objects in the database
 * file and writes modified version data into the
 * database file.
 *
 * data[] is array of structure storing all patient's data.
 * objectCount is the number of objects in the file.
 *
 *************************************************************/
void addModifiedData(HOSPITALDB_T data[], int objectCount);


/**************************************************************
 *
 * This function checks if the database file exists or not.
 * If not, the new database file will be created and number
 * of object in the file (zero at initial) will be written.
 *
 * No argument.
 *
 * This function returns 'status' which is 1 when the
 * database file is found, otherwise 0.
 *
 *************************************************************/
int checkFile();


/* Declarations of functions in searchObject program */

/**************************************************************
 *
 * This function is the major function for searching the
 * objects that is in the database file.
 *
 * This function lets the user select three options for
 * searching the data, which are
 *
 *      [1] - Search by Passport number
 *      [2] - Search by Name
 *      [3] - Exit searching / modifying
 *
 * This function will call responsible function for each
 * way of searching the patient's data.
 *
 * No argument.
 *
 *************************************************************/
void searchData();


/* Declarations of functions in validateData program */

/**************************************************************
 *
 * This function deletes the space after the input and space
 * that user may accidentally entered.
 *
 * input[] is the input data from the user
 *
 *************************************************************/
void deleteSpace(char input[]);


/**************************************************************
 *
 * This function checks the input if the user wrote nothing
 * and pressed enter or not.
 *
 * input[] is the input data from the user
 *
 * This function returns 'result' which is 0 when nothing
 * is written, otherwise 1.
 *
 *************************************************************/
int checkEnter(char input[]);


/**************************************************************
 *
 * This function is a major validation function used to validate
 * passport number with country code.
 * This function calls other functions to check invalid cases.
 *
 * passportNum[] is the input passport number from the user.
 *
 * This function returns 'validNum' which is 0 when invalid
 * and 1 when valid to the function calling this function.
 *
 *************************************************************/
int validatePassport(char passportNum[]);


/**************************************************************
 *
 * This function checks if the name contains only letters,
 * digits and spaces or not
 *
 * name[] is the input name from the user.
 *
 * This function returns 'result' which is 1 when the input
 * contains only letters, digits and spaces. Otherwise 0.
 *
 *************************************************************/
int validateName(char name[]);


/**************************************************************
 *
 * This function is a major validation function used to validate
 * date in form dd/mm/yyyy in Buddhist year.
 * This function calls other functions to check invalid cases.
 *
 * 'dd'   - means a two digit day
 * 'mm'   - means a two digit month
 * 'yyyy' - means a year in Buddhist year format
 *
 * date[] is the input date from the user
 *
 * This function returns 'validNum' which is 0 when invalid
 * and 1 when valid to the function calling this function.
 *
 *************************************************************/
int validateDate(char date[]);


/**************************************************************
 *
 * This function gets today's date by calling 'dateToday'.
 *
 * date[] is the variable to store today's date
 *
 *************************************************************/
void todaysDate(char date[]);


/**************************************************************
 *
 * This function is a major validation function used to validate
 * international phone number.
 * This function calls other functions to check invalid cases.
 *
 * number[] is the input phone number from the user
 *
 * This function returns 'validNum' which is 0 when invalid
 * and 1 when valid to the function calling this function.
 *
 *************************************************************/
int validatePhoneNum(char number[]);


/**************************************************************
 *
 * This function checks if the gender entered by the user is
 * correct or not.
 *
 * F - Female   M - Male    O - Other
 *
 * gender[] is the input gender from the user.
 *
 * This function returns 'result' which is 1 when the input
 * gender is in correct format. Otherwise 0.
 *
 *************************************************************/
int validateGender(char gender[]);


