/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:51:01 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/14 11:36:37 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	j = dstlen;
	i = 0;
	if (dstlen < size -1 && size > 0)
	{
		while (src[i] && dstlen + i < (size -1))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = 0;
	}
	if (dstlen >= size)
		dstlen = size;
	return (dstlen + srclen);
}
