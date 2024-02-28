/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:09:57 by npirard           #+#    #+#             */
/*   Updated: 2023/12/04 10:40:34 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*format_error(int error, char *parsing)
{
	ft_putstr_fd("FORMAT ERROR when parsing ", 2);
	ft_putstr_fd(parsing, 2);
	ft_putstr_fd(" : ", 2);
	if (error == 1)
		return (null_error("conflict between m$ index formatting and"
				" default format."));
	else if (error == 2)
		return (null_error("position arguments must be greater than zero."));
	else if (error == 3)
		return (null_error("invalid conversion type."));
	return (NULL);
}

int	arg_index_error(int error, int index)
{
	ft_putstr_fd("POSITIONNAL ARGUMENT ERROR at index ", 2);
	ft_putnbr_fd(index, 2);
	ft_putstr_fd(" : ", 2);
	if (error == 1)
		null_error("conflict between 2 type for an argument.");
	else if (error == 2)
		null_error("unused argument.");
	return (0);
}

bool	flag_error(char flag)
{
	ft_putstr_fd("FLAG ERROR for given flag ", 2);
	ft_putchar_fd(flag, 2);
	ft_putstr_fd(" : ", 2);
	if (flag == '#')
		ft_putendl_fd("Only works for xX types.", 2);
	else if (flag == '0' || flag == ' ')
		ft_putendl_fd("Only works for diuxX types.", 2);
	else if (flag == '-')
		ft_putendl_fd("Only works if flag 0 is not given.", 2);
	else if (flag == '+')
		ft_putendl_fd("Only works for diuxX types "
			"and if flag ' ' is not given.", 2);
	else if (flag == '.')
		ft_putendl_fd("Doesn't work for p and c types.", 2);
	return (false);
}
