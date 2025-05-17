#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY  // Add this line before including readline
# define MINISHELL main

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>   // Include readline after the define
# include <readline/history.h>    // history.h comes after readline.h
# include <dirent.h>
# include <libft.h>
# include <parse.h>
# include <functions.h>
# include <sys/wait.h>

#endif
