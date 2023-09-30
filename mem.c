#include "main.h"
#include <stdlib.h>

/**
 * free_data - free memory occupied by runtime data
 * @datash: struct for holding shell runtime data
 */
void free_data(data *datash)
{
	free_kv_list(datash->env);
	free_kv_list(datash->aliases);
	free(datash->progname);
	free(datash);
	/* NOTE: datash->command_list was freed in mainloop() */
}

/**
 * free_kv_list - free memory occupied by a kv_list
 * @list: kv_list to be freed
 */
void free_kv_list(kv_list *list)
{
	kv_list *next, *previous;

	if (!list)
		return;

	next = list;
	while (1)
	{
		if (next->next == NULL)
		{
			free(next->key);
			free(next->value);
			free(next);
			break;
		}
		previous = next;
		next = next->next;
		if (previous)
		{
			free(previous->key);
			free(previous->value);
			free(previous);
		}
	}
}

/**
 * free_command_list - free memory occupied by a kv_list
 * @list: commands list to be freed
 */
void free_command_list(commands *list)
{
	commands *next, *previous;

	if (!list)
		return;

	next = list;
	while (1)
	{
		if (next->next == NULL)
		{
			free_array(next->args);
			free(next->cmd_sep);
			free(next);
			break;
		}
		previous = next;
		next = next->next;
		if (previous)
		{
			free_array(previous->args);
			free(previous->cmd_sep);
			free(previous);
		}
	}
}

/**
 * free_array - free memory occupied by an array of strings
 * @mem: pointer to the array
 */
void free_array(char **mem)
{
	int size, i;

	if (!mem)
		return;

	size = sizeofarr(mem);
	for (i = 0; i < size; i++)
	{
		free(mem[i]);
	}
	free(mem);
}

/**
 * _calloc - allocate memory for an array and set to zero
 * @nmemb: Number of elements in the array
 * @size: size of each element in memory
 *
 * Return: a pointer to the allocated memory
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{

	char *mem;
	unsigned int i;

	if (nmemb == 0 || size == 0)
		return (NULL);

	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);

	for (i = 0; i < nmemb * size; i++)
		mem[i] = 0;

	return (mem);
}
