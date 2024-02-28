/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:53:13 by npirard           #+#    #+#             */
/*   Updated: 2024/01/11 16:56:37 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Allocate and return the concatenation of s1 and s2
/// ```NULL``` string are considered as empty string.
/// @param s1 Null terminated string. Can be ```NULL```
/// @param s2 Null terminated string. Can be ```NULL```
/// @return Address of allocated string
/// Empty string if both string were empty or ```NULL```.
/// ```NULL``` if allocation fails.
char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*buffer;
	size_t	len_s1;
	size_t	len_s2;
	size_t	size;

	if (s1)
		len_s1 = ft_strlen(s1);
	else
		len_s1 = 0;
	if (s2)
		len_s2 = ft_strlen(s2);
	else
		len_s2 = 0;
	size = len_s1 + len_s2 + 1;
	buffer = ft_calloc(1, size);
	if (!buffer)
		return (NULL);
	if (s1)
		ft_strlcpy(buffer, s1, size);
	if (s2)
		ft_strlcat(buffer, s2, size);
	return (buffer);
}
