#include "str.h"

/* Return the size of the opened file
*/
int docSize(FILE* buffer);

/* Returns a pointer to the text of a single doc
*/
string readSingle(string path, int numDoc);

/* Returns the list of pointer to the text of all
*  docs in the range [start, end]
*/
string* readTxts(string path, const int start, const int end);

/* Returns the triple pointer to all the strings
*  where all the double pointers refers to a
*  different documents. *(return + i) refers to the
*  document i, and *(*(return + i) + j) refers to 
*  the word j of the document i
*/
string** readStrs(string path, const int start, const int end);