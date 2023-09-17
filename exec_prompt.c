#include "shell.h"

#define MAX_ARGUMENTS 10
#define MAX_COMMANDS 10

/**
 * execute_command_2 - Executes a command
 * @command: The command to execute
 *
 * Description: This function Excutes a command.
 */
void execute_command_2(char *command)
{
	char *arguments[MAX_ARGUMENTS];
	int operator_length, is_logical_operator, exit_status;
	int should_execute_next_command;

	tokenize_input(command, arguments, MAX_ARGUMENTS);
	operator_length = strlen(arguments[0]);
	is_logical_operator = (arguments[0][operator_length - 2] == '&' &&
			arguments[0][operator_length - 1] == '&') ||
		(arguments[0][operator_length - 2] == '|' &&
		 arguments[0][operator_length - 1] == '|');

	if (is_logical_operator)
	{
		arguments[0][operator_length - 2] = '\0';
		exit_status = system(arguments[0]);
		should_execute_next_command =
			(arguments[0][operator_length - 1] == '&' && exit_status == 0) ||
			(arguments[0][operator_length - 1] == '|' && exit_status != 0);

		free_arguments(arguments);
		if (!should_execute_next_command)
		{
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		exec_builtin(arguments[0]);
		if (!getenv_info(arguments))
		{
			fprintf(stderr, "Error: Executable '%s' not found\n", arguments[0]);
			free_arguments(arguments);
			exit(EXIT_FAILURE);
		}
		free_arguments(arguments);
		exit(EXIT_SUCCESS);
	}
}

/**
 * tokenize_user_input - Tokenizes user input into commands
 * @user_input: The user input
 * @commands: Array to store the commands
 * @num_cd: Pointer to store the number of commands
 *
 * Description: This function takes user input and tokenizes it into commands
 * based on the semicolon delimiter.
 */
void tokenize_user_input(const char *user_input, char *commands[], int *num_cd)
{
	char *token = strtok((char *)user_input, ";");

	/* Split the user input into commands based on the semicolon delimiter */
	while (token != NULL)
	{
		commands[(*num_cd)++] = token;
		token = strtok(NULL, ";");
	}
}


/**
 * replace_variables - Replaces variables in a command
 * @command: The command to replace variables in
 * @exit_status: The exit status of the previous command
 *
 * Description: This function replaces variables in a command with their value.
 * It handles variables like $? and $$.
 */
void replace_variables(char *command, int exit_status)
{
	char *variable = NULL;
	char pid_str[20];

	snprintf(pid_str, sizeof(pid_str), "%d", getpid());

	variable = strstr(command, "$?");
	if (variable != NULL)
	{
		/* Replace "$?" with the exit status */
		snprintf(variable, 3, "%d", exit_status);
	}

	variable = strstr(command, "$$");
	if (variable != NULL)
	{
		/* Replace "$$" with the process ID */
		snprintf(variable, 20, "%s", pid_str);
	}
}


/**
 * fork_child_processes - Forks a child process for each command
 * @commands: The commands to execute
 * @num_commands: The number of commands
 *
 * Description: This function forks a child process
 *	for each command and executes it.
 */
void fork_child_processes(char *commands[], int num_commands)
{
	int i;
	int exit_status = 0;
	/* Fork a child process for each command */
	for (i = 0; i < num_commands; i++)
	{
		pid_t pid_of_child = fork();

		if (pid_of_child == -1)
		{
			perror("Error: Failed to fork");
			exit(EXIT_FAILURE);
		}
		else if (pid_of_child == 0)
		{
			replace_variables(commands[i], exit_status);
			execute_command_2(commands[i]);
		}
		else
		{
			wait(&exit_status);
		}
	}
}

/**
 * exec_prompt - Entry point
 * @user_input: The user input
 *
 * Description: This function takes user input, tokenizes it into commands
 *      based on the semicolon delimiter, and
 *	then forks a child process for each command.
 */
void exec_prompt(const char *user_input)
{
	char *commands[MAX_COMMANDS];
	int num_commands = 0;

	tokenize_user_input(user_input, commands, &num_commands);
	fork_child_processes(commands, num_commands);
}

