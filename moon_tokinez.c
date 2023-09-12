#include "shell.h"
/**
 * tokenize_string - Entry point.
 * Description: This function Splits a string into tokens based on a delimiter.
 * @input: The string to split.
 * @separator: The delimiter.
 *
 * Return: An array of tokens.
 */
char **tokenize_string(const char *input, char *separator)
{
	char **tokens;
	int index = 0, innerIndex = 0, strIndex = 0;

	tokens = malloc(sizeof(char *) * 100);
	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	tokens[index] = malloc(sizeof(char) * 100);
	if (tokens[index] == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (input[strIndex] != '\0')
	{
		innerIndex = 0;
		while (input[strIndex] != separator[0] && input[strIndex] != '\0')
		{
			tokens[index][innerIndex++] = input[strIndex++];
		}
		tokens[index][innerIndex] = '\0';

		if (input[strIndex] != '\0')
		{
			index++;
			tokens[index] = malloc(sizeof(char) * 100);
			if (tokens[index] == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			strIndex++;
		}
	}
	tokens[++index] = NULL;
	return (tokens);
}
