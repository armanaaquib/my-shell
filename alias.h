#include "var.h"

#ifndef __ALIAS_H_
#define __ALIAS_H_

typedef struct alias
{
  char *aka;
  char *actual;
  struct alias *next;
} Alias;

void add_alias(Alias **aliases, char *exp, Var *vars);
char *get_actual(Alias *aliases, char *aka);
char **replace_alias(Alias *aliasses, char **command);
void show(Alias *aliases);

#endif
