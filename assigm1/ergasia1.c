#include <stdio.h>
#include <stdlib.h>


__asm int my_palindrome(char *src)
{
begining
	MOV r5 , #0          //counter for the length
length
	LDRB r6 ,[r0,r5]    //take the memory of the current character
	ADDS r5 , #1        //point the next character
	CMP r6 , #0 
	BNE length
	SUBS r5 , #2  
	ADDS r4 , r0 , r5   // load the memory address of the last character 
loop1
	LDRB r2 , [r0]      // load byte into r2 from memory pointed by r0
	LDRB r3 , [r4]      // load byte into r3 from memory pointed by r4 
	CMP  r2 , r3        //compare the bytes
	BNE  notequal       //if the bytes are not the same the string is not palindrome. No further actions are needed
	ADDS r0 , #1        //point the next byte
	SUBS r4 , #1        //point the next byte 
	CMP  r0 , r4        //compare to find the end 
	BHI equal
	B loop1
	
notequal
	MOV r0 , #0         //the string is not palindrome
	BX lr
	
equal
	MOV r0 , #1         //the string is palindrome
	BX lr
	
}


int main(void)
{
	char a[]=  "Q";
	int x;
	x = my_palindrome(a);
	if (x) printf("it is palindrome ");
	else printf("it is not palindrome ");
	while (1);
}
