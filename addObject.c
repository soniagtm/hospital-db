/********************************************************************
 *
 * addObject.c
 *
 *      This program is responsible for adding a new object
 *      to the Hospital Database. The program will ask for
 *      the information needed then save it in the file.
 *
 *      Created by Sonia Gautam (Sonia) ID 63070503410
 *      06 December 2020
 *
 ********************************************************************
 */
#include "hospitalDB.h"

/* Declaration of function used for adding new object */
void getDateToday(char* pToday);
int checkUnique(char input[]);

/* declared in hospitalDB.h */
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
void addData()
    {
    HOSPITALDB_T newData;       /* an instance of a HOSPITALDB_T structure */
                                /* to hold new patient's data */
    int objectCount = 0;        /* variable to store number of objects in the file */

    printf("\033[2J\033[;H");
    printf("\n************************************************");
    printf("\n  [- Add a new object to Hospital Database -]\n");
    printf("************************************************\n");
    printf("\nFill in all information!\n\n");


    /* calling each function to ask each information */
    addPassportNum(newData.passportNum);
    addName(newData.name);
    addDateOfBirth(newData.dateOfBirth);
    getDateToday(newData.dateToday);
    addPhoneNum(newData.phoneNum);
    addGender(newData.gender);

    /* get the number of objects in the file */
    objectCount = readToCount();
    objectCount++;

    /* add new data into the file */
    addNewData(newData,objectCount);

    }

/* declared in hospitalDB.h */
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
void addPassportNum(char* pPassport)
    {
    char stringInput[MAXLEN];    /* variable to get input from the user */

    while(1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf("Passport number     : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter Passport number\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pPassport);

            if (validatePassport(pPassport) == 1)
                {
                if (checkUnique(pPassport) == 1)
                    {
                    break;
                    }

                }
            }

        }
    }

/* declared in hospitalDB.h */
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
void addName(char* pName)
    {
    char stringInput[MAXLEN];    /* variable to get input from the user */

    while(1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf("Name                : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the name\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pName);

            if (validateName(pName) == 1)
                {
                break;
                }
            }
        }
    }

/* declared in hospitalDB.h */
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
void addDateOfBirth(char* pBirth)
    {
    char stringInput[MAXLEN];    /* variable to get input from the user */

    while (1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf("Date of Birth       : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter date of birth\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pBirth);

            if (validateDate(pBirth) == 1)
                {
                break;
                }
            }

        }
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function is responsible for getting today's date
 * by calling 'todaysDate' function then prints the date.
 *
 * pToday is a pointer to get the address and store today's
 * date to the variable in that address.
 *
 *************************************************************/
void getDateToday(char* pToday)
    {
    todaysDate(pToday);
    printf("Today's date        : %s\n",pToday);
    }

/* declared in hospitalDB.h */
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
void addPhoneNum(char* pPhoneNum)
    {
    char stringInput[MAXLEN];    /* variable to get input from the user */

    while (1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf("International phone : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter phone number\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pPhoneNum);

            if (validatePhoneNum(pPhoneNum) == 1)
                {
                break;
                }
            }
        }

    }

/* declared in hospitalDB.h */
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
void addGender(char* pGender)
    {
    char stringInput[MAXLEN];    /* variable to get input from the user */

    while (1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf("Gender              : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter the gender\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pGender);

            if (validateGender(pGender) == 1)
                {
                break;
                }
            }

        }
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks if the Passport number entered by the
 * user is unique or not.
 *
 * input[] is the input Passport number from the user.
 *
 * This function returns 'result' which is 1 if the input
 * Passport number is unique, otherwise 0.
 *
 *************************************************************/
int checkUnique(char input[])
    {
    HOSPITALDB_T* patientData = NULL;  /* pointer to dynamically allocated array of structure */
                                       /* to hold patient's data read from file */
    int objectCount = 0;               /* variable to store number of objects in the file */
    int fileStatus = 0;                /* to store return value from 'checkFile' */
    int result = 1;                    /* variable to store return value */
    int i = 0;                         /* loop variable */

    /* check if the database file exists or not */
    fileStatus = checkFile();

    /* get the number of objects in the file */
    objectCount = readToCount();

    if (fileStatus == 1)
        {
        /* try to allocate enough memory to hold all the patient's data */
        patientData = calloc(objectCount,sizeof(HOSPITALDB_T));

        if (patientData == NULL)
            {
            printf("Memory allocation failure - exiting\n");
            exit(0);
            }

        /* read all the patient's data */
        readData(patientData);

        for (i = 0; i < objectCount; i++)
            {
            if (strcasecmp(input,patientData[i].passportNum) == 0)
                {
                printf("\t\tThis Passport number already existed in the file\n");
                result = 0;
                break;
                }
            }

        /* free the allocated memory */
        free(patientData);

        }
    return result;
    }
