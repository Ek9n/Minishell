/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:17:45 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/13 16:56:15 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	puterr(int err)
{
	if (err == ALLOCERR)
		ft_putstr_fd("Memory allocation failed!", 2);
	if (err == SYNERR)
		ft_putstr_fd("Syntax is wrong, Sunny.", 2);
}

void	free_split_commands(t_words *nodes)
{
	int		b;

	b = -1;
	while (nodes->split_command[++b])
		free(nodes->split_command[b]);
	free(nodes->split_command);
	close(nodes->fd_in);
	close(nodes->fd_out);
}

void	kill_the_child(t_data *data)
{
	int		b;

	b = -1;
	close(data->original_fd_in);
	close(data->original_fd_out);
	while (data->envp[++b])
		free(data -> envp[b]);
	free(data->envp);
	free(data);
	exit(EXIT_SUCCESS);
}

void	free_and_close_data(t_data *data)
{
	int		i;
	int		b;
	int		pid;

	pid = getpid();
	i = -1;
	b = -1;
	if (data->nodes != NULL)
	{
		while (data->nodes[++i])
		{
			free(data->nodes[i]->command);
			free(data->nodes[i]->output);
			if (data->nodes[i]->split_command)
				free_split_commands(data->nodes[i]);
			free(data->nodes[i]);
		}
	}
	unlink(".heredoc");
	free(data->nodes);
	data->nodes = NULL;
	if (pid == 0 || (g_exit_status == 69))
		kill_the_child(data);
}
