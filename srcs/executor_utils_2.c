/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:51:32 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/11 15:51:33 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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