/********************************************************************
 *
 * searchObject.c
 *
 *      This program is responsible for searching and modifying
 *      patient's information in Hospital Database. Once the object
 *      is found, the user will be able to modify the data. Then the
 *      program will save the modified data into the database file
 *      The option contains
 *
 *      Created by Sonia Gautam (Sonia) ID 63070503410
 *      06 December 2020
 *
 ********************************************************************
 */
#include "hospitalDB.h"

/* Declarations of function used for searching and modifying */
void searchByPassport();
void searchByName();
void findObject(char search[], int type);
int printFoundObject(HOSPITALDB_T patientData[], int foundItem[], char search[], int objectCount, int type);
int selectObject(int objectCount);
void checkObjectNum(HOSPITALDB_T patientData[], int foundItem[], int objectCount, int objectFound, int patientNumber);
void modifyData(HOSPITALDB_T patientData[], int objectCount, int modifyNum);
void changeAllInfo(HOSPITALDB_T patientData[], int modifyNum);
int changeSomeInfo(HOSPITALDB_T patientData[], int modifyNum);
void modifyAdmissionDate(char* pDate);


/* declared in hospitalDB.h */
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
void searchData()
    {
    char stringInput[MAXLEN];   /* variable to get input from the user */
    int choice = 0;             /* variable to store user's searching choice */
    int objectCount = 0;        /* variable to store number of objects in the file */
    int fileStatus = 0;         /* to store return value from 'checkFile' */

    /* check if the database file exists or not */
    fileStatus = checkFile();

    /* get the number of objects in the file */
    objectCount = readToCount();

    if ((fileStatus == 0) || (objectCount == 0))
        {
        printf("\n\tThe database is currently empty\n\n");
        }
    else
        {
        printf("\033[2J\033[;H");
        while (1)
            {
            printf("\n**********************************************************");
            printf("\n\n [- Search for / Modify an object in Hospital Database -]\n\n");
            printf("%s[1]  Search by Passport number\n","    ");
            printf("%s[2]  Search by Name\n","    ");
            printf("%s[3]  Exit searching / modifying\n","    ");
            printf("\n**********************************************************\n\n");

            printf("What do you want to do? ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%d",&choice);

            if (choice == 1)
                {
                searchByPassport();
                }
            else if (choice == 2)
                {
                searchByName();
                }
            else if (choice == 3)
                {
                break;
                }
            else
                {
                printf("\ninvalid input - please enter only 1, 2 and 3\n");
                }
            choice = 0;
            }
        }
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function asks the Passport number from the user and
 * checks if the user pressed enter (to exit) or not. If not,
 * the function will call 'findObject' function for further
 * process of search and modification.
 *
 * No argument.
 *
 *************************************************************/
void searchByPassport()
    {
    char stringInput[MAXLEN];   /* variable to get input from the user */
    char passportNum[32];       /* variable to store Passport number*/
    int type = 1;               /* variable to store searching type (1 - by Passport number) */

    printf("\n\nSearch by Passport number\n");
    printf("%sPassport number (press ENTER to exit) : ","    ");
    fgets(stringInput,sizeof(stringInput),stdin);

    if (checkEnter(stringInput) == 1)
        {
        deleteSpace(stringInput);
        sscanf(stringInput,"%[^\n]",passportNum);
        findObject(passportNum,type);
        }

    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function asks the name to search from the user and
 * checks if the user pressed enter (to exit) or not. If not,
 * the function will call 'findObject' function for further
 * process of search and modification.
 *
 * No argument.
 *
 *************************************************************/
void searchByName()
    {
    char stringInput[MAXLEN];   /* variable to get input from the user */
    char name[64];              /* variable to store name */
    int type = 2;               /* variable to store searching type (2 - by name) */

    printf("\n\nSearch by Name\n");
    printf("%sName (press ENTER to exit) : ","    ");
    fgets(stringInput,sizeof(stringInput),stdin);

    if (checkEnter(stringInput) == 1)
        {
        deleteSpace(stringInput);
        sscanf(stringInput,"%[^\n]",name);
        findObject(name,type);
        }

    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function gets the number of objects in the file.
 * Then, allocates enough memory for all objects, reads each
 * patient's data and calls several functions for further
 * process of search and modification.
 *
 * search[] is the input information for searching.
 * type     is number to represent searching method.
 *          (1 - by Passport number , 2 - by name)
 *
 *************************************************************/
void findObject(char search[], int type)
    {
    HOSPITALDB_T* patientData = NULL;   /* pointer to dynamically allocated array of structure */
                                        /* to hold patient's data read from file */
    int* foundItem = NULL;              /* pointer to dynamically allocated array of integer */
                                        /* to hold patient number that matches with information given */
    int objectCount = 0;                /* variable to store number of objects in the file */
    int objectFound = 0;                /* variable to store return value from 'printFoundObject' */
    int patientNumber = 0;              /* variable to store return value from 'selectObject' */

    /* get the number of objects in the file */
    objectCount = readToCount();

    /* try to allocate enough memory to hold all the patient's data */
    patientData = calloc(objectCount,sizeof(HOSPITALDB_T));

    if (patientData == NULL)
        {
        printf("Memory allocation failure - exiting\n");
        exit(0);
        }

    /* try to allocate enough memory to hold patient number */
    foundItem = calloc(objectCount,sizeof(int));

    if (foundItem == NULL)
        {
        printf("Memory allocation failure - exiting\n");
        exit(0);
        }

    /* read all the patient's data */
    readData(patientData);

    /* get number of objects matched with the given information */
    objectFound = printFoundObject(patientData,foundItem,search,objectCount,type);

    if (objectFound != 0)
        {
        /* get the patient number that the user wants to modify */
        patientNumber = selectObject(objectCount);

        if (patientNumber != 0)
            {
            /* do the further process of modification */
            checkObjectNum(patientData,foundItem,objectCount,objectFound,patientNumber);
            }
        }

    /* free the allocated memory */
    free(patientData);
    free(foundItem);
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function prints the data of the patients that matches
 * with the given information.
 *
 * patientData[]    is an array of structure storing all
 *                  patient's data.
 * foundItem[]      is an array of integer to hold patient
 *                  number that matches with information given.
 * search[]         is the input information for searching.
 * objectCount      is the number of objects in the file.
 * type             is number to represent searching method.
 *                  (1 - by Passport number , 2 - by name)
 *
 * This function returns 'result' which is the number of
 * objects matching with given information.
 *
 *************************************************************/
int printFoundObject(HOSPITALDB_T patientData[], int foundItem[], char search[], int objectCount, int type)
    {
    int objectFound = 0;    /* variable to count number of objects matched with the given information */
    int result = 0;         /* variable to store return value */
    int i = 0;              /* loop variable */

    printf("\n------------------------------------------------------------\n");
    for (i = 0; i < objectCount; i++)
        {
        if (type == 1)
            {
            if (strncasecmp(search,patientData[i].passportNum,strlen(search)) == 0)
                {
                printf("Patient no. %d : %s\n",i+1,patientData[i].passportNum);
                foundItem[objectFound] = i;
                objectFound++;
                printf("------------------------------------------------------------\n");
                }
            }
        if (type == 2)
            {
            if (strncasecmp(search,patientData[i].name,strlen(search)) == 0)
                {
                printf("Patient no. %d : %s\n",i+1,patientData[i].name);
                foundItem[objectFound] = i;
                objectFound++;
                printf("------------------------------------------------------------\n");
                }
            }
        }

    if (objectFound == 0)
        {
        printf("No patient found with given information\n");
        printf("------------------------------------------------------------\n");
        }
    else
        {
        result = objectFound;
        }

    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function lets the user select the patient that he/she
 * wants to modify and checks if it is out of the range or not.
 *
 * objectCount is the number of objects in the file.
 *
 * This function returns 'result' which is the patient
 * number that the user wants to modify.
 *
 *************************************************************/
int selectObject(int objectCount)
    {
    char stringInput[MAXLEN];   /* variable to get input from the user */
    int result = 0;             /* variable to store return value */
    int patientNumber = 0;      /* variable to store the patient number that the user wants to modify */

    printf("\n");
    printf("Which patient do you want to modify (Patient no.): ");
    fgets(stringInput,sizeof(stringInput),stdin);
    sscanf(stringInput,"%d",&patientNumber);

    if ((patientNumber <= 0) || (patientNumber > objectCount))
        {
        printf("\nWrong Patient number!\n");
        }
    else
        {
        result = patientNumber;
        }

    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks if the patient number that the user
 * wants to modify matches with the patient number that
 * matches with the information given or not. If it matches,
 * this function will call 'modifyData' function to do
 * further process of modification.
 *
 * patientData[]    is an array of structure storing all
 *                  patient's data.
 * foundItem[]      is an array of integer holding patient
 *                  number that matches with information given.
 * objectCount      is the number of objects in the file.
 * objectFound      is the number of objects matched with the
 *                  given information.
 * patientNumber    is the patient number that the user
 *                  wants to modify.
 *
 *************************************************************/
void checkObjectNum(HOSPITALDB_T patientData[], int foundItem[], int objectCount, int objectFound, int patientNumber)
    {
    int i = 0;             /* loop variable */
    int modifyNum = -1;    /* variable to get number of the patient that the user wants to modify */

    /* change to array subscript */
    patientNumber = patientNumber - 1;

    for (i = 0; i < objectFound; i++)
        {
        if (patientNumber == foundItem[i])
            {
            modifyNum = foundItem[i];
            break;
            }
        }

    if (modifyNum == -1)
        {
        printf("\nWrong Patient no!\n");
        }
    else
        {
        /* do the further process of modification */
        modifyData(patientData,objectCount,modifyNum);
        }
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function displays the patient that the user wants to
 * modify's data and confirms if he/she wants to modify it or
 * not. If he/she wants to modify, this function will ask if
 * he/she wants to modify all information or just some of it.
 * Then, the function will call responsible function for
 * each operation. Finally, this function will call
 * 'addModifiedData' to save the modified data into the
 * database file.
 *
 * patientData[]    is an array of structure storing all
 *                  patient's data.
 * objectCount      is the number of objects in the file.
 * modifyNum        is number of the patient that the user
 *                  wants to modify.
 *
 *************************************************************/
void modifyData(HOSPITALDB_T patientData[], int objectCount, int modifyNum)
    {
    char stringInput[MAXLEN];   /* variable to get input from the user */
    char demand[4];             /* variable to store answer if user wants to modify or not */
    char selectOption[4];       /* variable to store answer if user wants to modify all info or not */
    int infoChangeCount = 0;    /* variable to count how many times data have been changed */

    printf("\n**********************************************************\n");
    printf("\nPatient no. %d\n\n",modifyNum+1);
    printf("Passport number     : %s\n",patientData[modifyNum].passportNum);
    printf("Name                : %s\n",patientData[modifyNum].name);
    printf("Date of Birth       : %s\n",patientData[modifyNum].dateOfBirth);
    printf("Admission date      : %s\n",patientData[modifyNum].dateToday);
    printf("International phone : %s\n",patientData[modifyNum].phoneNum);
    printf("Gender              : %s\n",patientData[modifyNum].gender);
    printf("\n**********************************************************\n\n");

    printf("Do you want to modify? (Y - yes , other alphabet - no): ");
    fgets(stringInput,sizeof(stringInput),stdin);
    sscanf(stringInput,"%s",demand);

    if (strcasecmp(demand,"Y") == 0)
        {
        while (1)
            {
            memset(selectOption,0,sizeof(selectOption));
            printf("\nDo you want to modify all information? (Y or N): ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",selectOption);

            if (strcasecmp(selectOption,"Y") == 0)
                {
                infoChangeCount = 6;
                changeAllInfo(patientData,modifyNum);
                break;
                }
            else if (strcasecmp(selectOption,"N") == 0)
                {
                infoChangeCount = changeSomeInfo(patientData,modifyNum);
                break;
                }
            else
                {
                printf("Please enter only 'Y' or 'N'\n");
                }
            }

        if (infoChangeCount > 0)
            {
            /* add modified version data into the file */
            addModifiedData(patientData,objectCount);
            }

        }
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function gets new data from the user to modify the
 * old data. The data contains
 *
 *      -   Passport number
 *      -   Name
 *      -   Date of Birth
 *      -   Admission date
 *      -   International phone
 *      -   Gender
 *
 * patientData[]    is an array of structure storing all
 *                  patient's data.
 * modifyNum        is number of the patient that the user
 *                  wants to modify.
 *
 *************************************************************/
void changeAllInfo(HOSPITALDB_T patientData[], int modifyNum)
    {
    printf("\n");

    /* calling each function to modify each information */
    addPassportNum(patientData[modifyNum].passportNum);

    addName(patientData[modifyNum].name);

    addDateOfBirth(patientData[modifyNum].dateOfBirth);

    modifyAdmissionDate(patientData[modifyNum].dateToday);

    addPhoneNum(patientData[modifyNum].phoneNum);

    addGender(patientData[modifyNum].gender);
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function asks the user which part of the patient's
 * data he/she wants to modify. Then, gets new data from the
 * user to modify the old data. The option contains
 *
 *      -   Passport number
 *      -   Name
 *      -   Date of Birth
 *      -   Admission date
 *      -   International phone
 *      -   Gender
 *
 * patientData[]    is an array of structure storing all
 *                  patient's data.
 * modifyNum        is number of the patient that the user
 *                  wants to modify.
 *
 * This function returns 'infoChangeCount' which is the times
 * data have been changed.
 *
 *************************************************************/
int changeSomeInfo(HOSPITALDB_T patientData[], int modifyNum)
    {
    char stringInput[MAXLEN];   /* variable to get input from the user */
    char status[4];             /* variable to track if user wants to continue modifying or not */
    int option = 0;             /* to store option that user selects to modify */
    int infoChangeCount = 0;    /* variable to count how many times data have been changed */

    while (1)
        {

        printf("\n");
        printf("[1] - Passport number     : %s\n",patientData[modifyNum].passportNum);
        printf("[2] - Name                : %s\n",patientData[modifyNum].name);
        printf("[3] - Date of Birth       : %s\n",patientData[modifyNum].dateOfBirth);
        printf("[4] - Admission date      : %s\n",patientData[modifyNum].dateToday);
        printf("[5] - International phone : %s\n",patientData[modifyNum].phoneNum);
        printf("[6] - Gender              : %s\n",patientData[modifyNum].gender);

        printf("\nwhich option do you want to modify : ");
        fgets(stringInput,sizeof(stringInput),stdin);
        sscanf(stringInput,"%d",&option);
        printf("\n");

        switch (option)
            {
            case 1:
				addPassportNum(patientData[modifyNum].passportNum);
				infoChangeCount++;
                break;
            case 2:
				addName(patientData[modifyNum].name);
				infoChangeCount++;
                break;
            case 3:
				addDateOfBirth(patientData[modifyNum].dateOfBirth);
				infoChangeCount++;
                break;
            case 4:
                modifyAdmissionDate(patientData[modifyNum].dateToday);
                infoChangeCount++;
                break;
            case 5:
                addPhoneNum(patientData[modifyNum].phoneNum);
                infoChangeCount++;
                break;
            case 6:
                addGender(patientData[modifyNum].gender);
                infoChangeCount++;
                break;
            default:
                printf("\tinvalid input - should be an integer between 1 and 6\n");
            }

        printf("\nContinue modifying? (C - continue , other alphabet - exit) : ");
        fgets(stringInput,sizeof(stringInput),stdin);
        sscanf(stringInput,"%s",status);

        if (strcasecmp(status,"C") != 0)
            {
            break;
            }

        option = 0;
        }
    return infoChangeCount;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function is responsible for asking the patient's
 * admission date to modify and checking if it is valid or
 * not by calling 'validateDate' function.
 *
 * pDate is a pointer to get the address and store the
 * admission date to the variable in that address.
 *
 *************************************************************/
void modifyAdmissionDate(char* pDate)
    {
    char stringInput[MAXLEN];    /* variable to get input from the user */

    while (1)
        {
        memset(stringInput,0,sizeof(stringInput));
        printf("Admission date      : ");
        fgets(stringInput,sizeof(stringInput),stdin);

        if (checkEnter(stringInput) == 0)
            {
            printf("\t\tPlease enter admission date\n");
            }
        else
            {
            deleteSpace(stringInput);
            sscanf(stringInput,"%[^\n]",pDate);

            if (validateDate(pDate) == 1)
                {
                break;
                }
            }
        }
    }

