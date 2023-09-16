#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>

#define MAX_PATH_LENGTH 256
#define MAX_INPUT_SIZE 1024

/* Global variables */
extern ssize_t input_index; /* Declaration of input_index as a global variable */
extern ssize_t input_buffer_index; /* Declaration of input_buffer_index as a global variable */
extern char input_buffer[MAX_INPUT_SIZE]; /* Declaration of input_buffer as a global variable */
extern char **environ;
extern struct Alias *alias_list;

/* Alias structure */
typedef struct Alias {
	char name[100];
	char value[100];
	struct Alias* next;
} Alias;


/* Function prototypes for moon_print.c */
void moon_print(const char *printf_msg, ...);

/* Function prototypes for render_prompt.c */
void render_prompt(void);

/* Function prototypes for exec_prompt.c */
void exec_prompt(const char *user_input);

/* Function prototypes for read_user_input.c */
void read_user_input(char *user_input, size_t size);

/* Function prototypes for moon_getline.c */
ssize_t moon_getline(char **lineptr, size_t *n);

/* Function prototypes for input_tokinez.c and moon_tokinez.c */
void tokenize_input(const char *user_input, char **arguments,
		int max_argument);
void tokenize_user_input(const char *user_input, char *commands[], int *num_cd);

/* Function prototypes for moon_builtins.c */
void exec_builtin(const char *user_input);
void exec_exit(const char *user_input);
void exec_env(void);
void exec_cd(const char *user_input);
void exec_alias(const char *user_input);

/* Function prototypes for getenv_info.c */
void handle_setenv(char **arguments);
void handle_unsetenv(char **arguments);
void execute_command(char **arguments);
bool getenv_info(char **arguments);
/* Function prototypes for handle_other_commands.c and free_arguments.c */
void handle_other_commands(char **arguments[]);
void free_arguments(char **arguments);

/* Function prototypes for execute_command.c and fork_child_processes.c */
void fork_child_processes(char *commands[], int num_commands);
void execute_command_2(char *command);
/* Function prototypes for alias_builtin.c */
void print_all_aliases(Alias *alias_list);
void print_specific_aliases(Alias *alias_list, char* names[], int num_names);
void define_aliases(Alias **alias_list, char *args[], int num_args);
void free_alias_list(Alias **alias_list);

#endif /* SHELL_H_ */

