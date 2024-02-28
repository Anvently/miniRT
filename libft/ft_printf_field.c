/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_field.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:57:12 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Parse a ```%``` sequence as such :
/// ```%[m$][flags][width][.precision]conversion```
///    %[(number$)][# 0-+][number*(a number$)][(.)number*](cspdiuxX)
/// @param str Start of the sequence. Starts with ```%```
/// @param field Structure storing the result of the parsing.
/// @param args Given values. List is copied every time
/// a value is retrieved from the list.
/// @param arg_index Index of the last argument read in ```args```. Start at 0.
/// Get incremented each time an argument is read. If a ```m$``` format is
/// encountered when ```arg_index``` is bigger than 0 then a format error
/// is generated.
/// @return Right boundary of the found field where the input end.
/// Just after conversion type.
/// @note Warning : index overflowing ```args``` size are not checked.
char	*parse_field(char *str, t_field *field,
			t_list **args_req, int *arg_index)
{
	int	given_index;

	if (*(str + 1) == '%')
	{
		field->value = ft_strdup("%");
		return (str + 2);
	}
	str = parse_arg_index(str + 1, arg_index, &given_index, true);
	str = parse_flags(str, field);
	str = parse_width(str, field, args_req, arg_index);
	str = parse_precision(str, field, args_req, arg_index);
	str = parse_conversion_type(str, field);
	if (!given_index)
	{
		given_index = ++(*arg_index);
		if (!check_index_format(1, given_index, "field index argument."))
			return (NULL);
	}
	if (!str || !register_arg_request(args_req, &(field->value),
			given_index, field->type))
		return (NULL);
	return (str);
}

/// @brief Append the first field found in str to field list.
/// A field is defined either as a ```%..```. sequence or any string
/// between 2 ```%...``` sequences.
/// @param str Address to start the parsing from
/// @param fields Linked list of fields.
/// @return Right boundary of the found field.
/// ```NULL``` if allocation error.
char	*get_next_field(char *str, t_list **fields,
			t_list **args_req, int *arg_index)
{
	int		i;
	t_list	*field;

	field = new_field_node();
	if (!field)
		return (alloc_error());
	ft_lstadd_back(fields, field);
	i = 0;
	while (str[i] && str[i] != '%')
		i++;
	if (i)
		((t_field *) field->content)->value = ft_substr(str, 0, i);
	else if (str[i])
		str = parse_field(str, (t_field *) field->content, args_req, arg_index);
	if (!str || (i && ((t_field *) field->content)->value == NULL))
		return (NULL);
	return (str + i);
}

/// @brief Split the given strig in different fields, each rep
/// @param str String to parse.
/// @return Linked list of field structure containing all field
/// found in str.
/// ```NULL``` if allocation error.
t_list	*build_fields(char *str, va_list *va_args)
{
	t_list	*fields;
	t_list	*args_req;
	int		arg_index;

	args_req = NULL;
	arg_index = 0;
	fields = NULL;
	while (str && *str)
		str = get_next_field(str, &fields, &args_req, &arg_index);
	if (!str)
		ft_lstclear(&fields, &free_field);
	else
	{
		if (!retrieve_arguments(args_req, va_args))
			ft_lstclear(&fields, &free_field);
	}
	ft_lstclear(&args_req, &free_arg_req);
	return (fields);
}
