/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/18 20:49:24 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_data *data)
{
	int	i;
	int	a;

	a = 0;
	i = -1;
	while (data->nodes[++i])
		get_fds(data, i);
	if (data->numb_of_pipes == 0)
		single_command(data, 0);
	else if (data->numb_of_pipes != 0 && g_exit_status == 0)
		piperino9(data->nodes, data);
	return (0);
}

char	**resplit_lol(char **split_command)
{
	char	**old_split;
	char	**temp_split_one;
	int		deli;
	int		i;
	char	**new_split;

	if (check_for_only_tab_or_space(split_command[0]) == -1)
		return (NULL);
	old_split = arrdup(split_command);
	temp_split_one = ft_split(ft_strdup(split_command[0]), ' ');
	deli = count_spaces(split_command[0]);
	i = count_commands(split_command);
	new_split = malloc(sizeof(char *) * (i + deli + 1));
	copy_commands(new_split, temp_split_one, old_split);
	return (new_split);
}

void	exec(char *command, char **split_command, t_data *data)
{
	int	pid;
	int	status;

	handle_access(command);
	if (g_exit_status == 126)
		return ;
	pid = fork();
	if (pid == -1)
	{
		handle_fork_error();
		return ;
	}
	if (pid == 0 && g_exit_status == 0)
		execve(command, split_command, data->envp);
	waitpid(pid, &status, 0);
	handle_exit_status(status);
}

void	exec_cmd(char **split_command, t_data *data)
{
	char	*command;
	char	**path;
	int		i;

	path = malloc(sizeof(char *) * 2);
	if (split_command == NULL)
		return ;
	command = find_path(split_command, path, data);
	if (command == NULL)
	{
		free(path);
		printf("%s : Not found, sorry not sorry.\n", split_command[0]);
		g_exit_status = 127;
		return ;
	}
	exec(command, split_command, data);
	free(path);
	free(command);
}
