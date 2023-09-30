#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * init_command_list - create the command table using shell arguments
 * @datash: struct for holding shell runtime data
 * @args: arguments passed to the shell program
 */
void init_command_list(data *datash, char **args)
{
	/* TODO: Handle command delimiters (; || &&) */
	/* TODO: if args[0] is a regular non-executable file,
		make command table using its contents. Treat each ine as
		a separate command.	
	 */
	/* For now, assume the command is non-compound */
	commands *cmds;

	/* Parse args before building the command table */
	args = remove_comment(args);

	/* temp fix: substitution affects alias command */
	/* thus dont substitute is the command is "alias" */
	if (args && (_strcmp(args[0], "alias") != 0))
		substitute_args(args, datash);

	if (args == NULL)
	{
		datash->command_list = NULL;
		return;
	}

	cmds = malloc(sizeof(commands));
	if (!cmds)
		exit(12);

	cmds->args = args;
	cmds->cmd_sep = NULL;
	cmds->next = NULL;

	datash->command_list = cmds;
}

/**
 * init_env_list - create linked list of environment variables
 * @datash: struct for holding shell runtime data
 * @env: array of environment variables
 */
void init_env_list(data *datash, char **env)
{
	char *key, *value, *delimitter = "=";

	while (*env)
	{
		key = strtok(*env, delimitter);
		value = strtok(NULL, "");
		add_var(&(datash->env), key, value);
		env++;
	}
}

/**
 * init_data - initialize runtime data using commandline arguments
 * @datash: struct for holding runtime data and commands to be executed
 * @args: array of commandline arguments
 * @env: array of environment variables
 */
void init_data(data *datash, char **args, char **env)
{
	init_command_list(datash, args);
	datash->pid = getpid();
	datash->exit_status = 0;
	datash->exec_count = 1;
	datash->exit = 0;
	datash->env = NULL;
	datash->aliases = NULL;
	init_env_list(datash, env);
}
