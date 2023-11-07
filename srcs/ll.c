#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

typedef struct t_list
{
	char	*str;
	size_t	next;
} list;

void	list_print(t_list *head)
{
	if (head != NULL)
	{
		printf("%s", (char *)head->content);
		head = head->next;
		list_print(head);
	}
}

void	list_add(t_list *head)
{
	while (head->next != NULL)
		head = head->next;
	printf("hohoh\n");
}

int	main()
{


	t_list	*head;

	head = ft_lstnew("hi");
	// printf("%s\n", (char *)head->content);

	list_print(head);
	list_add(head);
	// printf("hohoh\n");
	// lstadd_back(t_list **lst, t_list *new)


	return (0);
}