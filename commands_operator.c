#include "main.h"

/**
 * divide_commands - divide string into commands
 * @words: string
 * @length: length of string
 * Return: void
 */

void divide_commands(char **words, int length)
{
	char **mod_words;
	int j = 0;
	int i;

	mod_words = malloc(sizeof(words) * length);
	for (i = 0; i < length; i++)
	{
		if (my_strcmp(words[i], ";") == 0)
		{
			execmd(mod_words);
			free(mod_words);
			mod_words = malloc(sizeof(words));
			j = 0;
			continue;
		}
		else
		{
			mod_words[j] = malloc(my_strlen(words[i]));
			my_strcpy(mod_words[j], words[i]);
			j++;
		}
	}

	execmd(mod_words);
}
