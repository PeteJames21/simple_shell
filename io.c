#include "main.h"
#include <unistd.h>
#include <stdio.h>

/**
 * _print - print a string to stdout
 * @s: string to be printed
 * @fd: file descriptor to which to write the string
 * Return: the number of chars printed, or -1 if an error occured
 */
int _print(char *s, int fd)
{
	int len, count;

	if (!s)
		return (-1);

	len = _strlen(s);
	count = write(fd, s, len);
	fflush(NULL);

	return (count);
}


