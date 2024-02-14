/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:02:35 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 11:36:07 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/types.h>

/// @brief Convert t_color format to int format.
/// @param color
/// @return int where RGB colors where put to their corresponding bits.
int	color_getint(t_color *color)
{
	int	rgb;

	rgb = color->r;
	rgb <<= 8;
	rgb |= color->g;
	rgb <<= 8;
	rgb |= color->b;
	return (rgb);
}

/// @brief Extract RGB colors from given int and put it in dest structure.
/// @param color
/// @param dest
t_color	color_getcolor(int icolor)
{
	t_color	color;

	color.r = color_get_r(icolor);
	color.g = color_get_g(icolor);
	color.b = color_get_b(icolor);
}
