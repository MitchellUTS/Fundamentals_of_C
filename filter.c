/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Vincent Lay, ...
 *  
 * Date of creation: 22/09/2019
 * 
 * Purpose: Function to parse through product database according to specific
 *              keywords, and print out result.
 * 
*******************************************************************************/
#include "core.h"

/*******************************************************************************
 * This function displays filtered entries of the database.
 * If input is '*', it will call a function to display all item entries.
 * inputs:
 * - item_t* items: An array of size MAX_NUM_items containing all item entries
 * - int items_size: The number of items currently in the array item_t* items
 * outputs:
 * - None  
*******************************************************************************/
void display_sel_items (int items_size)
{
  /* Input search term or asterisk (*) */
  char search_input[MAX_ITEM_NAME_LEN + 1];

  printf("Enter search term>\n");
  scanf("%s", search_input);

  /* If '*' is input, call function display_all_items */
  /* Also, if items_size == 0 (i.e. no items in database),
  /* Call function display_all_items */
  if (search_input[0] == '*' || items_size == 0) {
    display_all_items (items_size);
  }

  else {
    /* Checking if there are no matches between search term */
    /* and with structure item_t's variables */

    /* Placeholder (*.arrival_city, flight*) below! */
    if ((strcmp(search_input, flight1.arrival_city) != 0) &&
	(strcmp(search_input, flight2.arrival_city) != 0) &&
	(strcmp(search_input, flight3.arrival_city) != 0) &&
	(strcmp(search_input, flight4.arrival_city) != 0) &&
	(strcmp(search_input, flight5.arrival_city) != 0)) {
      printf("No flights\n");
    }
    /* Comparing search term with items in database */
    /* If strcmp returns a '0', call display_tiem function */
   if (strcmp(search_input, flight1.arrival_city) == 0) {
     display_flight (flight1);
   }
   if (strcmp(search_input, flight2.arrival_city) == 0) {
     display_flight (flight2);
   }
   if (strcmp(search_input, flight3.arrival_city) == 0) {
     display_flight (flight3);
   }
   if (strcmp(search_input, flight4.arrival_city) == 0) {
     display_flight (flight4);
   }
   if (strcmp(search_input, flight5.arrival_city) == 0) {
     display_flight (flight5);
   }
  }

  return;
}
