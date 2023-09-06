# Simple UNIX Command Interpreter

This is a simple UNIX command interpreter, also known as a shell, developed as part of a project. It provides basic command line functionality and executes commands entered by the user. The interpreter supports multiple tasks, each introducing new features and improvements.

## Tasks

1. **Task 0: Betty would be proud**
   - Write a beautiful code that passes the Betty checks.

2. **Task 1: Simple shell 0.1**
   - Write a UNIX command line interpreter.
   - Features:
     - Displays a prompt and waits for the user to type a command.
     - The prompt is displayed again after each command execution.
     - Command lines are simple, containing only one word.
     - Handles error messages when an executable cannot be found.
     - Handles the "end of file" condition (Ctrl+D).

3. **Task 2: Simple shell 0.2**
   - Builds upon Task 1.
   - Features:
     - Handles command lines with arguments.

4. **Task 3: Simple shell 0.3**
   - Builds upon Task 2.
   - Features:
     - Handles the PATH environment variable.
     - Avoids calling `fork` if the command doesn't exist.

5. **Task 4: Simple shell 0.4**
   - Builds upon Task 3.
   - Features:
     - Implements the `exit` built-in command to exit the shell.
     - Does not handle any arguments to the built-in `exit` command.

6. **Task 5: Simple shell 1.0**
   - Builds upon Task 4.
   - Features:
     - Implements the `env` built-in command to print the current environment.

7. **Task 6: Simple shell 0.1.1 (Advanced)**
   - Builds upon Task 1.
   - Advanced Features:
     - Implements a custom `getline` function.
     - Uses a buffer to read multiple characters at once.
     - Minimizes the use of the `read` system call.
     - Uses static variables.
     - Does not handle cursor movement.

8. **Task 7: Simple shell 0.2.1 (Advanced)**
   - Builds upon Task 2.
   - Advanced Features:
     - Does not use `strtok` for string tokenization.

9. **Task 8: Simple shell 0.4.1 (Advanced)**
   - Builds upon Task 4.
   - Advanced Features:
     - Handles arguments for the built-in `exit` command.
     - Usage: `exit status`, where `status` is an integer used to exit the shell.

10. **Task 9: setenv, unsetenv (Advanced)**
    - Builds upon Task 5.
    - Advanced Features:
      - Implements the `setenv` and `unsetenv` built-in commands.
      - `setenv`: Initializes or modifies environment variables.
        - Command syntax: `setenv VARIABLE VALUE`
        - Prints an error message on failure.
      - `unsetenv`: Removes environment variables.
        - Command syntax: `unsetenv VARIABLE`
        - Prints an error message on failure.

11. **Task 10: cd (Advanced)**
    - Builds upon Task 5.
    - Advanced Features:
      - Implements the built-in `cd` command to change the current directory.
      - Command syntax: `cd [DIRECTORY]`
        - If no argument is given, interprets the command as `cd $HOME`.
      - Handles the command `cd -`.
      - Updates the environment variable `PWD` when changing directories.

12. **Task 11: ; (Advanced)**
    - Builds upon Task 5.
    - Advanced Features:
      - Handles the command separator `;`.
      - Example:
        ```
        $ ls /var ; ls /var
        backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
        backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
        ```

13. **Task 12: && and || (Advanced)**
    - Builds upon Task 5.
    - Advanced Features:
      - Handles the shell logical operators `&&` and `||`.
      - Example:
        ```
        $ ls /var && ls /var
        backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
        backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
        ```

## Repository

The source code for this simple UNIX command interpreter can be found in the following GitHub repository: [simple_shell ↗](https://github.com/Muna-Saeed/simple_shell.git)

## Usage

To use the shell, follow these steps:

1. Clone the repository to your local machine.
2. Compile the source code.
3. Run the shell.
4. Enter commands at the prompt and observe the output.
5. Use the built-in commands or the supported features based on the task requirements.
6. Use the built-in `exit` command or Ctrl+C to exit the shell.
