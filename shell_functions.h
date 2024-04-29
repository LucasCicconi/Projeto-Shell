//shellfunctions.h
#ifndef SHELL_FUNCTIONS_H
#define SHELL_FUNCTIONS_H

void initialize_paths();

void add_path(char *path);

char *search_executable(char *command);

void execute_command(char *command);

#endif
