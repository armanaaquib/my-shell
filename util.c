#include <stdlib.h>
#include <string.h>

char *copy_string(char *str, int start, int end)
{
  char *n_str = malloc(sizeof(char) * (end - start));

  for (int i = start; i < end; i++)
  {
    n_str[i - start] = str[i];
  }

  return n_str;
}

char **splitIntoTwo(char *exp, char key)
{
  char **split = malloc(sizeof(char *) * 2);
  int ins_len = strlen(exp);

  for (int i = 0; i < ins_len; i++)
  {
    if (exp[i] == key)
    {
      split[0] = copy_string(exp, 0, i);
      split[1] = copy_string(exp, i + 1, ins_len);

      return split;
    }
  }

  return NULL;
}

char **splitIntoTen(char *instruction, char key)
{
  char **split = malloc(sizeof(char *) * 10);
  int s_count = 0;

  int ins_len = strlen(instruction);

  int start = 0;
  for (int i = 0; i <= ins_len; i++)
  {
    if (instruction[i] == key || instruction[i] == 0)
    {
      split[s_count++] = copy_string(instruction, start, i);
      start = i + 1;
    }
  }
  split[s_count] = NULL;

  return split;
}
