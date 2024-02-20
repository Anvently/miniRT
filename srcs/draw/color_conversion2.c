/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_conversion2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:02:35 by npirard           #+#    #+#             */
/*   Updated: 2024/02/20 13:44:08 by npirard          ###   ########.fr       */
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

int	color_3f_int(t_color3f *color)
{
	int	rgb;

	rgb = (int)(color->r * 255.f);
	rgb <<= 8;
	rgb |= (int)(color->g * 255.f);
	rgb <<= 8;
	rgb |= (int)(color->b * 255.f);
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
	return (color);
}

t_color3f	color_getcolor3f(int icolor)
{
	t_color3f	color;

	color.r = (double) color_get_r(icolor) / 255.f;
	color.g = (double) color_get_g(icolor) / 255.f;
	color.b = (double) color_get_b(icolor) / 255.f;
	return (color);
}
