/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:51:42 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Check if the string is to be formatted and format it using
/// given field flags and properties.
/// @param field
/// @param str
/// @return New allocated string (old one is freed during the process)
/// ```NULL``` if allocation error.
char	*format_str(t_field *field, char *str)
{
	if (ft_strchr("sdiuxX", field->type) && field->precision >= 0
		&& field->flags.precision)
		str = format_precision(field, str);
	if (field->flags.alternate_form && ft_strchr("xX", field->type)
		&& (unsigned long) field->value != 0)
		str = format_alt_form(field, str);
	if (ft_strchr("di", field->type) && str[0] != '-'
		&& (field->flags.force_sign || field->flags.sign_blank))
		str = format_sign(field, str);
	if (ft_strlen(str) < field->width)
		str = format_width(field, str);
	return (str);
}

/// @brief Format the field with given precision. For ```sdiuxX``` types, that
/// means adding 0 if necessary (or return empty string if value and
/// precision are both set to zero). For ```s``` types,
/// that means removing excess characters.
/// @param field
/// @param str
/// @return New allocated string (old one is freed during the process)
/// ```NULL``` if allocation error.
char	*format_precision(t_field *field, char *str)
{
	char	*buffer;
	int		len_str;

	len_str = (int) ft_strlen(str);
	if (field->type == 's' && (field->value != NULL
			|| (field->value == NULL && field->precision >= 6)))
		buffer = ft_substr(str, 0, field->precision);
	else
	{
		if ((unsigned long) field->value == 0 && (field->precision == 0
				|| (field->type == 's' && field->precision < 6)))
			buffer = ft_strdup("");
		else if (str[0] == '-' && len_str - 1 < field->precision)
			buffer = insert_n_char(str, 1,
					field->precision - len_str + 1, '0');
		else if (len_str < field->precision)
			buffer = insert_n_char(str, 0,
					field->precision - len_str, '0');
		else
			return (str);
	}
	if (!buffer)
		return (alloc_error());
	free (str);
	return (buffer);
}

/// @brief Convert ```xX``` types in different form. Add ```0x``` or
/// ```0X``` before number if non-null.
/// @param field
/// @param str
/// @return New allocated string (old one is freed during the process)
/// ```NULL``` if allocation error.
char	*format_alt_form(t_field *field, char *str)
{
	char	*buffer;

	if (field->type == 'x')
		buffer = ft_strjoin("0x", str);
	else
		buffer = ft_strjoin("0X", str);
	if (!buffer)
		return (alloc_error());
	free(str);
	return (buffer);
}

/// @brief Only for signed decimal (types ```di```). Check if a sign
/// or a blank is to be added before the number and adds it if necessary.
/// @param field
/// @param str
/// @return New allocated string (old one is freed during the process)
/// ```NULL``` if allocation error.
char	*format_sign(t_field *field, char *str)
{
	char	*buffer;

	buffer = NULL;
	if (field->flags.force_sign)
		buffer = ft_strjoin("+", str);
	else if (field->flags.sign_blank)
		buffer = ft_strjoin(" ", str);
	if (!buffer)
		return (alloc_error());
	free(str);
	return (buffer);
}

/// @brief Adds ```0``` or ```' '``` to the field, according to the given
/// flags and width. Also handle left justification.
/// @param field
/// @param str
/// @return New allocated string (old one is freed during the process)
/// ```NULL``` if allocation error.
char	*format_width(t_field *field, char *str)
{
	char	*buffer;
	size_t	len_str;

	len_str = ft_strlen(str);
	if (field->flags.precision && field->precision <= (int) field->width
		&& ft_strchr("diuxX", field->type))
		field->flags.zero_padding = false;
	if (field->flags.zero_padding && ft_strchr("diuxX", field->type))
	{
		if (str[0] == '-' || str[0] == '+')
			buffer = insert_n_char(str, 1, field->width - len_str, '0');
		else
			buffer = insert_n_char(str, 0, field->width - len_str, '0');
	}
	else if (field->flags.left_justify)
		buffer = insert_n_char(str, len_str, field->width - len_str, ' ');
	else
		buffer = insert_n_char(str, 0, field->width - len_str, ' ');
	if (!buffer)
		return (alloc_error());
	free (str);
	return (buffer);
}
