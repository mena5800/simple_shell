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
 * sigint_handler - function call when interept
 * Return: void
 */
void sigint_handler(void)
{
	char *prompt = "$ ";

	my_print("\n");
	my_print(prompt);
}

/**
 * get_location - get the location of exe file should excute
 * @command: the name of command
 * Return: the location of command
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
		free(command);
		return (NULL);
	}
	free(command);
	return (NULL);
}

/**
 * my_strtok- seprate the string to array of strings
 * @delim: the seprator
 * @s: string
 * Return: string
 */
char *my_strtok(char *s, const char *delim)
{
	static char *p;
	char *start;

	if (s != NULL)
		p = s;
	if (p == NULL)
		return (NULL);
	start = p;
	while (*p != '\0')
	{
		const char *d = delim;

		while (*d != '\0')
		{
			if (*p == *d)
			{
				*p = '\0';
				p++;
				if (start != p)
				{
					return (start);
				}
				else
				{
					start = p;
					break;
				}
			}
			d++;
		}
		p++;
	}
	if (start == p)
		return (NULL);
	else
		return (start);
}

/**
 * int_string - function to convert int to string
 * @num: int number
 * Return: string of int number
 */
char *int_string(int num)
{
	int i;
	int counter = 0;
	int num_mod = num;
	char *word;

	while (num % 10 || num != 0)
	{
		counter += 1;
		num /= 10;
	}

	word = malloc(counter + 1);

	for (i = counter - 1; i >= 0; i--)
	{
		word[i] = num_mod % 10 + '0';
		num_mod /= 10;
	}
	word[counter] = '\0';
	return (word);
}
