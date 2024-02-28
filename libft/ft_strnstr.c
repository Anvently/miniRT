/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:57:00 by npirard           #+#    #+#             */
/*   Updated: 2023/12/01 16:56:36 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Find the first occurence of little in the len first characters of big
/// @param big String where the search occcurs
/// @param little Substring to find
/// @param len Number of character to search in big
/// @return Address where little starts in big if found.
/// Big if little is empty.
/// NULL if little wasn't found in the len first characters
/// of big or if len is 0.
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l_little;

	l_little = ft_strlen(little);
	if (!l_little)
		return ((char *) big);
	if (!len)
		return (NULL);
	i = 0;
	while (big[i] && i < len && l_little <= len - i)
	{
		if (!ft_strncmp(big + i, little, l_little))
			return ((char *) big + i);
		i++;
	}
	return (NULL);
}
