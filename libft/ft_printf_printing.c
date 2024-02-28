/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_printing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:57:28 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Handle special case for printing ```\0``` byte when type is ```c```.
/// @param field
/// @param str
/// @return ```1``` if field with wasn't given. ```0``` if there was a given
/// field width (because in this case chars were already counted before.)
static int	print_null_byte(t_field *field, char *str)
{
	char	c;
	size_t	len_str;
	int		ret;

	c = '\0';
	len_str = ft_strlen(str);
	if (field->flags.left_justify)
	{
		write(1, &c, 1);
		write(1, str, len_str - 1);
	}
	else
	{
		if (len_str > 0)
			write(1, str, len_str - 1);
		write(1, &c, 1);
	}
	if (len_str > 0)
		ret = 0;
	else
		ret = 1;
	return (ret);
}

/// @brief Return an allocated string representing the value in the correct
/// conversion type.
/// @param field
/// @return Address of allocated string. ```NULL``` if no type specified
/// (should not happen) or allocation error.
char	*get_str_value(t_field *field)
{
	if (field->type == 'c')
		return (char_to_str((unsigned long) field->value));
	else if (field->type == 's')
		return (str_to_str((char *) field->value));
	else if (field->type == 'p')
		return (address_to_str((unsigned long) field->value));
	else if (ft_strchr("di", field->type))
		return (ft_itoa((unsigned long) field->value));
	else if (field->type == 'u')
		return (ft_uitoa((unsigned long)field->value));
	else if (ft_strchr("xX", field->type))
		return (hexa_to_str((unsigned long) field->value, field->type));
	return (NULL);
}

/// @brief Return the formatted string representing a given field.
/// @param field
/// @return Address of allocated string. ```NULL``` if allocation error.
char	*build_str(t_field *field)
{
	char	*str;

	str = get_str_value(field);
	if (!str)
		return (NULL);
	str = format_str(field, str);
	return (str);
}

/// @brief Print a given field
/// @param field
/// @return Number of characters printed.
int	print_field(t_field *field)
{
	int		nbr_chars;
	char	*str;

	nbr_chars = 0;
	if (field->type == '\0')
	{
		ft_putstr_fd((char *) field->value, 1);
		return (ft_strlen((char *) field->value));
	}
	str = build_str(field);
	if (!str)
		return (-1);
	nbr_chars = ft_strlen(str);
	if (field->type == 'c' && (unsigned long) field->value == 0)
		nbr_chars += print_null_byte(field, str);
	else
		ft_putstr_fd(str, 1);
	free (str);
	return (nbr_chars);
}

/// @brief Print all fields in the given list
/// @param fields
/// @return Number of characters printed
int	print_fields(t_list *fields)
{
	int	nbr_chars;
	int	ret;

	nbr_chars = 0;
	while (fields)
	{
		ret = print_field((t_field *) fields->content);
		if (ret < 0)
			return (-1);
		nbr_chars += ret;
		fields = fields->next;
	}
	return (nbr_chars);
}
