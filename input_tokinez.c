#include "shell.h"

/**
 * tokenize_input - Tokenizes user input into arguments.
 * @user_input: The input string to tokenize.
 * @arguments: An array to store the tokenized arguments.
 * @max_argument: The maximum number of arguments to store.
 * Description: This function tokenizes the @user_input
 *	string into individual arguments, using space (' ') as the delimiter.
 */
void tokenize_input(const char *user_input, char **arguments, int max_argument)
{
	int arguments_counter = 0;

	/* Tokenize whatever user enters */
	char *tokenize = strtok((char *)user_input, " ");

	while (tokenize != NULL && arguments_counter < max_argument - 1)
	{
		arguments[arguments_counter++] = strdup(tokenize);
		tokenize = strtok(NULL, " ");
	}
	arguments[arguments_counter] = NULL;
}

/**
 * free_arguments - Frees memory allocated for arguments.
 * @arguments: An array of arguments to free.
 * Description: This function takes an array of arguments and frees the memory
 *	allocated for each argument using the 'free' function.
 */
void free_arguments(char **arguments)
{
	unsigned int i;

	for (i = 0; arguments[i] != NULL; i++)
	{
		free(arguments[i]);
	}
}

