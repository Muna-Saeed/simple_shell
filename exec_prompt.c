#include "shell.h"

/**
 * tokenize_input - Entry point.
 * Description: This fucntion Tokenizes the user input.
 * @user_input: The user input.
 * @arguments: The arguments array.
 * @ar_counter: The arguments counter.
 */
void tokenize_input(const char *user_input, char *arguments[], int *ar_counter)
{
	char *tokenize = strtok((char *)user_input, " ");

	while (tokenize != NULL)
	{
		arguments[(*ar_counter)++] = tokenize;
		tokenize = strtok(NULL, " ");
	}
	arguments[*ar_counter] = NULL;
}
/**
 * handle_builtin_commands - Handles built-in commands.
 * @arguments: The arguments array.
 * @arguments_counter: The arguments counter.
 */
void handle_builtin_commands(char *arguments[], int arguments_counter)
{
	/* Trim all whitespace characters from the first argument */
	char *trimmed_input = strtok(arguments[0], " \t\r\n\v\f");

	if (arguments_counter == 1 && strcmp(trimmed_input, "exit") == 0)
		exit(EXIT_SUCCESS);
	else if (strcmp(arguments[0], "env") == 0)
	{
		char **env = environ;

		while (*env != NULL)
		{
			moon_print(*env);
			env++;
		}
		exit(EXIT_SUCCESS);
	}
}
/**
 * handle_other_commands - Entry point.
 * Description: This function Handles other commands.
 * @arguments: The arguments array.
 */
void handle_other_commands(char *arguments[])
{
	if (strchr(arguments[0], '/') != NULL)
	{
		if (execvp(arguments[0], arguments) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		char *path = getenv("PATH");
		char *path_copy = strdup(path);
		char *dir = strtok(path_copy, ":");
		char full_path[MAX_PATH_LENGTH];

		while (dir != NULL)
		{
			snprintf(full_path, sizeof(full_path), "%s/%s", dir, arguments[0]);

			if (execvp(full_path, arguments) != -1)
				break;

			dir = strtok(NULL, ":");
		}

		free(path_copy);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

/**
 * exec_prompt - Entry point.
 * Description: This function Executes the prompt.
 * @user_input: The user input.
 */
void exec_prompt(const char *user_input)
{
	pid_t pid_of_child;
	char *arguments[150];
	int arguments_counter = 0;

	pid_of_child = fork();
	if (pid_of_child == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid_of_child == 0)
	{
		tokenize_input(user_input, arguments, &arguments_counter);
		handle_builtin_commands(arguments, arguments_counter);
		handle_other_commands(arguments);
	}
	else
	{
		wait(NULL);
	}
}
