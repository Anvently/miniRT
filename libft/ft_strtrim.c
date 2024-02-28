/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:52:35 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:36 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Allocate and return a string where chars contained in set
/// are trimmed, only at the beginning and the end of s1
/// @param s1 String to trim
/// @param set Set of characters to trim in s1
/// @return Address of trimmed string.
/// NULL if allocation fails.
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	size_t	trim_len;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	trim_len = len;
	while (ft_strchr(set, s1[i]))
	{
		trim_len--;
		i++;
	}
	while (ft_strchr(set, s1[len]))
	{
		trim_len--;
		len--;
	}
	return (ft_substr(s1, i, trim_len + 1));
}
