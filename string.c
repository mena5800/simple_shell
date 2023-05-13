#include "main.h"

/**
 * my_strlen - returns the lenght of the string
 * @s: the string
 *
 * Return: length of the given string
 */
int my_strlen(const char *s)
{
    int len = 0;

    if (s == NULL) {
        return len;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        len++;
    }

    return len;
}
/**
 * my_strcpy - copies string
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
 * my_strdup - duplicate a given string
 * @str: given string
 *
 * Return: pointer to the duplicated string
 */
char *my_strdup(const char *str)
{
    if (str == NULL)
        return NULL;

    size_t len = my_strlen(str);
    char *dup = malloc(len + 1);

    if (dup == NULL)
        return NULL;

    for (size_t i = 0; i <= len; i++)
        dup[i] = str[i];

    return dup;
}
