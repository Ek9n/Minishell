/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:40:26 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/11 15:50:48 by jfoltan          ###   ########.fr       */
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

int	count_spaces(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ' ')
			count++;
		str++;
	}
	return (count);
}

int	count_commands(char **split_command)
{
	int	count;

	count = 0;
	while (split_command[count])
		count++;
	return (count);
}

void	copy_commands(char **new_split, char **temp_split_one, char **old_split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp_split_one[j])
		new_split[i++] = ft_strdup(temp_split_one[j++]);
	j = 1;
	while (old_split[j])
		new_split[i++] = ft_strdup(old_split[j++]);
	new_split[i] = NULL;
}

char	**fix_me(char **split_command)
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

void	handle_access(char *command)
{
	if (access(command, X_OK))
	{
		g_exit_status = 126;
		printf("Permission denied\n");
	}
}

void	handle_fork_error(void)
{
	g_exit_status = 1;
	perror("fork error");
}

void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 130 + WIFSIGNALED(status);
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

char	*get_command(char *split_command)
{
	if (split_command[0] == '/' || (split_command[0] == '.'
			&& split_command[0][1] == '/'))
		return (ft_strdup(split_command));
	if (split_command[0] == '.' && split_command[0][1] == '.'
		&& split_command[0][2] == '/')
		return (ft_strdup(split_command));
	return (NULL);
}

char	*join_path_and_command(char *path, char *split_command)
{
	char	*command;

	command = ft_strjoin(path, "/");
	return (ft_strjoin(command, split_command));
}

char	*find_path(char **split_command, char **path, t_data *data)
{
	char	*command;
	int		i;
	char	*temp_command;

	command = ft_strdup(split_command[0]);
	path[0] = ft_strdup("$PATH");
	path[1] = ft_strdup("\0");
	expand_vars(path, 0, data);
	path = ft_split(path[0], ':');
	i = 0;
	while (path[i])
	{
		temp_command = get_command(split_command[0]);
		if (temp_command)
		{
			command = temp_command;
			break ;
		}
		command = join_path_and_command(path[i], split_command[0]);
		if (access(command, F_OK) == 0)
			break ;
		i++;
	}
	return (command);
}

void	exec_cmd(char **split_command, t_data *data)
{
	char	*command;
	char	**path;
	int		i;

	path = malloc(sizeof(char *) * 2);
	if (ft_strchr(split_command[0], ' '))
		split_command = FIX_ME(split_command);
	if (split_command == NULL)
		return ;
	command = find_path(command, path, data);
	if (access(command, F_OK) == 0)
		exec(command, split_command, data);
	else
	{
		printf("%s : No such file or directory\n", split_command[0]);
		g_exit_status = 127;
	}
	if (command)
		free(command);
}
