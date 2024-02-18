/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:21:45 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/18 21:29:34 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_data *data, int i)
{
	int	a;

	a = 0;
	while (data->nodes[i]->split_command[a])
	{
		if (is_in_quotes(data->nodes[i]->split_command[a]) == 0)
		{
			if (check_token_syntax(data->nodes[i]->split_command[a]) == 4)
			{
				ft_heredoc(data->nodes[i]->split_command[a + 1], data);
				break ;
			}
		}
		a++;
	}
}

void	do_output_truncate(t_data *data, int i, int a, int *begin)
{
	data->nodes[i]->fd_out = open(data->nodes[i]->split_command[a + 1],
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->nodes[i]->fd_out == -1)
		handle_open_fail(data, i);
	*begin = 1;
	dup2(data->nodes[i]->fd_out, STDOUT_FILENO);
}

void	do_output_append(t_data *data, int i, int a, int *begin)
{
	data->nodes[i]->fd_out = open(data->nodes[i]->split_command[a + 1],
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (data->nodes[i]->fd_out == -1)
		handle_open_fail(data, i);
	*begin = 1;
	dup2(data->nodes[i]->fd_out, STDOUT_FILENO);
}

void	do_input(t_data *data, int i, int a, int *begin)
{
	data->nodes[i]->fd_in = open(data->nodes[i]->split_command[a + 1],
			O_RDONLY);
	if (data->nodes[i]->fd_in == -1)
		handle_open_fail(data, i);
	*begin = 1;
	dup2(data->nodes[i]->fd_in, STDIN_FILENO);
}

void	do_heredoc(t_data *data, int i, int *begin)
{
	data->nodes[i]->fd_in = open(".heredoc", O_RDONLY);
	if (data->nodes[i]->fd_in == -1)
		handle_open_fail(data, i);
	*begin = 1;
	dup2(data->nodes[i]->fd_in, STDIN_FILENO);
}
