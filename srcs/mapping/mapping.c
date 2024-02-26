/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:31:16 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/26 14:34:49 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>
#include <math.h>

t_double2	sphere_map(t_object *sph, t_vec3f *p)
{
	double		theta;
	double		phi;
	double		angle;
	t_double2	coord;

	angle = fmod(sph->angle, 2 * M_PI);
	if (angle < 0.f)
		angle = 2 * M_PI + angle;
	phi = atan2(p->y - sph->origin.y, p->x - sph->origin.x);
	phi -= angle;
	phi = fmod(phi, 2 * M_PI);
	theta = acos((p->z - sph->origin.z) / sph->radius);
	coord.x = 0.5 - phi / (2 * M_PI);
	coord.x = 1 - coord.x;
	coord.y = 1 - theta / M_PI;
	coord.y = 1 - coord.y;
	return (coord);
}

t_double2	plane_map(t_object *plane, t_vec3f *p)
{
	t_double2	coord;
	t_vec3f		plane_vector;

	plane_vector = vec3_diff(p, &plane->origin);
	coord.x = fmod(scalar_product(&plane_vector, &plane->loc_x), 1);
	coord.y = fmod(scalar_product(&plane_vector, &plane->loc_y), 1);
	return (coord);
}

t_double2	revolution_map(t_object *obj, t_vec3f *p)
{
	t_double3	local_coord;
	t_double2	map_coord;
	double		theta;
	t_vec3f		cyl_vector;

	cyl_vector = vec3_diff(p, &obj->origin);
	local_coord.x = scalar_product(&cyl_vector, &obj->loc_x);
	local_coord.y = scalar_product(&cyl_vector, &obj->loc_y);
	local_coord.z = scalar_product(&cyl_vector, &obj->orientation);
	theta = atan2(local_coord.y, local_coord.x);
	map_coord.x = 0.5 - (theta / (2 * M_PI));
	map_coord.y = local_coord.z / obj->height;
	return (map_coord);
}
