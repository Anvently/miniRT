/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:59:13 by npirard           #+#    #+#             */
/*   Updated: 2024/01/17 15:44:39 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>

/// @brief
/// @param dest
/// @param sign
/// @param c
/// @return ```0``` if no error. ```1``` if overflow.
static int	increment_nbr(int *dest, int sign, char c)
{
	int	add;

	add = c - '0';
	if (*dest > INT_MAX / 10)
		return (1);
	if (*dest == INT_MAX / 10)
	{
		if (sign > 0 && add > 7)
			return (1);
		if (sign < 0 && add > 8)
			return (1);
	}
	*dest = *dest * 10 + add;
	return (0);
}

/// @brief Convert the initial part of a string to an integer.
/// Format : \\[n spaces\\](+-)[n digit]
/// Check for overflow.
/// @param str String to convert
/// @param dest int receiving the conversion.
/// @return ```0``` if no error occured. ```1``` if overflow.
/// ```2``` if no digit was found at the beginning.
int	ft_strtoi(const char *str, int *dest)
{
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	*dest = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (2);
	while (ft_isdigit(str[i]))
		if (increment_nbr(dest, sign, str[i++]))
			return (1);
	*dest = sign * *dest;
	return (0);
}
