/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:02:35 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 16:25:32 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>

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
void	color_getcolor(int color, t_color *dest)
{
	dest->r = color_get_r(color);
	dest->g = color_get_g(color);
	dest->b = color_get_b(color);
}
