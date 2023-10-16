/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd_printf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:14:08 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/09 16:14:47 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd_printf(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

/*int main()
{
    ft_putchar_fd('h', 1);
}*/
