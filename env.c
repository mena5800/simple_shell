#include "main.h"


int get_env(char **envp)
{
  char **env = envp;
  for (; *env != 0; env++)
  {
    char *thisEnv = *env;
    printf("%s\n", thisEnv);    
  }
  return 0;
}

