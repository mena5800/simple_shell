#include "main.h"

/**
 * execmd - excute command
 * @argv: command
 * Return: always void
 */

int execmd(char **argv, info cmd)
{
	char *command = NULL;
	char *actual_command = NULL;
	pid_t pid;
	pid_t child_pid;
	int status = -1;

	if (argv)
	{
		/* get the command */
		command = argv[0];
		actual_command = get_location(command);
		if (actual_command != NULL)
		{
		pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
		}
		else if (pid == 0)
		{
			/* execute the command with execve */
			if (execve(actual_command, argv, cmd.envp) == -1)
			{
				print_error(cmd, "not found");
			};
		}
		else
		{
			child_pid = waitpid(pid, &status, 0);
			if (child_pid == -1)
			{
				perror("waitpid");
				return (-1);
			}
			return (status);
		}
		}
		else
		{
			print_error(cmd, "not found");
		}
		
	}
	return (status);

}
