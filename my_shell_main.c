#include "shell.h"
/**
 * main - Entry point.
 * Description: This function is where the execution of a C program starts.
 * @return The exit status of the program.
 * A value of 0 indicates successful execution.
 */
/* Define the global variables */
ssize_t input_index = 0;
char input_buffer[MAX_INPUT_SIZE];

int main(void)
{
	char user_input[150];

	while (1)
	{
		render_prompt();
		read_user_input(user_input, sizeof(user_input));
		exec_prompt(user_input);
	}

	return 0;
}

