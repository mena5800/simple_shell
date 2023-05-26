#include "main.h"

/**
 * main - main function
 * @argc: num of arguments pass from cmd
 * @argv: the arguemets
 * @envp: the environmetal variables
 * Return:1
 */
int main(int argc, char *argv[], char **envp)
{
	int status = 2;
	info cmd;
	char *command = NULL;
	size_t command_len = 0;
	char *args[MAX_COMMAND_LENGTH];
	int i;
	char *newline;
	int exit_code = 0;

	cmd.name = argv[0];
	cmd.line_count = 0;
	cmd.envp = envp;

	(void)argc;
	while (getline(&command, &command_len, stdin) != -1)
	{
		newline = strchr(command, '\n');
		if (newline != NULL)
		{
			*newline = '\0';
		}

		i = tokenize(command, args);
		cmd.command = malloc(20);
		strcpy(cmd.command, command);

		cmd.line_count += 1;

		option(i, args, envp, command, &command_len, cmd, exit_code, &status);
	}

	free(command);
	return (WEXITSTATUS(status));
}
