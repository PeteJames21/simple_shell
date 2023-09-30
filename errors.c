#include "main.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * print_cd_error - alert the user that it is not possible to cd into the dir
 * @dirname: name of the dir the user is trying to cd into
 * @datash: struct containing shell runtime data
 */
void print_cd_error(char *dirname, data *datash)
{
	char *err_msg;
	char *exec_count;

	if (dirname == NULL)
		return;

	err_msg = "can't cd to ";
	_print(datash->progname, STDERR_FILENO);
	_print(": ", STDERR_FILENO);
	exec_count = _itoa(datash->exec_count);
	_print(exec_count, STDERR_FILENO);
	_print(": cd: ", STDERR_FILENO);
	_print(err_msg, STDERR_FILENO);
	_print(dirname, STDERR_FILENO);
	_print("\n", STDERR_FILENO);
	free(exec_count);
}

/**
 * print_cmd_not_found - alert user that the command was not found
 * @cmd: name of the command
 * @datash: struct containing shell runtime data
 */
void print_cmd_not_found(char *cmd, data *datash)
{
	char *err_msg;
	char *exec_count;

	if (cmd == NULL)
		return;

	err_msg = ": not found";
	_print(datash->progname, STDERR_FILENO);
	_print(": ", STDERR_FILENO);
	exec_count = _itoa(datash->exec_count);
	_print(exec_count, STDERR_FILENO);
	_print(": ", STDERR_FILENO);
	_print(cmd, STDERR_FILENO);
	_print(err_msg, STDERR_FILENO);
	_print("\n", STDERR_FILENO);
	free(exec_count);
}

/**
 * print_err_from_builtin - print an error from a builtin function
 * @funcname: name of the builtin function generating the error
 * @err_msg: error message to be displayed
 * @datash: struct containing shell runtime data
 */
void print_err_from_builtin(char *funcname, char *err_msg, data *datash)
{
	char *exec_count;

	if (err_msg == NULL || funcname == NULL)
		return;

	_print(datash->progname, STDERR_FILENO);
	_print(": ", STDERR_FILENO);
	exec_count = _itoa(datash->exec_count);
	_print(exec_count, STDERR_FILENO);
	_print(": ", STDERR_FILENO);
	_print(funcname, STDERR_FILENO);
	_print(": ", STDERR_FILENO);
	_print(err_msg, STDERR_FILENO);
	_print("\n", STDERR_FILENO);
	free(exec_count);
}
