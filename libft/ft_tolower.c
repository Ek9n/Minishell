/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:58:44 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/09 16:43:52 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_tolower(int c)
{
	if (65 <= c && c <= 90)
		return (c + 32);
	else
		return (c);
}

/*int main()
{
	printf("A: %c\n", ft_tolower('A'));
	printf("a: %c\n", ft_tolower('a'));
	char text[] = "Welcome2C programming !!!\n";
	int i = 0;
	while( text[i] )
	{
    	printf( "%c", ft_tolower(text[i])); 
    	i++;
	}
}*/
