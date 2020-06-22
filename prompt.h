#include <limits.h>
#include "var.h"

#ifndef __PROMPT_H_
#define __PROMPT_H_

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef struct
{
  char *str;
  char *color;
} Str_color;

void prompt(int exit_code, Var *vars);

#endif
