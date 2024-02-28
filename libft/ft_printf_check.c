/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:47:13 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Check if there is conflict between positionnal argument format
/// and default format.
/// @param new_format Format used for the last call to an argument. ```1```
/// Arguments are given in order. ```2``` Argument are given by position.
/// @param given_index Index returned when parsing given index.
/// @param parsing String used to tell when the function is called.
/// Helps detecting when a error occurs. Can be set to anything.
/// @return ``true``` if no conflict, else ```false```.
bool	check_index_format(int new_format, int given_index, char *parsing)
{
	static int	pos_format = 0;
	int			error;

	error = 0;
	if (new_format < 0)
	{
		pos_format = 0;
		return (true);
	}
	if (!pos_format)
		pos_format = new_format;
	if (given_index && pos_format != new_format)
		error = 1;
	else if (new_format && !given_index)
		error = 2;
	if (error)
	{
		format_error(error, parsing);
		return (false);
	}
	return (true);
}

/// @brief Check any conflict between 2 argument's request type.
/// There is a conflict is two type are considered of different group.
/// Groups are ```c```, ```s```, ```pdiuxXt```
/// @param current_req
/// @param previous_req
/// @return ```true``` if no conflict, else ```false```.
bool	check_type_conflict(t_arg_req *node1, t_arg_req *node2)
{
	int	error;

	error = 0;
	if (node1->index != node2->index)
		return (true);
	if (((t_arg_req *) node1)->type == 'c'
		&& ((t_arg_req *) node2)->type != 'c')
		error++;
	else if (((t_arg_req *) node1)->type == 's'
		&& ((t_arg_req *) node2)->type != 's')
		error++;
	else if (ft_strchr("pdiuxXt", ((t_arg_req *) node1)->type)
		&& !ft_strchr("pdiuxXt", ((t_arg_req *) node2)->type))
		error++;
	if (error)
		return (arg_index_error(1, (int)((t_arg_req *) node2)->index));
	return (true);
}

/// @brief Check if there is any conflict between given flags according
/// to field type.
/// @note ```#``` Only works for ```xX``` types.
/// @note ```0``` Only works for ```diuxX``` types.
/// @note ```-``` ```0``` must be false.
/// @note ```' '``` Only works for ```diuxX``` types.
/// @note ```+``` Only works for ```diuxX``` types. ```' '``` must be false.
/// @note ```.``` Doesn't work for ```p``` and ```c``` type.
/// @param field
/// @return ```true``` if no conflict, else ```false```.
bool	check_flag_conflict(t_field *field)
{
	if (field->flags.alternate_form == true && !ft_strchr("xX", field->type))
		return (flag_error('#'));
	if (field->flags.zero_padding == true && !ft_strchr("diuxX", field->type))
		return (flag_error('0'));
	if (field->flags.left_justify == true && field->flags.zero_padding == true)
		return (flag_error('-'));
	if (field->flags.sign_blank == true && !ft_strchr("diuxX", field->type))
		return (flag_error(' '));
	if (field->flags.force_sign == true)
	{
		if (!ft_strchr("diuxX", field->type))
			return (flag_error('+'));
		if (field->flags.sign_blank == true)
			return (flag_error('+'));
	}
	if (field->precision != 0 && ft_strchr("pc", field->type))
		return (flag_error('.'));
	return (true);
}

/// @brief Check if each field has no conflict in its flags.
/// @param field
/// @return ```true``` if no conflict, else ```false```.
bool	check_fields(t_list *fields)
{
	while (fields)
	{
		if (!check_flag_conflict((t_field *) fields->content))
			return (false);
		fields = fields->next;
	}
	return (true);
}
