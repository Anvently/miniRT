/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:54:45 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:36 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Try to copy the full length of src after dst,
/// adding a null byte at the end.
/// If the resulting string doesn't fit into dst, size - 1 byte will be copied,
/// assuring the null byte at the end of dst.
/// @param dst The string receiving the concatenation.
/// @param src String to concatenate with dst
/// @param size Full size of the buffer dst.
/// @return The length of the intended resulting string,
/// meaning len(dst) len(src).
/// If dst is not null terminated, return size + len(src)
/// and dst will not be null terminated.
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	l_src;
	size_t	l_dst;

	l_src = ft_strlen(src);
	if (!size)
		return (size + l_src);
	l_dst = ft_strlen(dst);
	if (l_dst >= size)
		return (size + ft_strlen(src));
	i = 0;
	while (src[i] && i < (size - l_dst - 1))
	{
		dst[l_dst + i] = src[i];
		i++;
	}
	dst[l_dst + i] = '\0';
	return (l_dst + l_src);
}
