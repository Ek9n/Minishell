/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:02:52 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/12 20:10:19 by jfoltan          ###   ########.fr       */
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
