/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:41:20 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:41:24 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aux;

	aux = *lst;
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (aux -> next)
		aux = aux-> next;
	aux -> next = new;
}

/*void print_list(t_list *head)
{
    while (head)
    {
        printf("%d -> ", *(int*)head-> content);
        head = head->next;
    }
    printf("NULL\n");
}

int main(void)
{
    t_list *head = NULL;
	int a = 1;
	int b = 2;
	int c = 3;
	int	d = 4;
    ft_lstadd_back(&head, ft_lstnew(&a));
	print_list(head);
    ft_lstadd_back(&head, ft_lstnew(&b));
	print_list(head);
    ft_lstadd_back(&head, ft_lstnew(&c));
	print_list(head);
	ft_lstadd_back(&head, ft_lstnew(&d));
    printf("List after adding all the nodes:\n");
    print_list(head);

    return 0;
}*/
