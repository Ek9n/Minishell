/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:47:59 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/13 13:54:17 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
if (!dst)
		return (0);
um den no crash test zu bestehen: die erste if-bedingung raus
int main()
{
	char	target1[0xF00];
    char    target2[0xF00];
    char    start[] = "BBBB";
    size_t  n = -6;

	ft_memset(target1, 'A', 20);
	ft_memset(target2, 'A', 20);

    printf("ft_:%zu\n", ft_strlcpy(target1, start, n));
	printf("org:%zu\n", strlcpy(target2, start, n));
    printf("ft_:%s\n", target1);
	printf("org:%s\n", target2);
	if (!memcmp(target1, target2, 20))
		return (printf("success"));
	printf("no success?");
    return (0);
}*/
