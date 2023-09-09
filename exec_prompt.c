#include "shell.h"

/**
 * exec_prompt - Entry point.
 * @user_input: type const char pointer.
 * Description: this function executes the prompts.
 */

extern char **environ;

void exec_prompt(const char *user_input)
{
    pid_t pid_of_child = fork();

    if (pid_of_child == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid_of_child == 0)
    {
        /**
         * execute child process
         * parses the user input and its arguments
         */
        char *arguments[150];
        int arguments_counter = 0;

        /* tokenize whatever user enters */
        char *tokenize = strtok((char *)user_input, " ");

        while (tokenize != NULL)
        {
            arguments[arguments_counter++] = tokenize;
            tokenize = strtok(NULL, " ");
        }
        arguments[arguments_counter] = NULL;

        /** 
         * Handle built-in commands
         * if the command is "exit" and exit accordingly
         */

        if (arguments_counter == 1 && strcmp(arguments[0], "exit") == 0)
        {
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(arguments[0], "env") == 0)
        {
            /* Handle the "env" command here */
            char **env = environ;

            while (*env != NULL)
            {
                moon_print(*env);
                env++;
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
            /**
             * Checks if the command contains a / character
             * (indicating a full path)
             */ 
            if (strchr(arguments[0], '/') != NULL)
            {
                if (execvp(arguments[0], arguments) == -1)
                {
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                /**
                 * The command doesn't contain a / character, so it will search for it
                 * in the directories specified by the PATH variable
                 */
                char *path = getenv("PATH");
                char *path_copy = strdup(path);
                char *dir = strtok(path_copy, ":");

                while (dir != NULL)
                {
                    char full_path[MAX_PATH_LENGTH];
                    snprintf(full_path, sizeof(full_path), "%s/%s", dir, arguments[0]);

                    if (execvp(full_path, arguments) != -1)
                    {
                        /* Execution succeeded, no need to continue searching */
                        break;
                    }

                    dir = strtok(NULL, ":");
                }

                /* Free the dynamically allocated memory */
                free(path_copy);

                /* If the loop completes without finding a valid executable, perror and exit */
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        wait(NULL);
    }
}