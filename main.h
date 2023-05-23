#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

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

} info;

char *get_location(char *command);
int get_env(char **envp);
void divide_commands(char **words, int length, info cmd);
char *my_strcpy(char *, char *);
char *my_strdup(const char *);
int my_strlen(const char *);
int my_strcmp(char *str1, char *str2);
int my_strcat(char *str1, char *str2);
char *my_mod_strtok(char *str, const char *delim);
void my_print(char *str);
int my_atoi(char *str);
int my_getline(char **word);
char *clean_word(char *word);
char *int_string(int num);
void print_error(info cmd, char *error_name);
char **clean_command(char *command, int length, int *argc);
void handle_cd(int argc, char **argv, int *cd_return);
int get_num_lines(char *buffer);
void command_process(int real_arguments, char **argv, char **envp, info cmd);
char *my_strtok(char *s, const char *delim);
int execmd(char **argv, info cmd);
void handle_semi_colon(int i, int *j, int *flag, info cmd, char **mod_words);
int handle_and(int i, int *j, int *flag, char **mod_words, info cmd);

#endif /* MAIN_H */
