#ifndef __UTIL_H_
#define __UTIL_H_

char *copy_string(char *str, int start, int end);
char **splitIntoTwo(char *exp, char key);
char **splitIntoTen(char *instruction, char key);
int find_char(char *string, char c);

#endif
