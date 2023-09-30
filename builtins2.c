#include "main.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * _setenv - update or create an environment variable
 * @args: arguments passed to the function
 * @datash: struct containing shell runtime data
 *
 * Description - @args must be an array of exactly 2 strings. args[0]
 * is the name of the variable and args[1] is its value. If the variable
 * exists, it is updated with the new value, otherwise a new variable is
 * created.
 */
void _setenv(char **args, data *datash)
{
	int len_args;
	char *err_msg;

	len_args = sizeofarr(args);
	if (len_args != 2)
	{
		err_msg = "Exactly 2 arguments are required";
		print_err_from_builtin("setenv", err_msg, datash);
		datash->exit_status = 1;
		return;
	}

	add_var(&(datash->env), args[0], args[1]);
	datash->exit_status = 0;
}

/**
 * _unsetenv - delete an environment variable
 * @args: arguments passed to the function
 * @datash: struct containing shell runtime data
 *
 * Description - @args must be an array of exactly 1 string representing
 * the name of the environment variable to be deleted.
 */
void _unsetenv(char **args, data *datash)
{
	int len_args, success;
	char *err_msg;

	len_args = sizeofarr(args);
	if (len_args != 1)
	{
		err_msg = "Exactly 1 argument is required";
		print_err_from_builtin("unsetenv", err_msg, datash);
		datash->exit_status = 1;
		return;
	}

	success = remove_kv_list_node(&(datash->env), args[0]);
	if (success == 0)
	{
		err_msg = str_concat(args[0], ": not found");
		print_err_from_builtin("unsetenv", err_msg, datash);
		free(err_msg);
		datash->exit_status = 1;
	}
	else
	{
		datash->exit_status = 0;
	}
}

/**
 * cd - change the current working directory
 * @args: arguments passed to the function
 * @datash: struct containing shell runtime data
 *
 * Description - @args must either be empty or have 1 string representing
 * the directory to set as the current directory. The string may be a
 * name of a valid directory or `-`, in which case the new cd is set to the
 * previous one. If @args is empty, the cd is set to the home directory.
 * Extra args passed to the function are ignored.
 */
void cd(char **args, data *datash)
{
	char *old_pwd, *pwd, *dirname, *home;

	home = _strdup(get_var("HOME", datash->env));
	pwd = _strdup(get_var("PWD", datash->env));
	old_pwd = _strdup(get_var("OLDPWD", datash->env));
	(old_pwd == NULL) ? add_var(&(datash->env), "OLDPWD", pwd) : 0;
	args ? dirname = args[0] : 0;
	if (args == NULL)
	{
		(home == NULL) ? home = _strdup(pwd) : 0;
		add_var(&(datash->env), "OLDPWD", pwd);
		add_var(&(datash->env), "PWD", home);
		chdir(home);
		datash->exit_status = 0;
	}
	else if (_strcmp(dirname, "-") == 0)
	{
		(old_pwd == NULL) ? old_pwd = _strdup(pwd) : 0;
		add_var(&(datash->env), "OLDPWD", pwd);
		add_var(&(datash->env), "PWD", old_pwd);
		chdir(old_pwd);
		datash->exit_status = 0;
		_print(old_pwd, STDOUT_FILENO);
		_print("\n", STDOUT_FILENO);
	}
	else if (!is_dir(dirname))  /* Not a valid directory */
	{
		print_cd_error(dirname, datash);
		datash->exit_status = 2;
	}
	else
	{  /* TODO: check for permissions before attempting cd */
		add_var(&(datash->env), "OLDPWD", pwd);
		add_var(&(datash->env), "PWD", dirname);
		chdir(dirname);
		datash->exit_status = 0;
	}
	free(home);
	free(old_pwd);
	free(pwd);
}
