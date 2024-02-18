/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piperino_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:56:02 by hstein            #+#    #+#             */
/*   Updated: 2024/02/18 21:28:55 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
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

void	close_prepipes(int *ij, int **pipe_fd)
{
	if (ij[0] != 0)
	{
		close(pipe_fd[ij[0] - 1][0]);
		close(pipe_fd[ij[0] - 1][1]);
	}
	ij[0]++;
}
