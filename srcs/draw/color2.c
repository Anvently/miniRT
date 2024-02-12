/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:25:04 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 16:26:06 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>

int	color_get_t(int color)
{
	return ((color >> 24) & 255);
}

int	color_get_r(int color)
{
	return ((color >> 16) & 255);
}

int	color_get_g(int color)
{
	return ((color >> 8) & 255);
}

int	color_get_b(int color)
{
	return (color & 255);
}