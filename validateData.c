/********************************************************************
 *
 * validateData.c
 *
 *      This program is used for validating the information
 *      that the user entered if it is valid or not.
 *
 *      Created by Sonia Gautam (Sonia) ID 63070503410
 *      07 December 2020
 *
 ********************************************************************
 */
#include "hospitalDB.h"

/* Declarations of function used in Passport number validation */
int checkLowerCase(char passportNum[]);
int checkTitle(char passportNum[]);
int checkHyphen(char passportNum[]);
int checkCharLen(char passportNum[]);
int checkCountryCode(char passportNum[]);

/* Declarations of function used in Date validation */
int checkDate_String(char date[]);
int checkDate_Format(char date[]);
int checkDate_Range(char date[]);
int checkDay_Law(int day, int month, int year);

/* Declarations of function used in Phone number validation */
int checkSpace(char number[]);
int checkAlpha(char number[]);
int checkPlusSign(char number[]);
int checkDash(char number[]);
int checkCodes(char number[]);


/* declared in hospitalDB.h */
/**************************************************************
 *
 * This function deletes the space after the input and space
 * that user may accidentally entered.
 *
 * input[] is the input data from the user
 *
 *************************************************************/
void deleteSpace(char input[])
    {
    int i = strlen(input) - 1;      /* i is a length of the variable - 1 */

    while ((i >= 0) && (isspace(input[i])))
        {
        input[i] = '\0';
        i--;
        }
    }

/* declared in hospitalDB.h */
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
int checkEnter(char input[])
    {
    int result = 0;     /* variable to store return value */

    if ((input[0] != '\n') && (input[0] != '\r'))
        {
        result = 1;
        }

    return result;
    }


//---------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------PASSPORT NUMBER VALIDATION------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

