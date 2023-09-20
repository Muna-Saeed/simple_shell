#include "shell.h"
/**
 * main - Entry point.
 * Description: This function is where the execution of a C program starts.
 * @return The exit status of the program.
 * A value of 0 indicates successful execution.
 */

/* Define the global variables */
ssize_t input_index = 0;
char input_buffer[MAX_INPUT_SIZE];
/* the non-interactive mode */
void execute_commands_from_file(const char* filename)
{
	char line[256];
	FILE* file = fopen(filename, "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Failed to open file '%s'\n", filename);
		exit(EXIT_FAILURE);
	}


	while (fgets(line, sizeof(line), file) != NULL) 
	{

		/* Removes newline character from the end of the line */
		line[strcspn(line, "\n")] = '\0';

		/* Processes and executes the command in 'line' */
		exec_prompt(line);
	}

	fclose(file);
}

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		/** 
		 * If a filename is provided as a command-line argument,
		 * executes commands from the file
		 */
		execute_commands_from_file(argv[1]);
	}

	/* the interactive mode */
	else
	{
		char user_input[150];

		while (1)
		{
			if (!isatty(STDIN_FILENO) == 0)
				render_prompt();
			read_user_input(user_input, sizeof(user_input));
			if (strncmp(user_input, "exit", 4) == 0)
				exec_exit(user_input);
			exec_prompt(user_input);
		}
	}

	return (0);
}

