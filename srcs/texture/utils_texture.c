/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:49:41 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/22 14:24:07 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <math.h>

int	get_pixel_dame_coord(t_double2 *uv, double square_size)
{
	double	temp;
	int		pixel;

	pixel = 0;
	temp = square_size;
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

