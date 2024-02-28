/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:34:24 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:36 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Append new element to list's tail.
/// @param list Address of pointer toward list's head. Can be NULL.
/// @param new Element to append to the list.
void	ft_lstadd_back(t_list **list, t_list *new)
{
	if (!list)
		return ;
	else if (!*list)
		*list = new;
	else
		ft_lstlast(*list)->next = new;
}
