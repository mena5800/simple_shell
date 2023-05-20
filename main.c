#include "main.h"

#define BUFFER_SIZE 1024

int main(int ac, char **argv, char **envp)
{
	char *prompt = "(Eshell) $ ";
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " |&;\n";
	int num_tokens = 0;
	char *token;
	int i;
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
			num_tokens = 0;
			my_print(prompt);
			nchars_read = my_getline(&lineptr);
			/* check if the getline function failed or reached EOF or user use CTRL + D */
			if (nchars_read == -1)
			{
				my_print("Exiting shell....\n");
				return (-1);
			}

			/* allocate space for a copy of the lineptr */
			lineptr_copy = malloc(sizeof(char) * nchars_read);
			if (lineptr_copy == NULL)
			{
				perror("tsh: memory allocation error");
				return (-1);
			}

			/* lineptr = command      copy command lineptr_copy*/
			/* copy lineptr to lineptr_copy */
			my_strcpy(lineptr_copy, lineptr);

			/********** split the string (lineptr) into an array of words ********/
			/* calculate the total number of tokens */
			token = my_strtok(lineptr, delim);

			while (token != NULL)
			{
				num_tokens++;
				token = my_strtok(NULL, delim);
			}
			num_tokens++;

			/* Allocate space to hold the array of strings */
			argv = malloc(sizeof(char *) * num_tokens);

			/* Store each token in the argv array */
			token = my_strtok(lineptr_copy, delim);

			for (i = 0; token != NULL; i++)
			{
				argv[i] = malloc(sizeof(char) * my_strlen(token));
				my_strcpy(argv[i], token);

				token = my_strtok(NULL, delim);
			}
			argv[i] = NULL;

			/* execute the command */
			if (my_strcmp(argv[0], "env") == 0 && num_tokens == 2)
			{
				get_env(envp);
			}
			else if (my_strcmp(argv[0], "exit") == 0)
			{
				if (num_tokens == 2)
					exit(0);
				else
				{
					exit_code = my_atoi(argv[1]);
					exit(exit_code);
				}
			}
			else if (my_strcmp(argv[0], "cd") == 0)
			{
				if (num_tokens == 2)
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
				divide_commands(argv, num_tokens - 1);
			}
		}
	}
	else
	{
		/* Running in non interactive mode\n */
		nchars_read = read(STDIN_FILENO, cwd, BUFFER_SIZE - 1);
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
		printf("%s\n", cwd);

		// Execute the command using execve
		char *args[] = {"/bin/sh", "-c", cwd, NULL};
		execve("/bin/sh", args, NULL);

		// If execve fails, print an error and exit
		perror("execve");
		return 1;

	}

	/* free up allocated memory */
	free(lineptr_copy);
	free(lineptr);
	return (0);
}
