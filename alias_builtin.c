#include "shell.h"

/**
 * print_all_aliases - Print all aliases.
 * @alias_list: parameter
 * Description: This function prints all the aliases in the alias list.
 */
void print_all_aliases(Alias *alias_list)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		printf("%s='%s'\n", current->name, current->value);
		current = current->next;
	}
}

/**
 * print_specific_aliases - Print specific aliases.
 * @names: The names of the aliases to print.
 * @num_names: The number of names.
 * @alias_list: parameter
 * Description: This function prints the aliases with the specified names.
 */
void print_specific_aliases(Alias *alias_list, char *names[], int num_names)
{
	int i;

	for (i = 0; i < num_names; i++)
	{
		Alias *current = alias_list;

		while (current != NULL)
		{
			if (strcmp(current->name, names[i]) == 0)
			{
				printf("%s='%s'\n", current->name, current->value);
				break;
			}
			current = current->next;
		}
	}
}

/**
 * define_aliases - Define aliases.
 * @args: The arguments for the aliases.
 * @num_args: The number of arguments.
 * @alias_list: parameter
 * Description: This function defines aliases based on the provided arguments.
 */
void define_aliases(Alias **alias_list, char *args[], int num_args)
{
	int i;
	char *equal_sign;
	char *name;
	char *value;
	Alias *current;

	for (i = 0; i < num_args; i++)
	{
		equal_sign = strchr(args[i], '=');

		if (equal_sign != NULL)
		{
			*equal_sign = '\0'; /* Split the argument at the equal sign */
			name = args[i];
			value = equal_sign + 1;

			current = *alias_list;

			while (current != NULL)
			{
				if (strcmp(current->name, name) == 0)
				{
					strcpy(current->value, value);
					break;
				}
				current = current->next;
			}

			if (current == NULL)
			{
				Alias *new_alias = (Alias *)malloc(sizeof(Alias));

				strcpy(new_alias->name, name);
				strcpy(new_alias->value, value);
				new_alias->next = *alias_list;
				*alias_list = new_alias;
			}
		}
	}
}

/**
 * free_alias_list - Free the alias list.
 * @alias_list: parameter
 * Description: This function frees the memory allocated for the alias list.
 */
void free_alias_list(Alias **alias_list)
{
	Alias *current = *alias_list;

	while (current != NULL)
	{
		Alias *next = current->next;

		free(current);
		current = next;
	}
}
