/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:23:19 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/28 10:57:01 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>
#include <math.h>

double	self_sp(t_vec3f *vec)
{
	double	res;

	res = scalar_product(vec, vec);
	return (res);
}

int	check_coordinates(t_double3	*cd)
{
	if (cd->x < -T_MIN)
		return (0);
	if (cd->y < -T_MIN)
		return (0);
	if (cd->z > 1 + T_MIN)
		return (0);
	return (1);
}

int	check_inside_triangle(t_object *tr, t_vec3f *impact)
{
	t_vec3f		delta;
	t_double3	cd;
	t_double3	temp;

	delta = vec3_diff(impact, &tr->tr1);
	temp.x = scalar_product(&tr->origin, &tr->top);
	temp.z = self_sp(&tr->origin) * self_sp(&tr->top) - temp.x * temp.x;
	temp.x = scalar_product(&delta, &tr->origin) * \
	scalar_product(&tr->top, &tr->top);
	temp.y = scalar_product(&delta, &tr->top) * \
	scalar_product(&tr->origin, &tr->top);
	cd.x = (temp.x - temp.y) / temp.z;
	temp.x = scalar_product(&delta, &tr->top) * \
	scalar_product(&tr->origin, &tr->origin);
	temp.y = scalar_product(&delta, &tr->origin) * \
	scalar_product(&tr->origin, &tr->top);
	cd.y = (temp.x - temp.y) / temp.z;
	cd.z = cd.x + cd.y;
	return (check_coordinates(&cd));
}

void	triangle_inter(t_object *tr, t_ray *ray)
{
	t_double2	coeff;
	double		t;
	t_vec3f		temp;

	t = 0;
	temp = vec3_diff(&ray->origin, &tr->tr1);
	coeff.x = scalar_product(&ray->dir, &tr->orientation);
	coeff.y = scalar_product(&temp, &tr->orientation);
	if (linear_solver(coeff.x, coeff.y, &t) && t < ray->t && t > ray->t_min)
	{
		temp = get_inter_point(ray, t);
		if (!check_inside_triangle(tr, &temp))
			return ;
		ray->inter = temp;
		ray->t = t;
		if (ray->type != LIGHT_RAY)
		{
			ray->normal = tr->orientation;
			ray->inter_obj = tr;
			normalize_vec(&ray->normal);
			if (scalar_product(&ray->dir, &tr->orientation) >= T_MIN)
				ray->normal = vec3_scale(&ray->normal, -1);
		}
	}
}
