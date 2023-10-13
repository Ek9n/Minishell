/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoltan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:17:45 by jfoltan           #+#    #+#             */
/*   Updated: 2023/10/13 12:44:10 by jfoltan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	puterr(int err)
{
	if (err == ALLOCERR)
		ft_putstr_fd("Memory allocation failed!", 2);
	if (err == SYNERR)
		ft_putstr_fd("Syntax is wrong, Sunny.", 2);
	//ft_putendl_fd(parameter of error which we dont have yet?,2 ),also handle exit function
}