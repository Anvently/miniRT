/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:55:29 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 13:32:51 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <math.h>

t_color3f	color_average(t_color3f *colors, int size)
{
	t_color3f	color;
	int			i;

	i = 0;
	color.r = 0.0;
	color.g = 0.0;
	color.b = 0.0;
	while (i < size)
	{
		color.r += colors[i].r;
		color.g += colors[i].g;
		color.b += colors[i].b;
		i++;
	}
	color.r /= size;
	color.g /= size;
	color.b /= size;
	return (color);
}

// void	color_unsature(t_color3f *color)
// {
// 	double	*max_color;
// 	double	factor;

// 	max_color = (double *)ft_max(&color->r,
// 			ft_max(&color->g, &color->b, sizeof(double)), sizeof(double));
// 	if (*max_color <= 1.0)
// 		return ;
// 	printf("max color=%f\n", *max_color);
// 	factor = 1.f / *max_color;
// 	*max_color *= factor;
// 	if (&color->r != max_color)
// 		color->r *= factor;
// 	if (&color->g != max_color)
// 		color->g *= factor;
// 	if (&color->b != max_color)
// 		color->b *= factor;
// }

// void	color_unsature(t_color3f *color)
// {
// 	if (color->r > 1.0)
// 		color->r = 1.0;
// 	if (color->g > 1.0)
// 		color->g = 1.0;
// 	if (color->b > 1.0)
// 		color->b = 1.0;
// }

void	color_unsature(t_color3f *color)
{
	color->r = tanh(color->r);
	color->g = tanh(color->g);
	color->b = tanh(color->b);
}

t_color3f	color_ratio(t_color3f *color, double ratio)
{
	t_color3f	new_color;

	new_color.r = color->r * ratio;
	new_color.g = color->g * ratio;
	new_color.b = color->b * ratio;
	return (new_color);
}

t_color3f	color_product(t_color3f *color_a, t_color3f *color_b)
{
	t_color3f	color;

	color.r = color_a->r * color_b->r;
	color.g = color_a->g * color_b->g;
	color.b = color_a->b * color_b->b;
	return (color);
}

void	color_filter(t_color3f *color, t_color3f *filter)
{
	color->r *= filter->r;
	color->g *= filter->g;
	color->b *= filter->b;
}
