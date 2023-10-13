/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:35:09 by hstein            #+#    #+#             */
/*   Updated: 2023/02/02 21:35:09 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cc -Wall -Wextra -Werror main.c libftprintf.a libft/libft.a && ./a.out

#include "ft_printf.h"

char	*ft_writeline(char **ptr_ret_line, const char *formatstr, va_list *args)
{
	int	i;

	i = 0;
	while (formatstr[i])
	{
		if (formatstr[i] == '%' && formatstr[i + 1] != '\0')
		{
			i++;
			printtype(ptr_ret_line, formatstr[i], args);
		}
		else
			ft_putcharstr(ptr_ret_line, formatstr[i]);
		i++;
	}
	return (*ptr_ret_line);
}

char	*ft_savef(const char *formatstr, ...)
{
	va_list	args;
	char	*ret_line;

	ret_line = ft_strdup("\0");
	if (!ret_line)
		return (0);
	va_start(args, formatstr);
	ret_line = ft_writeline(&ret_line, (const char *)formatstr, &args);
	if (!ret_line)
		return (0);
	va_end(args);
	return (ret_line);
}

/*
int	main(void)
{	
	// ft_printf("I Think About You my Girl\n");
	// printf("%s, %p", NULL, NULL);
	// ft_printf("%s", NULL);
	// printf("%s", NULL);
	// printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	// printf("\n\n");

	int c;
	ft_printf("\nft_printf:\n");
	c = ft_printf("| %c %c %c |", '2', '1', 0);
	printf("\nReturn:%i\n", c);

	ft_printf("\nprintf:\n");
	c = printf("| %c %c %c |", '2', '1', 0);
	printf("\nReturn:%i\n", c);

	// printf("Hal%clo\n", '\0');

	// ft_putchar_fd('H', 1);
	// ft_putchar_fd('\0', 1);
	// ft_putchar_fd('H', 1);


	// ft_printf(" %c %c %c ", '0', 0, '1');


	return (0);
}
*/