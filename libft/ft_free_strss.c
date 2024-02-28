/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strss.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:21:18 by npirard           #+#    #+#             */
/*   Updated: 2023/12/08 11:24:15 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Free an array of array of strings.
/// @param strs
/// @return ```NULL```
char	***ft_free_strss(char ***strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		ft_free_strs(strs[i++]);
	free(strs);
	return (NULL);
}
