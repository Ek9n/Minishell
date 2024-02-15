/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:06:21 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/15 15:34:29 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_num_of_pipes(char *str)
{
	int	i;
	int	a;

	a = 0;
	i = 0;
	while (str[a])
	{
		if (str[a] == '|')
			i++;
		a++;
	}
	return (i);
}

char	*comb_extd_word(char **extd_words)
{
	char	*tmp_word;
	char	*comb_word;
	int		i;

	tmp_word = NULL;
	comb_word = NULL;
	i = 0;
	while (extd_words[i])
	{
		if (i == 0)
			comb_word = ft_strdup("");
		tmp_word = ft_strjoin(comb_word, extd_words[i]);
		free(comb_word);
		comb_word = tmp_word;
		i++;
	}
	return (comb_word);
}

int	redir_case(char *c)
{
	if ((*c == '<' && *(c + 1) == '<') || (*c == '>' && *(c + 1) == '>'))
		return (2);
	else if (*c == '<' || *c == '>')
		return (1);
	return (0);
}

void	detect_quote(char *dirty_word, bool *quotes, int *last_quote)
{
	if (*quotes == false && (dirty_word[0] == '\'' || dirty_word[0] == '\"'))
	{
		*quotes = true;
		if (dirty_word[0] == '\'')
			*last_quote = 1;
		else if (dirty_word[0] == '\"')
			*last_quote = 2;
	}
	else if (*quotes == true && *last_quote == 1 && dirty_word[0] == '\'')
	{
		*quotes = false;
		*last_quote = 0;
	}
	else if (*quotes == true && *last_quote == 2 && dirty_word[0] == '\"')
	{
		*quotes = false;
		*last_quote = 0;
	}
}
