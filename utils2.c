#include "main.h"

/**
 * execmd - excute command using execve
 * @path: the path of command
 * @command: the command name
 * @args: arguments
 * @envp: environmental variables
 * Return: status of command
 */
int execmd(char *path, char *command, char **args, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		/* Child process*/
		execve(path, args, envp);
		perror("execvp");
		exit(1);
	}
	else
	{
		/* Parent process */
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("wait");
			exit(1);
		}
		clear_execmd(path, command, args);
	}
	return (WEXITSTATUS(status));
}

/**
 * clear_execmd - free heap after excution
 * @path: the path of command
 * @command: the command name
 * @args: arguments
 * Return: void
 */
void clear_execmd(char *path, char *command, char **args)
{
	int i;

	if (strcmp(path, command) == 0)
		free(command);
	else if (strlen(command) == 0 && path[1] != 'u')
	{
		free(command);
	}
	else
	{
		free(path);
		free(command);
	}
	command = NULL;
	for (i = 0; i < MAX_COMMAND_LENGTH; i++)
	{
		args[i] = NULL;
	}
}

/**
 * free_args - free arguments
 * @command_len: the length of args
 * @command: the command name
 * @args: arguments
 * Return: void
 */
void free_args(size_t *command_len, char *command, char **args)
{
	int i;

	*command_len = 0;
	(void)command;
	command = NULL;
	for (i = 0; i < MAX_COMMAND_LENGTH; i++)
	{
		args[i] = NULL;
	}
}

/**
 * handle_exit - to handle command exit
 * @i: number of args
 * @command: the command name
 * @cmd: struct contain information
 * @args: arguments
 * @command_len: the length of command
 * @exit_code: code of exit
 * Return: void
 */
void handle_exit(int i, char *command, info cmd,
				 size_t *command_len, int exit_code, char **args)
{
	if (i == 1)
	{
		free(command);
		free(cmd.command);
		free_args(command_len, command, args);
		exit(exit_code);
	}
	else
	{
		exit_code = atoi(args[1]);
		if (exit_code == 0 && strcmp(args[1], "0") == 0)
		{
			free(command);
			free(cmd.command);
			free_args(command_len, command, args);
			exit(exit_code);
		}
		else if (exit_code <= 0)
		{
			fprintf(stderr, "%s: %d: exit: Illegal number: %s\n",
					cmd.name, cmd.line_count, args[1]);
			free(command);
			free_args(command_len, command, args);
		}
		else
		{
			free(command);
			free(cmd.command);
			free_args(command_len, command, args);
			exit(exit_code);
		}
	}
}

/**
 * option - to choose between cmd options
 * @i: number of args
 * @command: the command name
 * @cmd: struct contain information
 * @args: arguments
 * @envp: environmental variable
 * @status: the statue of code
 * @command_len: the length of command
 * @exit_code: code of exit
 * Return: void
 */
void option(int i, char **args, char **envp, char *command,
			size_t *command_len, info cmd, int exit_code, int *status)
{
	char *path;

	if (i == 0)
	{
	}
	else if (strcmp(args[0], "env") == 0 && i == 1)
	{
		get_env(envp);
		free(command);
		free_args(command_len, command, args);
	}
	else if (strcmp(args[0], "exit") == 0)
	{

		handle_exit(i, command, cmd, command_len, exit_code, args);
	}
	else if (i > 0)
	{
		path = get_location(args[0]);
		/* Get path to executable file*/
		if (path == NULL)
		{
			print_error(status, cmd);
			free_args(command_len, command, args);
		}
		else
		{

			*status = execmd(path, command, args, envp);
			*command_len = 0;
		}
	}
	free(cmd.command);
}
