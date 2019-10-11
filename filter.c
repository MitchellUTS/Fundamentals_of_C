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
 * for the filter type, then calling a function 'display_item'
 * to search through database entries and print them.
 * inputs:
 * - item_node_t* node: The head node of the database's linked list of items
 * outputs:
 * - None  
*******************************************************************************/
void select_filter (item_node_t* node)
{
  /* Choice of filter user has selected */
  int filter_selection; 
  /* Which case we are searching through for character data types */
  int char_search_case;
  /* Buffer array for checking input */
  char input_buffer[256];

  /* i.e. the node pointer points to nothing */
  if (node == NULL)
    {
      printf("No database loaded");
      return;
    }
  else
    {
       do
	 {
      /* Request a selection from user from filter selection menu */
      print_filter_menu();
      /* Checking if input is of integer data type */
      fgets(input_buffer, 256, stdin);
      if (sscanf(input_buffer, "%d", &filter_selection) == 1 )
	;  /* Do nothing (no operation) */

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
	  filter_int_items (node);
	  break;
	case 2:
	  /* Book ISBN's */
	  filter_long_items (node);
	  break;
	case 3:
	  /* Book Titles */
	  filter_char_items (char_search_case = 1, node);
	  break;
	case 4:
	  /* Book Authors */
	  filter_char_items (char_search_case = 2, node);
	  break;
	case 5:
	  /* Book Types */
	  filter_char_items (char_search_case = 3, node);
	  break;
	case 6:
	  /* Book Categories */
	  filter_char_items (char_search_case = 4, node);
	  break;
	}
     /* Continue the program until user types '7' to exit */
    } while (filter_selection != 7);
  }
  return;
}
/*******************************************************************************
 * This function filters database entries according to the book ID.
 * If input is '-1', it will call a function to display all item entries.
 * inputs:
 * - item_node_t* node: The head node of the database's linked list of items
 * outputs:
 * - None  
*******************************************************************************/
void filter_int_items (item_node_t* node)
{
  /* Input search term */
  int search_input;
  /* Buffer array for checking input */
  char input_buffer[256];
  /* Number matches for search */
  int matches = 0;

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

  if (search_input == -1)
    {
      printf("Displaying all items\n");
      /* Call display_database function */
      display_database (node);
  }

  else
    {
      printf("Searching for '%d' under Book 'IDs'\n", search_input);
      while (node != NULL)
	{
	  /* Check if item ID for structure within current node... */
	  /* ...is equal to search_input */
	  if (((item_t*)(current->item_data))->ID == search_input)
	    {
	      /* Call function to display items for current node */
	      display_item(node);
	      /* Increase item match count */
	      matches = matches + 1;
	    }
	  /* Move to next linked list node */
	  node = node->next;
	}
      if (matches == 0)
	{
	  /* Print no matches if there were no matches */
	  printf("No exact matches found for '%d'\n", search_input);
	}
    }
    
  return;
}

/*******************************************************************************
 * This function filters database entries according to ISBN.
 * If input is '-1', it will call a function to display all item entries.
 * inputs:
 * - item_node_t* node: The head node of the database's linked list of items
 * outputs:
 * - None  
*******************************************************************************/
void filter_long_items (item_node_t* node)
{
  /* Input search term */
  long search_input;
  /* Buffer for checking input value */
  char input_buffer[256];
  /* Number matches for search */
  int matches = 0;
  
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
    /* Call display_database function */
    display_database (node);
  }

  else
    {
      printf("Searching for '%li' under Book 'ISBNs'\n", search_input);
      while (node != NULL)
	{
	  /* Check if item ISBN for structure within current node... */
	  /* ...is equal to search_input */
	  if (((item_t*)(current->item_data))->ISBN == search_input)
	    {
	      /* Call function to display items for current node */
	      display_item(node);
	      /* Increase item match count */
	      matches = matches + 1;
	    }
	  /* Move to next linked list node */
	  node = node->next;
	}
      if (matches == 0)
	{
	  /* Print no matches if there were no matches */
	  printf("No exact matches found for '%li'\n", search_input);
	}
    }

  return;
}

