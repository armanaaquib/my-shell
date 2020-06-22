#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pwd.h>

#include "alias.h"
#include "util.h"
#include "built_in.h"
#include "var.h"
#include "prompt.h"

Alias *aliases = NULL;
Var *vars = NULL;

void add_defaults(Alias **aliases, Var **vars)
{
  add_var(vars, "ash_p=ash: [cyan]{pwd} [status]: ");
  add_alias(aliases, "md=mkdir", *vars);
  add_alias(aliases, "rd=rmdir", *vars);
}

void handle_cmd_not_found(char *command)
{
  printf(ANSI_COLOR_YELLOW "ash: " ANSI_COLOR_RESET);
  printf("command not found: %s\n", command);
  exit(127);
}

void execute(char *instruction, int *exit_code)
{
  char **command = splitIntoTen(instruction, ' ');
  expand(command, vars);

  if (handle_built_in(command, &aliases, &vars, exit_code))
  {
    return;
  }

  char *actual = get_actual(aliases, command[0]);

  int pid = fork();

  if (pid == 0)
  {
    signal(SIGINT, NULL);
    execvp(actual, command);
    handle_cmd_not_found(actual);
  }
  else
  {
    int status;
    wait(&status);
    *exit_code = WEXITSTATUS(status);
  }
}

void run_ashrc(int *exit_code)
{
  int buffer_len = 255;
  char buffer[buffer_len];

  // char *home_path = getpwuid(getuid())->pw_dir;
  // chdir(home_path);

  FILE *fp = fopen("/Users/aaquibequbal/.ashrc", "r");

  if (fp)
  {
    while (fgets(buffer, buffer_len, fp))
    {
      char *b = copy_string(buffer, 0, strlen(buffer) - 1);
      execute(b, exit_code);
    }

    fclose(fp);
  }
}

int main(void)
{
  signal(SIGINT, SIG_IGN);

  add_defaults(&aliases, &vars);
  int exit_code = 0;
  run_ashrc(&exit_code);

  while (1)
  {
    char instruction[255];

    prompt(exit_code, vars);
    gets(instruction);

    execute(instruction, &exit_code);
  }

  return 0;
}
