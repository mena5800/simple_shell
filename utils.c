#include "main.h"

/**
 * my_print - print string
 * @str: the string we want to print
 * Return: void
 */

void my_print(char *str)
{
	int length = my_strlen(str);
	int i = 0;
	char c;

	for (i = 0; i < length; i++)
	{
		c = str[i];
		write(1, &c, 1);
	}
}

/**
 * my_atoi - convert string to int
 * @str: string want to convert
 * Return: int after conversion from string
 */

int my_atoi(char *str)
{
	int length = my_strlen(str);
	int mul = 1;
	int result = 0;

	for (int i = length - 1; i >= 0; i--)
	{
		result += mul * (str[i] - '0');
		mul *= 10;
	}
	return (result);
}

/**
 * my_getline - get the command as input from console
 * @word: where the command save
 * Return: the length of input
*/

int my_getline(char **word)
{
	char buffer[1024];
	ssize_t num_bytes;
	char *w;

	/* Read input from the user */
	num_bytes = read(STDIN_FILENO, buffer, sizeof(buffer));
	if (num_bytes == -1)
	{
		perror("Failed to read input");
		return (EXIT_FAILURE);
	}

	buffer[num_bytes] = '\0';
	w = buffer;
	*word = w;
	return (num_bytes);
}
