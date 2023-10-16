/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:30:13 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/09 21:59:41 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

// #include <bsd/string.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *) malloc ((len + 1) * sizeof(char));
	if (joined == NULL)
		return (joined);
	else
	{
		ft_strlcpy(joined, s1, ft_strlen(s1) + 1);
		ft_strlcat(joined, s2, len + 1);
		return (joined);
	}
}
/*
int main()
{
	char	target[] = "abcde";
	char	source[] = "fghij";
	char	*res;

	res = ft_strjoin(target, source);
	printf("%s\n", res);
	free(res);
	return (0);
}*/