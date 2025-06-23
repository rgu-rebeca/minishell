/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:41:35 by rgu               #+#    #+#             */
/*   Updated: 2025/04/07 16:41:35 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst -> content);
	free (lst);
}

/*void	del(void*	content)
{
	printf("del called.\n");
	free(content);
}

int	main(void)
{
	int	*content = (int*)malloc(sizeof(int));

	*content = 42;
	t_list	*node = ft_lstnew(content);
	printf("the node before deletion is:%d\n", *(int*)node ->content);
	ft_lstdelone(node, del);
	printf("deletion done.\n");
	return 0;
}*/