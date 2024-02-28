/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:53:00 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/28 10:55:15 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>

int	bot_cap_intersec(t_object *cyld, t_ray *ray, double *t)
{
	double	a;
	double	b;
	t_vec3f	impact;

	a = scalar_product(&ray->dir, &cyld->orientation);
	b = (-1) * scalar_product(&cyld->origin, &cyld->orientation);
	b += scalar_product(&cyld->orientation, &ray->origin);
	if (!linear_solver(a, b, t))
		return (0);
	impact = get_inter_point(ray, *t);
	if (distance(&impact, &cyld->origin) > cyld->radius * cyld->radius)
		return (0);
	return (1);
}

int	top_cap_intersec(t_object *cyld, t_ray *ray, double *t)
{
	double	a;
	double	b;
	t_vec3f	impact;

	a = scalar_product(&ray->dir, &cyld->orientation);
	b = (-1) * scalar_product(&cyld->top, &cyld->orientation);
	b += scalar_product(&cyld->orientation, &ray->origin);
	if (!linear_solver(a, b, t))
		return (0);
	impact = get_inter_point(ray, *t);
	if (distance(&impact, &cyld->top) > cyld->radius * cyld->radius)
		return (0);
	return (1);
}

void	cylinder_update_normal(t_object *cyld, t_ray *ray, t_vec3f *temp)
{
	ray->inter = *temp;
	ray->normal = vec3_diff(&ray->inter, &cyld->origin);
	ray->normal = vector_product(&ray->normal, &cyld->orientation);
	ray->normal = vector_product(&cyld->orientation, &ray->normal);
	normalize_vec(&ray->normal);
	if (scalar_product(&ray->normal, &ray->dir) >= 0)
		ray->normal = vec3_scale(&ray->normal, -1);
}
