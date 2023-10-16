/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:39:36 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/13 16:36:53 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	check(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(set))
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	while (s1[i] != '\0' && check(s1[i], set))
		i++;
	j = ft_strlen(s1) - 1;
	while (check(s1[j], set) && i < j)
		j--;
	res = (char *) malloc((j - i + 2) * sizeof(char));
	if (res == NULL)
		return (0);
	else
		ft_strlcpy(res, s1 + i, (j - i + 2));
	return (res);
}
/*
int main()
{
    char    test[] = "abcccccx         ababa     x ccccbcacbcabab";
    char    weg[] = "abc ";
    char    *res;

    res = ft_strtrim(test, weg);
    printf("%s\n", res);
    free(res);
}*/