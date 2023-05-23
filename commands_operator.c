#include "main.h"

void handle_semi_colon(int i, int *j, int *flag, info cmd, char **mod_words);
int handle_and(int i, int *j, int *flag, char **mod_words, info cmd);
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
	int flag = 0;

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
			handle_semi_colon(i, &j, &flag, cmd, mod_words);
			mod_words = malloc(sizeof(words));
			continue;
		}
		else if (my_strcmp(words[i], "&&") == 0)
		{
			if (handle_and(i, &j, &flag, mod_words, cmd))
				return;
			mod_words = malloc(sizeof(words));
			continue;
		}
		else if (my_strcmp(words[i], "||") == 0)
		{
			mod_words[i] = NULL;
			if (execmd(mod_words, cmd) != 0)
			{
				free(mod_words);
				mod_words = malloc(sizeof(words));
				flag = 1;
				j = 0;
				continue;
			}
			else
			{
				return;
			}
		}
		else
		{
			mod_words[j] = malloc(my_strlen(words[i]));
			my_strcpy(mod_words[j], words[i]);
			j++;
		}
	}
	if (flag)
		mod_words[j] = NULL;
	else
		mod_words[i] = NULL;

	execmd(mod_words, cmd);
}

