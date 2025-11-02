#include "xdg_path.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE FILENAME_MAX

static char *str_join(int nb, ...);

void test_XDG_RUNTIME_DIR(void);
void test_XDG_CONFIG_HOME(void);
void test_XDG_CACHE_HOME(void);
void test_XDG_STATE_HOME(void);
void test_XDG_DATA_HOME(void);

char username_buf[FILENAME_MAX];

int main(void)
{
	getlogin_r(username_buf, FILENAME_MAX - 1);

	test_XDG_CONFIG_HOME();
	test_XDG_RUNTIME_DIR();
	test_XDG_CACHE_HOME();
	test_XDG_STATE_HOME();
	test_XDG_DATA_HOME();
	return 0;
}

/* NOLINTBEGIN */
void test_XDG_DATA_HOME(void)
{
	/* Nothing is set. */
	setenv("XDG_DATA_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "", 1);
	setenv("LOGNAME", "", 1);
	char *expected = str_join(3, "/home/", username_buf, "/.local/share/");
	assert(strcmp(XDG_DATA_HOME(), expected) == 0);

	/* Relative path. */
	setenv("XDG_DATA_HOME", "./blah", 1);
	assert(XDG_DATA_HOME() == NULL);

	/* Empty env var, empty HOME empty USER */
	setenv("XDG_DATA_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "", 1);
	setenv("LOGNAME", "logname", 1);
	assert(strcmp(XDG_DATA_HOME(), "/home/logname/.local/share/") == 0);

	/* Empty env var, empty HOME but USER is set */
	setenv("XDG_DATA_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "test", 1);
	assert(strcmp(XDG_DATA_HOME(), "/home/test/.local/share/") == 0);

	/* Empty env var but HOME is set */
	setenv("XDG_DATA_HOME", "", 1);
	setenv("HOME", "/home/test", 1);
	assert(strcmp(XDG_DATA_HOME(), "/home/test/.local/share/") == 0);

	/* Env var is set */
	setenv("XDG_DATA_HOME", "/home/test/datahome.dir", 1);
	assert(strcmp(XDG_DATA_HOME(), "/home/test/datahome.dir") == 0);
}

void test_XDG_CONFIG_HOME()
{
	/* Nothing is set. */
	setenv("XDG_CONFIG_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "", 1);
	setenv("LOGNAME", "", 1);
	char *expected = str_join(3, "/home/", username_buf, "/.config/");
	assert(strcmp(XDG_CONFIG_HOME(), expected) == 0);

	/* Empty env var, empty HOME empty USER */
	setenv("XDG_CONFIG_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "", 1);
	setenv("LOGNAME", "logname", 1);
	assert(strcmp(XDG_CONFIG_HOME(), "/home/logname/.config/") == 0);

	/* Empty env var, empty HOME but USER is set */
	setenv("XDG_CONFIG_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "test", 1);
	assert(strcmp(XDG_CONFIG_HOME(), "/home/test/.config/") == 0);

	/* Empty env var but HOME is set */
	setenv("XDG_CONFIG_HOME", "", 1);
	setenv("HOME", "/home/test", 1);
	assert(strcmp(XDG_CONFIG_HOME(), "/home/test/.config/") == 0);

	/* Env var is set */
	setenv("XDG_CONFIG_HOME", "/home/test/datahome.dir", 1);
	assert(strcmp(XDG_CONFIG_HOME(), "/home/test/datahome.dir") == 0);
}

void test_XDG_STATE_HOME()
{
	/* Nothing is set. */
	setenv("XDG_STATE_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "", 1);
	setenv("LOGNAME", "", 1);
	char *expected = str_join(3, "/home/", username_buf, "/.local/state/");
	assert(strcmp(XDG_STATE_HOME(), expected) == 0);

	/* Empty env var, empty HOME empty USER */
	setenv("XDG_STATE_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "", 1);
	setenv("LOGNAME", "logname", 1);
	assert(strcmp(XDG_STATE_HOME(), "/home/logname/.local/state/") == 0);

	/* Empty env var, empty HOME but USER is set */
	setenv("XDG_STATE_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "test", 1);
	assert(strcmp(XDG_STATE_HOME(), "/home/test/.local/state/") == 0);

	/* Empty env var but HOME is set */
	setenv("XDG_STATE_HOME", "", 1);
	setenv("HOME", "/home/test", 1);
	assert(strcmp(XDG_STATE_HOME(), "/home/test/.local/state/") == 0);

	/* Env var is set */
	setenv("XDG_STATE_HOME", "/home/test/datahome.dir", 1);
	assert(strcmp(XDG_STATE_HOME(), "/home/test/datahome.dir") == 0);
}

void test_XDG_CACHE_HOME()
{
	/* Nothing is set. */
	setenv("XDG_CACHE_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "", 1);
	setenv("LOGNAME", "", 1);
	char *expected = str_join(3, "/home/", username_buf, "/.cache/");
	assert(strcmp(XDG_CACHE_HOME(), expected) == 0);

	/* Empty env var, empty HOME empty USER */
	setenv("XDG_CACHE_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "", 1);
	setenv("LOGNAME", "logname", 1);
	assert(strcmp(XDG_CACHE_HOME(), "/home/logname/.cache/") == 0);

	/* Empty env var, empty HOME but USER is set */
	setenv("XDG_CACHE_HOME", "", 1);
	setenv("HOME", "", 1);
	setenv("USER", "test", 1);
	assert(strcmp(XDG_CACHE_HOME(), "/home/test/.cache/") == 0);

	/* Empty env var but HOME is set */
	setenv("XDG_CACHE_HOME", "", 1);
	setenv("HOME", "/home/test", 1);
	assert(strcmp(XDG_CACHE_HOME(), "/home/test/.cache/") == 0);

	/* Env var is set */
	setenv("XDG_CACHE_HOME", "/home/test/datahome.dir", 1);
	assert(strcmp(XDG_CACHE_HOME(), "/home/test/datahome.dir") == 0);
}

void test_XDG_RUNTIME_DIR()
{
	/* Nothing is set. */
	setenv("XDG_RUNTIME_DIR", "", 1);
	assert(XDG_RUNTIME_DIR() == NULL);

	/* Env var is set */
	setenv("XDG_RUNTIME_DIR", "/home/test/datahome.dir", 1);
	assert(strcmp(XDG_RUNTIME_DIR(), "/home/test/datahome.dir") == 0);
}

/* NOLINTEND */

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
