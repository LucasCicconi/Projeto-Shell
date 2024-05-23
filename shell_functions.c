//shell_functions.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shell_functions.h"
#include "error_handling.h"

#define MAX_PATHS 10
#define MAX_COMMAND_LENGTH 1024

char *search_paths[MAX_PATHS];
int num_paths = 0;
char shell_directory[MAX_COMMAND_LENGTH]; // Variável para armazenar o diretório do shell

void initialize_paths() {
    search_paths[0] = "custom_lib";
    search_paths[1] = "/bin";
    search_paths[2] = "/usr/bin";
    num_paths = 3;

    if (getcwd(shell_directory, sizeof(shell_directory)) == NULL) {
        print_error(PATH_FAILED);
        exit(EXIT_FAILURE);
    }
}

void add_path(char *path) {
    if (num_paths < MAX_PATHS) {
        search_paths[num_paths++] = path;
    } else {
        print_error(MAX_PATHS_LIMIT);
    }
}

char *search_executable(char *command) {
    for (int i = 0; i < num_paths; i++) {
        char *full_path = malloc(strlen(search_paths[i]) + strlen(command) + 2);
        if (!full_path) {
            print_error(MALLOC_FAILED);
            exit(EXIT_FAILURE);
        }
        sprintf(full_path, "%s/%s", search_paths[i], command);
        if (access(full_path, X_OK) == 0) {
            return full_path;
        }
        free(full_path);
    }
    return NULL;
}

void execute_single_command(char *command) {
    char *args[64];
    int arg_count = 0;
    pid_t pid;

    char *output_file = NULL;
    char *redirection = strchr(command, '>');
    if (redirection != NULL) {
        *redirection = '\0';
        redirection++;
        while (*redirection == ' ') redirection++; // Pula os espaços iniciais
        output_file = redirection;
    }

    char *token = strtok(command, " ");
    while (token != NULL && arg_count < 64) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;

    if (strcmp(args[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    } else if (strcmp(args[0], "cd") == 0) {
        if (arg_count > 1) {
            if (chdir(args[1]) != 0) {
                print_error(CD_FAILED);
            } else {
                if (getcwd(shell_directory, sizeof(shell_directory)) == NULL) {
                    print_error(PATH_FAILED);
                    exit(EXIT_FAILURE);
                }
            }
        } else {
            printf("Uso: cd <caminho>\n");
        }
        return;
    } else if (strcmp(args[0], "path") == 0) {
        num_paths = 0;
        for (int i = 1; i < arg_count; i++) {
            add_path(args[i]);
        }
        printf("Caminhos armazenados:\n");
        for (int i = 0; i < num_paths; i++) {
            printf("%s\n", search_paths[i]);
        }
        return;
    }

    char *executable_path = search_executable(args[0]);
    if (executable_path != NULL) {
        pid = fork();
        if (pid < 0) {
            print_error(FORK_FAILED);
            return;
        } else if (pid == 0) {
            if (output_file) {
                int fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                if (fd < 0) {
                    print_error(OPEN_FAILED);
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            execv(executable_path, args);
            print_error(EXEC_FAILED);
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
        free(executable_path); // Liberar a memória alocada para o caminho do executável
    } else {
        print_error(INVALID_COMMAND);
    }
}


void execute_command(char *command) {
    char *single_command;
    char *rest = command;
    pid_t pid;

    while ((single_command = strsep(&rest, "&")) != NULL) {
        while (*single_command == ' ') single_command++; // Pula os espaços iniciais

        if (strcmp(single_command, "exit") == 0) {
            exit(EXIT_SUCCESS);
        } else if (strncmp(single_command, "cd ", 3) == 0) {
            char *path = single_command + 3; // Pega o caminho após "cd "
            if (chdir(path) != 0) {
                print_error(CD_FAILED);
            } else {
                if (getcwd(shell_directory, sizeof(shell_directory)) == NULL) {
                    print_error(PATH_FAILED);
                    exit(EXIT_FAILURE);
                }
            }
        } else {
            pid = fork();
            if (pid < 0) {
                print_error(FORK_FAILED);
                return;
            } else if (pid == 0) {
                execute_single_command(single_command);
                exit(EXIT_SUCCESS);
            }
        }
    }

    while (wait(NULL) > 0);
}

