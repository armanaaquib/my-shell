#ifndef __ALIAS_H_
#define __ALIAS_H_

typedef struct alias
{
  char *aka;
  char *actual;
  struct alias *next;
} Alias;

void add_alias(Alias **aliases, char *exp);
char *get_actual(Alias *aliases, char *aka);
void show(Alias *aliases);

#endif
