#include "shell.h"

/**
 * handle_setenv - Handles the setenv command
 * @arguments: The command and its arguments
 *
 * Return: Nothing
 */
void handle_setenv(char **arguments)
{
	/* Check if variable and value are provided */
	if (arguments[1] != NULL && arguments[2] != NULL)
	{
		/* Set the environment variable to the specified value */
		if (setenv(arguments[1], arguments[2], 1) == -1)
		{
			perror("setenv");
		}
		else
		{
			char *var_value = getenv(arguments[1]);

			printf("Variable %s is set to: %s\n", arguments[1], var_value);
		}
	}
	else
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
	}
}

/**
 * handle_unsetenv - Handles the unsetenv command
 * @arguments: The command and its arguments
 *
 * Return: Nothing
 */
void handle_unsetenv(char **arguments)
{
	/* Check if variable is provided */
	if (arguments[1] != NULL)
	{
		/* Unset the environment variable */
		if (unsetenv(arguments[1]) == -1)
		{
			perror("unsetenv");
		}
	}
	else
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	}
}

/**
 * execute_command - Executes a command
 * @arguments: The command and its arguments
 *
 * Return: Nothing
 */
void execute_command(char **arguments)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");

	/* Loop through directories specified by PATH */
	while (dir != NULL)
	{
		char full_path[MAX_PATH_LENGTH];

		snprintf(full_path, sizeof(full_path), "%s/%s", dir, arguments[0]);

		/* Try to execute the command in each directory */
		if (execve(full_path, arguments, NULL) != -1)
		{
			/* Execution succeeded, no need to continue searching */
			free(path_copy);
			return;
		}
		dir = strtok(NULL, ":");
	}

	/* Free the dynamically allocated memory */
	free(path_copy);

	perror("execve");
	exit(EXIT_FAILURE);
}

/**
 * getenv_info - Handles environment variables in a shell
 * @arguments: The command and its arguments
 *
 * Return: true if it successfully handles a "setenv" or "unsetenv" command
 *	or executes a command, false otherwise.
 */
bool getenv_info(char **arguments)
{
	/* Handle setenv command */
	if (strcmp(arguments[0], "setenv") == 0)
	{
		handle_setenv(arguments);
		return (true);
	}
	/* Handle unsetenv command */
	else if (strcmp(arguments[0], "unsetenv") == 0)
	{
		handle_unsetenv(arguments);
		return (true);
	}
	/* Skips processing if the command is a comment */
	else if (arguments[0][0] == '#')
	{
		return (true);
	}
	/**
	 * Checks if the command contains a / character
	 * (indicating the command includes a path, a full path)
	 */
	else if (strchr(arguments[0], '/') != NULL)
	{
		if (execve(arguments[0], arguments, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		return (true);
	}
	/**
	 * The command doesn't contain a / character, so it will search for it
	 * in the directories specified by the PATH variable
	 */
	else
	{
		execute_command(arguments);
		return (true);
	}
	return (false);
}

