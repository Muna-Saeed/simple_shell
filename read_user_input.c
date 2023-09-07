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
			moon_print("\n");
		}
		else
		{
			moon_print("Error an executable can not be found while reading user input");
			exit(EXIT_FAILURE);
		}
	}

}