/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:20:20 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/15 08:59:03 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include "../../includes/minirt/calculus.h"

void	sphere_normal(t_object *sphere, t_ray *ray)
{
	t_vec3f	impact;

	impact = get_inter_point(ray);
	ray->normal = vec3_diff(&impact, &sphere->origin);
	ray->normal.x /= sphere->diameter;
	ray->normal.y /= sphere->diameter;
	ray->normal.z /= sphere->diameter;
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
	c = scalar_product(&t_r, &t_r) - sphere->diameter * sphere->diameter;
	if (quadra_solver(a, b, c, &t) && t >= 1 && t < ray->t)
	{
		ray->t = t;
		sphere_normal(sphere, ray);
	}

}

