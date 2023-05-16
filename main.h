#ifndef MAIN_H
#define MAIN_H

	#include<stdio.h>
	#include<stdlib.h>
	#include<unistd.h>
	#include<sys/types.h>
	#include<sys/stat.h>
	#include<sys/wait.h>
	


	void execmd(char **argv);
	char *get_location(char *command);
	int get_env(char **envp);
	void divide_commands(char **words,int length);
	char *my_strcpy(char *, char *);
	char *my_strdup(const char *);
	int my_strlen(const char *);
	int my_strcmp(char *str1, char *str2);
	int my_strcat(char *str1, char *str2);
	char *my_strtok(char *str, const char *delim);
	void my_print(char *str);

#endif /* MAIN_H */

