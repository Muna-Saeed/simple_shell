#include "shell.h"
/**
 * main - Entry point.
 * Description: this function is where the execution of a C program starts.
 * @return The exit status of the program.
 * A value of 0 indicates successful execution.
*/
int main(void)
{
	char user_input[150];

	while (true)
	{
		render_prompt();
		read_user_input(user_input, sizeof(user_input));
		exec_prompt(user_input);
		
		}
	return (0);
}
