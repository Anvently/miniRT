/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:59:47 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:36 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Iterate through list and apply f function to
/// the content of all its element.
/// @param list List's head.
/// @param f Function to apply.
void	ft_lstiter(t_list *list, void (*f)(void *))
{
	if (!f)
		return ;
	while (list)
	{
		(*f)(list->content);
		list = list->next;
	}
}
