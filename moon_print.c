#include "shell.h"
/**
 * moon_print - Entry point.
 * @printf_msg: type const char pointer.
 * Description: this function prints the outputs.
*/
void moon_print(const char *printf_msg)
{
	write(STDOUT_FILENO, printf_msg, strlen(printf_msg));
}

