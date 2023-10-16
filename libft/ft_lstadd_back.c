/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:51:17 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/17 19:34:31 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

/*Function name     ft_lstadd_back
Prototype           void ft_lstadd_back(t_list **lst, t_list *new);
Turn in files -
Parameters lst:     The address of a pointer to the first link of a list.
new:                The address of a pointer to the node to be added to the list.
Return value        None
External functs.    None
Description         Adds the node ’new’ at the end of the list.*/
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

/*lst && */