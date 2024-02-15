/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:53:46 by hstein            #+#    #+#             */
/*   Updated: 2024/02/15 14:07:27 by hstein           ###   ########.fr       */
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

static void	cd_endfree(char ***buffer, char **dir)
{
	free(buffer[0][0]);
	free(buffer[0][1]);
	free(buffer[0][2]);
	free(buffer[0]);
	free(dir[0]);
}

static int	cd_prep(t_words *node, char **oldpwd, char **dir)
{
	if (node->num_of_elements > 2)
	{
		ft_putstr_fd("-minishell: cd: too many arguments\n", 1);
		return (EXIT_FAILURE);
	}
	if (node->num_of_elements == 2 && !ft_strcmp(node->split_command[1], ""))
		return (EXIT_SUCCESS);
	*oldpwd = ft_strjoin("OLDPWD=", getpwd());
	if (node->split_command[1] == NULL || \
		ft_strcmp(node->split_command[1], "~") == 0)
		*dir = ft_strdup(getenv("HOME"));
	else
		*dir = ft_strdup(node->split_command[1]);
	if (chdir(*dir) != 0) 
	{
		perror("(cd) No valid pathname");
		free(*dir);
		free(*oldpwd);
		return (EXIT_FAILURE);
	}
	return (99);
}

int	cd(t_words *node, t_data *data)
{
	char	*dir;
	char	*pwd;
	char	*oldpwd;
	char	**buffer;
	int		exit_status;

	exit_status = cd_prep(node, &oldpwd, &dir);
	if (exit_status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (exit_status == 99)
	{
		pwd = ft_strjoin("PWD=", getpwd());
		buffer = calloc(4, sizeof(char *));
		buffer[0] = ft_strdup("export");
		buffer[1] = oldpwd;
		buffer[2] = pwd;
		export(buffer, &data->envp);
		cd_endfree(&buffer, &dir);
	}
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
