/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: Create a database file and some interfacing tools.
 * 
*******************************************************************************/
#include "core.h"

/*******************************************************************************
 * This function saves all items in memory to the database file as plain text.
 * inputs:
 * - item_t* items: This is an array of size MAX_NUM_itemS which will be
 *                      saved to the database. 
 * - int items_size: This is the number of items currently in the array.
 * outputs:
 * - none
*******************************************************************************/
void save_items(item_node_t* item_list) {
	FILE* file_stream;

    char format_string[] = "%003d %l %s %s %s %s\n";

    /* Open/Create the file for writing text data */ 
    file_stream = fopen(DB_NAME, "w");

    /* Check if opening the file was successful */
    if (file_stream == NULL)
    	return;

    int i;
    for (i = 0; i < items_size; i++) {

        /* Print each item to the database in the same format that is used
        in the display function. */
    	fprintf(file_stream, format_string, item.ID, item.ISBN,
    	        item.title, item.author, item.type, item.category);
    }
    
    /* Always close the file after you have finished using it. */ 
    fclose(file_stream);
}

/*******************************************************************************
 * This function loads all items from the database file to memory.
 * inputs:
 * - item_t* items: This is an array of size MAX_NUM_itemS which will be
 *                      populated with records from the database. 
 * - int* items_size: This is the number of items currently in the array,
 *                      this value will be updated when the database contents
 *                      have been loaded.
 * outputs:
 * - none
*******************************************************************************/
void load_items(item_node_t* item_list) {
	FILE* file_stream;
    char format_string[] = "%003d %l %s %s %s %s\n";

    /* Open the file for reading text data */
    file_stream = fopen(DB_NAME, "r");

    /* Check if opening the file was successful */
    if (file_stream == NULL) {
        printf("Read error\n");
    	return;
    }

    int i = 0;

    /* Keep reading records from the file until an invalid line is read
        or memory has been filled*/
    
    while (fscanf(file_stream, format_string, &item_list[i].ID, 
    		&item_list[i].ISBN, item_list[i].title, item_list[i].author, 
			item_list[i].type, item_list[i].category) == 6 &&
            i < MAX_NUM_itemS) {
            i++; /*TO DELETE COMMENT: what is MAX_NUM_itemS value?*/
    }

    /* Update the number of items currently in use as part of the array */
    *items_size = i; /*TO DELETE COMMENT: where are we saving that value?*/   
    
    /* Always close the file once you are no longer using it */
    fclose(file_stream);
}
