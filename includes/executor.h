#ifndef EXECUTOR_H
# define EXECUTOR_H

# define _GNU_SOURCE

# include "minishell.h"


void	executor(char *clean_word, char **envp);

#endif