/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:41:54 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:41:55 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst -> next;
	}
	return (size);
}

/*int	main(void)
{
	t_list node1 = {"asd", NULL};
	t_list node2 = {"adsf", NULL};
	t_list node3 = {"jij", NULL};
	node1.next = &node2;
	node2.next = &node3;
	int	size = ft_lstsize(&node1);
	printf("%d\n", size);
}*/