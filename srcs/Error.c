/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:17:45 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/07 16:30:42 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	puterr(int err)
{
	if (err == ALLOCERR)
		ft_putstr_fd("Memory allocation failed!", 2);
	if (err == SYNERR)
		ft_putstr_fd("Syntax is wrong, Sunny.", 2);
/*
typedef struct t_words
{
	char	*word; //julius Lexer
	int		num_of_elements; //julius Lexer
	int		quotes_case;
	char	*token_after_word; //julius Lexer
 	char 	*output; // Hannes Parser
	char 	**enviroment;
	int		redirection;
}		t_words;
*/
}
void free_and_close_data(t_data *data)
{
	int i;
	int b;
	int pid;

	pid = getpid();
	i = 0;
	b = 0;
	// printf("EXIT_ON_FREE: %d\n", g_exit_status);
	if (data->nodes != NULL)
		while (data->nodes[i])
		{
			free(data->nodes[i]->command);
			free(data->nodes[i]->output);
			if(data->nodes[i]->split_command)
			{
				while (data->nodes[i]->split_command[b])
				{
					free(data->nodes[i]->split_command[b]);
					b++;
				}
			free(data->nodes[i]->split_command);
			close(data->nodes[i]->fd_in);
			close(data->nodes[i]->fd_out);
			}
			if (data->nodes[i])
			{
				free(data->nodes[i]);
				data->nodes[i] = NULL;
			}
			i++;
		unlink(".heredoc"); //I guess here is the best place to do it
		}
	free(data->nodes);
	data->nodes = NULL;
	if (pid == 0 || (g_exit_status == 69))
	{
		close(data->original_fd_in);
		close(data->original_fd_out);
		b = 0;
		while(data->envp[b])
		{
			free(data -> envp[b]);
			b++;
		}
		free(data->envp);
		free(data);
		exit(EXIT_SUCCESS);
	}
}

