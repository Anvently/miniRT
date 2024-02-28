/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:51:21 by npirard           #+#    #+#             */
/*   Updated: 2024/01/22 16:35:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	**ft_free_strs(char **strings)
{
	int	i;

	i = 0;
	while (strings && strings[i])
		free(strings[i++]);
	free(strings);
	return (NULL);
}
