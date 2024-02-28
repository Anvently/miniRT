/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:13:22 by npirard           #+#    #+#             */
/*   Updated: 2024/01/18 14:00:58 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Remove any element of the list where f(el) is 1.
/// @param lst List's head
/// @param f
/// @param del
void	ft_lstdelif(t_list **lst, int (*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	if ((*f)(*lst))
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
	node = *lst;
	while (node && node->next)
	{
		if ((*f)(node->next))
		{
			next = node->next->next;
			ft_lstdelone(node->next, del);
			node->next = next;
		}
		else
			node = node->next;
	}
}
