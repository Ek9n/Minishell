/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:58:04 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/04 14:05:53 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *) s)[i] = '\0';
		i++;
	}
}

/*int main()
{
	char	test[] = "qwerty";
	size_t	n = 3;

	ft_bzero(test, n);
	printf("%s\n", test);
	printf("%c\n", test[5]);
}*/
