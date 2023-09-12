#include "shell.h"

/**
 * exec_builtin - Execute built-in commands.
 * @user_input: The user-provided input string.
 *
 * Description: This function handles built-in commands.
 * If the command is "exit," it exits the shell with a success status code.
 * Return: None (void)
 */
void exec_builtin(const char *user_input)
{
	if (strcmp(user_input, "exit") == 0)
	{
		const char *argument = user_input + 5;
		int exit_status = atoi(argument);
		/* Exit the shell with the specified status code */
		exit(exit_status);
	}
	else if (strcmp(user_input, "env") == 0)
	{
		/* Handle the "env" command here */
		char **env = environ;

		while (*env != NULL)
		{
			moon_print(*env);
			env++;
		}
		/* exit(EXIT_SUCCESS); */
		return;
	}
}
