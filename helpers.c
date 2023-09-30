#include "main.h"
#include <stdlib.h>

/**
 * sizeofarr - get the number of elements in the array
 * @arr: a null-terminated array
 * Return: the number of elements, excluding the NULL terminator
 */
int sizeofarr(char **arr)
{
	int count = 0;
	int i = 0;

	if (!arr)
		return (0);

	while (arr[i])
	{
		count += 1;
		i++;
	}

	return (count);
}

/**
 * pop_array - create a new array that excludes the first element of the array
 * @arr: array to be popped. The array must be null-terminated
 * Return: pointer to the new array (must be freed using malloc after use)
 */
char **pop_array(char **arr)
{
	int i;
	int size = sizeofarr(arr);
	char **arr2 = NULL;

	if (!arr || size <= 1)
		return (NULL);

	arr2 = malloc(sizeof(char *) * size);
	if (!arr2)
		exit(12);  /* Out of memory */

	for (i = 0; i < size; i++)
	{
		if (!arr[i + 1])
		{
			arr2[i] = NULL;
			break;
		}
		arr2[i] = _strdup(arr[i + 1]);
	}

	return (arr2);
}

/**
 * size_of_kv_list - determine the length of a kv_list
 * @list: kv_list to be evaluated
 * Return: the number of nodes in @list, excluding the NULL terminator
 */
int size_of_kv_list(kv_list *list)
{
	int size;
	kv_list *node;

	size = 0;
	node = list;

	while (node != NULL)
	{
		size++;
		node = node->next;
	}

	return (size);
}
