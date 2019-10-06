/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, Christopher Wong ...
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
    
    /*TO DO: SORT ITEMS [merge_sort(item_list);] */

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

/*******************************************************************************
 * This function selects which variable to sort database.
 * inputs:
 * - item_node_t* item_list: This is a pointer that directs to a linked 
 * - int* items_size: This is the number of items currently in the array,
 *                      this value will be updated when the database contents
 *                      have been loaded.
 * outputs:
 * - none
*******************************************************************************/
int sort_option(void) {
	
	int user_selection;
	
	/* Request a selection from the user */
	print_sorting_option();
	scanf("%d", &user_selection);
	        
	/* Allow to user to re-input their selection until it is valid */
	while (user_selection < 1 || user_selection > 5) {
		printf("Invalid choice\n");
		print_sorting_option();
		scanf("%d", &user_selection);
	}	
	
	return user_selection;
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
/* sorts the linked list by changing next pointers (not data) */
void merge_sort(struct item_node_t** start) 
{ 
    item_node_t* head = *start; 
    item_node_t* a, b; 
  
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
  
    /* Split head into 'a' and 'b' sublists */
    split_lists(head, &a, &b); 
  
    /* Recursively sort the sublists */
    merge_sort(&a); 
    merge_sort(&b); 
  
    /* answer = merge the two sorted lists together */
    *headRef = sort_items(a, b); 
} 
  
struct item_node_t* sort_items(struct item_node_t* a, struct item_node_t* b) {
	
    struct item_node_t* result = NULL; 
  
    /* Base cases */
    if (a == NULL) return b; 
    else if (b == NULL) return a; 
  
    /* Sort via ID */
    if (((item_t*)(a->item_data))->ID <= ((item_t*)(b->item_data))->ID) { 
        result = a; 
        result->next = sort_items(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = sort_items(a, b->next); 
    } 
    
    return result; 
} 
  
/* Split the nodes of the list into two evenly sized lists. */
void split_lists(struct item_node_t* head, 
                 struct item_node_t** front, struct item_node_t** back) 
{ 
    struct item_node_t* first_list, second_list; 
    first_list = head; 
    second_list = head->next; 
  
    /* Position nodes to evenly split lists */
    while (second_list != NULL) { 
        second_list = second_list->next; 
        if (second_list != NULL) { 
            first_list = first_list->next; 
            second_list = second_list->next; 
        } 
    } 
  
    /* Splits the lists */
    *front = head; 
    *back = first_list->next; 
    first_list->next = NULL; 
} 
  
/* TO DO: Function to insert a node at the beginging of the linked list 
void add_item(struct item_node_t** head_ref) 
{ 
    struct item_node_t* new_node = 
    		(struct item_node_t*)malloc(sizeof(struct item_node_t)); 
  
    new_node->item_data = create_item(new_node); 
  
    new_node->next = (*head_ref); 
  
    (*head_ref) = new_node; 
} */

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_sorting_menu (void)
{
    printf("\n"
    "1. Sort by ID\n"
	"2. Sort by Title\n"
	"3. Sort by Author\n"
    "4. Sort by Type\n"
	"5. Sort by Genre\n"
    "Enter your choice (number between 1-5)>\n");
}
