#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#include "built_in.h"

int handle_alias(Alias **aliases, char **command, int *exit_code)
{
  if (command[1])
  {
    add_alias(aliases, command[1]);
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

int handle_built_in(char **command, Alias **aliases, int *exit_code)
{
  if (strcmp(command[0], "") == 0)
  {
    return 1;
  }

  if (strcmp(command[0], "exit") == 0)
  {
    exit(0);
  }

  if (strcmp(command[0], "alias") == 0)
  {
    return handle_alias(aliases, command, exit_code);
  }

  if (strcmp(command[0], "cd") == 0)
  {
    return handle_cd(command[1], exit_code);
  }

  return 0;
}
