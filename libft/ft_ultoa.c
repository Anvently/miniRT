/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:59:43 by npirard           #+#    #+#             */
/*   Updated: 2023/12/18 22:14:01 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	len_nb(size_t len, unsigned long nb)
{
	if (nb > 0)
		len = len_nb(len + 1, nb / 10);
	if (len > 0)
		return (len);
	else
		return (1);
}

static void	put_nbr(char **s, unsigned long nb)
{
	if (nb <= 9)
	{
		**s = '0' + nb;
		*s = *s + 1;
	}
	else
	{
		put_nbr(s, nb / 10);
		put_nbr(s, nb % 10);
	}
}

/// @brief Return an allocated string representing n.
/// @param n Unsigned long to convert.
/// @return String representing n. NULL if allocation fails.
char	*ft_ultoa(unsigned long n)
{
	char	*buffer;
	char	*index;
	size_t	size;

	size = len_nb(0, (unsigned long) n);
	buffer = malloc(size + 1);
	if (!buffer)
		return (NULL);
	buffer[size] = '\0';
	index = buffer;
	put_nbr(&index, (unsigned long) n);
	return (buffer);
}
