/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:20:20 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/21 11:09:42 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include "../../includes/minirt/calculus.h"

void	sphere_normal(t_object *sphere, t_ray *ray)
{
	t_vec3f	impact;

	impact = get_inter_point(ray, ray->t);
	ray->normal = vec3_diff(&impact, &sphere->origin);
	ray->normal.x /= sphere->radius;
	ray->normal.y /= sphere->radius;
	ray->normal.z /= sphere->radius;
	if (scalar_product(&ray->dir, &ray->normal) >= 0)
		ray->normal = vec3_scale(&ray->normal, -1);
}

void	sphere_intersec(t_object *sphere, t_ray *ray)
{
	t_double3	coeff;
	double	t;
	t_vec3f	t_r;

	if (sphere->type != SPHERE)
		return ;
	t_r = vec3_diff(&ray->origin, &sphere->origin);
	coeff.x = scalar_product(&ray->dir, &ray->dir);
	coeff.y = 2 * scalar_product(&t_r, &ray->dir);
	coeff.z = scalar_product(&t_r, &t_r) - sphere->radius * sphere->radius;
	if (quadra_solver(&coeff, &t, ray->t_min) && t > ray->t_min && t < ray->t)
	{
		ray->t = t;
		if (ray->t_min == 1)
			ray->inter_obj = sphere;
		sphere_normal(sphere, ray);
	}

}

