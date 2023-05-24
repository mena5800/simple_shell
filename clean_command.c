// #include "main.h"

// /**
//  * clean_command - clean the command
//  * @command: string
//  * @length: length of string
//  * @argc: num of arguments
//  */
// char **clean_command(char *command, int length, int *argc)
// {
// 	int num_tokens = 0;
// 	char *command_copy = NULL;
// 	const char *delim = " |&;\n";
// 	char *token;
// 	char **argv;
// 	int num;
// 	char *word;
	
// 	/* allocate space for a copy of the lineptr */
// 	command_copy = malloc(strlen(command));
// 	if (command_copy == NULL)
// 	{
// 		perror("tsh: memory allocation error");
// 		exit(0);
// 	}
// 	/* copy lineptr to lineptr_copy */
// 	my_strcpy(command_copy, command);
// 	/* calculate the total number of tokens */
// 	token = strtok(command, delim);
// 	while (token != NULL)
// 	{
// 		num_tokens++;
// 		token = strtok(NULL, delim);
// 	}
// 	num_tokens++;
// 	argv = malloc(500);
// 	token = strtok(command_copy, delim);
// 	num = 0;
// 	while (token != NULL)
// 	{
// 		word = clean_word(token);
// 		if (my_strlen(word) != 0)
// 		{
// 			argv[num] = malloc(500);
// 			my_strcpy(argv[num], word);
// 			num++;
// 			free(word);
// 		}

// 		token = strtok(NULL, delim);
// 	}
// 	argv[num] = NULL;
// 	*argc = num;
// 	free(command_copy);
// 	return (argv);
// }