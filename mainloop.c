#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * mainloop - REPL for executing commands
 * @datash: struct for holding shell runtime data
 */
void mainloop(data *datash)
{
	char **args, *line = NULL;
	size_t len_input = 0;
	ssize_t len = 0;

	while (datash->exit == 0)
	{
		if ((isatty(STDIN_FILENO) == 1) && (isatty(STDOUT_FILENO) == 1))
			_print("$ ", STDOUT_FILENO);

		len = getline(&line, &len_input, stdin);
		if (len == EOF)
		{
			free(line);
			break;
		}
		args = tokenize(line, " \n");
		if (!args)  /* An empty line has been encountered */
			continue;
		init_command_list(datash, args);  /* Update command table */
		exec(datash);  /* Execute commands in the command table */
		if (datash->exit == 1)
			free(line);
		free_command_list(datash->command_list);
		(datash->exec_count)++;
	}

}
