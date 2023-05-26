#include "main.h"

/**
 * tokenize - divide string
 * @command: command string
 * @args: the arguments
 * Return: the length of args
 */
int tokenize(char *command, char **args)
{
	char *token;
	int i = 0;

	token = my_strtok(command, " \n");
	while (token != NULL && i < MAX_COMMAND_LENGTH - 1)
	{

		/* Ignore comments */
		if (token[0] == '#')
		{
			token = NULL;
			break;
		}
		if (strlen(token) == 0)
		{
			token = my_strtok(NULL, " ");
			continue;
		}

		args[i++] = token;
		token = my_strtok(NULL, " \n");
	}
	args[i] = NULL;
	return (i);
}

/**
 * print_error - print error
 * @status: the status of code
 * @cmd: struct has information
 * Return: void
 */
void print_error(int *status, info cmd)
{
	char error[1024] = "";
	char *line_count;

	line_count = int_string(cmd.line_count);
	strcat(error, cmd.name);
	strcat(error, ": ");
	strcat(error, line_count);
	strcat(error, ": ");
	strcat(error, cmd.command);
	strcat(error, ": not found\n");
	fprintf(stderr, "%s", error);
	*status = 127;
	free(line_count);
}