/*******************************************************************************
 * This function filters specified string entries within database.
 * If input is '****', it will call a function to display all item entries.
 * inputs:
 * - int char_search_case: An integer corresponding to each string-type...
 * ...member of items_t array
 * - item_node_t* node: The head node of the database's linked list of items
 * outputs:
 * - None  
*******************************************************************************/
void filter_char_items (int char_search_case, item_node_t* node)
{
  /* Input search term */
  char search_input[256];
  /* Storage for string to trigger wildcard search */
  char str1[6];
  /* Pointer to store value returned by strstr function, for later checking */
  char *str_chkp;
  /* Number matches for search */
  int matches = 0;
  
  strcpy(str1, "****");
  
  printf("Enter search term>\n");
  scanf("%s", search_input);

  /* If '****' is input, call function display_all_items */
  /* Also, if items_size == 0 (i.e. no items in database),
  Call function display_all_items */
  if (strcmp(search_input, str1) == 0 || items_size == 0) {
    printf("Displaying all items\n");
    /* Call display_database function */
    display_database (node);
  }

  else if (char_search_case == 1)
    /* Search case for titles */
    {
    printf("Searching for '%s' under Book 'Titles'\n", search_input);
    while (node != NULL)
	{
	  /* Check if substring of search term inside 'title' */
	  *str_chkp = strstr(((item_t*)(current->item_data))->title,
			     search_input);
	  /* strstr returns NULL if no substring found */
	  if (str_chkp != NULL)
	    {
	      /* Call function to display items for current node */
	      display_item(node);
	      /* Increase item match count */
	      matches = matches + 1;
	    }
	  /* Move to next linked list node */
	  node = node->next;
	}
    if (matches == 0)
	{
	  /* Print no matches if there were no matches */
	  printf("No exact matches found for '%s'\n", search_input);
	}
    }
  else if (char_search_case == 2)
    /* Search case for authors */
    {
    printf("Searching for '%s' under 'Author'\n", search_input);
        while (node != NULL)
	{
	  /* Check if substring of search term inside 'author' */
	  *str_chkp = strstr(((item_t*)(current->item_data))->author,
			     search_input);
	  /* strstr returns NULL if no substring found */
	  if (str_chkp != NULL)
	    {
	      /* Call function to display items for current node */
	      display_item(node);
	      /* Increase item match count */
	      matches = matches + 1;
	    }
	  /* Move to next linked list node */
	  node = node->next;
	}
    if (matches == 0)
	{
	  /* Print no matches if there were no matches */
	  printf("No exact matches found for '%s'\n", search_input);
	}
    }
  else if (char_search_case == 3)
    /* Search case for types */
    {
    printf("Searching for '%s' under Book 'Type'\n", search_input);
        while (node != NULL)
	{
	  /* Check if substring of search term inside 'type' */
	  *str_chkp = strstr(((item_t*)(current->item_data))->type,
			     search_input);
	  /* strstr returns NULL if no substring found */
	  if (str_chkp != NULL)
	    {
	      /* Call function to display items for current node */
	      display_item(node);
	      /* Increase item match count */
	      matches = matches + 1;
	    }
	  /* Move to next linked list node */
	  node = node->next;
	}
    if (matches == 0)
	{
	  /* Print no matches if there were no matches */
	  printf("No exact matches found for '%s'\n", search_input);
	}
    }
  else if (char_search_case == 4)
    /* Search case for categories */
    {
    printf("Searching for '%s' under Book 'Category'\n", search_input);
        while (node != NULL)
	{
	  /* Check if substring of search term inside 'category' */
	  *str_chkp = strstr(((item_t*)(current->item_data))->category,
			     search_input);
	  /* strstr returns NULL if no substring found */
	  if (str_chkp != NULL)
	    {
	      /* Call function to display items for current node */
	      display_item(node);
	      /* Increase item match count */
	      matches = matches + 1;
	    }
	  /* Move to next linked list node */
	  node = node->next;
	}
    if (matches == 0)
	{
	  /* Print no matches if there were no matches */
	  printf("No exact matches found for '%s'\n", search_input);
	}
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
