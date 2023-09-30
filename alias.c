#include "main.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * print_alias_list - print all defined aliases
 * @list: kv_list containing defined aliases
 */
void print_alias_list(kv_list *list)
{
	kv_list *node = list;

	while (node != NULL)
	{
		print_alias(node->key, node->value);
		node = node->next;
	}
}

/**
 * print_alias - print a single alias to STDOUT
 * @key: name of the alias
 * @value: value of the alias
 */
void print_alias(char *key, char *value)
{
	_print(key, STDOUT_FILENO);
	_print("='", STDOUT_FILENO);
	_print(value, STDOUT_FILENO);
	_print("'\n", STDOUT_FILENO);
}

