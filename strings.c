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