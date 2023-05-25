#include "main.h"

/**
 * my_print - print string
 * @str: the string we want to print
 * Return: void
 */

void my_print(char *str)
{
	int length = strlen(str);
	int i = 0;
	char c;

	for (i = 0; i < length; i++)
	{
		c = str[i];
		write(1, &c, 1);
	}
}


/**
 * my_getline - get the command as input from console
 * @word: where the command save
 * Return: the length of input
 */

int my_getline(char *word)
{
	char buffer[1024];
	ssize_t num_bytes;
	char *w;

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		return (1);
	}
	/* Read input from the user */
	if ((num_bytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
	{
		buffer[num_bytes] = '\0';
		w = buffer;
		my_strcpy(word,w);
		return (num_bytes);
	}
    free(word);
	my_print("\n");
	exit(EXIT_SUCCESS);
}

void sigint_handler(int signum) {
	char *prompt = "$ ";
	(void)signum;
    my_print("\n");
	my_print(prompt);
}

/**
 * get_location - get the location of exe file should excute
 * @command: the name of command
 * Return - the location of command
*/

char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	struct stat buffer;

	path = getenv("PATH");
	if (path)
	{
		path_copy = strdup(path);
		path_token = my_strtok(path_copy, ":");
		while (path_token != NULL)
		{
			file_path = malloc(1024);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = my_strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	return (NULL);
}
