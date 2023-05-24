#include "main.h"

/**
 * interactive_mode - interactive mode function
 * @cmd: shell information
 * @argv: array of strings
 * @envp: environment variables
 * Return: 1 or -1
*/
int interactive_mode(info cmd, char **argv, char **envp)
{
	char *lineptr = NULL;
	int real_arguments;
	ssize_t nchars_read;

	nchars_read = my_getline(&lineptr);
	cmd.line_count += 1;
	/* check if the getline function failed or reached EOF or user use CTRL + D */
	if (nchars_read == -1)
	{
		my_print("Exiting shell....\n");
		return (-1);
	}
	real_arguments = 0;
	argv = clean_command(lineptr, nchars_read, &real_arguments);
	cmd.command = argv[0];
	command_process(real_arguments, argv, envp, cmd);
	free(argv);
	return (1);
}