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
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(user_input, "env") == 0)
	{
		char **env = environ;

		while (*env != NULL)
		{
			moon_print(*env);
			env++;
		}

		return;
	}
}

