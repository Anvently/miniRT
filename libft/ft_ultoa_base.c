/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:59:43 by npirard           #+#    #+#             */
/*   Updated: 2023/12/18 22:14:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	len_nb(size_t len, unsigned long nb, size_t len_base)
{
	if (nb > 0)
		len = len_nb(len + 1, nb / len_base, len_base);
	if (len > 0)
		return (len);
	else
		return (1);
}

static void	put_nbr(char **s, unsigned long nb, char *base, size_t len_base)
{
	if (nb <= (len_base - 1))
	{
		**s = *(base + (nb % len_base));
		*s = *s + 1;
	}
	else
	{
		put_nbr(s, nb / len_base, base, len_base);
		put_nbr(s, nb % len_base, base, len_base);
	}
}

/// @brief Return an allocated string representing n in a given base.
/// @param n Unsigned long to convert.
/// @return String representing n. NULL if allocation fails.
char	*ft_ultoa_base(unsigned long n, char *base)
{
	char	*buffer;
	char	*index;
	size_t	size;
	size_t	len_base;

	len_base = ft_strlen(base);
	if (len_base < 2)
		return (NULL);
	size = len_nb(0, n, len_base);
	buffer = malloc(size + 1);
	if (!buffer)
		return (NULL);
	buffer[size] = '\0';
	index = buffer;
	put_nbr(&index, n, base, len_base);
	return (buffer);
}
