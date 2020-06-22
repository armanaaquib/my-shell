#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alias.h"
#include "util.h"
#include "var.h"

void add_alias(Alias **aliases, char *exp, Var *vars)
{
  char **aka_actual = splitIntoTwo(exp, '=');
  expand(aka_actual, vars);

  Alias *p_walk = *aliases;
  Alias *last = NULL;

  while (p_walk)
  {
    if (strcmp(p_walk->aka, aka_actual[0]) == 0)
    {
      p_walk->actual = copy_string(aka_actual[1], 0, strlen(aka_actual[1]));
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

  last->aka = copy_string(aka_actual[0], 0, strlen(aka_actual[0]));
  last->actual = copy_string(aka_actual[1], 0, strlen(aka_actual[1]));
}

char *get_actual(Alias *aliases, char *aka)
{
  Alias *p_walk = aliases;

  while (p_walk)
  {
    if (strcmp(p_walk->aka, aka) == 0)
    {
      return get_actual(aliases, p_walk->actual);
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
