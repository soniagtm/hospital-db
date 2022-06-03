/********************************************************************
 *
 * displayObject.c
 *
 *      This program is responsible for displaying each patient's
 *      data in the Hospital Database. The information contains
 *
 *          - Patient number
 *          - Patient's Passport number
 *          - Patient's name
 *          - Patient's date of birth
 *          - Admission date
 *          - Patient's phone number
 *          - Patient's gender
 *
 *      Created by Sonia Gautam (Sonia) ID 63070503410
 *      06 December 2020
 *
 ********************************************************************
 */
#include "hospitalDB.h"

/* Declaration of function used for displaying all object */
void printData(HOSPITALDB_T data[], int objectCount);


/* declared in hospitalDB.h */
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
void readToDisplay()
    {
    HOSPITALDB_T* data = NULL;      /* pointer to dynamically allocated array of structure */
                                    /* to hold patient's data read from file */
    int objectCount = 0;            /* variable to store number of objects in the file */
    int fileStatus = 0;             /* to store return value from 'checkFile' */

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
        printf("\n************************************************");
        printf("\n [- Display all objects in Hospital Database -]\n");
        printf("************************************************\n");

        /* try to allocate enough memory to hold all the patient's data */
        data = calloc(objectCount,sizeof(HOSPITALDB_T));

        if (data == NULL)
            {
            printf("Memory allocation failure - exiting\n");
            exit(0);
            }

        /* read all the patient's data */
        readData(data);

        /* print each patient's data */
        printData(data,objectCount);

        /* free the allocated memory */
        free(data);
        }

    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function prints each patient's data which contains
 *
 *      -   Passport number
 *      -   Name
 *      -   Date of Birth
 *      -   Admission date
 *      -   International phone
 *      -   Gender
 *
 * data[]      is array of structure storing all patient's data.
 * objectCount is the number of objects in the file.
 *
 *************************************************************/
void printData(HOSPITALDB_T data[], int objectCount)
    {
    char stringInput[MAXLEN];   /* variable to get input from the user */
    char page[4];               /* variable to store which page user wants to see */
    int number = 0;             /* variable to store patient number to display */
    int loopCount = 0;          /* variable to store count of data printed each time*/
    int i = 0;                  /* loop variable */



    while ((strcasecmp(page,"E") != 0))
        {
        for(i = number; i < number + 3; i++)
            {
            if (i >= objectCount)
                {
                break;
                }

            if (i >= 0)
                {
                printf("\nPatient no. %d\n\n",i+1);
                printf("Passport number     : %s\n",data[i].passportNum);
                printf("Name                : %s\n",data[i].name);
                printf("Date of Birth       : %s\n",data[i].dateOfBirth);
                printf("Admission date      : %s\n",data[i].dateToday);
                printf("International phone : %s\n",data[i].phoneNum);
                printf("Gender              : %s\n",data[i].gender);
                printf("\n--------------------------------------------\n");
                loopCount++;
                }
            }

        while (1)
            {
            memset(page,0,sizeof(page));
            printf("\nEnter P - previous page\n");
            printf("Enter E - exit displaying\n");
            printf("Enter N - next page : ");
            fgets(stringInput,sizeof(stringInput),stdin);
            sscanf(stringInput,"%s",page);

            if (strcasecmp(page,"E") == 0)
                {
                break;
                }
            else if (strcasecmp(page,"P") == 0)
                {
                if (i <= 3)
                    {
                    printf("\n\t\tNo previous page yet\n");
                    }
                else
                    {
                    number = i - (loopCount + 3);
                    break;
                    }

                }
            else if (strcasecmp(page,"N") == 0)
                {
                if (i == objectCount)
                    {
                    printf("\n\t\tNo more page to display\n");
                    }
                else
                    {
                    number = i;
                    break;
                    }
                }
            else
                {
                printf("\n\t\tPlease enter only P , E or N\n");
                }
            }
        loopCount = 0;

        }
    }
