#include "xdg_path.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE FILENAME_MAX

static char *str_dup(char *original)
{
	char *new = malloc(strlen(original) + sizeof(char));
	int i;
	for (i = 0; i <= strlen(original); ++i)
		new[i] = original[i];
	return new;
}

/*
 * @brief path must be non-null, nonempty and absolute.
 */
static int is_valid(char *path)
{
	return (path != NULL && strcmp(path, "") != 0 && path[0] == '/');
}

/*
 * Variadic joins. If one of the string is NULL, the final string will be NULL.
 * You can see it as a concatenation operator on a set, with NULL as the
 * absorbing element.
 */
static char *str_join(int nb, ...)
{
	va_list l;
	va_start(l, nb);

	long  total_length = 0;
	char *final_str	   = calloc(BUF_SIZE, sizeof(char));

	int i;
	for (i = 0; i < nb; ++i)
	{
		char *str = va_arg(l, char *);

		if (str == NULL)
		{
			free(final_str);
			final_str = NULL;
			break;
		}
		unsigned int length = strlen(str);
		memcpy(final_str + total_length, str, length + 1);
		total_length += length;
		if (total_length > BUF_SIZE)
			break;
	}
	va_end(l);
	return final_str;
}

static char *USER(void)
{
	char *user = getenv("USER");
	if (user != NULL && strcmp(user, "") != 0)
		return str_dup(user);
	user = getenv("LOGNAME");
	if (user != NULL && strcmp(user, "") != 0)
		return str_dup(user);

	char username_buf[FILENAME_MAX];
	if (getlogin_r(username_buf, FILENAME_MAX - 1) == 0)
		return str_dup(username_buf);

	/* Well, shit */
	fprintf(
		stderr,
		"please define the variables defined in the XDG BASE DIRECTORY "
		"specification, or at least define USER and I'll assume /home/USER "
		"as your home directory.\n Expect a segfault, incorrect behaviour, "
		"failed mkdirs or open calls and files created in unexpected "
		"location.\n"
	);
	return NULL;
}

static char *HOME(void)
{
	char *dir = getenv("HOME");
	if (is_valid(dir))
		return str_dup(dir);
	dir		   = NULL;
	char *user = USER();
	if (user != NULL && strcmp(user, "") != 0)
		dir = str_join(2, "/home/", user);
	free(user);
	return dir;
}

char *XDG_DATA_HOME(void)
{
	char *dir = getenv("XDG_DATA_HOME");
	if (is_valid(dir))
		return str_dup(dir);
	dir		   = NULL;
	char *home = HOME();
	if (is_valid(home))
		dir = str_join(2, home, "/.local/share/");
	free(home);
	return dir;
}

char *XDG_CONFIG_HOME(void)
{
	char *dir = getenv("XDG_CONFIG_HOME");
	if (is_valid(dir))
		return str_dup(dir);
	dir		   = NULL;
	char *home = HOME();
	if (is_valid(home))
		dir = str_join(2, home, "/.config/");
	free(home);
	return dir;
}

char *XDG_STATE_HOME(void)
{
	char *dir = getenv("XDG_STATE_HOME");
	if (is_valid(dir))
		return str_dup(dir);
	dir		   = NULL;
	char *home = HOME();
	if (is_valid(home))
		dir = str_join(2, home, "/.local/state/");
	free(home);
	return dir;
}

char *XDG_CACHE_HOME(void)
{
	char *dir = getenv("XDG_CACHE_HOME");
	if (is_valid(dir))
		return str_dup(dir);
	dir		   = NULL;
	char *home = HOME();
	if (is_valid(home))
		dir = str_join(2, home, "/.cache/");
	free(home);
	return dir;
}

char *XDG_RUNTIME_DIR(void)
{
	char *dir = getenv("XDG_RUNTIME_DIR");
	if (is_valid(dir))
		return str_dup(dir);
	return NULL;
}
