/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:36:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/26 18:00:46 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>

t_color3f	texture_get_solid_color(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_sphere_dame(void *obj, t_double3 *coord)
{
	t_object	*pt;
	t_double2	text_coord;
	double		square_size;
	int			pixel;

	pt = (t_object *) obj;
	text_coord = sphere_map(pt, coord);
	square_size = 1 / (double) pt->texture.resolution;
	pixel = get_pixel_dame(&text_coord, square_size);
	if (pixel % 2 == 0)
		return (pt->texture.color1);
	else
		return (pt->texture.color2);
}

t_color3f	texture_get_plan_dame(void *obj, t_double3 *coord)
{
	t_object	*pt;
	t_double2	text_coord;
	double		square_size;
	int			pixel;

	pt = (t_object *) obj;
	text_coord = plane_map(obj, coord);
	square_size = 1 / (double) pt->texture.resolution;
	pixel = get_pixel_dame(&text_coord, square_size);
	if (pixel % 2 == 0)
		return (pt->texture.color1);
	else
		return (pt->texture.color2);
}

t_color3f	texture_get_cylinder_dame(void *obj, t_double3 *coord)
{
	t_object	*pt;
	t_double2	text_coord;
	double		square_size;
	int			pixel;

	pt = (t_object *) obj;
	text_coord = revolution_map(obj, coord);
	square_size = 1 / (double) pt->texture.resolution;
	pixel = get_pixel_dame(&text_coord, square_size);
	if (pixel % 2 == 0)
		return (pt->texture.color1);
	else
		return (pt->texture.color2);
}

t_color3f	texture_get_cone_dame(void *obj, t_double3 *coord)
{
	t_object	*pt;
	t_double2	text_coord;
	double		square_size;
	int			pixel;

	pt = (t_object *) obj;
	text_coord = revolution_map(obj, coord);
	square_size = 1 / (double) pt->texture.resolution;
	pixel = get_pixel_dame(&text_coord, square_size);
	if (pixel % 2 == 0)
		return (pt->texture.color1);
	else
		return (pt->texture.color2);
}
