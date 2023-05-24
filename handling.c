#include "main.h"

/**
 * handle_semi_colon - handle semi colon
 * @i: the index of mod_words
 * @j: the first flag
 * @flag: second flag
 * @cmd: shell informations
 * @mod_words: aray of strings contain command
 * Return: void
*/
void handle_semi_colon(int i, int *j, int *flag, info cmd, char **mod_words)
{
	mod_words[i] = NULL;
	execmd(mod_words, cmd);
	free(mod_words);
	*flag = 1;
	*j = 0;
}


/**
 * handle_and - handle &&
 * @i: the index of mod_words
 * @j: the first flag
 * @flag: second flag
 * @cmd: shell informations
 * @mod_words: aray of strings contain command
 * Return: 1 or 0
*/

int handle_and(int i, int *j, int *flag, char **mod_words, info cmd)
{
	mod_words[i] = NULL;
	if (execmd(mod_words, cmd) != 0)
	{
		return (1);
	}
	else
	{
		free(mod_words);
		*flag = 1;
		*j = 0;
		return (0);
	}
}
