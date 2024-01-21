/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:56:02 by hstein            #+#    #+#             */
/*   Updated: 2024/01/21 03:00:45 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	free_peperino(int **pipe_fd, pid_t *pids, int numb_of_pipes)
{
	int	i;

	i = -1;
	while (++i < numb_of_pipes)
		free(pipe_fd[i]);
	free(pipe_fd);
	free(pids);
}

void	close_pipes(int	**pipe_fd, int numb_of_pipes)
{
	int	j;

	j = -1;
	while (++j < numb_of_pipes)
	{
		close(pipe_fd[j][0]);
		close(pipe_fd[j][1]);
	}
}

void	piperino_allocater(t_data *data, int ***pipe_fd, pid_t **pids)
{
	int	i;

	*pids = malloc((data->numb_of_pipes + 1) * sizeof(int));
	*pipe_fd = malloc(data->numb_of_pipes * sizeof(int *));
	i = -1;
	while (++i < data->numb_of_pipes)
	{
		(*pipe_fd)[i] = malloc(2 * sizeof(int));
		if (pipe((*pipe_fd)[i]) == -1)
			error_exit("(piperino6) Pipe creation failed\n");
	}
}

int	piperino9(t_words **nodes, t_data *data)
{
	char	**cmd1;
	char	*path1;
	int		**pipe_fd;
	pid_t	*pids;
	int		i;
	int		j;

	piperino_allocater(data, &pipe_fd, &pids);
	// printf("PIPES:%d\n", data->numb_of_pipes);
	i = 0;
	while (nodes[i] != NULL)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (data->numb_of_pipes > 0)
			{
				// Handle Pipes
				if (i == 0 && nodes[0]->fd_in != STDIN_FILENO)
					dup2(nodes[0]->fd_in, STDIN_FILENO);
				if (i != 0)
					dup2(pipe_fd[i - 1][0], STDIN_FILENO);
				if (i < data->numb_of_pipes)
					dup2(pipe_fd[i][1], STDOUT_FILENO);
				// if (i == data->numb_of_pipes && nodes[i]->fd_out != STDOUT_FILENO)
				// 	dup2(nodes[i]->fd_out, STDOUT_FILENO);

				// // Closing Pipearray:
				close_pipes(pipe_fd, data->numb_of_pipes);
			}
			// Execve:
			single_command(data, i);
			exit(0); // here may we need some function to exit correct
		}
		if (i != 0)
		{
			close(pipe_fd[i - 1][0]);
			close(pipe_fd[i - 1][1]);
		}
		i++;
	}
	close_pipes(pipe_fd, data->numb_of_pipes);
	// Wait for pids (add exitstatus here :)
	j = -1;
	while (++j < i)
	{
		waitpid(pids[j], NULL, 0);
	}
	return (0);
}
