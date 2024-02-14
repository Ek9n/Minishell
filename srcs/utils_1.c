/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:44:47 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/12 19:44:47 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;

	if (!s1 || !s2)
		return (-1);
	n = ft_strlen(s1);
	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	print_nodes(t_words **nodes)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (nodes[i])
	{
		printf("command at pos %i: %s\n", i, nodes[i]->command);
		while (nodes[i]->split_command[a])
		{
			printf("split_command at node %i, pos %i: %s\n", i, a,
				nodes[i]->split_command[a]);
			a++;
		}
		i++;
	}
}

char	*ft_join(char **arr)
{
	char	*str;
	int		i;
	int		total_length;
	size_t	current_length;

	i = -1;
	total_length = 0;
	current_length = 0;
	while (arr[++i] != NULL)
		total_length += ft_strlen(arr[i]);
	str = ft_calloc(total_length + i + 2, sizeof(char));
	i = -1;
	while (arr[++i] != NULL)
	{
		if (arr[i][0] != 6)
		{
			if (arr[i][0] == '\0')
				arr[i] = ft_strdup(" ");
			current_length += ft_strlcat(str, arr[i], total_length + i + 2);
			if (arr[i + 1] && arr[i + 1][0] != '\0')
				current_length += ft_strlcat(str, " ", total_length + i + 2);
		}
	}
	return (str);
}
void free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}