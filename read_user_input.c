#include "shell.h"
/**
 * read_user_input - Entry point.
 * @user_input: type const char pointer holds string.
 * @size: calculate the size of the string.
 * Description: this function reads the inputs from the user.
 */
void read_user_input(char *user_input, size_t size)
{
	if (fgets(user_input, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
			/* moon_print("\n"); */
		}
		else
		{
			perror("Error an executable can't be found while reading user (fgets)");
			exit(EXIT_FAILURE);
		}
	}

	/* Remove trailing newline character */
	user_input[strcspn(user_input, "\n")] = '\0';
}

