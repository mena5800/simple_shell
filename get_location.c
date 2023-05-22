#include "main.h"

/**
 * get_location - get the location of exe file should excute
 * @command: the name of command
 * Return - the location of command
*/

char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = getenv("PATH");
	if (path)
	{
		path_copy = my_strdup(path);
		command_length = my_strlen(command);
		path_token = my_strtok(path_copy, ":");
		while (path_token != NULL)
		{
			directory_length = my_strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			my_strcpy(file_path, path_token);
			my_strcat(file_path, "/");
			my_strcat(file_path, command);
			my_strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = my_strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	return (NULL);
}
