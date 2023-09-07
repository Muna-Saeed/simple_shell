#include <shell.h>

void exec_prompt(const char *directive)
{
	pid_t pid_of_child = fork();
	if (pid_of_child == -1) {
		perror ("fork");
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
		//the process of the parent must wait
		wait(NULL);
	}
