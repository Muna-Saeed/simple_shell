#include "shell.h"

void moon_print(const char *printf_msg) {
	write(STDOUT_FILENO, printf_msg, stlen(printf_msg));
}

