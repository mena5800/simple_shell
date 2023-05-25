#include "main.h"

info cmd;

void executeCommand(char *args[], char **envp) {
    pid_t pid;
    int status;
    char *path;
    
    if (args[0] != NULL) {
        path = get_location(args[0]);
        if (path == NULL) {
            printf("%s: command not found\n", args[0]);
        } else {
            pid = fork();

            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                /* Child process */
                int ret = execve(path, args, envp);
                if (ret == -1) {
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            } else {
                /* Parent process */
                waitpid(pid, &status, 0);
            }

            /* Free memory allocated for path */
            free(path);
        }
    }
}

void processInteractiveMode() {
    char *prompt = "$ ";
    char *args[1024];
    char *lineptr = NULL;
    char *newline;
    int num_args;
    char *token;

    while (1) {
        lineptr = malloc(1024);
        my_print(prompt);
        my_getline(lineptr);
        cmd.line_count += 1;

        newline = strchr(lineptr, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        token = my_strtok(lineptr, " ");
        num_args = 0;

        while (token != NULL) {
            if (token[0] == '#') {
                token = NULL;
                break;
            }

            args[num_args++] = token;
            token = my_strtok(NULL, " ");
        }
        args[num_args] = NULL;

        executeCommand(args, cmd.envp);

        free(lineptr);
    }
}

void processNonInteractiveMode() {
    char *args[1024];
    char *lineptr = NULL;
    char *newline;
    int num_args;
    char *token;

    lineptr = malloc(1024);
    my_getline(lineptr);
    cmd.line_count += 1;

    newline = strchr(lineptr, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    token = my_strtok(lineptr, " ");
    num_args = 0;

    while (token != NULL) {
        if (token[0] == '#') {
            token = NULL;
            break;
        }

        args[num_args++] = token;
        token = my_strtok(NULL, " ");
    }
    args[num_args] = NULL;

    executeCommand(args, cmd.envp);

    free(lineptr);
}

int main(int ac, char **argv, char **envp) {
    cmd.name = argv[0];
    cmd.command = argv[1];
    cmd.line_count = 0;
    cmd.envp = envp;

    if (isatty(STDIN_FILENO)) {
        processInteractiveMode();
    } else {
        processNonInteractiveMode();
    }

    return 0;
}
