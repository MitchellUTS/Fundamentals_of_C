/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: Add all item specific functionality include the struct and basic
 *              creation and manipulation tools.
 * 
*******************************************************************************/
#include "core.h"

/*******************************************************************************
 * This function prints a item structure with a newline at the end
 * inputs:
 * - item_t* item: this is a pointer to the item that needs to be printed.
 * outputs:
 * - none
*******************************************************************************/
void print_item(item_t item)
{
    char format_string[] = "%003d %l %s %s %s %s\n";

    printf(format_string, item.ID, item.ISBN,
        item.title, item.author, item.type, item.category);
}