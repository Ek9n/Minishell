/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:22:35 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/09 17:51:17 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*s;

	s = (void *) malloc(num * size);
	if (s == NULL)
		return (0);
	else
	{
		ft_bzero(s, num * size);
		return (s);
	}
}
