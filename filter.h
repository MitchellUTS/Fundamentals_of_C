/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Vincent Lay, ...
 *  
 * Date of creation: 22/09/2019
 * 
 * Purpose: To provide functions related to search within the item structure
 * 
*******************************************************************************/

void select_filter (item_node_t* node);
void print_filter_menu (void);
void filter_int_items (item_node_t* node);
void filter_long_items (item_node_t* node);
void filter_char_items (int char_search_case, item_node_t* node);
