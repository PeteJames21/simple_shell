#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/**
 * handle_sigint - Handle CTRL-C
 * @sig: Signal handler
 */
void handle_sigint(int sig)
{
	(void)sig;

	_print("\n$ ", STDOUT_FILENO);
}

/**
 * main - entry point to the shell program
 * @argc: number of commandline arguments passed
 * @argv: array containing commandline arguments
 * @env: array of environment variables
 * Return: the exit status of the program
 */
int main(int argc, char **argv, char **env)
{
	data *datash;
	char **args, *progname;
	int exit_status;

	(void) argc;
	datash = malloc(sizeof(data));
	signal(SIGINT, handle_sigint);  /* handle CTRL-C */
	progname = _strdup(argv[0]);
	args = pop_array(argv);  /* Remove the program name from the list */
	init_data(datash, args, env);
	datash->progname = progname;

	mainloop(datash);
	exit_status = datash->exit_status;
	free_data(datash);

	return (exit_status);
}
