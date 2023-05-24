#include "main.h"

/**
 * my_my_strcpy - copies string
 * @dest: destination
 * @src: source
 *
 * Return: a pointer to the destination where the string is copied
 */
char *my_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}


/**
 * strtok_- seprate the string to array of strings
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