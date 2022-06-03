/********************************************************************
 *
 * mainFunction.c
 *
 *      This program is a main program for Hospital Database.
 *      This program repeatedly ask the user which operation
 *      he/she wants to do. The option contains
 *
 *          [1] - Display all objects
 *          [2] - Add a new object
 *          [3] - Search for / Modify an object
 *          [4] - Exit
 *
 *      When the user has selected his/her option, the program
 *      will redirect to other program which handles a different
 *      aspect of the program depending on the option.
 *
 *      Created by Sonia Gautam (Sonia) ID 63070503410
 *      06 December 2020
 *
 ********************************************************************
 */
#include "hospitalDB.h"

/**************************************************************
 *
 * This function is a main function.
 * This function shows the menu, and repeatedly asks the user
 * which operation he or she wants to do, until the user
 * selects exit. Then the program will exit.
 *
 *************************************************************/
int main(int argc, char* argv[])
    {
    char stringInput[MAXLEN];   /* to get input from the user */
    int choice = 0;             /* to store input from the user */
    int fileStatus = 0;         /* to store return value from 'checkFile' */

    printf("\n************************************************");
    printf("\n\tWelcome to Hospital Database!\n");
    printf("************************************************\n");

    /* check if the database file exists or not */
    fileStatus = checkFile();

    if (fileStatus == 1)
        {
        printf("\t    Found database file!\n");
        }

    while (choice != 4)
        {
        printf("************************************************\n");
        printf("\n\t[- HOSPITAL DATABASE MENU -]\n\n");
        printf("%s[1]  Display all objects\n","    ");
        printf("%s[2]  Add a new object\n","    ");
        printf("%s[3]  Search for / Modify an object\n","    ");
        printf("%s[4]  Exit\n\n","    ");
        printf("************************************************\n");

        printf("What do you want to do? ");
        fgets(stringInput,sizeof(stringInput),stdin);
        sscanf(stringInput,"%d",&choice);

        switch (choice)
            {
            case 1:
				readToDisplay();
                break;
            case 2:
				addData();
                break;
            case 3:
				searchData();
                break;
            case 4:
                printf("\nGoodbye!\n\n");
                exit(0);
            default:
                printf("\ninvalid input - should be an integer between 1 and 4\n");
            }
        choice = 0;
        printf("\n");
        }

    }
