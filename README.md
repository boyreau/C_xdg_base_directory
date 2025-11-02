## Simple C implementation of the XDG Base directory specification

A single .c, a single .h and unit tests.

See [here](https://specifications.freedesktop.org/basedir/latest/) for the full XDG base directory specifications.

After including `xdg_path.h` you may use:

 - `char *XDG_DATA_HOME()` to retrieve a directory suitable for various and variable application data (images, extensions...).
 - `char *XDG_CONFIG_HOME()` to retrieve a directory suitable for configuration files.
 - `char *XDG_STATE_HOME()` to retrieve a driectory suitable for application state files. This is useful if you want to restore a workspace, or create save files.
 - `char *XDG_CACHE_HOME()` to retrieve a directory suitable for cache files.
 - `char *XDG_RUNTIME_DIR()` to retrieve a directory suitable for runtime files (pipes, sockets, pid files...)


If an environment variable contains a relative path, the corresponding function returns a NULL pointer and rants about your configuration.

That's a choice I made after falling into the trap of a relative path defaulting to /home/user (which is pretty confusing). It also overrode some files in my home directory in the process (I don't want that to happen to my users).

I prefer a loud fail over a hidden assumption.
