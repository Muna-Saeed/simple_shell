#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_PATH_LENGTH 256
#define MAX_INPUT_SIZE 1024

/* Global variables */
extern ssize_t input_index;             // Declaration of input_index as a global variable
extern char input_buffer[MAX_INPUT_SIZE]; // Declaration of input_buffer as a global variable
extern char **environ;

/* Function prototypes */
void moon_print(const char *printf_msg, ...);
void render_prompt(void);
void exec_prompt(const char *user_input);
void read_user_input(char *user_input, size_t size);
ssize_t moon_getline(char **lineptr, size_t *n);
void tokenize_input(const char *user_input, char *arguments[], int *arguments_counter);
void handle_builtin_commands(char *arguments[], int arguments_counter);
void handle_other_commands(char *arguments[]);

#endif /* SHELL_H */

