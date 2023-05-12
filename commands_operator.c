#include "main.h"


void divide_commands(char **words,int length)
{
    char **mod_words;
    int j = 0;
    int i;

    mod_words = malloc(sizeof(words)*length);
    for (i =0 ; i< length;i++)
    {
        if (strcmp(words[i],";")==0)
        {
            execmd(mod_words);
            free(mod_words);
            mod_words = malloc(sizeof(words));
            j = 0;
            continue;
        }
        else
        {
            mod_words[j] = malloc(strlen(words[i]));
            strcpy(mod_words[j],words[i]);
            j++;
        }

    }
    
    execmd(mod_words);


}