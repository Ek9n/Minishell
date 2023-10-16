/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:17:36 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/28 19:58:02 by sung-hle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "libft.h"

static int	diu(const char *str, va_list args, int i)
{
	int	len;
	int	counter;

	len = 0;
	counter = 0;
	if (str[i + 1] == 'd' || str[i + 1] == 'i')
		len += ft_putnbr_fd_printf(va_arg(args, int), 1, &counter);
	else if (str[i + 1] == 'u')
		len += ft_putnbr_ui_fd_printf(va_arg(args, unsigned int), 1, &counter);
	return (len);
}

static int	xxp(const char *str, va_list args, int i)
{
	int	len;
	int	c;

	len = 0;
	c = 0;
	if (str[i + 1] == 'x')
		len += ft_putnbr_base_fd(va_arg(args, unsigned int), "abcdef", 1, &c);
	else if (str[i + 1] == 'X')
		len += ft_putnbr_base_fd(va_arg(args, unsigned int), "ABCDEF", 1, &c);
	else if (str[i + 1] == 'p')
		len += ft_voidcase(va_arg(args, long long), "abcdef", 1, &c);
	return (len);
}

static int	elseout(const char *str, va_list args, int i)
{
	int	len;

	len = 0;
	if (str[i + 1] == 'd' || str[i + 1] == 'i' || str[i + 1] == 'u')
		len += diu(str, args, i);
	else if (str[i + 1] == 'x' || str[i + 1] == 'X' || str[i + 1] == 'p')
		len += xxp(str, args, i);
	else if (str[i + 1] == 'c')
		len += ft_putchar_fd_printf(va_arg(args, unsigned int), 1);
	else if (str[i + 1] == 's')
		len += ft_putstr_printf_fd(va_arg(args, char *), 1);
	else if (str[i + 1] == '%')
		len += ft_putchar_fd_printf('%', 1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] != '%' && str[i] != '\0')
		{
			len += ft_putchar_fd_printf(str[i], 1);
		}
		else
		{
			len += elseout(str, args, i);
			i++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
/*
int main()
{
	//void *test = -1;
	//unsigned int ui = 42949672951;
	//void	*bla;
	int len1 = 0;
	int len2 = 0;

	len1 = ft_printf(0);
	len2 = printf(0);
	ft_printf("len10ft_: %d\n", len1);
	printf("len20org: %d\n", len2);
	len1 = ft_printf("uft_: %d %d %d %d %d %d %d\n",
	 INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	len2 = printf("uorg: %d %d %d %d %d %d %d\n", 
	INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	len1 =ft_printf("      \n");
	len2=printf("      \n");
	ft_printf("len1ft_: %d\n", len1);
	printf("len2org: %d\n", len2);

	len1= ft_printf("longminuft_: %d\n", LONG_MAX);
	len2 = printf("longmaxuorg: %d\n", LONG_MAX);
	ft_printf("len1ft_: %d\n", len1);
	printf("len2org: %d\n", len2);
	len1 = 0;
	len2 = 0;
	len1= ft_printf("1ft_: %p %p \n", LONG_MIN, LONG_MAX);
	len2 = printf("1org: %p %p \n", LONG_MIN, LONG_MAX);
	ft_printf("ft_: %d\n", len1);
	printf("org: %d\n", len2);
	ft_printf("2ft_: %p %p \n", INT_MIN, INT_MAX);
	printf("2org: %p %p \n", INT_MIN, INT_MAX);
	ft_printf("3ft_: %p %p \n", ULONG_MAX, -ULONG_MAX);
	printf("3org: %p %p \n", ULONG_MAX, -ULONG_MAX);
	
	//printf("%p\n", bla);
}
	unsigned int xZahl = 52;
	
	printf("%x\n", xZahl);
	
	void	*vptr;
	int inte = 187;
	vptr = (void *)&inte;
	
	length = printf("%p\n", vptr);//0x...undnullterminatorwohl
	printf("%d\n", length);
	
	
	int
	length = ft_printf("%d\n", 2147483647);
	ft_printf("length: %d\n", length);
	return (0);
}
void pointer size same as of character, perception dito

xX calculate an unsigned int to hex


counter kann noch zu trouble führen, wenn verschiedentlich aufgerufen*/
