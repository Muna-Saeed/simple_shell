#include "shell.h"

/**
 * initialize_buffer - Initialize or expand the line buffer if needed.
 * @lineptr: A pointer to a pointer to the line buffer.
 * @n: A pointer to the size of the allocated buffer.
 *
 * Return: void
 *
 * This function initializes or expands the line buffer if needed.
 */
static void initialize_buffer(char **lineptr, size_t *n)
{
	char *line = *lineptr;

	if (line == NULL || *n < 1)
	{
		*n = MAX_INPUT_SIZE;
		line = (char *)malloc(*n);
		if (line == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		*lineptr = line;
	}
}

/**
 * read_data_into_buffer - Read data into the buffer if needed.
 * @bytes_read: A pointer to store the number of bytes read.
 *
 * Return: 1 if data was read, 0 on EOF, or -1 on error.
 *
 * This function reads data into the buffer if needed.
 */
static int read_data_into_buffer(ssize_t *bytes_read)
{
	if (input_index == 0)
	{
		*bytes_read = read(STDIN_FILENO, input_buffer, MAX_INPUT_SIZE);
		if (*bytes_read < 0)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		else if (*bytes_read == 0)
		{
			return (0); /* EOF */
		}
	}
	return (1);
}

/**
 * copy_chars_to_line - Copy characters from input_buffer to line.
 * @line: The line buffer.
 * @lineptr: A pointer to a pointer to the line buffer.
 * @n: A pointer to the size of the allocated buffer.
 * @input_index: A pointer to the input buffer index.
 * @bytes_read: A pointer to the number of bytes read.
 *
 * Return: 1 if a newline is found, 0 otherwise.
 *
 * This function copies characters from input_buffer to line.
 */
static int copy_chars_to_line(char *line, char **lineptr, size_t *n,
		ssize_t *input_index, ssize_t *bytes_read)
{
	while (*input_index < *bytes_read && input_buffer[*input_index] != '\n')
	{
		if (*n <= strlen(line))
		{
			*n *= 2;
			line = (char *)realloc(line, *n);
			if (line == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
			*lineptr = line;
		}
		line[strlen(line)] = input_buffer[*input_index];
		(*input_index)++;
	}

	if (*input_index < *bytes_read && input_buffer[*input_index] == '\n')
	{
		line[strlen(line)] = '\0';
		(*input_index)++;
		return (1); /* Found newline character */
	}
	return (0); /* Did not find newline character */
}

/**
 * moon_getline - Read a line from standard input.
 * @lineptr: A pointer to a pointer to the line buffer.
 * @n: A pointer to the size of the allocated buffer.
 *
 * Return: The number of characters read (excluding newline),
 *         -1 on EOF, or -1 on error.
 *
 * This function reads a line from standard input.
 */
ssize_t moon_getline(char **lineptr, size_t *n)
{
	ssize_t bytes_read = 0;
	char *line = *lineptr;

	initialize_buffer(lineptr, n);

	while (1)
	{
		if (read_data_into_buffer(&bytes_read) == 0)
		{
			return (-1); /* EOF */
		}

		if (copy_chars_to_line(line, lineptr, n, &input_index, &bytes_read) == 1)
		{
			return (strlen(line));
		}
	}
}

