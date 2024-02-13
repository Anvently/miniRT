/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:36:00 by npirard           #+#    #+#             */
/*   Updated: 2024/02/13 16:33:42 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <errno.h>
#include <string.h>

void	error(char *context)
{
	if (context)
	{
		ft_putstr_fd(context, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errno), 2);
}

void	error_file(char *context, char *path)
{
	ft_putstr_fd("error: ", 2);
	if (context)
	{
		ft_putstr_fd(context, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror(errno), 2);
	if (path)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(path, 2);
	}
	ft_putstr_fd("\n", 2);
}

void	error_parsing(char *context, int nbr, char *line)
{
	ft_putstr_fd("error parsing ", 2);
	if (context)
		ft_putstr_fd(context, 2);
	if (line)
	{
		ft_putstr_fd(" at line ", 2);
		ft_putnbr_fd(nbr, 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(line, 2);
	}
	else
		ft_putstr_fd("\n", 2);
}
