/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_field_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:56:16 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	init_field(t_field *field)
{
	field->flags.alternate_form = false;
	field->flags.force_sign = false;
	field->flags.left_justify = false;
	field->flags.precision = false;
	field->flags.sign_blank = false;
	field->flags.zero_padding = false;
	field->type = '\0';
	field->precision = 0;
	field->value = NULL;
	field->width = 0;
}

t_list	*new_field_node(void)
{
	t_field	*field;
	t_list	*node;

	field = malloc(sizeof(t_field));
	if (field)
		init_field(field);
	node = ft_lstnew(field);
	if (!node)
		free(field);
	return (node);
}

void	free_field(void *field)
{
	if (field && ((t_field *) field)->type == 0)
		free(((t_field *) field)->value);
	free(field);
}
