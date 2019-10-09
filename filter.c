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
 * This function displays filtered entries of the database, by first asking
 * for the filter type, then calling a function 'display_sel_items'
 * to search through database entries and print them.
 * inputs:
 * - item_t* items: An array of size MAX_NUM_items containing all item entries
 * - int items_size: The number of items currently in the array item_t* items
 * outputs:
 * - None  
*******************************************************************************/
void select_filter (void)
{
  int filter_selection;  /* Choice of filter user has selected */
  /* Call function to get number of records within database */
  int items_size = getNoOfRecords(); 

  /* Continue the program until user types '7' to exit */
  do
    {
      /* Request a selection from user from filter selection menu */
      print_filter_menu();
      scanf("%d", &filter_selection);

      /* Force user to re-input selection until valid */
      while (filter_selection < 1 || filter_selection > 7)
	{
	  printf("Invalid choice\n");
	  printf_filter_menu();
	  scanf("%d", &filter_selection);
	}

      /* Select which item to filter through, based on user input */
      switch(filter_selection)
	{
	case 1:
	  filter_int_items (items_size);
	  break;
	case 2:
	  filter_long_items (items_size);
	  break;
	case 3:

	  break;
	case 4:

	  break;
	case 5:

	  break;
	case 6:

	  break;
	}

      
    } while (filter_selection != 7);
  return;
}
/*******************************************************************************
 * This function filters database entries according to the book ID.
 * If input is '-1', it will call a function to display all item entries.
 * inputs:
 * - item_t* items: An array of size MAX_NUM_items containing all item entries
 * - int items_size: The number of items currently in the array item_t* items
 * - 
 * outputs:
 * - None  
*******************************************************************************/
void filter_int_items (int items_size)
{
  /* Input search term */
  int search_input;

  /* -1 not a valid book ID, so we will use this number to display all items*/
  printf("Enter '-1' without quotes to display all items, or\n"
	 "Enter search term>\n");
  scanf("%d", &search_input);

  /* Allow user to re-input search term until it is valid */
  while (search_input < -1 || search_input > 32767 || search_input == 0)
    {
      printf("Invalid search term\n");
      printf("Enter '-1' without quotes to display all items, or\n"
	      "Enter search term>\n");
      scanf("%d", &search_input);
    }

  /* If '-1' is input, call function display_all_items */
  /* Also, if items_size == 0 (i.e. no items in database),
  /* Call function display_all_items */
  if (search_input == -1 || items_size == 0)
    {
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
    /* If strcmp returns a '0', call display_item function */
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

/*******************************************************************************
 * This function filters database entries according to ISBN.
 * If input is '-1', it will call a function to display all item entries.
 * inputs:
 * - item_t* items: An array of size MAX_NUM_items containing all item entries
 * - int items_size: The number of items currently in the array item_t* items
 * - 
 * outputs:
 * - None  
*******************************************************************************/
void filter_long_items (int items_size)
{
  /* Input search term */
  long search_input;
  
  printf("Enter search term>\n");
  scanf("%li", search_input);

  /* Allow user to re-input search term until it is valid */
  while (search_input < -1 || search_input > 2147483647 || search_input == 0)
    {
      printf("Invalid search term\n");
      printf("Enter '-1' without quotes to display all items, or\n"
	      "Enter search term>\n");
      scanf("%li", &search_input);
    }

  /* If '-1' is input, call function display_all_items */
  /* Also, if items_size == 0 (i.e. no items in database),
  /* Call function display_all_items */
  if (search_input == -1 || items_size == 0) {
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

/*******************************************************************************
 * This function filters specified string entries within database.
 * If input is '****', it will call a function to display all item entries.
 * inputs:
 * - item_t* items: An array of size MAX_NUM_items containing all item entries
 * - int items_size: The number of items currently in the array item_t* items
 * - 
 * outputs:
 * - None  
*******************************************************************************/
void filter_char_items (int items_size)
{
  /* Input search term */
  char search_input[256];
  
  printf("Enter search term>\n");
  scanf("%s", search_input);

  /* If '****' is input, call function display_all_items */
  /* Also, if items_size == 0 (i.e. no items in database),
  /* Call function display_all_items */
  if (search_input[0] == '****' || items_size == 0) {
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

/*******************************************************************************
 * This function prints the filter selection menu with multiple filter options
 * available for selection, or to cancel filter selection.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_filter_menu (void)
{
    printf("\n"
    "1. ID\n"
    "2. ISBN\n"
    "3. Book Title\n"
    "4. Author\n"
    "5. Book Type\n"
    "6. Book Category\n"
    "7. Cancel filter selection\n"
    "Enter your choice of filter selection (Number between 1-7)>\n");
}
