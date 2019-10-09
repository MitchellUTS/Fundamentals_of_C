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

#include "core.h"

void print_byte_as_bits(char val) {
    int i = 0;
    for (i = 7; 0 <= i; i--) {
        printf("%c", (val & (1 << i)) ? '1' : '0');
    }
}

void print_bits(char * ty, char * val, unsigned char * bytes, size_t num_bytes) {
    printf("(%s) %s = [ ", ty, val);
    int i;
    for (i = 0; i < num_bytes; i++) {
        print_byte_as_bits(bytes[i]);
        printf(" ");
    }
    printf("]\n");
}

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

void loginFunction()
{
  
  char username[20];
  char userpwd[10]; 
  int i=0;
  
  printf("Enter your username for the IMS : ");

  scanf("%s",username);
  
  printf("Enter your password : ");

 
  for(i=0;i<10;i++)
  {
   userpwd[i]=getchar();
   printf("*");   	
  }
  userpwd[i]='\0';
 
  printf("\n\nPress any key to continue");
  getchar();
 
 if((!strcmp(username,"admin") && !strcmp(userpwd,"fundaC")) || 
  (!strcmp(username,"student") && !strcmp(userpwd,"fundaC")) || 
  (!strcmp(username,"lecturer") && !strcmp(userpwd,"fundaC")))
 {
  printf("\n\n Successful Login");
 }else
 {
  printf("\n\nIncorrect username or password");
 }
}