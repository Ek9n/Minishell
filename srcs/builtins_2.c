/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:02:52 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/10 19:02:56 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd(t_words *node, t_data *data)
{
	char	*dir;
	char	*pwd;
	char	*oldpwd;
	char	**buffer;
	int		i;

	if (node->num_of_elements > 2)
	{
		ft_putstr_fd("-minishell: cd: too many arguments\n", 1);
		return (EXIT_FAILURE);
	}
	if (node->num_of_elements == 2 && !ft_strcmp(node->split_command[1], ""))
		return (EXIT_SUCCESS);
	oldpwd = ft_strjoin("OLDPWD=", getpwd());
	if (node->split_command[1] == NULL || ft_strcmp(node->split_command[1],
			"~") == 0)
		dir = ft_strdup(getenv("HOME"));
	else
		dir = ft_strdup(node->split_command[1]);
	if (chdir(dir) != 0)
	{
		perror("(cd) No valid pathname");
		free(dir);
		free(oldpwd);
		i = -1;
		return (EXIT_FAILURE);
	}
	pwd = ft_strjoin("PWD=", getpwd());
	buffer = calloc(4, sizeof(char *));
	buffer[0] = ft_strdup("export");
	buffer[1] = oldpwd;
	buffer[2] = pwd;
	export(buffer, &data->envp);
	free(buffer[0]);
	free(buffer[1]);
	free(buffer[2]);
	free(buffer);
	free(dir);
	return (EXIT_SUCCESS);
}

int	ls(char *dir)
{
	pid_t		p;
	char		*ls_argv[] = {"ls", dir, NULL};

	p = fork();
	if (p < 0)
	{
		perror("fork fail");
		exit(1);
	}
	if (p == 0)
	{
		execv("/bin/ls", ls_argv);
		perror("execv failed");
		exit(1);
	}
	return (0);
}

void	unset(char **split_cmds, char ***env)
{
	int		i;

	i = 1;
	while (split_cmds[i])
	{
		delete_env_var(split_cmds[i], env);
		i++;
	}
}

void	export(char **split_cmds, char ***env)
{
	int		i;

	if (split_cmds[1] == NULL)
	{
		i = 0;
		while (env[0][i] != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env[0][i], 1);
			printf("\n");
			i++;
		}
	}
	else
	{
		i = 1;
		while (split_cmds[i])
		{
			purge_arr(split_cmds[i], env);
			add_env_var(split_cmds[i], env);
			i++;
		}
	}
}
