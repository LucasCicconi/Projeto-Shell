//shellfunctions.h
#ifndef SHELL_FUNCTIONS_H
#define SHELL_FUNCTIONS_H

#include <stdio.h>

void initialize_paths();

void add_path(char *path);

char *search_executable(char *command);

void execute_command(char *command, FILE*);

#endif
