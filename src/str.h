#include <stdio.h>

#define string char*
#define uint unsigned int
#define capacity(object) (sizeof(object)/sizeof(object[0])) // Returns the capacity of an array

int strcmp(string wordOne, string wordTwo);

int strsize(string word);

/* Example :
*  > char dst[15] = "abcdefg";
*  > char src[8] = "MakeCopy";
*  > strcopy(src, dst, 3, 12);
*  > printf("%s", dst);
*  >> abcMakeCopy
*/
void strcopy(string src, string dst, uint start, uint end);