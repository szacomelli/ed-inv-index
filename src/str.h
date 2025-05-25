#include <stdio.h>
#include <stdlib.h>

#define string char*
#define uint unsigned int
#define capacity(object) (sizeof(object)/sizeof(object[0])) // Returns the capacity of an array

int strcmp(string wordOne, string wordTwo);

/* Count the occurrences of the char `wanted` in the string
*  `txt`
*/
int countChar(string txt, char wanted);

/* Returns the lenght of the string occupied. It stops
*  at the first `\0` character
*/
int strSize(string word);

/* Example :
*  > char dst[15] = "abcdefg";
*  > char src[8] = "MakeCopy";
*  > strcopy(src, dst, 3, 12);
*  > printf("%s", dst);
*  >> abcMakeCopy
*/
void strImplant(string src, string dst, uint start, uint end);

/* Copy the content of string `src` in string `dst`
*/
void strCopy(string src, string dst);

/* Concatenates the strings `str1` and `str2` in the string
*  `result`. If the `sep` is set to `\0`, there won't have
*  a separator character 
*/
void strConcat(string str1, string str2, string result, char sep);

/* Returns a list of pointers to the splitted content. The 
*  content of `str` is modified so if you are going to use
*  the string yet, make a copy before use this function.
*  The returned pointer must be freed.
*/
string* strSplit(string str, char sep);