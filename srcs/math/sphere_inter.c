/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:20:20 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/28 10:49:12 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>

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
	double		t;
	t_vec3f		t_r;

	t = 0.0;
	if (sphere->type != SPHERE)
		return ;
	t_r = vec3_diff(&ray->origin, &sphere->origin);
	coeff.x = scalar_product(&ray->dir, &ray->dir);
	coeff.y = 2 * scalar_product(&t_r, &ray->dir);
	coeff.z = scalar_product(&t_r, &t_r) - sphere->radius * sphere->radius;
	if (quadra_solver(&coeff, &t, ray->t_min) && t > ray->t_min && t < ray->t)
	{
		ray->t = t;
		if (ray->type != LIGHT_RAY)
		{
			ray->inter_obj = sphere;
			sphere_normal(sphere, ray);
		}
	}
}
