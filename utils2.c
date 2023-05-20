#include "main.h"

/**
 * clean_word - remove spaces in word
 * @word: the word you need to remove space from it
 * Return: clean word
*/
char *clean_word(char *word)
{
	int i;
	int index = 0;
	char *new_word = malloc(my_strlen(word) + 2);

	for (i = 0; i < my_strlen(word); i++)
	{
		if (word[i] != ' ')
		{
			new_word[index] = word[i];
			index += 1;
		}
	}
	new_word[index] = '\0';
	return (new_word);
}
