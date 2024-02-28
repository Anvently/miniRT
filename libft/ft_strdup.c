/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:51:39 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:36 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Allocate and return a copy of s
/// @param s String to copy
/// @return Address of the copy
///NULL if allocation fails
char	*ft_strdup(const char *s)
{
	char	*buffer;
	size_t	size;

	size = ft_strlen(s) + 1;
	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, s, size);
	return (buffer);
}
