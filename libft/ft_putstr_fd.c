/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:41:06 by npirard           #+#    #+#             */
/*   Updated: 2024/01/08 14:50:43 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Write s on given file descriptor
/// @param s String
/// @param fd File descriptor. 0 STDIN_FILENO. 1 STDOUT_FILENO. 2 stderr.
void	ft_putstr_fd(char *s, int fd)
{
	write (fd, s, ft_strlen(s));
}
