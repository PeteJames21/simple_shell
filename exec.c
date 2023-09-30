#include "main.h"
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/**
 * exec - execute all commands in the command table
 * @datash: struct containing shell runtime data
 */
void exec(data *datash)
{
	void (*func)(char **args, data *datash);
	char *pathname, **args, **args2;
	commands *command;

	command = datash->command_list;
	while (command != NULL)
	{
		args = command->args;
		pathname = get_fullpathname(args[0], datash);
		func = get_builtin(args[0]);  /* Check if the arg is a builtin */
		if (func)
		{
			/* Remove the name of the function from args */
			args2 = pop_array(args);
			func(args2, datash);
			free_array(args2);
			if (datash->exit == 1)
				return;
		}
		/* Execute file if it points to a valid executable file */
		else if (is_executable_file(args[0]) == 1)
			_exec(args, datash);
		/* Check if arg is an executable in $PATH */
		else if (pathname)
		{
			free(args[0]);
			args[0] = _strdup(pathname);
			_exec(args, datash);
		}
		/* Check if the arg if a regular non-executable file */
		else if (is_executable_file(args[0]) == 0 && sizeofarr(args) == 1)
			exec_from_file(args, datash);
		else
		{
			print_cmd_not_found(args[0], datash);
			datash->exit_status = 127;
		}
		command = command->next;
		free(pathname);
	}
}

/**
 * _exec - execute the provided command in a separate process
 * @datash: struct containing shell runtime data
 * @args: argument array to be passed to execve
 */
void _exec(char **args, data *datash)
{
	int pid;
	int status = 0;
	char **env;

	if (!args)
	{
		errno = 22;
		perror(PROGNAME);
		exit(22);
	}

	/* Convert the linked list to an array for compatibility with execve */
	env = kv_list_to_array(datash->env);

	pid = fork();

	if (pid == -1)
	{
		perror(PROGNAME);
	}
	else if (pid == 0)
	{
		status = execve(args[0], args, env);
		if (status == -1)
			_exit(errno);
	}
	else
	{
		wait(&status);
	}

	datash->exit_status = status / 256;  /* wait status = errno * 256 */
	free_array(env);
}

/**
 * exec_from_file - execute commands from file
 * @args: array of arguments
 * @datash: struct containing shell runtime data
 *
 * Decription: the commands are executed line by line. The execution is
 * stopped when the first error is encountered. In this case, the exit
 * status code of the command that exited with an error is returned.
 */
void exec_from_file(char **args, data *datash)
{
	/* TODO: implement */

	(void) args;
	(void) datash;
}
