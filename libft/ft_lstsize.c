/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:51:40 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/13 20:57:21 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
/*
int main()
{
	t_list	*a, *b, *c, *d;
	char aa[] = "aaa";
	char bb[] = "bbb";
	char cc[] = "ccc";
	char dd[] = "ddd";
	int	size;

	a = ft_lstnew(aa);
	b = ft_lstnew(bb);
	c = ft_lstnew(cc);
	d = ft_lstnew(dd);
	ft_lstadd_back(&a, ft_lstnew(b));
	ft_lstadd_back(&a, ft_lstnew(c));
	ft_lstadd_back(&a, ft_lstnew(d));
	
	printf("%d\n", ft_lstsize(a));
	return (0);
}*/