#include "main.h"

/**
 * divide_commands - divide string into commands
 * @words: string
 * @length: length of string
 * Return: void
 */

void divide_commands(char **words, int length, info cmd)
{
	char **mod_words;
	int j = 0;
	int i;
	int m = 1;

	mod_words = malloc(sizeof(words) * length);
	for (i = 0; i < length; i++)
	{
		/* handle spaces in commands */
		if (my_strlen(words[i]) == 0)
		{
			continue;
		}
		/* handle comments */
		if (words[i][0] == '#')
		{
			break;
		}
		if (my_strcmp(words[i], ";") == 0)
		{
			execmd(mod_words,cmd);
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
	
	execmd(mod_words,cmd);
}



