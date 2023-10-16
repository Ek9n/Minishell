/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:33:35 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/13 16:03:01 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

// #include <bsd/string.h>
// #include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(dst);
	i = 0;
	if (len > size)
		return (ft_strlen(src) + size);
	else
	{
		while (len + i + 1 < size && src[i] != '\0')
		{
			dst[len + i] = src[i];
			i++;
		}
		dst[len + i] = '\0';
		return (len + ft_strlen(src));
	}
}
/*
int main()
{
    char    target1[] = "abcde";
	char	target2[] = "abcde";
    char    source[] = "fghij";
    size_t  n = 3;

    printf("ft_: %lu\n", ft_strlcat(target1, source, n));
	printf("org: %lu\n", strlcat(target2, source, n));
    printf("t1: %s\n", target1);
	printf("t2: %s\n", target2);
}*/
