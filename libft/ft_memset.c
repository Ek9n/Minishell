/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:52:00 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/04 13:57:19 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char	*ft_memset(char *target, int value, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		target[i] = (unsigned char) value;
		i++;
	}
	return (target);
}
/*
int main()
{
	char	test[] = "qwerty";
	char	c = 'a';
	size_t	n = 5;

	printf("%s\n", ft_memset(test, c, n));
}*/