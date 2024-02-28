/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:59:55 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:36 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Create a new list where f function was applied to the content of
/// every element from lst.
/// @param lst Source list to work with.
/// @param f Function applied to the content of elements.
/// @param del Function used to delete the content of an element.
/// @return Head of the new list.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	head = ft_lstnew((*f)(lst->content));
	if (!head || !head->content)
	{
		ft_lstclear(&head, del);
		return (NULL);
	}
	current = head;
	lst = lst->next;
	while (lst)
	{
		current->next = ft_lstnew((*f)(lst->content));
		if (!current->next || !current->content)
		{
			ft_lstclear(&head, del);
			break ;
		}
		current = current->next;
		lst = lst->next;
	}
	return (head);
}
