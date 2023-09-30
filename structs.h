#ifndef STRUCTS_H
#define STRUCTS_H

/**
 * struct kv_list - a linked list for storing key-value pairs
 * @key: name of variable
 * @value: value of variable
 * @next: pointer to the next node
 */
typedef struct kv_list
{
	char *key;
	char *value;
	struct kv_list *next;
} kv_list;

/**
 * struct commands - linked list for storing the command table
 * @args: array containing a command and its arguments
 * @cmd_sep: the separator to the right of the command (&&, ||, ;)
 * @next: pointer to the next node
 */
typedef struct commands
{
	char **args;  /* array of commandline arguments */
	char *cmd_sep; /* Value should be `;` for the last node */
	struct commands *next;
} commands;

/**
 * struct data - struct for holding the command table and runtime data
 * @command_list: the command table - a list of commands to be executed
 * @pid: the pid of the shell program
 * @exit: a flag that indicates whether to exit the shell (0 = No, 1 = Yes)
 * @exit_status: the exit code of the last executed command
 * @exec_count: the number of commands executed during the shell session
 * @progname: the name of the progarm as passed to main()
 * @env: a list of environment variables
 * @aliases: a list of aliases of shell commands
 */
typedef struct data
{
	commands *command_list;
	int pid;
	int exit_status;
	int exit;
	int exec_count;
	char *progname;
	kv_list *env;
	kv_list *aliases;

} data;

#endif
