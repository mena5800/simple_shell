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
#define MAX_COMMAND_LENGTH 1024

/**
 * struct info - A struct to represent the cmd
 *
 * @name: name of shell
 * @command: the name of command
 * @line_count: line counter
 * @envp: environmental vars
 */

typedef struct info
{
	char *name;
	char *command;
	int line_count;
	char **envp;

} info;

void my_print(char *str);
void sigint_handler(void);
char *get_location(char *command);
char *my_strtok(char *s, const char *delim);
int get_env(char **envp);
char *int_string(int num);
void print_error(int *status, info cmd);
int execmd(char *path, char *command, char **args, char **envp);
void clear_execmd(char *path, char *command, char **args);
void free_args(size_t *command_len, char *command, char **args);
void handle_exit(int i, char *command, info cmd,
				 size_t *command_len, int exit_code, char **args);
void option(int i, char **args, char **envp, char *command,
			size_t *command_len, info cmd, int exit_code, int *status);
int tokenize(char *command, char **args);

#endif /* MAIN_H */
