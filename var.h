#ifndef __VAR_H_
#define __VAR_H_

typedef struct var
{
  char *name;
  char *value;
  struct var *next;
} Var;

void add_var(Var **vars, char *exp);
char *get_val(Var *vars, char *name);
void expand(char **command, Var *vars);

#endif
