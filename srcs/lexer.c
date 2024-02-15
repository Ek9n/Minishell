/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:38:38 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/15 15:34:47 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_space_extender(char **dirty_word)
{
	int		i;
	int		j;
	char	*tmp_word2;
	bool	quotes;
	int		last_quote;

	tmp_word2 = malloc(ft_strlen(*dirty_word) * 2);
	quotes = false;
	last_quote = 0;
	i = 0;
	j = 0;
	while (dirty_word[0][i])
	{
		detect_quote(&dirty_word[0][i], &quotes, &last_quote);
		if (!quotes && redir_case(&dirty_word[0][i]) == 1)
		{
			tmp_word2[j++] = ' ';
			tmp_word2[j++] = dirty_word[0][i++];
			tmp_word2[j++] = ' ';
			detect_quote(&dirty_word[0][i], &quotes, &last_quote);
		}
		else if (!quotes && redir_case(&dirty_word[0][i]) == 2)
		{
			tmp_word2[j++] = ' ';
			tmp_word2[j++] = dirty_word[0][i++];
			tmp_word2[j++] = dirty_word[0][i++];
			tmp_word2[j++] = ' ';
			detect_quote(&dirty_word[0][i], &quotes, &last_quote);
		}
		tmp_word2[j] = dirty_word[0][i];
		j++;
		i++;
	}
	tmp_word2[j] = '\0';
	free(dirty_word[0]);
	dirty_word[0] = ft_strdup(tmp_word2);
	free(tmp_word2);
}

void	clean_spaces_in_command(char **command)
{
	char	*tmp_clean;
	int		i;
	int		j;

	tmp_clean = malloc(ft_strlen(*command) + 1);
	i = 0;
	j = 0;
	i += skip_spaces(*command);
	while (command[0][i] != '\0')
	{
		if (command[0][i] == ' ' || command[0][i] == '\t')
		{
			i += skip_spaces(&command[0][i]);
			tmp_clean[j++] = ' ';
		}
		else
			tmp_clean[j++] = command[0][i++];
	}
	while (tmp_clean[--j] == ' ');

	tmp_clean[j + 1] = '\0';
	free(*command);
	*command = ft_strdup(tmp_clean);
	free(tmp_clean);
}

void	putback_spaces_and_pipes_in_quotes(char **input, t_data *data)
{
	int	i;
	int	j;
	int	quotes;

	quotes = 0;
	i = 0;
	j = 0;
	while (*input && input[0][i] != '\0')
	{
		if (input[0][i] == '\'' && quotes == 0)
			quotes = 1;
		else if (input[0][i] == '\'' && quotes == 1)
			quotes = 0;
		if (input[0][i] == '\"' && quotes == 0)
			quotes = 2;
		else if (input[0][i] == '\"' && quotes == 2)
			quotes = 0;
		if (input[0][i] == '@' && (quotes == 1 || quotes == 2))
			input[0][i] = ' ';
		if (input[0][i] == '&' && (quotes == 1 || quotes == 2))
			input[0][i] = '\t';
		if (input[0][i] == '*' && (quotes == 1 || quotes == 2))
			input[0][i] = '|';
		if (input[0][i] == 26)
			expand_vars(input, i, data);
		i++;
	}
}

void	remove_quotes(char **word)
{
	char	*tmp_clean;
	int		i;
	int		j;
	int		quotes;

	tmp_clean = malloc(ft_strlen(*word) + 1);
	quotes = 0;
	i = 0;
	j = 0;
	while (*word && (*word)[i] != '\0')
	{
		if ((*word)[i] == '\'' && quotes == 0)
			quotes = 1;
		else if ((*word)[i] == '\'' && quotes == 1)
			quotes = 0;
		if ((*word)[i] == '\"' && quotes == 0)
			quotes = 2;
		else if ((*word)[i] == '\"' && quotes == 2)
			quotes = 0;
		else if (!(((*word)[i] == '\'' && quotes != 2) || ((*word)[i] == '\"'
			&& quotes != 1)))
		{
			tmp_clean[j] = (*word)[i];
			j++;
		}
		i++;
	}
	tmp_clean[j] = '\0';
	free(*word);
	*word = ft_strdup(tmp_clean);
	free(tmp_clean);
}

t_words	**init_nodes(char *input, t_data *data)
{
	t_words	**nodes;
	char	**buffer;
	int		i;
	int		a;

	replace_spaces_and_pipes_in_quotes(input);
	redirection_space_extender(&input);
	nodes = ft_calloc(get_num_of_pipes(input) + 2, sizeof(t_words *));
	if (!nodes)
		g_exit_status = 1;
	buffer = ft_split(input, '|');
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
	data->numb_of_pipes = a - 1;
	a = 0;
	free(input);
	while(buffer[a])
	{
		free(buffer[a]);
		a++;
	}
	free(buffer);
	return (nodes);
}
