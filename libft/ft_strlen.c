/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:51:18 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/09 16:36:56 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/*int main(int a, char **b)
{
	if (a != 2)
		return (-1);
	else
	{
		printf("%lu\n", strlen(b[1]));
	}
	return (0);
}*/
