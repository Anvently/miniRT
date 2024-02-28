/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:34:59 by npirard           #+#    #+#             */
/*   Updated: 2024/02/13 14:43:09 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	add_dec_part(char *str, float *dest)
{
	int		digit;
	float	factor;

	factor = 0.1;
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		*dest += factor * (float) digit;
		factor *= 0.1;
		str++;
	}
}

static int	get_sign(char **str)
{
	int	sign;

	sign = 1;
	while (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign *= -1;
		(*str)++;
	}
	return (sign);
}

/// @brief Convert the initial part of a string to an integer.
/// Format : \\[n spaces\\](+-)[n digit](.)([m digit])
/// Check for overflow.
/// @param str String to convert
/// @param dest int receiving the conversion.
/// @param ptr Optional parameter which will pointed to the end of the parsed
/// sequence. The full sequence is parsed even in case of errors.
/// @return ```0``` if no error occured.
/// ```1``` if no digit was found at the beginning of integer or decimal part.
/// Overflow are NOT checked.
int	ft_strtof(char *str, float *dest, char **ptr)
{
	int	err;
	int	sign;

	*dest = 0;
	err = 0;
	if (ptr == NULL)
		ptr = &str;
	while (ft_isspace(**ptr))
		(*ptr)++;
	sign = get_sign(ptr);
	if (ft_isdigit(**ptr))
	{
		*dest = (float) ft_atoi(*ptr);
		while (ft_isdigit(**ptr))
			(*ptr)++;
	}
	else if (**ptr != '.')
		err = 1;
	if (**ptr == '.')
		add_dec_part(++(*ptr), dest);
	while (**ptr && !ft_isspace(**ptr))
		(*ptr)++;
	if (*dest > 0)
		*dest *= sign;
	return (err);
}
