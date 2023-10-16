/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:37:45 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/13 14:27:14 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	i = 0;
	res = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!s || !f || res == NULL)
		return (0);
	while (s[i] != '\0')
	{
		res[i] = f(i, ((char *)s)[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

/*if (!f)
		return ((char *) s);
		rausgenommen, weil successive application.
		 kein f, keine successive app*/