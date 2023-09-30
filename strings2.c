#include "main.h"
#include <stdlib.h>

/**
* _strchr - locate a character in a string
* @s: string to be searched
* @c: character to be found
*
* Return: a pointer to the first location of c, else NULL if c is not found
*/
char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);

		i++;
	}

	/* Check if the user intended to search for the nullbyte*/
	if (c == '\0')
		return (s);

	return (NULL);  /* c not found*/
}

/**
 * _itoa - convert an integer to a string
 * @n: integer to be converted
 *
 * Return: a pointer to the string. The string is created using malloc
 */
char *_itoa(int n)
{
	int i, size, rem, quotient;
	char *n_string;

	/* Determine the no. of chars to be printed (includes any -ve sign) */
	size = count_chars(n);
	/* For holding the string representation of n */
	n_string = malloc(size + 1);  /* +1 for null byte */

	if (!n_string)
		exit(12);

	if (n < 1)
	{
		/* Append the negative sign and convert n to a positive int */
		n_string[0] = '-';
		n = -1 * n;
	}

	i = size - 1;  /* For looping through n_string */

	do {
		quotient = n / 10;
		rem = n % 10;
		n = quotient;

		n_string[i] = rem + 48;  /* Add 48 to convert int to char */
		i -= 1;

	} while (quotient);

	n_string[size] = '\0'; /* Add null byte to string */

	return (n_string);
}

/**
 * count_chars - determine the number of chars needed to represent a given int
 * @n: the integer to be represented as a string. May be positive or negative
 *
 * Return: the number of characters needed to represent n
 */
int count_chars(int n)
{
	int count = 0;
	int quotient;

	if (n < 0)
		count = 1;  /* Account for the negative sign */

	do {
		quotient = n / 10;
		n = quotient;
		count += 1;

	} while (quotient);

	return (count);
}
