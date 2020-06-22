#include <stdio.h>
#include <unistd.h>
#include "prompt.h"

void prompt(int exit_code)
{
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));

  printf(ANSI_COLOR_CYAN "%s ", cwd);

  if (exit_code)
  {
    printf(ANSI_COLOR_RED "$ ");
  }
  else
  {
    printf(ANSI_COLOR_GREEN "$ ");
  }

  printf(ANSI_COLOR_RESET);
}
