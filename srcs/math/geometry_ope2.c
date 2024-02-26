/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_ope2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:04:58 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/26 13:37:53 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>

t_vec3f	vec3_scale(t_vec3f *vector, double scale)
{
	t_vec3f	new;

	new.x = vector->x * scale;
	new.y = vector->y * scale;
	new.z = vector->z * scale;
	return (new);
}

double	distance(t_vec3f *a, t_vec3f *b)
{
	double	dist;
	t_vec3f	vec_diff;

	vec_diff = vec3_diff(a, b);
	dist = scalar_product(&vec_diff, &vec_diff);
	return (dist);
}

t_vec3f	vec3f_get_dir(t_coord3f *a, t_coord3f *b)
{
	t_vec3f	dir;

	dir.x = b->x - a->x;
	dir.y = b->y - a->y;
	dir.z = b->z - a->z;
	normalize_vec(&dir);
	return (dir);
}
