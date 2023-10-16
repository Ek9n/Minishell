/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:33:39 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/13 14:28:19 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nlen(int n)
{
	size_t	counter;

	counter = 1;
	if (n < 0)
	{
		n *= -1;
		counter++;
	}
	while (n >= 10)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

static char	*fillres(char *res, int n, size_t counter, size_t i)
{
	if (n < 0)
	{
		res[i] = '-';
		n *= -1;
		i++;
	}
	res[counter] = '\0';
	while (i < counter)
	{
		res[counter - 1] = n % 10 + '0';
		n /= 10;
		counter--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	size_t		i;
	size_t		counter;
	char		*res;

	counter = nlen(n);
	if (n == -2147483648)
		counter = 11;
	i = 0;
	res = (char *)malloc((counter + 1) * sizeof(char));
	if (res == NULL)
		return (0);
	if (n == -2147483648)
	{
		res[0] = '-';
		res[1] = '2';
		res = fillres(res, 147483648, 11, 2);
	}
	else
		res = fillres(res, n, counter, i);
	return (res);
}
/*
int main(int a, char **b)
{
	char	*test;
       
	(void) a;
	test = ft_itoa(ft_atoi(b[1]));
	printf("%s\n", test);
	free(test);
}*/
