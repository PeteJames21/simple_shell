#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
 * tokenize -  splits a string into null-terminated array containing the words
 * @s: the string to be split
 * @delimiter: delimiter to use in splitting the string
 * Return: an array of strings (the tokens found)
 */
char **tokenize(char *s, char *delimiter)
{
	int i;
	char *token;
	char **tokens;
	int token_count;

	if (!s)
		return (NULL);

	token_count = count_tokens(s, delimiter);
	if (token_count == 0)
		return (NULL);

	tokens = malloc(sizeof(char *) * token_count + sizeof(NULL));
	if (!tokens)
		exit(12);

	token = strtok(s, delimiter);
	for (i = 0; i < token_count; i++)
	{
		tokens[i] = _strdup(token);
		token = strtok(NULL, delimiter);
	}

	tokens[i] = NULL;

	return (tokens);
}

/**
 * count_tokens - count the number of tokens in a string based on whitespace
 * @s: the string to be parsed
 * @delimiter: string to use as delimiter
 * Return: the number of tokens
 */
int count_tokens(char *s, char *delimiter)
{
	/* make a copy since strtok modifies the string */
	char *cpy = _strdup(s);
	int count = 0;

	char *token = strtok(cpy, delimiter);

	while (token)
	{
		count++;
		token = strtok(NULL, delimiter);
	}

	free(cpy);

	return (count);
}


/**
 * remove_comment - remove a comment from an array of args
 * @args: pointer to the array containing the args
 * Return: a copy of @args with the comment removed.
 *
 * Description - for a line to be treated as a comment, the `#` symbol must
 * be preceded by a whitespace(s) if it appears after another non-whitespace
 * character. Thus, the line "foo#bar" does not have a comment, whereas
 * "foo # bar", "foo #bar" and "# foobar" have comments.
 */
char **remove_comment(char **args)
{
	char **new_args;
	int i = 0, loc = -1;

	loc = locate_comment(args);
	if (loc == -1)
		return (args); /* No comment found */

	if (loc == 0)
	{
		/* The entire `args` is a comment */
		free_array(args);
		return (NULL);
	}

	new_args = malloc(sizeof(char *) * (loc + 1));  /* +1 for NULL */
	if (!new_args)
		exit(12);

	for (i = 0; i < loc; i++)
		new_args[i] = _strdup(args[i]);

	new_args[i] = NULL;

	/* Free the old array and replace it with the new one */
	free_array(args);

	return (new_args);
}


/**
 * locate_comment - locate a comment in a list of strings
 * @args: array of commandline arguments
 * Return: the index at which the comment starts, or -1 if not found
 */
int locate_comment(char **args)
{
	int i, loc = -1;

	if (args == NULL)
		return (loc);

	/* Get index of the arg starting with `#` */
	for (i = 0; args[i]; i++)
	{
		if (_strcmp(args[i], "#") == 0)
		{
			loc = i;
			break;
		}
		if ((args[i][0] == '#') && (i != 0))
		{
			loc = i;
			break;
		}
	}

	return (loc);
}


/**
 * substitute_args - perform command substitution
 * @args: array of commandline arguments
 * @datash: struct contaning shell runtime data
 *
 * Description - the following are substituted in @args if found: aliases,
 * $$, $?
 */
void substitute_args(char **args, data *datash)
{
	char *alias, *pid, *exit_status;
	int i;

	if (args == NULL)
		return;

	for (i = 0; args[i]; i++)
	{
		alias = get_var(args[i], datash->aliases);
		if (alias)
		{
			alias = _strdup(alias);
			free(args[i]);
			args[i] = alias;
		}
		else if (_strcmp(args[i], "$$") == 0)
		{
			pid = _itoa(datash->pid);
			free(args[i]);
			args[i] = pid;
		}
		else if (_strcmp(args[i], "$?") == 0)
		{
			exit_status = _itoa(datash->exit_status);
			free(args[i]);
			args[i] = exit_status;
		}
	}
}
