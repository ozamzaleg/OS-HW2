#ifndef FUNCTION_H_
#define FUNCTION_H_

int *readArrFromFile(FILE *file, char *letter, int *len);
void readElementFromFile (FILE *file , int len, int* arr);
char* getNameFile(char* argv[], int argc);
int getMax(int* arr, int start, int end);

#endif /* FUNCTION_H_ */
