#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>

#include "alias.h"
#include "util.h"
#include "built_in.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

Alias *aliases = NULL;

void handle_cmd_not_found(char *command)
{
  printf(ANSI_COLOR_YELLOW "ash: " ANSI_COLOR_RESET);
  printf("command not found: %s\n", command);
  exit(127);
}

void handle_ctrl_c(int signal)
{
  exit(130);
}

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

int main(void)
{
  signal(SIGINT, SIG_IGN);

  int exit_code = 0;

  while (1)
  {
    char instruction[255];

    prompt(exit_code);

    gets(instruction);

    char **command = splitIntoTen(instruction, ' ');

    if (handle_built_in(command, &aliases, &exit_code))
    {
      continue;
    }

    char *aka = command[0];
    char *actual = get_actual(aliases, aka);
    while (strcmp(aka, actual) != 0)
    {
      strcpy(aka, actual);
      actual = get_actual(aliases, actual);
    }

    int pid = fork();

    if (pid == 0)
    {
      signal(SIGINT, handle_ctrl_c);
      execvp(actual, command);
      handle_cmd_not_found(actual);
    }
    else
    {
      int status;
      wait(&status);
      exit_code = WEXITSTATUS(status);
    }
  }

  return 0;
}
