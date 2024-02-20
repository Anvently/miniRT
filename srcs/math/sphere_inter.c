/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:20:20 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/20 15:16:36 by npirard          ###   ########.fr       */
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
}

void	sphere_intersec(t_object *sphere, t_ray *ray)
{
	double	a;
	double	b;
	double	c;
	double	t;
	t_vec3f	t_r;

	if (sphere->type != SPHERE)
		return ;
	t_r = vec3_diff(&ray->origin, &sphere->origin);
	a = scalar_product(&ray->dir, &ray->dir);
	b = 2 * scalar_product(&t_r, &ray->dir);
	c = scalar_product(&t_r, &t_r) - sphere->radius * sphere->radius;
	if (quadra_solver(a, b, c, &t) && t > ray->t_min && t < ray->t)
	{
		ray->t = t;
		if (ray->t_min == 1)
			ray->inter_obj = sphere;
		sphere_normal(sphere, ray);
	}

}

