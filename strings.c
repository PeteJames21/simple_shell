#include "main.h"
#include <stdlib.h>

/**
* _strdup - copy the provided string to a new memory location
* @str: pointer to the string to be copied
*
* Return: a pointer to the memory holding the copy of the string
*/
char *_strdup(char *str)
{
	unsigned int i, size = 0;
	char *p;

	if (str == NULL)
		return (NULL);

	/* Determine the size of the string excluding the null byte */
	while (*(str + size))
		size += 1;

	p = malloc(size + 1);  /* +1 to accomodate null byte */

	if (p == NULL)
		return (NULL);

	/* Copy str to new memory location */
	for (i = 0; *(str + i); i++)
		*(p + i) = *(str + i);

	p[i] = '\0';

	return (p);
}

/**
 * _strlen - determine the length of a string
 * @s: pointer of string variable to analyzed
 * Return: the length of the string referenced by the pointer
 */
int _strlen(char *s)
{
	int i;
	int length;

	length = 0;
	i = 0;

	while (1)
	{
		if (!s[i])
			break;

		length++;
		i++;
	}

	return (length);
}

/**
* _strcmp - compare two strings
* @s1: first string to be compared
* @s2: second string to be compared
*
* Return: 0 if s1 == s2, a negative int if s1 < s2, a positive int if s1 > s2
*/
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (1)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
}

/**
 * _atoi - convert a string to an integer
 * @s: string to be converted
 * Return: the converted value or 0 on error
 */
int _atoi(char *s)
{
	int c = 0;
	unsigned int ni = 0;
	int min = 1;
	int isi = 0;

	while (s[c])
	{
		if (s[c] == 45)
		{
			min *= -1;
		}

		while (s[c] >= 48 && s[c] <= 57)
		{
			isi = 1;
			ni = (ni * 10) + (s[c] - '0');
			c++;
		}

		if (isi == 1)
		{
			break;
		}

		c++;
	}

	ni *= min;
	return (ni);
}

/**
* str_concat - concatenate two strings into a new memory location
* @s1: the first string
* @s2: the second string
*
* Return: the pointer to the new string, else NULL if the operation fails
*/
char *str_concat(char *s1, char *s2)
{
	unsigned int total_size = 0;
	char *p, *q;

	if (s1 != NULL)
		total_size += _strlen(s1);
	if (s2 != NULL)
		total_size += _strlen(s2);

	p = malloc(total_size + 1);  /* +1 to accomodate the null byte */
	if (p == NULL)
		return (NULL);
	q = p;

	if (s1 != NULL)
	{
		while (*s1)
		{
			*q = *s1;
			s1++;
			q++;
		}
	}
	if (s2 != NULL)
	{
		while (*s2)
		{
			*q = *s2;
			s2++;
			q++;
		}
	}
	*q = '\0';

	return (p);
}
