/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:41:45 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/15 15:41:30 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_open_fail(t_data *data, int i)
{
	//dup2(data->original_fd_in, STDIN_FILENO);
	//dup2(data->original_fd_out, STDOUT_FILENO);
	//close(data->original_fd_in);
	//close(data->original_fd_out); LEAK_FIXING
	dup2(data->nodes[i]->fd_in, STDIN_FILENO);
	dup2(data->nodes[i]->fd_out, STDOUT_FILENO);
	ft_putstr_fd("open failed\n", 1);
	g_exit_status = 1;
}

void	cleanup(t_data *data, int i, int a, int begin)
{
	while (data->nodes[i]->split_command[a] && begin == 1)
	{
		free(data->nodes[i]->split_command[a]);
		data->nodes[i]->split_command[a] = NULL;
		a++;
	}
	if (begin == 1)
		data->nodes[i]->command = ft_join(data->nodes[i]->split_command);
}

void	init_vars(int *counter, int *a, int *begin)
{
	*counter = 0;
	*a = -1;
	*begin = 0;
}
