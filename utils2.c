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

/**
 * clean_command - clean the command
 * @command: string
 * @length: length of string
 * @argc: num of arguments
 */
char **clean_command(char *command, int length, int *argc)
{
	int num_tokens = 0;
	char *command_copy = NULL;
	const char *delim = " |&;\n";
	char *token;
	char **argv;
	int num;
	/* allocate space for a copy of the lineptr */
	command_copy = malloc(sizeof(char) * length);
	if (command_copy == NULL)
	{
		perror("tsh: memory allocation error");
		exit(0);
	}
	/* copy lineptr to lineptr_copy */
	my_strcpy(command_copy, command);
	/* calculate the total number of tokens */
	token = my_mod_strtok(command, delim);
	while (token != NULL)
	{
		num_tokens++;
		token = my_mod_strtok(NULL, delim);
	}
	num_tokens++;
	argv = malloc(sizeof(char *) * num_tokens);
	token = my_mod_strtok(command_copy, delim);
	num = 0;
	while (token != NULL)
	{
		if (my_strlen(clean_word(token)) != 0)
		{
			argv[num] = malloc(sizeof(char) * my_strlen(token));
			my_strcpy(argv[num], clean_word(token));
			num++;
		}

		token = my_mod_strtok(NULL, delim);
	}
	argv[num] = NULL;
	*argc = num;
	return (argv);
}

/**
 * handle_cd - function to handle the cd
 * @argc: length of arguments
 * @argv: array of string
 * @cd_retrun: the return value of chdir
 * Return: void
 */
void handle_cd(int argc, char **argv, int *cd_return)
{
	static char cwd[1024];
	static char last_cwd[1024];

	if (argc == 1)
	{
		getcwd(last_cwd, sizeof(last_cwd));
		*cd_return = chdir(getenv("HOME"));
		getcwd(cwd, sizeof(cwd));
	}
	else if (my_strcmp(argv[1], "-") == 0)
	{
		*cd_return = chdir(last_cwd);
		my_strcpy(last_cwd, cwd);
		getcwd(cwd, sizeof(cwd));
	}
	else
	{
		getcwd(last_cwd, sizeof(last_cwd));
		*cd_return = chdir(argv[1]);
		getcwd(cwd, sizeof(cwd));
	}
	if (*cd_return != 0)
	{
		perror("Error: ");
	}
}

/**
 * command_process - choose which command should do
 * @real_arguments: the num of arguments after clean
 * @argv: array of string contain command
 * @envp: contian env variables
 * @cmd: struct object contain some information about shell
 * Return: void
 */
void command_process(int real_arguments, char **argv, char **envp, info cmd)
{
	int exit_code;
	int cd_return;

	if (my_strcmp(argv[0], "env") == 0 && real_arguments == 1)
	{
		get_env(envp);
	}
	else if (my_strcmp(argv[0], "exit") == 0)
	{
		if (real_arguments == 1)
			exit(0);
		else
		{
			exit_code = my_atoi(argv[1]);
			exit(exit_code);
		}
	}
	else if (my_strcmp(argv[0], "cd") == 0)
	{
		handle_cd(real_arguments, argv, &cd_return);
	}
	else
	{
		divide_commands(argv, real_arguments, cmd);
	}
}

/**
 * get_num_lines - get the number of lines
 * @buffer: string
 * Return: number of lines in string
 */
int get_num_lines(char *buffer)
{
	int counter = 1;
	int i = 0;

	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			counter++;
		}
		i++;
	}
	return (counter);
}

void sigint_handler() {
	char *prompt = "$ ";
    my_print("\n");
	my_print(prompt);
}