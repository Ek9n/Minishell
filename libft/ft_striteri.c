/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:15 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/12 15:54:46 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*static void	ft_toupper2(unsigned int i, char * chr)
{
	while (chr[i] != '\0')
	{
		if (97 <= chr[i] && chr[i] <= 122)
			chr[i] = chr[i] - 32;
		i++;
	}
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}
/*
int main()
{
	char	test[] = "abcde";

	ft_striteri(test, &ft_toupper2);
	printf("%s\n", test);
}*/
