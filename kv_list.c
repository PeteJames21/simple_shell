#include "main.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * print_kv_list - print all key-value pairs in the kv_list
 * @list: a pointer to the head of the kv_list
 */
void print_kv_list(kv_list *list)
{
	kv_list *node;

	node = list;

	while (node != NULL)
	{
		_print(node->key, STDOUT_FILENO);
		_print("=", STDOUT_FILENO);
		_print(node->value, STDOUT_FILENO);
		_print("\n", STDOUT_FILENO);
		node = node->next;
	}
}

/**
 * get_var - get the value of a variable from a kv_list
 * @key: name of variable
 * @list: a pointer to the head of the kv_list
 * Return: the value of the variable or NULL if the variable is not set
 */
char *get_var(char *key, kv_list *list)
{
	kv_list *next_node;

	next_node = list;
	while (next_node != NULL)
	{
		if (_strcmp(next_node->key, key) == 0)
			return (next_node->value);

		next_node = next_node->next;
	}

	return (NULL);  /* Variable not found */
}

/**
 * add_var - create or update a variable in a kv_list
 * @list: a pointer to the head of the kv_list
 * @key: name of the variable
 * @value: value of the variable
 * Return: the value of the variable on success or NULL if an error occurred
 */
char *add_var(kv_list **list, char *key, char *value)
{
	kv_list *next_node, *new_node;

	next_node = *list;
	while (1)
	{
		if (next_node != NULL && _strcmp(next_node->key, key) == 0)
		{
			free(next_node->value);
			next_node->value = _strdup(value);
			return (value);
		}
		if (next_node == NULL || next_node->next == NULL)
		{
			new_node = malloc(sizeof(kv_list));
			if (!new_node)
			{
				perror("Error creating node");
				exit(12);
			}
			new_node->key = _strdup(key);
			new_node->value = _strdup(value);
			new_node->next = NULL;
			if (next_node == NULL)  /* Make node the head */
			{
				*list = new_node;
			}
			else
			{
				next_node->next = new_node;
			}
			return (value);
		}
		next_node = next_node->next;
	}
}

/**
 * kv_list_to_array - convert a kv_list of variables to an array
 * @list: kv_list containing the variables
 * Return: an array of variables of the form ["key=value", ..., NULL]
 */
char **kv_list_to_array(kv_list *list)
{
	char **arr, *kv_pair, *key, *value;
	kv_list *node;
	int num_vars, i;

	num_vars = size_of_kv_list(list);
	if (num_vars < 1)
		return (NULL);

	arr = malloc(sizeof(char *) * (num_vars + 1));
	if (arr == NULL)
		exit(12);

	node = list;
	i = 0;
	while (node != NULL)
	{
		key = str_concat(node->key, "=");
		value = node->value;
		kv_pair = str_concat(key, value);
		arr[i] = kv_pair;
		free(key);
		i++;
		node = node->next;
	}
	arr[i] = NULL;  /* Add a NULL terminator to the array */

	return (arr);
}

/**
 * remove_kv_list_node - delete a variable from a kv_list
 * @key: name of variable to be deleted. No error occurs if key is not found.
 * @list: a pointer to the head of the kv_list
 * Return: 1 on success and 0 on failure (e.g. if key not found)
 */
int remove_kv_list_node(kv_list **list, char *key)
{
	int i = 0;
	kv_list *prev_node, *node;

	if (!*list)
		return (0);  /* List is empty */

	node = *list;

	while (node)
	{
		if (_strcmp(node->key, key) == 0)
		{
			if (i == 0)
			{
				*list = node->next;
				free(node->key);
				free(node->value);
				free(node);
				return (1);
			}

			prev_node->next = node->next;
			free(node->key);
			free(node->value);
			free(node);
			return (1);
		}

		prev_node = node;
		node = node->next;
		i++;
	}
	return (0);
}
