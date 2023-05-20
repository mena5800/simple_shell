#include "main.h"

/**
 * execmd - excute command
 * @argv: command
 * Return: always void
 */

void execmd(char **argv,info cmd)
{
	char *command = NULL;
	char *actual_command = NULL;
	pid_t pid;

	if (argv)
	{
		/* get the command */
		command = argv[0];
		actual_command = get_location(command);
		pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
		}
		else if (pid == 0)
		{
			/* execute the command with execve */
			if (execve(actual_command, argv, NULL) == -1)
			{
				print_error(cmd,"not found");
				// perror("");
			};
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(NULL);
		}
	}
}
