#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<stdbool.h>
#include<stdlib.h>
#include <sys/wait.h>

void moon_print(const char *printf_msg);
void render_prompt(void);
void exec_prompt(const char *user_input);
void read_user_input(char *user_input, size_t size);

#endif
