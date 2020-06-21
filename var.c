#include <stdlib.h>
#include <string.h>
#include "var.h"
#include "util.h"

void add_var(Var **vars, char *exp)
{
  char **name_value = splitIntoTwo(exp, '=');

  Var *p_walk = *vars;
  Var *last = NULL;

  while (p_walk)
  {
    if (strcmp(p_walk->name, name_value[0]) == 0)
    {
      strcpy(p_walk->value, name_value[1]);
      return;
    }
    last = p_walk;
    p_walk = p_walk->next;
  }

  if (last)
  {
    last->next = malloc(sizeof(Var));
    last = last->next;
  }
  else
  {
    last = malloc(sizeof(Var));
    *vars = last;
  }

  last->name = malloc(sizeof(strlen(name_value[0])));
  last->value = malloc(sizeof(strlen(name_value[1])));

  strcpy(last->name, name_value[0]);
  strcpy(last->value, name_value[1]);
}

char *get_val(Var *vars, char *name)
{
  char *var_name = copy_string(name, 1, strlen(name));
  Var *p_walk = vars;

  while (p_walk)
  {
    if (strcmp(p_walk->name, var_name) == 0)
    {
      return p_walk->value;
    }
    p_walk = p_walk->next;
  }

  return NULL;
}
