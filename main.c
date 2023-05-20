#include "main.h"

#define BUFFER_SIZE 1024

int main(int ac, char **argv, char **envp)
{
	info cmd;
	cmd.name = argv[0];
	cmd.command = argv[1];
	cmd.line_count = 0;
	char *prompt = "$ ";
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	int real_arguments;
	int exit_code;
	int cd_return;
	char cwd[BUFFER_SIZE];

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
			/* execute the command */
			if (my_strcmp(argv[0], "env") == 0 && real_arguments == 1)
			{
				get_env(envp);
			}
			else if (my_strcmp(argv[0], "exit") == 0)
			{
				if (real_arguments == 1)
					exit(0);
				else
				{
					exit_code = my_atoi(argv[1]);
					exit(exit_code);
				}
			}
			else if (my_strcmp(argv[0], "cd") == 0)
			{
				if (real_arguments == 1)
				{
					getcwd(cwd, sizeof(cwd));
					cd_return = chdir(getenv("HOME"));
				}
				else if (my_strcmp(argv[1], "-") == 0)
				{
					cd_return = chdir(cwd);
				}
				else
				{
					getcwd(cwd, sizeof(cwd));
					cd_return = chdir(argv[1]);
				}

				if (cd_return != 0)
				{
					perror("Error: ");
				}
			}
			else
			{
				divide_commands(argv, real_arguments, cmd);
			}
		}
	}
	else
	{
		/* Running in non interactive mode\n */
		nchars_read = read(STDIN_FILENO, cwd, BUFFER_SIZE - 1);
		cmd.line_count += 1;
		if (nchars_read <= 0)
		{
			perror("read");
			return 1;
		}
		cwd[nchars_read] = '\0';
		if (nchars_read > 0 && cwd[nchars_read - 1] == '\n')
		{
			cwd[nchars_read - 1] = '\0';
		}

		// Execute the command using execve
		char *args[] = {cmd.name, "-c", cwd, NULL};
		execve("/bin/sh", args, NULL);

		// If execve fails, print an error and exit
		perror("execve");
		return 1;
	}

	/* free up allocated memory */
	free(lineptr);
	return (0);
}



void handle_cd(char *cwd,int argc,char **argv,int *cd_return)
{
	int return_val;

	if (argc == 1)
	{
		getcwd(cwd, sizeof(cwd));
		return_val = chdir(getenv("HOME"));
	}
	else if (my_strcmp(argv[1], "-") == 0)
	{
		return_val = chdir(cwd);
	}
	else
	{
		getcwd(cwd, sizeof(cwd));
		return_val = chdir(argv[1]);
	}
	cd_return = return_val;
	if (return_val != 0)
	{
		perror("Error: ");
	}

}