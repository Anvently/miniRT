/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:41:44 by npirard           #+#    #+#             */
/*   Updated: 2024/01/08 14:50:43 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief Write n on given file descriptor
/// @param n Number to write
/// @param fd File descriptor. 0 STDIN_FILENO. 1 STDOUT_FILENO. 2 stderr.
void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		nb = - (long) n;
		ft_putchar_fd('-', fd);
	}
	else
		nb = n;
	if (nb <= 9)
		ft_putchar_fd('0' + nb, fd);
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
}
