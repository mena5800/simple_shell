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
	int i;

	for (i = length - 1; i >= 0; i--)
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

/**
 * print_error - function to print not found command error
 * @cmd: object to get error information
 * @error_name: the name of error
 * Return: void
 */
void print_error(info cmd, char *error_name)
{
	my_print(cmd.name);
	my_print(": ");
	my_print(int_string(cmd.line_count));
	my_print(": ");
	my_print(cmd.command);
	my_print(": ");
	my_print(error_name);
	my_print("\n");
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
