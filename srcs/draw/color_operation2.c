/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operation2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:40:33 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 10:03:23 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>

t_color3f	color_sum(t_color3f *color_a, t_color3f *color_b)
{
	t_color3f	color;

	color.r = color_a->r + color_b->r;
	color.g = color_a->g + color_b->g;
	color.b = color_a->b + color_b->b;
	color_unsature(&color);
	return (color);
}

void	color_add(t_color3f *color, t_color3f color_add)
{
	color->r += color_add.r;
	color->g += color_add.g;
	color->b += color_add.b;
	color_unsature(color);
}

t_color3f	color_normalize(t_color *colori)
{
	t_color3f	color;

	color.r = (double) colori->r / 255.f;
	color.g = (double) colori->g / 255.f;
	color.b = (double) colori->b / 255.f;
	return (color);
}
