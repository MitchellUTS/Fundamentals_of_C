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

#include "date.c"

/*#ifdef*/
struct date {
    int year, month, day;
};
typedef struct date date_t;

void print_date(date_t date);
void create_date(date_t* date);
int validate_date(date_t* date);


