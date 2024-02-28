/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:25:33 by npirard           #+#    #+#             */
/*   Updated: 2024/01/12 10:39:52 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Insert the full list ```from``` after ```node```.
/// Last element of from will point toward node->next.
/// Node->next will point toward first element of from.
/// WARNING : no copy is made. From pointer is set to ```NULL```
/// to avoid unwanted free.
/// @param node Last
/// @param from
/// @return Pointer toward old node->next
t_list	*ft_lstmerge(t_list *node, t_list **from)
{
	t_list	*old_next;

	if (!*from)
		return (node->next);
	ft_lstlast(*from)->next = node->next;
	old_next = node->next;
	node->next = *from;
	*from = NULL;
	return (old_next);
}
