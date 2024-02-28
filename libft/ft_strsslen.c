/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsslen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:08:15 by npirard           #+#    #+#             */
/*   Updated: 2023/12/08 11:10:19 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Return the size of an array of string array.
/// @param strs
/// @return
int	ft_strsslen(char ***strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		i++;
	return (i);
}
