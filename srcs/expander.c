/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:51:50 by hstein            #+#    #+#             */
/*   Updated: 2024/02/15 15:34:06 by jfoltan          ###   ########.fr       */
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

int	expand_vars(char **input, int i, t_data *data)
{
	char	*l_m_r[3];
	char	*tmp_var;
	char	*new_str;
	int		cnt;

	tmp_var = NULL;
	l_m_r[0] = NULL;
	l_m_r[1] = NULL;
	l_m_r[2] = NULL;
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
	input[0] = new_str;
	free(l_m_r[0]);
	free(l_m_r[1]);
	return (0);
}

// int	expand_vars(char **input, int i, t_data *data)
// {
// 	char	*l_m_r[3];
// 	char	*tmp_var;
// 	char	*new_str;
// 	int		cnt;

// 	init_expander(i, input, tmp_var, l_m_r);
// 	tmp_var = put_var(input, i + 1, data->envp);
// 	if (tmp_var != NULL)
// 	{
// 		cnt = ft_strchr(tmp_var, '=') - tmp_var + 1;
// 		l_m_r[1] = ft_strdup(ft_strchr(tmp_var, '=') + 1);
// 	}
// 	else
// 	{
// 		cnt = cnt_var(input, i);
// 		if (cnt == 0 && input[0][i + 1] == '?')
// 		{
// 			l_m_r[1] = ft_itoa(data->last_exit_status);
// 			cnt++;
// 		}
// 		else if (cnt == 0)
// 			l_m_r[1] = ft_strdup("$");
// 		else
// 			l_m_r[1] = ft_strdup("");
// 		cnt++;
// 	}
// 	l_m_r[2] = &input[0][i + cnt];
// 	new_str = ft_savef("%s%s%s", l_m_r[0], l_m_r[1], l_m_r[2]);
// 	free(input[0]);
// 	input[0] = new_str;
// 	return (0);
// }