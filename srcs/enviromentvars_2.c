/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviromentvars_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:08:30 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/10 19:08:34 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cntenv(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

void	freeenv(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	delete_env_var(char *name, char ***env)
{
	int			size;
	char		**new_env;
	int			i;
	int			j;

	size = cntenv(*env);
	new_env = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (env[0][i] != NULL)
	{
		if (ft_strcmp(name, env[0][i]) == 0
			&& (env[0][i][ft_strlen(name)] == '\0'
				|| env[0][i][ft_strlen(name)] == '='))
		{
			free(env[0][i]);
		}
		else
		{
			new_env[j] = env[0][i];
			j++;
		}
		i++;
	}
	free(*env);
	*env = new_env;
}

int	valid_var(char *name)
{
	int		i;

	i = -1;
	while (name[++i])
	{
		if (i == 0 && !(ft_isalpha(name[i]) || name[i] == '_'))
		{
			printf("-minishell: export: '%s': not a valid identifier\n", name);
			return (0);
		}
		else if (i > 0 && name[i] == '=')
			break ;
		else if (i > 0 && !(ft_isalpha(name[i]) || name[i] == '_'
				|| ft_isdigit(name[i])))
		{
			printf("-minishell: export: '%s': not a valid identifier\n", name);
			return (0);
		}
	}
	return (1);
}

void	add_env_var(char *name, char ***env)
{
	int		size;
	int		i;
	char	**new_env;

	size = cntenv(*env) + 1;
	if (valid_var(name))
	{
		new_env = ft_calloc(size + 1, sizeof(char *));
		i = 0;
		while (env[0][i] != NULL)
		{
			new_env[i] = env[0][i];
			i++;
		}
		new_env[i] = ft_strdup(name);
		free(*env);
		*env = new_env;
	}
}