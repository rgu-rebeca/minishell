/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:41:39 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:41:39 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst -> content);
		lst = lst -> next;
	}
}

/*void	f(void *content)
{
	int	*aux;

	aux = (int*) content;
	*aux = *aux + 1;
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
	ft_lstiter(node1, &f);
	print_list(node1);
}*/