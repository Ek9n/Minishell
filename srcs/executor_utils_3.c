/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:15:51 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/18 19:17:32 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_spaces(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ' ')
			count++;
		str++;
	}
	return (count);
}

int	count_commands(char **split_command)
{
	int	count;

	count = 0;
	while (split_command[count])
		count++;
	return (count);
}

void	copy_commands(char **new_split, char **temp_split_one, char **old_split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp_split_one[j])
		new_split[i++] = ft_strdup(temp_split_one[j++]);
	j = 1;
	while (old_split[j])
		new_split[i++] = ft_strdup(old_split[j++]);
	new_split[i] = NULL;
}

char	*find_path(char **split_command, char **path, t_data *data)
{
	char	*command;
	int		i;
	char 	*temp_path;
	
	i = 0;
	if (get_command(split_command))
			return(ft_strdup(split_command[0]));
	temp_path = ft_strdup("$PATH");
	expand_vars(&temp_path, 0, data);
	path = ft_split(temp_path, ':');
	free(temp_path);
	while (path[i])
	{
		temp_path = ft_strjoin(path[i], "/");
		command = ft_strjoin(temp_path, split_command[0]);
		free(temp_path);
		if (access(command, F_OK) == 0)
			break ;
		free(command);
		command = NULL;
		i++;
	}
	free_arr(path);
	return (command);
}
