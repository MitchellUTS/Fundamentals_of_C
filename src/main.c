/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):       Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: To provide the core framework and functionality for the application.
 * 
*******************************************************************************/


#include "core.h"

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    int user_selection, sort_num = -1;

    printf("%d\n", sort_num);

    /*item_node_t item_list;
    item_node_t* list = NULL;
    list = (item_node_t*) malloc(sizeof(item_node_t)); Uncomment later*/
    
    /*NODE TEST
    ((item_t*)(item_list->item_data))->ID = 1;
    ((item_t*)(item_list->item_data))->ISBN = 1234;
    ((item_t*)(item_list->item_data))->title = "Hello World";
    ((item_t*)(item_list->item_data))->author = "Programmer";
    ((item_t*)(item_list->item_data))->type = "Textbook";
    ((item_t*)(item_list->item_data))->category = "IT";
    */

   mask_file("input.txt", "output.txt", "passphrase");
   mask_file("output.txt", "input.txt", "passphrase");

   compress_file("input_compression.txt", "test_compression.cmp");
   decompress_file("test_compression.cmp", "out_compression.txt");

    /* Continue the program until the user types '5' to exit */
    do {
        
        /* Request a selection from the user */
        print_main_menu();
        scanf("%d", &user_selection);

        /* Allow to user to re-input their selection until it is valid */
        while (user_selection < 1 || user_selection > 5) {
           	printf("Invalid choice\n");
            print_main_menu();
            scanf("%d", &user_selection);
        }

        /* Select the function to call based on the user input */
        switch(user_selection) {
            case 1: 
                /*add_item(&item_list);*/ /*I'm assuming create_item() from item.h?*/
                break;
            case 4: 
			    sort_num = sort_option();
				/*merge_sort(&item_list);*/
				break;
        }

    } while (user_selection != 5);
    return 0;
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_main_menu (void)
{
    printf("\n"
    "1. Add an Item\n"
	"4. Sort Database\n"
    "5. Exit the Program\n"
    "Enter your choice (number between 1-5)>\n");
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
int sort_option(void) {
	
	int user_selection;
	
	/* Request a selection from the user */
	print_sorting_menu();
	scanf("%d", &user_selection);
	        
	/* Allow to user to re-input their selection until it is valid */
	while (user_selection < 1 || user_selection > 5) {
		printf("Only 1 available. Enter 1\n"); /*Temporary*/
		print_sorting_menu();
		scanf("%d", &user_selection);
	}	
	
	return user_selection;
}

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