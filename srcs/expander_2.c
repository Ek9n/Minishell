/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:51:50 by hstein            #+#    #+#             */
/*   Updated: 2024/02/18 21:12:17 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	build_str(char **input, char **l_m_r, int i, t_data *data)
{
	int	cnt;

	cnt = cnt_var(input, i);
	if (cnt == 0 && input[0][i + 1] == '?')
	{
		l_m_r[1] = ft_itoa(data->last_exit_status);
		cnt++;
	}
	else if (cnt == 0)
		l_m_r[1] = ft_strdup("$");
	else
		l_m_r[1] = ft_strdup("");
	cnt++;
	return (cnt);
}

static void	expander_setnull(char **tmp_var, char **l_m_r)
{
	*tmp_var = NULL;
	l_m_r[0] = NULL;
	l_m_r[1] = NULL;
	l_m_r[2] = NULL;
}

int	expand_vars(char **input, int i, t_data *data)
{
	char	*l_m_r[3];
	char	*tmp_var;
	char	*new_str;
	int		cnt;

	expander_setnull(&tmp_var, l_m_r);
	l_m_r[0] = ft_strdup(input[0]);
	l_m_r[0][i] = '\0';
	tmp_var = put_var(input, i + 1, data->envp);
	if (tmp_var != NULL)
	{
		cnt = ft_strchr(tmp_var, '=') - tmp_var + 1;
		l_m_r[1] = ft_strdup(ft_strchr(tmp_var, '=') + 1);
	}
	else
		cnt = build_str(input, l_m_r, i, data);
	l_m_r[2] = &input[0][i + cnt];
	new_str = ft_savef("%s%s%s", l_m_r[0], l_m_r[1], l_m_r[2]);
	free(input[0]);
	input[0] = new_str;
	free(l_m_r[0]);
	free(l_m_r[1]);
	return (0);
}
