/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:50:24 by jfoltan           #+#    #+#             */
/*   Updated: 2024/02/10 19:42:01 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*ptr;

	i = ft_strlen(s) + 1;
	ptr = (char *) malloc(sizeof(char) * i);
	if (!ptr)
		return (NULL);
	ptr = ft_memcpy(ptr, s, i);
	return (ptr);
}
