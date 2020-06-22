#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#include "built_in.h"
#include "alias.h"
#include "var.h"
#include "util.h"

int handle_alias(Alias **aliases, char **command, int *exit_code, Var *vars)
{
  if (command[1])
  {
    add_alias(aliases, command[1], vars);
    *exit_code = command[2] ? 1 : 0;
  }
  else
  {
    show(*aliases);
    *exit_code = 0;
  }

  return 1;
}

int handle_cd(char *path, int *exit_code)
{
  if (path == NULL || strcmp(path, "~") == 0)
  {
    char *home_path = getpwuid(getuid())->pw_dir;
    *exit_code = chdir(home_path);
    return 1;
  }

  *exit_code = chdir(path);
  if (*exit_code)
  {
    perror("cd");
  }

  return 1;
}

int handle_built_in(char **command, Alias **aliases, Var **vars, int *exit_code)
{
  char *actual = get_actual(*aliases, command[0]);

  if (strcmp(actual, "") == 0)
  {
    return 1;
  }

  if (strcmp(actual, "exit") == 0)
  {
    exit(0);
  }

  if (strcmp(actual, "alias") == 0)
  {
    return handle_alias(aliases, command, exit_code, *vars);
  }

  if (strcmp(actual, "cd") == 0)
  {
    return handle_cd(command[1], exit_code);
  }

  if (find_char(actual, '='))
  {
    add_var(vars, actual);
    *exit_code = command[2] ? 1 : 0;
    return 1;
  }

  return 0;
}
