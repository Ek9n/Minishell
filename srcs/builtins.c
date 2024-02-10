/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:53:46 by hstein            #+#    #+#             */
/*   Updated: 2024/02/10 19:02:12 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strxcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int	cmp_keywordx(char *keyword, char *str)
{
	int	len;

	len = ft_strlen(keyword) - ft_strlen(str);
	if (len < 0)
		len *= -1;
	if ((ft_strcmp(keyword, str) == 0) && len == 0)
		return (1);
	return (0);
}

int	echo(t_words *node)
{
	char	*tmp;
	char	*word;
	bool	flag;

	flag = false;
	if (node->num_of_elements == 1 && !cmp_keywordx("echo", node->command))
	{
		printf("-minishell.c (echo) %s: command not found\n", node->command);
		return (1);
	}
	tmp = ft_strdup(node->command);
	word = tmp;
	word += 5;
	while (ft_strcmp("-n ", word) == 0)
	{
		flag = true;
		word += 3;
	}
	if (*(word + 3) == '\0' && ft_strcmp("-n", word) == 0)
	{
		flag = true;
		word += 2;
	}
	if (flag)
		ft_putstr_fd(word, 1);
	else
		printf("%s\n", word);
	free(tmp);
	return (0);
}

char	*getpwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("getcwd() error");
		return (NULL);
	}
	return (buf);
}
