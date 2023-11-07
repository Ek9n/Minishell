#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include "minishell.h"

char	**arrdup(char **enviroment);
void	printenv(char **env);
int		cntenv(char **env);
void	freeenv(char **env);
char	**delete_env_var(char *name, char **env);
char	**add_env_var(char *name, char **env);

#endif
