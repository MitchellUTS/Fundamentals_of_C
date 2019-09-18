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
    char format_string[] = "%-6s %-3s %02d-%02d %02d:%02d %-3s %02d-%02d %02d:%02d\n";

    printf(format_string, item.itemcode, "SYD",
        item.departure_dt.month, item.departure_dt.day,
        item.departure_dt.hour, item.departure_dt.minute,
        item.arrival_city, item.arrival_dt.month,
        item.arrival_dt.day, item.arrival_dt.hour,
        item.arrival_dt.minute);
}