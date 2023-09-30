#include "main.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * env - print the current environment
 * @args: arguments passed to the function
 * @datash: struct containing shell runtime data
 */
void env(char **args, data *datash)
{
	char *err_msg;

	if (args != NULL)  /* env does not take any arguments */
	{
		err_msg = ": env: too many arguments\n";
		_print(PROGNAME, STDERR_FILENO);
		_print(err_msg, STDERR_FILENO);
		datash->exit_status = 1;
		return;
	}

	print_kv_list(datash->env);

	datash->exit_status = 0;
}

/**
 * exit_shell - exit the shell with the specified error code, if any
 * @args: arguments passed to the function
 * @datash: struct containing shell runtime data
 *
 * Return: no value is returned. A value is only returned on failure
 */
void exit_shell(char **args, data *datash)
{
	int len_args;
	int exit_code;
	char *err_msg;

	len_args = sizeofarr(args);

	if (len_args > 1)
	{
		err_msg = ": exit: too many arguments\n";
		_print(PROGNAME, STDERR_FILENO);
		_print(err_msg, STDERR_FILENO);
		datash->exit_status = 1;
		return;
	}
	else if (len_args == 1)
		exit_code = _atoi(args[0]);
	else
		exit_code = 0;  /* No args have been provided */

	datash->exit_status = exit_code;
	datash->exit = 1; /* Signal the mainloop to exit */
}

/**
 * alias - create/update an alias or print list of aliases
 * @args: arguments passed to the function
 * @datash: struct containing shell runtime data
 */
void alias(char **args, data *datash)
{
	char *key, *value;
	int len_args, error = 0;

	len_args = sizeofarr(args);
	if (len_args == 0)
	{
		print_alias_list(datash->aliases);
		datash->exit_status = 0;
		return;
	}
	while (*args)
	{
		if ((_strchr(*args, '=')) == NULL)
		{
			/* Arg doesn't have an `=` sign. Print the alias. */
			value = get_var(*args, datash->aliases);
			if (value == NULL)
			{
				_print("alias: ", STDERR_FILENO);
				_print(*args, STDERR_FILENO);
				_print(" not found\n", STDERR_FILENO);
				error = 1;
			}
			else
			{
				print_alias(*args, value);
			}

		}
		else  /* Update alias if it exists, otherwise create it */
		{
			key = strtok(*args, "=");
			value = strtok(NULL, "'\"");
			add_var(&(datash->aliases), key, value);
		}
		args++;
	}

	datash->exit_status = error;
}

/**
 * get_builtin - return builtin function matching the string
 * @name: string containing name of the function
 * Return: the builtin function, or NULL if name does not match any function
 */
void (*get_builtin(char *name)) (char **args, data *datash)
{
	if (_strcmp(name, "exit") == 0)
		return (exit_shell);
	else if (_strcmp(name, "env") == 0)
		return (env);
	else if (_strcmp(name, "alias") == 0)
		return (alias);
	else if (_strcmp(name, "setenv") == 0)
		return (_setenv);
	else if (_strcmp(name, "unsetenv") == 0)
		return (_unsetenv);
	else if (_strcmp(name, "cd") == 0)
		return (cd);
	else
		return (NULL);
}
