#include "main.h"

/**
 * my_strcmp - compare between two strings
 * @str1: the first string
 * @str2: the second string
 * Return: 1 if 2 strings are not the same 0 if the 2 strings are the same
*/

int my_strcmp(char *str1, char *str2)
{
	int length;
	int i;
	int flag = 1;

	if (my_strlen(str1) != my_strlen(str2))
		return (1);

	length = my_strlen(str1);
	for (i = 0; i < length ; i++)
	{
		if (str1[i] != str2[i])
		{
			flag = 0;
			break;
		}

	}
	if (flag)
	{
		return (0);
	}

	return (1);
}

/**
 * my_strcat_ - concat 2 strings
 * @str1: the first string
 * @str2: the second string
 * Return: the concatenated strings
*/

int my_strcat(char *str1, char *str2)
{
	int length1;
	int length2;
	int i;

	length1 = my_strlen(str1);
	length2 = my_strlen(str2);

	for (i = 0; i < length1; i++)
		str1++;

	for (i = 0 ; i < length2; i++)
	{
		*str1 = str2[i];
		str1++;
	}
	*str1 = '\0';
	return (0);

}


/**
 * my_strtok_- seprate the string to array of strings
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
	{
		return (NULL);
	}
	else
	{
	return (start);
	}
}
