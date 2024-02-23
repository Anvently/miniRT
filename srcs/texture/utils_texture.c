/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:49:41 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/23 10:16:23 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <math.h>

int	get_pixel_dame_coord(t_double2 *uv, double square_size)
{
	double	temp;
	int		pixel;

	pixel = (1 - sign(uv->x)) * 0.5 + (1 - sign(uv->y)) * 0.5;
	temp = square_size;
	uv->x = fabs(uv->x);
	uv->y = fabs(uv->y);
	while (temp <= uv->x && temp < 1.f)
	{
		pixel++;
		temp += square_size;
	}
	temp = square_size;
	while (temp <= uv->y && temp < 1.f)
	{
		pixel++;
		temp += square_size;
	}
	return (pixel);
}

void	coord_abs(t_coord2f *coord)
{
	if (coord->x < 0.f)
		coord->x = 1.f - (-coord->x);
	if (coord->y < 0.f)
		coord->y = 1.f - (-coord->y);
}
