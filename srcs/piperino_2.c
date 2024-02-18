/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piperino_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:56:02 by hstein            #+#    #+#             */
/*   Updated: 2024/02/18 21:29:58 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_int_array(int **arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(arr[i]);
	free(arr);
}

void	init_piperino(t_data *data, int ***pipe_fd, pid_t **pids)
{
	int	i;

	*pids = malloc((data->numb_of_pipes + 1) * sizeof(int));
	*pipe_fd = malloc(data->numb_of_pipes * sizeof(int *));
	i = -1;
	while (++i < data->numb_of_pipes)
	{
		(*pipe_fd)[i] = malloc(2 * sizeof(int));
		if (pipe((*pipe_fd)[i]) == -1)
			error_exit("(piperino) Pipe creation failed\n");
	}
}

void	terminate_piperino(int *ij, int **pipe_fd, pid_t *pids, t_data *data)
{
	close_pipes(pipe_fd, data->numb_of_pipes);
	free_int_array(pipe_fd, data->numb_of_pipes);
	ij[1] = -1;
	while (++ij[1] < ij[0])
	{
		waitpid(pids[ij[1]], NULL, 0);
	}
	free(pids);
}

void	handle_cases(int *ij, int **pipe_fd, t_data *data)
{
	if (data->numb_of_pipes > 0)
	{
		if (ij[0] == 0 && data->nodes[0]->fd_in != STDIN_FILENO)
			dup2(data->nodes[0]->fd_in, STDIN_FILENO);
		if (ij[0] > 0)
			dup2(pipe_fd[ij[0] - 1][0], STDIN_FILENO);
		if (ij[0] == data->numb_of_pipes && \
				data->nodes[ij[0]]->fd_in != STDIN_FILENO)
			dup2(data->nodes[ij[0]]->fd_in, STDIN_FILENO);
		if (ij[0] == data->numb_of_pipes - 1 && \
				data->nodes[ij[0]]->fd_out != STDOUT_FILENO)
			dup2(data->nodes[ij[0]]->fd_out, STDOUT_FILENO);
		else if (ij[0] == data->numb_of_pipes && \
			data->nodes[ij[0] - 1]->fd_out != STDOUT_FILENO)
		{
			if (data->nodes[ij[0]]->fd_out == STDOUT_FILENO)
				dup2(data->original_fd_out, STDOUT_FILENO);
			else
				dup2(data->nodes[ij[0]]->fd_out, STDOUT_FILENO);
		}
		else
			if (ij[0] < data->numb_of_pipes)
				dup2(pipe_fd[ij[0]][1], STDOUT_FILENO);
		close_pipes(pipe_fd, data->numb_of_pipes);
	}
}

int	piperino9(t_words **nodes, t_data *data)
{
	int		**pipe_fd;
	pid_t	*pids;
	int		ij[2];

	init_piperino(data, &pipe_fd, &pids);
	ij[0] = 0;
	while (nodes[ij[0]] != NULL)
	{
		pids[ij[0]] = fork();
		if (pids[ij[0]] == 0)
		{
			handle_cases(ij, pipe_fd, data);
			single_command(data, ij[0]);
			free_int_array(pipe_fd, data->numb_of_pipes);
			free(pids);
			free_and_close_data(data);
			exit(0);
		}
		close_prepipes(ij, pipe_fd);
	}
	terminate_piperino(ij, pipe_fd, pids, data);
	return (0);
}
