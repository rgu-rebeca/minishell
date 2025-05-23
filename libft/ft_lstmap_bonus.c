/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:41:47 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:41:48 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*new_node;
	void	*new_content;

	result = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, new_node);
		lst = lst -> next;
	}
	return (result);
}

/*void	del(void *content)
{
	free(content);
}

void	*f(void *content)
{
	int	*new_value;

	new_value = (int *) malloc(sizeof(int));
	if (!new_value)
		return (NULL);
	*new_value = *(int*)content +20;
	return (new_value);
}

void print_list(t_list *head)
{
    while (head)
    {
        printf("%d -> ", *(int*)head-> content);
        head = head->next;
    }
    printf("NULL\n");
}

int	main(void)
{
	int	*content1 = (int*)malloc(sizeof(int));
	int	*content2 = (int*)malloc(sizeof(int));

	*content1 = 42;
	*content2 = 25;
	t_list	*node1 = ft_lstnew(content1);
	ft_lstadd_back(&node1, ft_lstnew(content2));
	print_list(node1);
	t_list	*result = ft_lstmap(node1, &f, del);
	if (result)
		print_list (result);
	return 0;
}*/