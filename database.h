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
    item_t item;
};
typedef struct item_node item_node_t;


void save_database(item_node_t* item_list);
void load_database(item_node_t* item_list);