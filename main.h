#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>



void execmd(char **argv);
char *get_location(char *command);
int get_env(char **envp);
void divide_commands(char **words,int length);