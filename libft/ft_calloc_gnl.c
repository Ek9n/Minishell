/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_gnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:52:11 by sung-hle          #+#    #+#             */
/*   Updated: 2023/03/23 17:52:28 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_gnl(size_t size)
{
	void	*s;
	size_t	i;

	i = 0;
	s = (void *) malloc(size);
	if (s == NULL)
		return (0);
	else
	{
		while (i < size)
		{
			((char *) s)[i] = '\0';
			i++;
		}
		return (s);
	}
}
