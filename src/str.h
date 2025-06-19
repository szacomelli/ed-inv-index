#include <stdio.h>
#include <stdlib.h>

#define string char*

/* Returns the relative position of `strOne` to `strTwo`.
*  That is, 1 if `strOne > strTwo`, 0 if `strOne == strTwo`
*  and 1 if neither.
*/
int strcmp(const string strOne, const string strTwo);

/* @brief Count the occurrences of the char `wanted` 
*  in the string `txt`
*  
*  @example 
*  > int result = countChar("M_u_s_t p_r_i_n_t 7", '_');
*  > printf("%d\n", result);
*  >> 7
*/
int countChar(string txt, char wanted);

/* @brief Returns the lenght of the string occupied.
*  It stops at the first `\0` character
*/
int strSize(const string str);

/* @brief Change the string the characters in `dst` from 
* `start` to `end` indexes with the string in `src`. The
* function assumes that dst will have enough space 
* pre-allocated
*
*  @example
*  > char dst[15] = "abcdefg";
*  > char src[8] = "MakeCopy";
*  > strcopy(src, dst, 3, 12);
*  > printf("%s", dst);
*  >> abcMakeCopy
*/
void strImplant(string src, string dst, int start, int end);

/* Copy the content of string `src` in string `dst`. You
*  must create the dst string with sufficient space
*/
void strCopy(const string src, string dst);

/* Concatenates the strings `strOne` and `strTwo` in the 
*  string `result`. If the `sep` is set to `\0`, there 
*  won't have a separator character. You must pre-allocate
*  the result string with suficcient space
*/
void strConcat(string strOne, string strTwo, string result, char sep);

/* Returns a list of pointers to the splitted content. The
*  content of `str is modified` so if you are going to use
*  the string yet, make a copy before use this function.
*  The returned pointer must be `freed`.
*/
string* strSplit(string str, char sep);

/* Returns 1 if `strOne` is a substring of `strTwo` and 
*  0 otherwise. Is case sensitive (i.e. -> a != A)
*/
int isSubstr(string strOne, string strTwo);