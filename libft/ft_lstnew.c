/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:26:49 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/13 14:34:45 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (new == NULL)
		return (0);
	else
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}
/*
int main()
{
	//struct s_list	*test;
	t_list *test;
	char	dings[] = "blubb";

	test = ft_lstnew(dings);
	printf("%s\n", (char *)test->cont);
	free(test);
}*/
