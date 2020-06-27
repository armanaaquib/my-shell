#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "prompt.h"
#include "util.h"

char *get_to(char *string, char c, int *start)
{
  char *sub_str = malloc(sizeof(char) * 10);
  int ss_c = 0;

  while (string[*start] != c)
  {
    sub_str[ss_c++] = string[(*start)++];
  }
  sub_str[ss_c] = '\0';

  return sub_str;
}

char *get_color(char *ash_p, int *start, int exit_code)
{
  char *color = get_to(ash_p, ']', start);

  if (strcmp(color, "red") == 0)
  {
    return ANSI_COLOR_RED;
  }
  else if (strcmp(color, "green") == 0)
  {
    return ANSI_COLOR_GREEN;
  }
  else if (strcmp(color, "yellow") == 0)
  {
    return ANSI_COLOR_YELLOW;
  }
  else if (strcmp(color, "cyan") == 0)
  {
    return ANSI_COLOR_CYAN;
  }
  else if (strcmp(color, "status") == 0)
  {
    if (exit_code)
    {
      return ANSI_COLOR_RED;
    }

    return ANSI_COLOR_GREEN;
  }

  return NULL;
}

char *expand_to(char *ash_p, int *start)
{
  char *pd = get_to(ash_p, '}', start);

  if (strcmp(pd, "pwd") == 0)
  {
    char buf[PATH_MAX];
    getcwd(buf, sizeof(buf));
    return copy_string(buf, 0, strlen(buf));
  }
  else if (strcmp(pd, "user") == 0)
  {
    char *uname = malloc(sizeof(char) * 20);
    getlogin_r(uname, 20);
    return uname;
  }

  return pd;
}

Str_color *create_sc(char *color, char *str)
{
  Str_color *sc = malloc(sizeof(Str_color));
  sc->color = color;
  sc->str = str;

  return sc;
}

Str_color **parse_prompt(char *ash_p, int exit_code)
{
  Str_color **sc = malloc(sizeof(Str_color *) * 10);
  int sc_c = 0;

  int start = 0, i = 0;
  char *color = malloc(sizeof(char) * 10);
  color = NULL;

  while (i <= strlen(ash_p))
  {
    if (ash_p[i] == '\0')
    {
      sc[sc_c++] = create_sc(color, copy_string(ash_p, start, i));
    }

    if (ash_p[i] == '[')
    {
      sc[sc_c++] = create_sc(color, copy_string(ash_p, start, i));
      start = i + 1;

      color = get_color(ash_p, &start, exit_code);
      i = start++;
    }

    if (ash_p[i] == '{')
    {
      sc[sc_c++] = create_sc(color, copy_string(ash_p, start, i));
      start = i + 1;

      sc[sc_c++] = create_sc(color, expand_to(ash_p, &start));
      i = start++;
    }

    i += 1;
  }
  sc[sc_c] = NULL;

  return sc;
}

void display_prompt(Str_color **sc)
{
  int i = 0;
  while (sc[i] != NULL)
  {
    char *color = sc[i]->color;
    char *str = sc[i]->str;

    if (color == NULL)
    {
      color = ANSI_COLOR_RESET;
    }

    printf("%s%s", color, str);
    i++;
  }

  printf(ANSI_COLOR_RESET);
}

void prompt(int exit_code, Var *vars)
{
  char *ash_p = get_val(vars, "$ash_p");
  Str_color **sc = parse_prompt(ash_p, exit_code);

  display_prompt(sc);
}
