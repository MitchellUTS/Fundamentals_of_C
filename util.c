/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: Provide a variety of core/basic functions
 * 
*******************************************************************************/

/*******************************************************************************
 * This provides a boolean answer that determines if a value is 
 * between (inclusive) a specified range.
 * inputs:
 * - char value: this is the value to test
 * - char min: this is the minium value that <value> can be and stil have the 
 *              function return true
 * - char max: this the maxium value that <value> can be and still have the 
 *              function return true
 * outputs:
 * - int: this will be true or false
*******************************************************************************/
int between(int value, int min, int max) {
    return (value >= min && value <= max);
}