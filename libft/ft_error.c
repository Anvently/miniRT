/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:39:53 by npirard           #+#    #+#             */
/*   Updated: 2023/12/04 10:40:26 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*alloc_error(void)
{
	return (null_error("Allocation error."));
}

void	*null_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (NULL);
}
