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
