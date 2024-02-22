/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:36:51 by npirard           #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/02/22 14:02:16 by npirard          ###   ########.fr       */
=======
/*   Updated: 2024/02/22 14:24:14 by lmahe            ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>

<<<<<<< Updated upstream
t_color3f	texture_get_solid_color(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_sphere_dame(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_plan_dame(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_cylinder_dame(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_cone_dame(void *obj, t_double3 *coord)
{
	(void)coord;
	return (((t_object *)obj)->texture.color1);
}
=======
// t_color3f	texture_get_solid_color(void *obj, t_double3 *coord)
// {
// 	return (((t_object *)obj)->texture.color1);
// }

// t_color3f	texture_get_sphere_dame(void *obj, t_double3 *coord)
// {
// 	return (((t_object *)obj)->texture.color1);
// }

t_color3f	texture_get_plan_dame(void *obj, t_double3 *coord)
{
	t_object	*pt;
	t_double2	text_coord;
	double		square_size;
	int			pixel;

	pt = (t_object *) obj;
	text_coord = plane_map(obj, coord);
	square_size = 1 / (double) pt->texture.resolution;
	pixel = get_pixel_dame_coord(&text_coord, square_size);
	if (pixel % 2 == 0)
		return (pt->texture.color1);
	else
		return (pt->texture.color2);
}

// t_color3f	texture_get_cylinder_dame(void *obj, t_double3 *coord)
// {
// 	return (((t_object *)obj)->texture.color1);
// }

// t_color3f	texture_get_cone_dame(void *obj, t_double3 *coord)
// {
// 	return (((t_object *)obj)->texture.color1);
// }
>>>>>>> Stashed changes
