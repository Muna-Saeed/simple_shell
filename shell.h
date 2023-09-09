#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdbool.h>

#define MAX_PATH_LENGTH 256

void moon_print(const char *printf_msg, ...);
void render_prompt(void);
void exec_prompt(const char *user_input);
void read_user_input(char *user_input, size_t size);

#endif
