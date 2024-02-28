/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:59:48 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @note [# 0-+]
/// @brief Look for any flag and add them to the field structure. Stop looking
/// at the first non flag character encountered.
/// @param str string to look into.
/// @param field structure storing the result of the parsing.
/// @return Right boundary of the parsed sequence. ```str``` if no sequence
/// is found. ```NULL``` in case of format error.
char	*parse_flags(char *str, t_field *field)
{
	int	i;

	i = 0;
	while (str && str[i] && ft_strchr("# 0-+", str[i]))
	{
		if (str[i] == '#')
			field->flags.alternate_form = true;
		else if (str[i] == ' ')
			field->flags.sign_blank = true;
		else if (str[i] == '0')
			field->flags.zero_padding = true;
		else if (str[i] == '-')
			field->flags.left_justify = true;
		else if (str[i] == '+')
			field->flags.force_sign = true;
		i++;
	}
	return (str + i);
}

/// @brief Look for a digit number, a ```*``` if value is given in next
/// argument, or a ```*m$``` if the value is specified in the m-th argument.
/// @note ```[number*(*a number$)]```
/// @param str string to look into
/// @param field structure storing the result of the parsing.
/// @param args Given values. List is copied every time
/// a value is retrieved from the list.
/// @param arg_index Index of the last argument read in ```args```. Start at 0.
/// @return Right boundary of the parsed sequence. ```str``` if no sequence
/// is found. ```NULL``` in case of format error.
char	*parse_width(char *str, t_field *field,
			t_list **args_req, int *arg_index)
{
	int	i;
	int	given_index;

	i = 0;
	str = parse_arg_index(str, arg_index, &given_index, false);
	if (given_index)
	{
		if (!register_arg_request(args_req, &(field->width), given_index, 't'))
			return (NULL);
	}
	else if (!str)
		return (NULL);
	else if (ft_isdigit(str[i]))
	{
		field->width = (size_t) ft_atoi(str);
		while (ft_isdigit(str[i]))
			i++;
	}
	return (str + i);
}

/// @note (.[number*(*number$)])
/// @brief Look for ```.``` followed by a decimal digit or a ```*```
/// if value is given in next argument, or a ```*m$``` if the value
///  is specified in the m-th argument.
/// @param str string to look into
/// @param field structure storing the result of the parsing.
/// @param args Given values. List is copied every time
/// a value is retrieved from the list.
/// @param arg_index Index of the last argument read in ```args```. Start at 0.
/// @return Right boundary of the parsed sequence. ```str``` if no sequence
/// is found. ```NULL``` in case of format error.
char	*parse_precision(char *str, t_field *field,
			t_list **args_req, int *arg_index)
{
	int	given_index;

	if (!str || *str != '.')
		return (str);
	str = parse_arg_index(++str, arg_index, &given_index, false);
	if (given_index)
	{
		if (!register_arg_request(args_req, &(field->precision),
				given_index, 'd'))
			return (NULL);
	}
	else if (str && ft_isdigit(*str))
	{
		field->precision = (size_t) ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
	}
	field->flags.precision = true;
	return (str);
}

/// @note (cspdiuxX)
/// @brief Look for a conversion type specifier at the first char of str.
/// @param str string to look into
/// @param field structure storing the result of the parsing.
/// @return ```str + 1``` if a valid conversion type is found.
/// ```NULL``` if conversion type is invalid.
char	*parse_conversion_type(char *str, t_field *field)
{
	if (!str)
		return (NULL);
	if (ft_strchr("cspdiuxX", str[0]) && str[0])
		field->type = str[0];
	else
		return (format_error(3, "conversion type"));
	return (str + 1);
}
