/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sung-hle <sung-hle@42student.berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:55:39 by sung-hle          #+#    #+#             */
/*   Updated: 2022/12/12 17:29:54 by sung-hle         ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst)
		new->next = *lst;
	*lst = new;
}
/*
int main()
{
	struct s_list	*test;
	struct s_list	*danach;
	char	dingstxt[] = "blubb";
	char	danachtxt[] = "dingsdabumms";

	test = ft_lstnew((void *)dingstxt);
	danach = ft_lstnew((void *)danachtxt);
	ft_lstadd_front(&test, danach);
	while (test != NULL)
	{

		printf("%s\n", (char *)test->cont);
		test = test->next;
	}
	free(danach);
	free(test);
}*/
