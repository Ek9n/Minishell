/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:51:32 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/14 13:54:49 by jfoltan          ###   ########.fr       */
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

char	*get_command(char **split_command)
{
	if (split_command[0][0] == '/' || (split_command[0][0] == '.'
			&& split_command[0][1] == '/'))
		return (ft_strdup(split_command[0]));
	if (split_command[0][0] == '.' && split_command[0][1] == '.'
		&& split_command[0][2] == '/')
		return (ft_strdup(split_command[0]));
	return (NULL);
}

char	*join_path_and_command(char *path, char *split_command)
{
	char	*command;
	char	*temp;
	command = ft_strjoin(path, "/");
	temp = ft_strjoin(command, split_command);
	free(command);
	return (temp);
}
