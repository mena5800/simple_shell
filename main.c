#include "main.h"




int main(int ac, char **argv, char **envp)
{
	info cmd;
	char *prompt = "$ ";
	char *lineptr = NULL;
	ssize_t nchars_read;
	int real_arguments;
	char buffer[BUFFER_SIZE];
	int i;
	int num_lines;

	cmd.name = argv[0];
	cmd.command = argv[1];
	cmd.line_count = 0;
	cmd.envp = envp;
	if (isatty(STDIN_FILENO))
	{
		/*Running in interactive mode\n");*/
		/* declaring void variables */
		(void)ac;

		/* Create a loop for the shell's prompt */
		while (1)
		{
			my_print(prompt);
			if (interactive_mode(cmd, argv, envp) == -1)
			{
				return (-1);
			}
		}
	}
	else
	{
		/* Running in non interactive mode */
		nchars_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
		if (nchars_read <= 0)
		{
			perror("read");
			return (1);
		}

		buffer[nchars_read] = '\0';

		if (nchars_read > 0 && buffer[nchars_read - 1] == '\n')
		{
			buffer[nchars_read - 1] = '\0';
		}
		real_arguments = 0;
		num_lines = get_num_lines(buffer);
		argv = clean_command(buffer, nchars_read, &real_arguments);

		for (i = 0; i < num_lines; i++)
		{
			/*need more handling*/
			cmd.line_count += 1;
			cmd.command = argv[i];
			command_process(real_arguments, argv, envp, cmd);
		}
		free(argv);
		return (0);
	}

	/* free up allocated memory */
	free(lineptr);
	return (0);
}
