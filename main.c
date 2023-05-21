#include "main.h"

#define BUFFER_SIZE 1024

void command_process(int real_arguments, char **argv, char **envp, info cmd);

int main(int ac, char **argv, char **envp)
{
	info cmd = {argv[0],argv[1],0};
	char *prompt = "$ ";
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	int real_arguments;
	char buffer[BUFFER_SIZE];

	if (isatty(STDIN_FILENO))
	{
		/*Running in interactive mode\n");*/

		/* declaring void variables */
		(void)ac;

		/* Create a loop for the shell's prompt */
		while (1)
		{
			my_print(prompt);
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
			command_process(real_arguments,argv,envp,cmd);

		}
	}
	else
	{
		/* Running in non interactive mode\n */
		nchars_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
		if (nchars_read <= 0)
		{
			perror("read");
			return 1;
		}
		cmd.line_count += 1;

		buffer[nchars_read] = '\0';

		if (nchars_read > 0 && buffer[nchars_read - 1] == '\n')
		{
			buffer[nchars_read - 1] = '\0';
		}

		real_arguments = 0;
		argv = clean_command(buffer, nchars_read, &real_arguments);
		cmd.command = argv[0];
		command_process(real_arguments,argv,envp,cmd);
		return 1;
	}

	/* free up allocated memory */
	free(lineptr);
	return (0);
}

