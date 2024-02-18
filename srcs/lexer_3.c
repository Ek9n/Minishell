/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:38:38 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/18 01:55:59 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_check_conditions(char *input, char *tmp_clean, int i, int *j)
{
	int		quotes;

	quotes = 0;
	if (input[i] == '\'' && quotes == 0)
		quotes = 1;
	else if (input[i] == '\'' && quotes == 1)
		quotes = 0;
	if (input[i] == '\"' && quotes == 0)
		quotes = 2;
	else if (input[i] == '\"' && quotes == 2)
		quotes = 0;
	else if (!((input[i] == '\'' && quotes != 2) || (input[i] == '\"' \
		&& quotes != 1)))
	{
		tmp_clean[*j] = input[i];
		(*j)++;
	}
}

void	remove_quotes(char **word)
{
	char	*tmp_clean;
	int		i;
	int		j;

	tmp_clean = malloc(ft_strlen(*word) + 1);
	i = 0;
	j = 0;
	while (*word && (*word)[i] != '\0')
	{
		remove_check_conditions(*word, tmp_clean, i, &j);
		i++;
	}
	tmp_clean[j] = '\0';
	free(*word);
	*word = ft_strdup(tmp_clean);
	free(tmp_clean);
}

int	routine(t_data *data, t_words **nodes, int i)
{
	int	a;

	a = 0;
	while (nodes[a] && nodes[a]->command)
	{
		nodes[a]->split_command = ft_split(nodes[a]->command, ' ');
		i = -1;
		while (nodes[a]->split_command[++i])
		{
			putback_spaces_and_pipes_in_quotes(&nodes[a]->split_command[i],
				data);
			remove_quotes(&nodes[a]->split_command[i]);
		}
		nodes[a]->num_of_elements = i;
		putback_spaces_and_pipes_in_quotes(&nodes[a]->command, data);
		remove_quotes(&nodes[a]->command);
		nodes[a]->fd_in = dup2(data->original_fd_in, STDIN_FILENO);
		nodes[a]->fd_out = dup2(data->original_fd_out, STDOUT_FILENO);
		a++;
	}
	return (a);
}

t_words	**init_nodes(char *input, t_data *data)
{
	t_words	**nodes;
	char	**buffer;
	int		i;
	int		a;

	replace_spaces_and_pipes_in_quotes(input);
	// redirection_space_extender(&input);
	char *input2 = NULL;
	input2 = redirection_space_extender(input);
	if (input2)
	{
		nodes = ft_calloc(get_num_of_pipes(input2) + 2, sizeof(t_words *));
		if (!nodes)
			g_exit_status = 1;
		buffer = ft_split(input2, '|');
		a = 0;
		i = 0;
		while (buffer[i] != NULL)
		{
			nodes[a] = ft_calloc(1, sizeof(t_words));
			nodes[a]->command = ft_strdup(buffer[i]);
			clean_spaces_in_command(&nodes[a]->command);
			a++;
			i++;
		}
		a = routine(data, nodes, i);
		data->numb_of_pipes = a - 1;
		a = 0;
		return (nodes);
	}
	return (NULL);
}
