#include "main.h"

/**
 * main - the main function
 * @ac: the number of arguments
 * @argv: the arguments
 * @envp: the environmetal variables
 * Return: 0 or -1
 */
int main(int ac, char **argv, char **envp)
{
	info cmd;
	char *prompt = "$ ";
	char *lineptr = NULL;

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
		interactive_mode(cmd, argv, envp);
		free(lineptr);
		return (0);
	}

	/* free up allocated memory */
}
