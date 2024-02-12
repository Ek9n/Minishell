/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:18 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/12 10:43:23 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_token_syntax(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (str[0] == '|')
			return (1);
		if (str[0] == '<')
			return (2);
		if (str[0] == '>')
			return (3);
	}
	else if (ft_strlen(str) == 2)
	{
		if (str[0] == '<' && str[1] == '<')
			return (4);
		if (str[0] == '>' && str[1] == '>')
			return (5);
	}
	return (0);
}

int	find_char_from_index(char *str, char c, int index)
{
	int	i;

	i = index;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_heredoc(char *delimiter, t_data *data)
{
	char	*line;
	int		fd;
	int		i;
	int		dollar;

	i = 0;
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	line = ft_calloc(1, sizeof(char));
	while (true)
	{
		line = readline("> ");
		if (ft_strchr(line, '$') != NULL)
		{
			dollar = find_char_from_index(line, '$', 0);
			expand_vars(&line, dollar, data);
		}
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
	return (fd);
}

int	is_in_quotes(char *string)
{
	if (string[0] == '\"' && string[ft_strlen(string)] == '\'')
		return (1);
	if (string[0] == '\'' && string[ft_strlen(string)] == '\'')
		return (1);
	return (0);
}

void	get_fds(t_data *data, int i)
{
	int	a;
	int	counter;
	int	begin;

	begin = 0;
	counter = 0;
	a = 0;
	handle_heredoc(data, i);
	while (data->nodes[i]->split_command[a] != NULL)
	{
		if (is_in_quotes(data->nodes[i]->split_command[a]) == 0)
		{
			if (check_token_syntax(data->nodes[i]->split_command[a]) == 3)
				do_output_truncate(data, i, a, &begin);
			else if (check_token_syntax(data->nodes[i]->split_command[a]) == 5)
				do_output_append(data, i, a, &begin);
			else if (check_token_syntax(data->nodes[i]->split_command[a]) == 2)
				do_input(data, i, a, &begin);
			else if (check_token_syntax(data->nodes[i]->split_command[a]) == 4)
				do_heredoc(data, i, a, &begin);
		else if (begin != 1)
			counter++;
		}
		a++;
	}
	a = counter;
	cleanup(data, i, a, begin);
}
