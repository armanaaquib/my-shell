#include <stdlib.h>
#include <string.h>
#include "var.h"
#include "util.h"

void add_var(Var **vars, char *exp)
{
  char **name_value = splitIntoTwo(exp, '=');
  expand(name_value, *vars);

  Var *p_walk = *vars;
  Var *last = NULL;

  while (p_walk)
  {
    if (strcmp(p_walk->name, name_value[0]) == 0)
    {
      p_walk->value = copy_string(name_value[1], 0, strlen(name_value[1]));
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

  last->name = copy_string(name_value[0], 0, strlen(name_value[0]));
  last->value = copy_string(name_value[1], 0, strlen(name_value[1]));
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

  return "";
}

void expand(char **command, Var *vars)
{
  int i = 0;
  while (command[i])
  {
    if (command[i][0] == '$' && find_char(command[i], '=') == 0)
    {
      char *to_free = command[i];
      command[i] = get_val(vars, command[i]);
    }
    i++;
  }
}
