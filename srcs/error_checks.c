/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:09:18 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/10 19:09:53 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_input(char *str)
{
	if (quote_error(str))
		return (0);
	return (1);
}

int	quote_error(char *str)
{
	int		i;
	int		quote;

	quote = 0;
	i = -1;
	while (str[++i])
	{
		if ((quote == 1 && str[i] == '\'') || (quote == 2 && str[i] == '\"'))
			quote = 0;
		else if (quote != 2 && str[i] == '\'')
			quote = 1;
		else if (quote != 1 && str[i] == '\"')
			quote = 2;
	}
	if (quote != 0)
	{
		printf("(quote_error) problem in inputstr!\n");
		return (1);
	}
	return (0);
}
