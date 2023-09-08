#include "shell.h"
/**
 * exec_prompt - Entry point.
 * @user_input: type const char pointer.
 * Description: this function executes the prompts.
 */
void exec_prompt(const char *user_input)
{
	pid_t pid_of_child = fork();

	if (pid_of_child == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid_of_child == 0)
	{
		/**
		 * execute child process
		 * parses the user input and its arguments
		 */
		char *arguments[150];
		int arguments_counter = 0;

		/*tokenize whatever user enters*/
		char *tokenize = strtok((char *)user_input, " ");

		while (tokenize != NULL)
		{
			arguments[arguments_counter++] = tokenize;
			tokenize = strtok(NULL, " ");
		}
		arguments[arguments_counter] = NULL;
		{
			execvp(arguments[0], arguments);

		}
	}
	else
	{
		wait(NULL);
	}
}
