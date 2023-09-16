#include "shell.h"

#define MAX_ARGUMENTS 100

/**
 * exec_exit - Execute exit command.
 * @user_input: The user-provided input string.
 *
 * Description: This function handles the "exit" command. It exits the shell
 * with a status code provided by the user.
 *
 * Return: None (void)
 */
void exec_exit(const char *user_input)
{
	const char *argument = user_input + 5;
	int exit_status = atoi(argument);

	exit(exit_status);
}

/**
 * exec_env - Execute env command.
 *
 * Description: This function handles the "env" command. It prints all the
 * environment variables.
 *
 * Return: None (void)
 */
void exec_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		moon_print(*env);
		moon_print("\n");
		env++;
	}
}

/**
 * exec_cd - Execute cd command.
 * @user_input: The user-provided input string.
 *
 * Description: This function handles the "cd" command. It changes the current
 * directory to the one specified by the user, or to the home directory if no
 * directory is specified.
 *
 * Return: None (void)
 */
void exec_cd(const char *user_input)
{
	const char *argument = user_input + 3;
	char current_dir[MAX_PATH_LENGTH];

	if (strlen(argument) == 0)
	{
		const char *home_dir = getenv("HOME");

		if (home_dir == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return;
		}
		if (chdir(home_dir) == -1)
		{
			perror("chdir");
			return;
		}
	}
	else
	{
		if (chdir(argument) == -1)
		{
			perror("chdir");
			return;
		}
	}

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("getcwd");
		return;
	}
	if (setenv("PWD", current_dir, 1) == -1)
	{
		perror("setenv");
		return;
	}
}
/*void exec_cd(const char *user_input)
  {
  const char *path = user_input + 3;

  if (chdir(path) != 0) 
  {
  perror("cd failed");
  }
  }*/
/**
 * exec_alias - Execute alias command.
 * @user_input: The user-provided input string.
 *
 * Description: This function handles the "alias" command. It defines aliases
 * for commands.
 *
 * Return: None (void)
 */
void exec_alias(const char *user_input)
{
	const char *argument = user_input + 6;
	char *aliases[MAX_ARGUMENTS];
	int num_aliases = 0;
	Alias *alias_list[100];
	char *token = strtok((char *)argument, " ");

	while (token != NULL)
	{
		aliases[num_aliases++] = token;
		token = strtok(NULL, " ");
	}
	define_aliases(alias_list, aliases, num_aliases);
}

/**
 * exec_builtin - Execute built-in commands.
 * @user_input: The user-provided input string.
 *
 * Description: This function handles built-in commands. It checks if the user
 * input matches any of the builtin comands and calls the appropriate function.
 *
 * Return: None (void)
 */
void exec_builtin(const char *user_input)
{
	if (strcmp(user_input, "exit") == 0)
		exec_exit(user_input);

	else if (strcmp(user_input, "env") == 0)
		exec_env();

	else if (strncmp(user_input, "cd", 2) == 0)
		exec_cd(user_input);

	else if (strncmp(user_input, "alias", 5) == 0)
		exec_alias(user_input);
}
/*void exec_builtin(const char *user_input)
  {
  if (strncmp(user_input, "exit", 4) == 0)
  {
  exec_exit(user_input);
  return;
  }

  else if (strncmp(user_input, "env", 3) == 0)
  {
  exec_env();
  return;
  }

  else if (strncmp(user_input, "cd", 2) == 0)
  exec_cd(user_input);

  else if (strncmp(user_input, "alias", 5) == 0)
  exec_alias(user_input);
  }
 */
