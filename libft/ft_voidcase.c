/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voidcase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:34:40 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/28 19:35:12 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_voidcase(long long int vptr, char *s, int fd, int *counter)
{
	if (!vptr)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	else
	{
		write(1, "0x", 2);
		*counter = (*counter) + 2;
		ft_putnbr_base_fd(vptr, s, fd, counter);
	}
	return (*counter);
}
