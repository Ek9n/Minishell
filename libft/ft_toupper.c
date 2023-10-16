/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:02:49 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/09 16:44:23 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int	ft_toupper(int chr)
{
	if (97 <= chr && chr <= 122)
		return (chr - 32);
	else
		return (chr);
}

/*int	main(int a, char **b)
{
	(void) a;
	printf("%c\n", toupper(*b[1]));
}*/
