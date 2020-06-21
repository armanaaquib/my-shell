#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

char *copy_string(char *str, int start, int end)
{
  char *n_str = malloc(sizeof(char) * (end - start));

  for (int i = start; i < end; i++)
  {
    n_str[i - start] = str[i];
  }

  return n_str;
}

char **parse_command(char *instruction)
{
  char **command = malloc(sizeof(char *) * 10);
  int c_count = 0;

  int ins_len = strlen(instruction);

  int start = 0;
  for (int i = 0; i <= ins_len; i++)
  {
    if (instruction[i] == 32 || instruction[i] == 0)
    {
      command[c_count++] = copy_string(instruction, start, i);
      start = i + 1;
    }
  }
  command[c_count] = NULL;

  return command;
}

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

int handle_built_in(char **command, int *color_ind)
{
  if (strcmp(command[0], "") == 0)
  {
    *color_ind = 1;
    return 1;
  }

  if (strcmp(command[0], "exit") == 0)
  {
    exit(0);
  }

  if (strcmp(command[0], "cd") == 0)
  {
    chdir(command[1]);
    return 1;
  }

  return 0;
}

void prompt(int *color_ind)
{
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));

  printf(ANSI_COLOR_CYAN "%s ", cwd);

  if (*color_ind)
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

  int *color_ind = malloc(sizeof(int));
  *color_ind = 0;

  while (1)
  {
    char instruction[255];

    prompt(color_ind);

    gets(instruction);

    char **command = parse_command(instruction);

    if (handle_built_in(command, color_ind))
    {
      continue;
    }

    int pid = fork();
    int status;

    if (pid == 0)
    {
      signal(SIGINT, handle_ctrl_c);
      execvp(command[0], command);
      handle_cmd_not_found(command[0]);
    }
    else
    {
      wait(&status);
      *color_ind = WEXITSTATUS(status);
    }
  }

  return 0;
}
