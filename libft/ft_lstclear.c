/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:59:37 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:36 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Delete all element and their content starting from given element.
/// @param list Pointer toward the first element to clear.
/// Pointer is set to NULL.
/// @param del Function used to delete element's content.
void	ft_lstclear(t_list **list, void (*del)(void *))
{
	t_list	*next;

	if (!list)
		return ;
	while (*list)
	{
		next = (*list)->next;
		ft_lstdelone(*list, del);
		*list = next;
	}
}
