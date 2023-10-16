/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:20:00 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/23 16:58:47 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
		i++;
	}
	return (dest);
}

/*
if (!src)
		return (dest);
	if (!dest)
		return (0);

int main()
{
	char	target[] = "abcdef";
	char	source[] = "ghijkl";
	size_t	n = 5;

	printf("%s\n", ((char *)ft_memcpy(target, source, n)));
}*/
