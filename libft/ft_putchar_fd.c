/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:39:48 by npirard           #+#    #+#             */
/*   Updated: 2024/01/08 14:50:43 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Write c on given file descriptor
/// @param c Char
/// @param fd File descriptor. 0 STDIN_FILENO. 1 STDOUT_FILENO. 2 stderr.
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
