/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:51:50 by hstein            #+#    #+#             */
/*   Updated: 2024/02/18 21:11:42 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_var(char *str, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp(str, envp[i]) == 0 && \
			(envp[i][ft_strlen(str)] == '\0' || envp[i][ft_strlen(str)] == '='))
			return (i);
		i++;
	}
	return (-1);
}

char	*put_var(char **str, int dollar_pos, char **envp)
{
	char	*tmp;
	int		var_idx;
	int		i;
	int		j;

	tmp = malloc(ft_strlen(*str));
	i = dollar_pos;
	j = 0;
	while ((ft_isalpha(str[0][i]) || str[0][i] == '_') && str[0][i] != 26)
	{
		tmp[j] = str[0][i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	var_idx = find_var(tmp, envp);
	free(tmp);
	if (var_idx != -1)
		tmp = envp[var_idx];
	else
		tmp = NULL;
	return (tmp);
}

int	cnt_var(char **str, int dollar_pos)
{
	int	i;
	int	j;

	i = dollar_pos + 1;
	j = 0;
	while ((ft_isalpha(str[0][i]) || str[0][i] == '_') && str[0][i] != 26)
	{
		j++;
		i++;
	}
	return (j);
}
