#ifndef MAIN_H
#define MAIN_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#define BUFFER_SIZE 1024

/**
 * struct info - A struct to represent the cmd
 *
 * @name: name of shell
 * @command: the name of command
 * @line_cound: line counter
 */

typedef struct info
{
	char *name;
	char *command;
	int line_count;
	char **envp;

} info;


int my_getline(char *word);
void my_print(char *str);
void sigint_handler();
char *my_strcpy(char *, char *);
char *get_location(char *command);
char *my_strtok(char *s, const char *delim);
int get_env(char **envp);
int my_strcmp(char *str1, char *str2);
int my_strlen(const char *s);



#endif /* MAIN_H */
