/********************************************************************
 *
 * readWriteData.c
 *
 *      This program is responsible for reading, writing
 *      and creating new Hospital Database file. The Hospital
 *      Database file is created as a binary file.
 *
 *      Created by Sonia Gautam (Sonia) ID 63070503410
 *      06 December 2020
 *
 ********************************************************************
 */
#include "hospitalDB.h"

/* declared in hospitalDB.h */
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
int readToCount()
    {
    FILE* pDatabase = NULL;     /* File pointer - will be used to access file */
    int objectCount = 0;        /* variable to get number of objects in the file */

    pDatabase = fopen(FILENAME,"rb");

    if (pDatabase == NULL)
        {
        printf("Error opening file\n");
        exit(1);
        }
    if (fread(&objectCount,sizeof(int),1,pDatabase) != 1)
        {
        printf("Error occurred while reading the file\n");
        exit(2);
        }
    else
        {
        if (fclose(pDatabase))
            {
            printf("Error occurred while closing the file\n");
            exit(3);
            }
        }

    return objectCount;
    }

/* declared in hospitalDB.h */
/**************************************************************
 *
 * This function reads all data from the file and store each
 * patient's data in the array of structure.
 *
 * patientData[] is array of structure to store each
 * patient's data.
 *
 *************************************************************/
void readData(HOSPITALDB_T patientData[])
    {
    FILE* pDatabase = NULL;     /* File pointer - will be used to access file */
    int objectCount = 0;        /* variable to get number of objects in the file */

    pDatabase = fopen(FILENAME,"rb");

    if (pDatabase == NULL)
        {
        printf("Error opening file\n");
        exit(1);
        }
    if (fread(&objectCount,sizeof(int),1,pDatabase) != 1)
        {
        printf("Error occurred while reading the file\n");
        exit(2);
        }
    else if (fread(patientData,sizeof(HOSPITALDB_T),objectCount,pDatabase) != objectCount)
        {
        printf("Error occurred while reading the file\n");
        exit(2);
        }
    else
        {
        if (fclose(pDatabase))
            {
            printf("Error occurred while closing the file\n");
            exit(3);
            }
        }
    }

/* declared in hospitalDB.h */
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
void addNewData(HOSPITALDB_T newData, int objectCount)
    {
    FILE* pDatabase = NULL;     /* File pointer - will be used to access file */

    pDatabase = fopen(FILENAME,"rb+");

    if (pDatabase == NULL)
        {
        printf("Error opening file\n");
        exit(1);
        }

    /* move to the end of the file */
    fseek(pDatabase,0,SEEK_END);

    if (fwrite(&newData,sizeof(HOSPITALDB_T),1,pDatabase) != 1)
        {
        printf("Error occurred while writing new data to the file\n");
        exit(4);
        }

    /* move to the beginning of the file */
    fseek(pDatabase,0,SEEK_SET);

    if (fwrite(&objectCount,sizeof(int),1,pDatabase) != 1)
        {
        printf("Error occurred while writing number of object to the file\n");
        exit(4);
        }
    else
        {
        if (fclose(pDatabase))
            {
            printf("Error occurred while closing the file\n");
            exit(3);
            }
        }
    printf("\nAdded new object to Hospital Database!\n\n");
    }

/* declared in hospitalDB.h */
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
void addModifiedData(HOSPITALDB_T data[], int objectCount)
    {
    FILE* pDatabase = NULL;     /* File pointer - will be used to access file */

    pDatabase = fopen(FILENAME,"wb");

    if (pDatabase == NULL)
        {
        printf("Error opening file\n");
        exit(1);
        }

    if (fwrite(&objectCount,sizeof(int),1,pDatabase) != 1)
        {
        printf("Error occurred while writing number of object to the file\n");
        exit(4);
        }
    else if (fwrite(data,sizeof(HOSPITALDB_T),objectCount,pDatabase) != objectCount)
        {
        printf("Error occurred while writing new data to the file\n");
        exit(4);
        }
    else
        {
        if (fclose(pDatabase))
            {
            printf("Error occurred while closing the file\n");
            exit(3);
            }
        }

    printf("\nSuccessfully modified the data\n\n");

    }

/* declared in hospitalDB.h */
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
int checkFile()
    {
    FILE* pNew = NULL;      /* File pointer - will be used to access file */
    int status = 0;         /* variable to store return value */
    int fileStatus = 0;     /* variable to store return value from access function */
    int count = 0;          /* variable to store number of object at the beginning */

    /* check if the database file exists or not*/
    fileStatus = access(FILENAME,F_OK);

    if (fileStatus == 0)
        {
        status = 1;
        }
    else
        {
        printf("\t    Database file not found\n");

        pNew = fopen(FILENAME,"wb");

        if (pNew == NULL)
            {
            printf("Error creating new database file\n");
            exit(0);
            }
        if (fwrite(&count,sizeof(int),1,pNew) != 1)
            {
            printf("Error writing number of data in database file\n");
            exit(4);
            }
         else
            {
            if (fclose(pNew))
                {
                printf("Error occurred while closing the file\n");
                exit(3);
                }
            }
        printf("\t   Created new database file\n");
        }

    return status;
    }


