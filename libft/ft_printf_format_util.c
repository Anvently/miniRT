/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:41:14 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Return an allocated string where ```c``` was inserted ```n``` times
/// in ```str``` starting from index ```start```.
/// @param str
/// @param start
/// @param n
/// @param c
/// @return Address of the new string. ```NULL``` if allocation error.
char	*insert_n_char(char *str, int start, int n, char c)
{
	char	*buffer;
	size_t	size;
	int		i;

	size = ft_strlen(str) + n + 1;
	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, str, start + 1);
	i = start;
	while (i - start < n)
	{
		buffer[i] = c;
		i++;
	}
	buffer[n + start] = '\0';
	ft_strlcat(buffer, str + start, size);
	return (buffer);
}
