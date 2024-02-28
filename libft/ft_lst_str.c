/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:42:54 by npirard           #+#    #+#             */
/*   Updated: 2024/01/18 14:53:47 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Append a string to a list of string.
/// @param lst
/// @param str
/// @return ```0``` for success.
/// ```-1``` if allocation error, list is freed.
int	ft_lst_str_append(t_list **lst, char *str)
{
	t_list	*node;
	char	*content;

	content = ft_strdup(str);
	if (!content)
	{
		ft_lstclear(lst, free);
		return (-1);
	}
	node = ft_lstnew(content);
	if (!node)
	{
		free(content);
		ft_lstclear(lst, free);
		return (-1);
	}
	ft_lstadd_back(lst, node);
	return (0);
}

void	ft_lst_str_print(t_list *lst)
{
	char	*str;

	while (lst)
	{
		str = (char *) lst->content;
		if (!str)
			ft_putendl_fd("(null)", 1);
		else
			ft_putendl_fd(str, 1);
		lst = lst->next;
	}
}

/// @brief Return a conversion of ```strs``` into a list
/// where all strings were copied.
/// @param strs
/// @return ```NULL``` if allocation error or if ```strs``` was
/// empty.
t_list	*ft_strstolst(char **strs)
{
	t_list	*list;

	list = NULL;
	while (strs && *strs)
	{
		if (ft_lst_str_append(&list, *strs))
		{
			ft_lstclear(&list, free);
			return (NULL);
		}
		strs++;
	}
	return (list);
}

/// @brief Return a conversion of list of string into an array
/// of string were all strings were copied.
/// @param list
/// @return ```NULL``` if allocation error.
/// Array with NULL as the first element if list was ```NULL```.
char	**ft_lsttostrs(t_list *list)
{
	int		size;
	char	**strs;
	int		i;

	size = ft_lstsize(list);
	strs = malloc(sizeof(char *) * (size + 1));
	if (!strs)
		return (NULL);
	strs[size] = NULL;
	i = 0;
	while (list)
	{
		strs[i] = ft_strdup((char *)list->content);
		if (!strs[i++])
			return (ft_free_strs(strs));
		list = list->next;
	}
	return (strs);
}
