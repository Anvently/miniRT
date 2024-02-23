/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_get2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:36:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/23 10:40:24 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <minirt/objects.h>

t_color3f	texture_get_sphere_img(void *obj, t_double3 *coord)
{
	t_color3f	color;
	t_object	*object;
	t_coord2f	text_coord;

	object = (t_object *)obj;
	text_coord = sphere_map(object, coord);
	printf("x=%f, y =%f\n",text_coord.x, text_coord.y);
	printf("ratio = %f\n", (2.f * (double) object->texture.height) \
		/ (double) object->texture.width);
	printf("width=%d, height=%d\n", object->texture.width, object->texture.height);
	text_coord.x *= (2.f * (double) object->texture.height) \
		/ (double) object->texture.width;
	color = texture_img_get_pxl(&object->texture,
			(int)(text_coord.x * object->texture.width),
			(int)(text_coord.y * object->texture.height));
	return (color);
}

// t_color3f	texture_get_sphere_img(void *obj, t_double3 *coord)
// {
// 	t_color3f	color;
// 	t_object	*object;
// 	t_coord2f	text_coord;
// 	int			x;

// 	object = (t_object *)obj;
// 	text_coord = sphere_map(object, coord);
// 	x = (int)(text_coord.x * object->texture.width) * \
// 		(2.f * (double) object->texture.height) \
// 		/ (double) object->texture.width;
// 	text_coord.x = x / ((2.f * (double) object->texture.height) \
// 		/ (double) object->texture.width);
// 	color = texture_img_get_pxl(&object->texture,
// 			(int)(text_coord.x * object->texture.width),
// 			(int)(text_coord.y * object->texture.height));
// 	return (color);
// }

t_color3f	texture_get_plan_img(void *obj, t_double3 *coord)
{
	t_color3f	color;
	t_object	*object;
	t_coord2f	text_coord;

	object = (t_object *)obj;
	text_coord = plane_map(object, coord);
	coord_abs(&text_coord);
	color = texture_img_get_pxl(&object->texture,
			(int)(text_coord.x * object->texture.width),
			(int)(text_coord.y * object->texture.height));
	return (color);
}

t_color3f	texture_get_cylinder_img(void *obj, t_double3 *coord)
{
	(void)coord;
	return ((t_color3f){0,120,120});
	return (((t_object *)obj)->texture.color1);
}

t_color3f	texture_get_cone_img(void *obj, t_double3 *coord)
{
	(void)coord;
	return ((t_color3f){0,120,120});
	return (((t_object *)obj)->texture.color1);
}
