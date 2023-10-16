/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ui_fd_printf.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:15:35 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/09 20:54:59 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_ui_fd_printf(unsigned int nb, int fd, int *counter)
{
	if (nb >= 10)
	{
		ft_putnbr_fd_printf(nb / 10, fd, counter);
		ft_putnbr_fd_printf(nb % 10, fd, counter);
	}
	else
	{
		(*counter)++;
		ft_putchar_fd_printf(nb + '0', fd);
	}
	return (*counter);
}
/*
int main()
{
	int counter = 0;
    int len = 0;
	len = ft_putnbr_fd_printf(12345678, 1, &counter);
	printf("%d\n", len);
}
*/
