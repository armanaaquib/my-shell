#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alias.h"
#include "util.h"

void add_alias(Alias **aliases, char *exp)
{
  char **aka_actual = splitIntoTwo(exp, '=');

  Alias *p_walk = *aliases;
  Alias *last = NULL;

  while (p_walk)
  {
    if (strcmp(p_walk->aka, aka_actual[0]) == 0)
    {
      strcpy(p_walk->actual, aka_actual[1]);
      return;
    }
    last = p_walk;
    p_walk = p_walk->next;
  }

  if (last)
  {
    last->next = malloc(sizeof(Alias));
    last = last->next;
  }
  else
  {
    last = malloc(sizeof(Alias));
    *aliases = last;
  }

  last->aka = malloc(sizeof(strlen(aka_actual[0])));
  last->actual = malloc(sizeof(strlen(aka_actual[1])));

  strcpy(last->aka, aka_actual[0]);
  strcpy(last->actual, aka_actual[1]);
}

char *get_actual(Alias *aliases, char *aka)
{
  Alias *p_walk = aliases;

  while (p_walk)
  {
    if (strcmp(p_walk->aka, aka) == 0)
    {
      return p_walk->actual;
    }
    p_walk = p_walk->next;
  }

  return aka;
}

void show(Alias *aliases)
{
  Alias *p_walk = aliases;

  while (p_walk)
  {
    printf("%s='%s'\n", p_walk->aka, p_walk->actual);
    p_walk = p_walk->next;
  }
}
