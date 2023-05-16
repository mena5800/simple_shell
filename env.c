#include "main.h"

/**
 * get_env - print the enviromental variables
 * @envp: environmenal variables
 * Return: 0
 */

int get_env(char **envp)
{
	char **env = envp;

	for (; *env != 0; env++)
	{
		char *thisEnv = *env;

		my_print(thisEnv);
		my_print("\n");

	}
	return (0);
}
