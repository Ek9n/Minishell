/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:53:46 by hstein            #+#    #+#             */
/*   Updated: 2024/02/12 20:10:53 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo(t_words *node)
{
	char	*tmp;
	char	*word;
	bool	flag;

	flag = false;
	tmp = ft_strdup(node->command);
	word = tmp;
	word += 5;
	while (ft_strcmp("-n ", word) == 0)
	{
		flag = true;
		word += 3;
	}
	if (*(word + 3) == '\0' && ft_strcmp("-n", word) == 0)
	{
		flag = true;
		word += 2;
	}
	if (flag)
		ft_putstr_fd(word, 1);
	else
		printf("%s\n", word);
	free(tmp);
	return (0);
}

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
	if (node->split_command[1] == NULL || \
		ft_strcmp(node->split_command[1], "~") == 0)
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
	pid_t	p;
	char	*ls_argv[3];

	ls_argv[0] = "ls";
	ls_argv[1] = dir;
	ls_argv[2] = NULL;
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
	int	i;

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
