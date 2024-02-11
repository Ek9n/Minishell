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

#include "ft_savef.h"

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
