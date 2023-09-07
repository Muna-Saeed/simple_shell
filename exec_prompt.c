#include <shell.h>
/**
 * exec_prompt - Entry point.
 * @directive: type const char pointer.
 * Description: this function executes the prompts.
*/
void exec_prompt(const char *directive)
{
	pid_t pid_of_child = fork();

	if (pid_of_child == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid_of_child == 0)
	{
		execlp(directive, directive, (char *)NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{
		/*
		*the process of the parent must wait until the child process is done.
		*/
		wait(NULL);
	}