/* declared in hospitalDB.h */
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
int validatePassport(char passportNum[])
    {
    int validNum = 1;       /* variable to track errors */

    if (checkLowerCase(passportNum) == 0)
        {
        printf("\t\tNot valid - country code must be in capital letters\n");
        validNum = 0;
        }
    if (validNum && (checkTitle(passportNum) == 0))
        {
        printf("\t\tNot valid - must have country code\n");
        validNum = 0;
        }
    if (validNum && ((strlen(passportNum) < 11) || (strlen(passportNum) > 17)))
        {
        printf("\t\tNot valid - must have between 8 and 14 characters after the country code\n");
        validNum = 0;
        }
    if (validNum && (checkHyphen(passportNum) == 0))
        {
         printf("\t\tNot valid - must have dash after the country code\n");
        validNum = 0;
        }
    if (validNum && (checkCharLen(passportNum) == 0))
        {
        printf("\t\tNot valid - must have only digits or alphabets with a dash\n");
        validNum = 0;
        }
    if (validNum && (checkCountryCode(passportNum) == 0))
        {
        printf("\t\tNot valid - wrong country code\n");
        validNum = 0;
        }
    if (validNum && (checkCountryCode(passportNum) == 1))
        {
        validNum = 1;
        }
    return validNum;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks if the first two characters are lowercase
 * alphabet or not. (country code must be capital letter)
 *
 * passportNum[] is the input passport number from the user.
 *
 * This function returns 'result' which is 0 when the country
 * code is lowercase alphabet, otherwise 1.
 *
 *************************************************************/
int checkLowerCase(char passportNum[])
    {
    int result = 1;     /* variable to store return value */
    int i = 0;          /* loop variable */

    if ((islower(passportNum[0])) || (islower(passportNum[1])))
        {
        result = 0;
        }

    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks if the input begins with two letters
 * or not. (two letters represent the country code)
 *
 * passportNum[] is the input passport number from the user.
 *
 * This function returns 'result' which is 1 when the input
 * begins with two letter country code, otherwise 0.
 *
 *************************************************************/
int checkTitle(char passportNum[])
    {
    int result = 0;     /* variable to store return value */

    if (isalpha(passportNum[0]) && isalpha(passportNum[1]))
        {
        result = 1;
        }
    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks if the input has a hyphen after
 * the country code or not.
 *
 * passportNum[] is the input passport number from the user.
 *
 * This function returns 'result' which is 1 when the input
 * has a hyphen in correct place, otherwise 0.
 *
 *************************************************************/
int checkHyphen(char passportNum[])
    {
    int result = 0;     /* variable to store return value */

    if (passportNum[2] == '-')
        {
        result = 1;
        }
    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks if the Passport number after the
 * country code is all alphanumeric characters or not.
 *
 * passportNum[] is the input passport number from the user.
 *
 * This function returns 'result' which is 1 when the input
 * contains all alphanumeric characters (except the dash),
 * otherwise 0.
 *
 *************************************************************/
int checkCharLen(char passportNum[])
    {
    int i = 0;          /* loop variable */
    int count = 0;      /* variable to count digits and alphabets */
    int result = 0;     /* variable to store return value */

    for (i = 0; i < strlen(passportNum); i++)
        {
        if(isalnum(passportNum[i]))
            {
            count += 1;
            }
        }

    if (count == strlen(passportNum)-1)     /* -1 to ignore one dash after country code*/
        {
        result = 1;
        }

    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks if the passport number begins with
 * a valid two letters country code or not.
 *
 * passportNum[] is the input passport number from the user.
 *
 * This function returns 'result' which is 1 when the input
 * begins with a valid two letters country code, otherwise 0.
 *
 *************************************************************/
int checkCountryCode(char passportNum[])
    {
    char code[4];
    int i = 0;              /* loop variable */
    int result = 0;         /* variable to store return value */
    int countryCount = 0;   /* to count total number of countries */

    char* countryCodes[] = {"AD","AE","AF","AG","AI","AL","AM","AO","AQ","AR",
    "AS","AT","AU","AW","AX","AZ","BA","BB","BD","BE","BF","BG","BH","BI","BJ",
    "BL","BM","BN","BO","BQ","BR","BS","BT","BV","BW","BY","BZ","CA","CC","CD",
    "CF","CG","CH","CI","CK","CL","CM","CN","CO","CR","CU","CV","CW","CX","CY",
    "CZ","DE","DJ","DK","DM","DO","DZ","EC","EE","EG","EH","ER","ES","ET","FI",
    "FJ","FK","FM","FO","FR","GA","GB","GD","GE","GF","GG","GH","GI","GL","GM",
    "GN","GP","GQ","GR","GS","GT","GU","GW","GY","HK","HM","HN","HR","HT","HU",
    "ID","IE","IL","IM","IN","IO","IQ","IR","IS","IT","JE","JM","JO","JP","KE",
    "KG","KH","KI","KM","KN","KP","KR","KW","KY","KZ","LA","LB","LC","LI","LK",
    "LR","LS","LT","LU","LV","LY","MA","MC","MD","ME","MF","MG","MH","MK","ML",
    "MM","MN","MO","MP","MQ","MR","MS","MT","MU","MV","MW","MX","MY","MZ","NA",
    "NC","NE","NF","NG","NI","NL","NO","NP","NR","NU","NZ","OM","PA","PE","PF",
    "PG","PH","PK","PL","PM","PN","PR","PS","PT","PW","PY","QA","RE","RO","RS",
    "RU","RW","SA","SB","SC","SD","SE","SG","SH","SI","SJ","SK","SL","SM","SN",
    "SO","SR","SS","ST","SV","SX","SY","SZ","TC","TD","TF","TG","TH","TJ","TK",
    "TL","TM","TN","TO","TR","TT","TV","TW","TZ","UA","UG","UM","US","UY","UZ",
    "VA","VC","VE","VG","VI","VN","VU","WF","WS","YE","YT","ZA","ZM","ZW"};

    countryCount = sizeof(countryCodes)/sizeof(char*);

    memset(code,0,sizeof(code));
    strncpy(code,passportNum,2);            /* to copy country code from full string */

    for (i = 0; i < countryCount; i++)
        {
        if (strcmp(code,countryCodes[i]) == 0)
            {
            result = 1;
            break;
            }
        }
    return result;
    }


//---------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------NAME VALIDATION----------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

/* declared in hospitalDB.h */
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
int validateName(char name[])
    {
    int result = 0;     /* variable to store return value */
    int i = 0;          /* loop variable */

    for(i = 0; i < strlen(name); i++)
        {
        if (isalnum(name[i]) || isspace(name[i]))
            {
            result = 1;
            }
        else
            {
            printf("\t\tNot valid - must be only any combination of letters, digits and spaces\n");
            result = 0;
            break;
            }
        }

    return result;
    }


//---------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------DATE VALIDATION-----------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

/* declared in hospitalDB.h */
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
int validateDate(char date[])
    {
    int validNum = 1;   /* variable to track errors */

    if (strlen(date) != 10)
        {
        printf("\t\tNot valid - should be dd/mm/yyyy (10 characters)\n");
        validNum = 0;
        }
    if (validNum && (checkDate_String(date) == 0))
        {
        printf("\t\tNot valid - should be dd/mm/yyyy (digits)\n");
        validNum = 0;
        }
    if (validNum && (checkDate_Format(date) == 0))
        {
        printf("\t\tNot valid - wrong delimeter, should be 2 slashes\n");
        validNum = 0;
        }
    if (validNum && (checkDate_Range(date) == -1))
        {
        printf("\t\tNot valid - can't be future date\n");
        validNum = 0;
        }
    if (validNum && (checkDate_Range(date) == -5))
        {
        printf("\t\tNot valid - please enter BE year (not exceeding past 120 years)\n");
        validNum = 0;
        }
    if (validNum && (checkDate_Range(date) == -2))
        {
        printf("\t\tNot valid - unknown month\n");
        validNum = 0;
        }
    if (validNum && (checkDate_Range(date) == -3))
        {
        printf("\t\tNot valid - illegal day of month\n");
        validNum = 0;
        }
    if (validNum && (checkDate_Range(date) == -4))
        {
        printf("\t\tNot valid - not a leap year\n");
        validNum = 0;
        }
    if (validNum && (checkDate_Range(date) == 1))
        {
        validNum = 1;
        }
    return validNum;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks the string of the input date which
 * must be dd/mm/yyyy ('dd' 'mm' 'yyyy' must be digit)
 *
 * date[] is the input date from the user
 *
 * This function returns 'result' which is 1 when input string
 * is digit(with two slashes), otherwise 0.
 *
 *************************************************************/
int checkDate_String(char date[])
    {
    int result = 0;     /* variable to store return value */

    if ((isdigit(date[0])) && (isdigit(date[1])) && (isdigit(date[3])) && (isdigit(date[4])))
        {
        if ((isdigit(date[6])) && (isdigit(date[7])) && (isdigit(date[8])) && (isdigit(date[9])))
            {
            result = 1;
            }
        }

    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks the format of the input which must be
 * dd/mm/yyyy (one slash after day and one slash after month)
 *
 * date[] is the input date from the user
 *
 * This function returns 'result' which is 1 when slashes
 * are in correct form, otherwise 0.
 *
 *************************************************************/
int checkDate_Format(char date[])
    {
    int result = 0;     /* variable to store return value */

    if ((date[2] == '/') && (date[5] == '/'))
        {
        result = 1;
        }
    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks the range of the date with the input
 * and call 'checkDay_Existence' function to check remaining
 * invalid cases related to day/month/year.
 *
 * day   - between 1 and 31
 * month - between 1 and 12
 * year  - between 2443 and 2563 (not future date)
 *
 * date[] is the input date from the user
 *
 * This function returns 'result' which is -1,-2,-3,-5 when
 * year, month, day is out of the range, date is future
 * date respectively. Other return values depend on
 * 'checkDay_Existence' function.
 *
 *************************************************************/
int checkDate_Range(char date[])
    {
    int result = 0;         /* variable to store return value */
    int day = 0;            /* variable to store day */
    int month = 0;          /* variable to store month */
    int year = 0;           /* variable to store year */
    int dayToday = 0;       /* variable to get today's day */
    int monthToday = 0;     /* variable to get today's month */
    int yearToday  = 0;     /* variable to get today's year */
    int status = 0;         /* variable to store return value from 'dateCompare' */

    sscanf(date,"%d/%d/%d",&day,&month,&year);

    year = year - 543;      /* change to western year for easier calculation */

    /* get today's date */
    dateToday(&dayToday,&monthToday,&yearToday);

    /* compare today's date with the input date */
    status = dateCompare(day,month,year,dayToday,monthToday,yearToday);

    if (status == 1)
        {
        result = -1;
        }
    else if (year < yearToday - 120)
        {
        result = -5;
        }
    else if ((month < 1) || (month > 12))
        {
        result = -2;
        }
    else if ((day < 1) || (day > 31))
        {
        result = -3;
        }
    else
        {
        result = checkDay_Law(day,month,year);
        }

    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks the input date if it is legal or not.
 *
 * day - equals to or less than the day each month contains.
 * special case for February - if it is a leap year, the day
 * can be equal to or less than 29.
 *
 * day,month,year are input date split into 3 parts of integer.
 *
 * This function returns 'result' which is 1 when date is legal
 * -4 when it's not a leap year and -3 when date is illegal.
 *
 *************************************************************/
int checkDay_Law(int day, int month, int year)
    {
    int result = 0;     /* variable to store return value */
    int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    /* an array of integer to hold days in each month */

    if (daysInMonth[month-1] >= day)
        {
        result = 1;
        }
    else if ((month == 2) && (day == 29))
        {
        if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))
            {
            result = 1;
            }
        else
            {
            result = -4;
            }
        }
    else
        {
        result = -3;
        }
    return result;
    }


//---------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------GETTING TODAY'S DATE--------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

/* declared in hospitalDB.h */
/**************************************************************
 *
 * This function gets today's date by calling 'dateToday'.
 *
 * date[] is the variable to store today's date
 *
 *************************************************************/
void todaysDate(char date[])
	{
	int dayToday = 0;       /* variable to store today's day */
    int monthToday = 0;     /* variable to store today's month */
    int yearToday = 0;      /* variable to store today's year */

	dateToday(&dayToday,&monthToday,&yearToday);

    if (dayToday < 10)
        {
        sprintf(date,"0%d/%d/%d",dayToday,monthToday,yearToday+543);
        }
    else
        {
        sprintf(date,"%d/%d/%d",dayToday,monthToday,yearToday+543);
        }
	}


//---------------------------------------------------------------------------------------------------------------------------
//--------------------------------------INTERNATIONAL PHONE NUMBER VALIDATION------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

/* declared in hospitalDB.h */
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
int validatePhoneNum(char number[])
    {
    int validNum = 1;       /* variable to track errors */

    if (checkSpace(number) == 0)
        {
        printf("\t\tNot valid - no space allowed\n");
        validNum = 0;
        }
    if (validNum && (checkAlpha(number) == 0))
        {
        printf("\t\tNot valid - no alphabetic character allowed\n");
        validNum = 0;
        }
    if (validNum && (checkPlusSign(number) == 0))
        {
        printf("\t\tNot valid - must begin with a plus\n");
        validNum = 0;
        }
    if (validNum && (checkDash(number) == 0))
        {
        printf("\t\tNot valid - must be digits with 2 dashes\n");
        validNum = 0;
        }
    if (validNum && (checkCodes(number) == -1))
        {
        printf("\t\tNot valid - must have between 1 and 3 digits for country code\n");
        validNum = 0;
        }
    if (validNum && (checkCodes(number) == -2))
        {
        printf("\t\tNot valid - must have between 1 and 3 digits for city/area code\n");
        validNum = 0;
        }
    if (validNum && (checkCodes(number) == 0))
        {
        printf("\t\tNot valid - must have between 6 and 10 additional digits\n");
        validNum = 0;
        }
    if (validNum && (checkCodes(number) == 1))
        {
        validNum = 1;
        }
    return validNum;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks if the input contains a space or not.
 * (no space allowed in phone number)
 *
 * number[] is the input phone number from the user
 *
 * This function returns 'result' which is 0 when space is
 * found in the string, otherwise 1.
 *
 *************************************************************/
int checkSpace(char number[])
    {
    int i = 0;          /* loop variable */
    int result = 1;     /* variable to store return value */

    for (i = 0; i < strlen(number); i++)
        {
        if (isspace(number[i]))
            {
            result = 0;
            break;
            }
        }
    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks if the input contains an alphabet
 * or not. (no alphabet allowed in phone number)
 *
 * number[] is the input phone number from the user
 *
 * This function returns 'result' which is 0 when alphabet
 * is found in the string, otherwise 1.
 *
 *************************************************************/
int checkAlpha(char number[])
    {
    int i = 0;          /* loop variable */
    int result = 1;     /* variable to store return value */

    for (i = 0; i < strlen(number); i++)
        {
        if (isalpha(number[i]))
            {
            result = 0;
            break;
            }
        }
    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks if the input begins with the plus
 * sign or not.
 *
 * number[] is the input phone number from the user
 *
 * This function returns 'result' which is 1 when the input
 * phone number begins with a plus, otherwise 0.
 *
 *************************************************************/
int checkPlusSign(char number[])
    {
    int result = 0;     /* variable to store return value */

    if (number[0] == '+')
        {
        result = 1;
        }
    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks if the input contains two dashes and
 * checks if the remaining input is digit or not.
 *
 * number[] is the input phone number from the user
 *
 * This function returns 'result' which is 1 when the input
 * phone number contains two dashes and remaining data
 * is all digits (not including - and +), otherwise 0.
 *
 *************************************************************/
int checkDash(char number[])
    {
    int i = 0;          /* loop variable */
    int count1 = 0;     /* variable to count dashes */
    int count2 = 0;     /* variable to count digits */
    int result = 0;     /* variable to store return value */

    for (i = 0; i <= strlen(number); i++)
        {
        if (number[i] == '-')
            {
            count1 += 1;
            }
        else
            {
            if (isdigit(number[i]))
                {
                count2 += 1;
                }
            }
        }

    if (count1 == 2)                            /* check if there are 2 dashes */
        {
        if (count2 == strlen(number)-3)         /* check if other characters are digits */
            {                                   /* -3 to ignore 2 dashes and a plus sign */
            result = 1;
            }
        }

    return result;
    }

/* Local function, not exposed in the header file */
/**************************************************************
 *
 * This function checks length for each part of phone number.
 *
 * After +, between 1 and 3 digits for country code.
 * After 1st -, between 1 and 3 digits for city code.
 * After 2nd -, between 6 and 10 additional digits.
 *
 * number[] is the input phone number from the user
 *
 * This function returns 'result' which is 0,-1,-2 when
 * additional digit, country code and city code is out of
 * the range respectively. Otherwise, result equals to 1.
 *
 *************************************************************/
int checkCodes(char number[])
    {
    char digit[MAXLEN];     /* variable to store additional digits */
    int countryCode = 0;    /* variable to store country code */
    int cityCode = 0;       /* variable to store city code */
    int result = 0;         /* variable to store return value */

    sscanf(number,"+%d-%d-%s",&countryCode,&cityCode,digit);

    if ((countryCode > 999) || (countryCode < 0))
        {
        result = -1;
        }
    else
        {
        if ((cityCode > 999) || (cityCode < 0))
            {
            result = -2;
            }
        else if ((strlen(digit) < 6) || (strlen(digit) > 10))
            {
            result = 0;
            }
        else
            {
            result = 1;
            }
        }
    return result;
    }


//---------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------GENDER VALIDATION--------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

/* declared in hospitalDB.h */
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
int validateGender(char gender[])
    {
    int result = 0;     /* variable to store return value */

    if ((strcasecmp(gender,"M") == 0) || (strcasecmp(gender,"F") == 0) || (strcasecmp(gender,"O") == 0))
        {
        result = 1;
        }
    else
        {
        printf("\t\tNot valid - unknown gender\n");
        }
    return result;
    }

