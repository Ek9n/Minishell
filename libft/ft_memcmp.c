/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:54:28 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/09 22:04:41 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
	char	s1[] = "abcde";
	char	s2[] = "abcde";
	char	s3[] = "ab\3E";
	size_t	n = 3;

	printf("s1, s2: %d\n", ft_memcmp(s1, s2, n));
	printf("s1, s3: %d\n", ft_memcmp(s1, s3, n));
}*/
