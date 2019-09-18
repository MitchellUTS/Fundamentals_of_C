/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: Add all date specific functionality include the struct and basic
 *              creation and manipulation tools.
 * 
*******************************************************************************/
#include "core.h"

/*******************************************************************************
 * This function creates a date object from user input.
 * inputs:
 * - date_t* date: This provides the location to store the date structure.
 * outputs:
 * - This function populates the date struct 'date' with valid data 
 *   that is collected from the user.
*******************************************************************************/
void create_date(date_t* date){

    /*Force the user to enter valid input by looping until the input is valid */ 
	while (true) {
        /* Ensure that the location in memory is clear */
		date->year = -1;
		date->month = -1;
		date->day = -1;

        /* Collect user input */
		printf("Enter date (DD/MM/YYYY)>\n");
		scanf("%d/%d/%d", &date->day, &date->month, &date->year);

        /* Exit if the user has provided valid data */
        if (!validate_date(date)) {
            return;
        }

        printf("Invalid input\n");
	}

    return;
}

/*******************************************************************************
 * This function checks if the provided date struct is valid as defined by
 * the business rules.
 * inputs:
 * - date_t* date: This is a pointer to the date structure to validate.
 * outputs:
 * - result_code, A value of 0 indicates a valid date and any value is an 
 *                  error code.
*******************************************************************************/
int validate_date(date_t* date){
    if (!between(date->month, 1, 12)) {
        return RESULT_CODE_date_ERROR_MONTH;

    } else if (!between(date->day, 1, 31)) {
        return RESULT_CODE_date_ERROR_DAY;
    }

    return RESULT_CODE_date_SUCCESS;
}

/*******************************************************************************
 * This function prints a date_ structure with no white space padding.
 * inputs:
 * - date__t* date: this is a pointer to the date__t that is to be printed.
 * outputs:
 * - none
*******************************************************************************/
void print_date(date_t date)
{
    printf("%02d-%02d", date->month, date->day);
}
