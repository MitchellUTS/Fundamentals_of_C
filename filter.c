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
  /* Choice of filter user has selected */
  int filter_selection; 
  /* Call function to get number of records within database */
  /* int items_size = getNoOfRecords(); */
  /* Placeholder value of 1 for testing */
  int items_size = 1;
  /* Which case we are searching through for character data types */
  int char_search_case;
  /* Buffer array for checking input */
  char input_buffer[256];

  /* Continue the program until user types '7' to exit */
  do
    {
      /* Request a selection from user from filter selection menu */
      print_filter_menu();
      /* Checking if input is of integer data type */
      fgets(input_buffer, 256, stdin);
      if (sscanf(input_buffer, "%d", &filter_selection) == 1 )
	;  /* Do nothing (no operation) */
       /* scanf("%d", &filter_selection); */

      /* Force user to re-input selection until valid */
      while (filter_selection < 1 || filter_selection > 7)
	{
	  printf("Invalid choice\n");
	  print_filter_menu();
	  /* Check input data type again */
	  fgets(input_buffer, 256, stdin);
	  if (sscanf(input_buffer, "%d", &filter_selection) == 1 )
	    break;
	}

      /* Select which item to filter through, based on user input */
      switch(filter_selection)
	{
	case 1:
	  /* Book ID's */
	  filter_int_items (items_size);
	  break;
	case 2:
	  /* Book ISBN's */
	  filter_long_items (items_size);
	  break;
	case 3:
	  /* Book Titles */
	  filter_char_items (items_size, char_search_case = 1);
	  break;
	case 4:
	  /* Book Authors */
	  filter_char_items (items_size, char_search_case = 2);
	  break;
	case 5:
	  /* Book Types */
	  filter_char_items (items_size, char_search_case = 3);
	  break;
	case 6:
	  /* Book Categories */
	  filter_char_items (items_size, char_search_case = 4);
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
  /* Buffer array for checking input */
  char input_buffer[256];

  /* -1 not a valid book ID, so we will use this number to display all items*/
  printf("Enter '-1' without quotes to display all items, or\n"
	 "Enter search term>\n");
  
  /* Checking if input is of integer data type */
  fgets(input_buffer, 256, stdin);
  if (sscanf(input_buffer, "%d", &search_input) == 1)
    ; /* No operation */

  /* Allow user to re-input search term until it is valid */
  while (search_input < -1 || search_input > 32767 || search_input == 0)
    {
      printf("Invalid search term\n");
      printf("Enter '-1' without quotes to display all items, or\n"
	      "Enter search term>\n");
      /* Check input data type again */
      fgets(input_buffer, 256, stdin);
      if (sscanf(input_buffer, "%d", &search_input) == 1)
      break;
    }

  if (search_input == -1 || items_size == 0)
    {
      printf("Displaying all items\n");
  }

  else
    {
      printf("Searching for '%d' under Book 'IDs'\n", search_input);
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
  /* Buffer for checking input value */
  char input_buffer[256];
  
  printf("Enter search term>\n");
  /* Check if input is of valid data type (integer/long) */
  fgets(input_buffer, 256, stdin);
  if (sscanf(input_buffer, "%li", &search_input) == 1)
    ; /* No operation */

  /* Allow user to re-input search term until it is valid */
  while (search_input < -1 || search_input > 2147483647 || search_input == 0)
    {
      printf("Invalid search term\n");
      printf("Enter '-1' without quotes to display all items, or\n"
	      "Enter search term>\n");
      /* Check data type again */
      fgets(input_buffer, 256, stdin);
      if (sscanf(input_buffer, "%li", &search_input) == 1)
      break;
    }

  /* If '-1' is input, call function display_all_items */
  /* Also, if items_size == 0 (i.e. no items in database),
  Call function display_all_items */
  if (search_input == -1 || items_size == 0) {
    printf("Displaying all items\n");
  }

  else
    {
      printf("Searching for '%li' under Book 'ISBNs'\n", search_input);
    }

  return;
}

/*******************************************************************************
 * This function filters specified string entries within database.
 * If input is '****', it will call a function to display all item entries.
 * inputs:
 * - item_t* items: An array of size MAX_NUM_items containing all item entries
 * - int items_size: The number of items currently in the array item_t* items
 * - int char_search_case: An integer corresponding to each string-type...
 * ...member of items_t array
 * outputs:
 * - None  
*******************************************************************************/
void filter_char_items (int items_size, int char_search_case)
{
  /* Input search term */
  char search_input[256];
  char str1[256];

  strcpy(str1, "****");
  
  printf("Enter search term>\n");
  scanf("%s", search_input);

  /* If '****' is input, call function display_all_items */
  /* Also, if items_size == 0 (i.e. no items in database),
  Call function display_all_items */
  if (strcmp(search_input, str1) == 0 || items_size == 0) {
    printf("Displaying all items\n");
  }

  else if (char_search_case == 1)
    {
    printf("Searching for '%s' under Book 'Titles'\n", search_input);
    }
  else if (char_search_case == 2)
    {
    printf("Searching for '%s' under 'Author'\n", search_input);
    }
  else if (char_search_case == 3)
    {
    printf("Searching for '%s' under Book 'Type'\n", search_input);
    }
  else if (char_search_case == 4)
    {
    printf("Searching for '%s' under Book 'Category'\n", search_input);
    }
  else
    {
    printf("Error!\n"
    "Please contact the software vendor with the following:\n"
	   "char_search_case = %d\n", char_search_case);
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
