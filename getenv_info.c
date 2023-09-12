#include "shell.h"

/**
 * getenv_info - Execute a command by searching for it in the PATH variable.
 * @arguments: An array containing the command and its arguments.
 *
 * Description: This function executes a command specified in @arguments[0] by
 * checking if it contains a '/' character (indicating a full path) or
 *	searching for it in directories specified by the PATH variable.
 * Return: true Command execution was successful.
 *	- false: Command execution failed.
 */
bool getenv_info(char **arguments)
{
	if (strchr(arguments[0], '/') != NULL)
	{
		if (execve(arguments[0], arguments, NULL) == -1)
		{
			return (false);
		}
	}
	else
	{
		char *path = getenv("PATH");
		char *path_copy = strdup(path);
		char *dir = strtok(path_copy, ":");

		while (dir != NULL)
		{
			char full_path[MAX_PATH_LENGTH];

			snprintf(full_path, sizeof(full_path), "%s/%s", dir, arguments[0]);

			if (execve(full_path, arguments, NULL) != -1)
			{
				break;
			}

			dir = strtok(NULL, ":");
		}

		free(path_copy);

		return (false);
	}

	return (true);
}
