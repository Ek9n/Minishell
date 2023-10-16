/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:08:06 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/13 15:46:00 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	a;
	char	*b;

	i = 0;
	a = (char) c;
	b = (char *) s;
	while (b[i])
	{
		if (b[i] == a)
			return (&b[i]);
		i++;
	}
	if (b[i] == a)
		return (&b[i]);
	return (0);
}
/*
int main()
{
	char	check[] = "abcdefg";
	char	c = 'c' + 256;

	printf("%s\n", ft_strchr(check, c));
printf("%c\n", c);
}*/
