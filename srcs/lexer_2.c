/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:38:38 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/13 23:54:12 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_check_conditions(char *input, int i)
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
	if (input[i] == ' ' && (quotes == 1 || quotes == 2))
		input[i] = '@';
	if (input[i] == '\t' && (quotes == 1 || quotes == 2))
		input[i] = '&';
	if (input[i] == '|' && (quotes == 1 || quotes == 2))
		input[i] = '*';
	if (input[i] == '$' && quotes != 1)
		input[i] = 26;
}

void	replace_spaces_and_pipes_in_quotes(char *input)
{
	int		quotes;
	int		i;

	quotes = 0;
	i = 0;
	while (input[i] != '\0')
	{
		replace_check_conditions(input, i);
		i++;
	}
}

static void	putback_check_conditions(char *input, int i)
{
	int	quotes;

	quotes = 0;
	if (input[i] == '\'' && quotes == 0)
		quotes = 1;
	else if (input[i] == '\'' && quotes == 1)
		quotes = 0;
	if (input[i] == '\"' && quotes == 0)
		quotes = 2;
	else if (input[i] == '\"' && quotes == 2)
		quotes = 0;
	if (input[i] == '@' && (quotes == 1 || quotes == 2))
		input[i] = ' ';
	if (input[i] == '&' && (quotes == 1 || quotes == 2))
		input[i] = '\t';
	if (input[i] == '*' && (quotes == 1 || quotes == 2))
		input[i] = '|';
}

void	putback_spaces_and_pipes_in_quotes(char **input, t_data *data)
{
	int	i;

	i = 0;
	while (*input && input[0][i] != '\0')
	{
		putback_check_conditions(*input, i);
		i++;
	}
	i = 0;
	while (*input && input[0][i] != '\0')
	{
		if (input[0][i] == 26)
			expand_vars(input, i, data);
		i++;
	}
}
