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

struct item_node {
    struct item_node* next;
    item_t* item_data;
};
typedef struct item_node item_node_t;


void save_database(item_node_t* item_list);
void load_database(item_node_t* item_list);
void add_record(FILE* file_ptr, item_node_t* node, int id, long isbn, 
		 	 	char title[], char author[], char type[], char chategory[]);
void merge_sort(item_node_t** start); 
struct item_node_t* sort_items(item_node_t* a, item_node_t* b);
void split_lists(item_node_t* head, 
                 item_node_t** front, item_node_t** back); 
void print_sorting_menu(void);