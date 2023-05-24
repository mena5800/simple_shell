#include "main.h"

info cmd;

int main(int ac, char **argv, char **envp)
{

    char *prompt = "$ ";
    char *args[1024];
    pid_t pid;
    int status;
    char *path;
    char *newline;
    int num_args;
    char *token;
    char *lineptr = NULL;


    cmd.name = argv[0];
    cmd.command = argv[1];
    cmd.line_count = 0;
    cmd.envp = envp;

    (void)ac;
    if (isatty(STDIN_FILENO))
    {
        /*runing in interactive mode*/
        while (1)
        {
            lineptr = malloc(1024);
            my_print(prompt);
            my_getline(lineptr);
            /* command excute */ 
            cmd.line_count += 1;

            newline = strchr(lineptr, '\n');
            if (newline != NULL)
            {
                *newline = '\0';
            }
            /* Parse command into arguments */
            token = my_strtok(lineptr, " ");
            num_args = 0;

            while (token != NULL)
            {
                /* Ignore comments */
                if (token[0] == '#')
                {
                    token = NULL;
                    break;
                }

                /* Store argument and update counter*/
                args[num_args++] = token;

                /* Get next token */
                token = my_strtok(NULL, " ");
            }
            args[num_args] = NULL;

            /* Execute command*/
            if (num_args > 0)
            {
                /* Get path to executable file*/
                path = get_location(args[0]);
                if (path == NULL)
                {
                    printf("%s: command not found\n", args[0]);
                }
                else
                {
                    pid = fork();

                    if (pid == -1)
                    {
                        perror("fork");
                        exit(EXIT_FAILURE);
                    }
                    else if (pid == 0)
                    {
                        /* Child process*/
                        int ret = execve(path, args, envp);
                        if (ret == -1)
                        {
                            perror("execve");
                            exit(EXIT_FAILURE);
                        }
                    }
                    else
                    {
                        /* Parent process */
                        waitpid(pid, &status, 0);
                    }

                    /* Free memory allocated for path */
                }
            }
            free(path);
            free(lineptr);
        }
    }
    else
    {
        /*runing in non-interactive mode*/
        lineptr = malloc(1024);
        my_getline(lineptr);
        /* command excute*/
        cmd.line_count += 1;

        newline = strchr(lineptr, '\n');
        if (newline != NULL)
        {
            *newline = '\0';
        }
        /* Parse command into arguments */
        token = my_strtok(lineptr, " ");
        num_args = 0;

        while (token != NULL)
        {
            /* Ignore comments */
            if (token[0] == '#')
            {
                token = NULL;
                break;
            }

            /*Store argument and update counter*/
            args[num_args++] = token;

            /* Get next token */
            token = my_strtok(NULL, " ");
        }
        args[num_args] = NULL;

        /* Execute command*/
        if (num_args > 0)
        {
            /* Get path to executable file*/
            path = get_location(args[0]);
            if (path == NULL)
            {
                printf("%s: command not found\n", args[0]);
            }
            else
            {
                pid = fork();

                if (pid == -1)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                else if (pid == 0)
                {
                    /* Child process*/
                    int ret = execve(path, args, envp);
                    if (ret == -1)
                    {
                        perror("execve");
                        exit(EXIT_FAILURE);
                    }
                }
                else
                {
                    /* Parent process*/
                    waitpid(pid, &status, 0);
                }

            }
        }
        /* Free memory allocated for path*/
        free(path);
        return (0);
    }
}