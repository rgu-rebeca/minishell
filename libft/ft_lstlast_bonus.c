/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:41:43 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:41:44 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

/*void	print_lst(t_list *lst)
{
	while(lst)
	{
		printf("%d->", *(int *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}
int	main(void)
{
	int	a = 1;
	int	b = 2;
	int	c = 3;
	t_list node1 = {&a, NULL};
	t_list node2 = {&b, NULL};
	t_list node3 = {&c, NULL};

	node1.next = &node2;
	node2.next = &node3;
	print_lst(&node1);
	t_list *result = ft_lstlast(&node1);
	print_lst(result);
}*/
