#include "shell.h"
#define MAX_ARGUMENTS 10
/**
 * exec_prompt - Entry point.
 * @user_input: type const char pointer.
 * Description: this function executes the prompts.
 */

void exec_prompt(const char *user_input)
{

	/* create a child process */
	pid_t pid_of_child = fork();

	if (pid_of_child == -1)
	{

		perror("Error: Failed to fork");
		exit(EXIT_FAILURE);
	}
	else if (pid_of_child == 0)
	{
		char *arguments[MAX_ARGUMENTS];

		tokenize_input(user_input, arguments, MAX_ARGUMENTS);
		exec_builtin(arguments[0]);

		if (!getenv_info(arguments))
		{
			fprintf(stderr, "Error: Executable '%s' not found\n", arguments[0]);
			free_arguments(arguments);
			exit(EXIT_FAILURE);

		}

		/* Free the dynamically allocated memory */
		free_arguments(arguments);
		/* Exit the child process */
		exit(EXIT_SUCCESS);

	}
	else
	{
		/* parent  process */
		wait(NULL);
	}
}
