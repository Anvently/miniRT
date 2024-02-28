/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:58:01 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdint.h>

t_list	*new_argument_node(void)
{
	t_arg_req	*argument;
	t_list		*node;

	argument = malloc(sizeof(t_arg_req));
	if (!argument)
		return (NULL);
	node = ft_lstnew(argument);
	if (!node)
		free(argument);
	return (node);
}

void	free_arg_req(void *arg_req)
{
	free(arg_req);
}

/// @brief Insert the given arg request in the list according to its index,
/// check any conflict with a previous request.
/// @param args_req Linked list of arg request. The list is sorted in
/// ascending order.
/// @param node Node to insert
/// @return Address of the new node. ```NULL``` in
/// case of type conflict with an existing request.
t_list	*insert_arg_req(t_list **args_req, t_list *arg_node)
{
	t_arg_req	*req;
	t_list		*current_node;

	req = (t_arg_req *) arg_node->content;
	current_node = *args_req;
	while (current_node)
	{
		if (!check_type_conflict((t_arg_req *) current_node->content, req))
			return (NULL);
		if (((t_arg_req *) current_node->content)->index > req->index)
		{
			ft_lstadd_front(args_req, arg_node);
			return (arg_node);
		}
		else if (current_node->next
			&& ((t_arg_req *) current_node->next->content)->index > req->index)
		{
			ft_lstinsert(current_node, arg_node);
			return (arg_node);
		}
		current_node = current_node->next;
	}
	ft_lstadd_back(args_req, arg_node);
	return (arg_node);
}

/// @brief Add a new argument request to the arg list.
/// @param args_req Linked list of arg request.
/// @param dest Address where the value will be stored once the args retrieved
/// @param index Index of the argument to read
/// @param type Type of the argument ro read
/// @return Address of the new node. ```NULL``` if allocation error or in
/// case of type conflict with an existing request.
t_list	*register_arg_request(t_list **args_req, void *dest,
		size_t index, char type)
{
	t_list		*arg_node;
	t_arg_req	*req;

	arg_node = new_argument_node();
	if (!arg_node)
		return (alloc_error());
	req = (t_arg_req *) arg_node->content;
	req->dest = dest;
	req->index = index;
	req->type = type;
	if (!insert_arg_req(args_req, arg_node))
		return (NULL);
	return (arg_node);
}

/// @brief Read every argument of ```va_args``` and assign every
/// request in ```args_req``` to its destination variable. Check for
/// any out of reach or unused index.
/// @param args_req Linked list of arg request.
/// @param va_args Given argument when calling ```ft_printf```.
/// @return
int	retrieve_arguments(t_list *args_req, va_list *va_args)
{
	int			i;
	t_arg_req	*req;
	void		*value;

	i = 0;
	value = NULL;
	while (args_req)
	{
		req = (t_arg_req *) args_req->content;
		if (req->index - i > 1)
		{
			free(value);
			return (arg_index_error(2, i + 1));
		}
		else if (req->index - i == 1)
		{
			i++;
			free(value);
			value = get_arg_value(va_args, req->type);
		}
		cast_to_dest(req->dest, value, req->type);
		args_req = args_req->next;
	}
	free(value);
	return (1);
}
