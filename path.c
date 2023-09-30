#include "main.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * is_executable_file - Check if a File is a non-executable file
 * @path: full pathname of the file
 * Return: -1 if @path does not exist, 1 if it is executable, and 0 otherwise
 */
int is_executable_file(char *path)
{
	if (!path)
		return (-1);

	if (access(path, F_OK) == 0)  /* Is a file */
	{
		if (access(path, X_OK) == 0)  /* Is executable */
			return (1);
		else
			return (0);  /* Is non-executable */
	}
	else
		return (-1);  /* Does not exist */

	return (0);
}

/**
 * is_dir - Check if a file is a directory
 * @path: full pathname of the file
 * Return: 1 if @path is a directory, 0 otherwise
 */
int is_dir(char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);

	return (S_ISDIR(statbuf.st_mode));
}


/**
 * get_fullpathname - check if file is in PATH and return the full pathname
 * @fname: the basename of file to be searched for
 * @datash: struct containing shell runtime data
 * Return: the full pathname of the file, or NULL if file is not in PATH
 */
char *get_fullpathname(char *fname, data *datash)
{
	char *dir, *fullpathname, *path, *tmp;

	path = _strdup(get_var("PATH", datash->env));
	dir = strtok(path, ":");

	while (dir != NULL)
	{
		tmp = str_concat(dir, "/");
		fullpathname = str_concat(tmp, fname);
		free(tmp);
		if (is_executable_file(fullpathname) == 1)
		{
			free(path);
			return (fullpathname);
		}

		free(fullpathname);
		dir = strtok(NULL, ":");
	}

	free(path);

	return (NULL);  /* File not found in path */
}
