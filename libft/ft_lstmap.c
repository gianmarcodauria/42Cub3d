/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gd-auria <gd-auria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:12:43 by gd-auria          #+#    #+#             */
/*   Updated: 2025/04/23 16:12:45 by gd-auria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_head;

	if (!lst || !f || !del)
		return (NULL);
	new_node = ft_lstnew(f(lst -> content));
	new_head = new_node;
	while (lst -> next)
	{
		lst = lst -> next;
		if (!(lst -> content))
			del(lst -> content);
		new_node -> next = ft_lstnew(f(lst -> content));
		if (!new_node -> next)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		new_node = new_node -> next;
	}
	return (new_head);
}
