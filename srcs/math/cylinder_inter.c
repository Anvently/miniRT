/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:21:21 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/20 15:16:16 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt/types.h"
#include "../../includes/minirt/calculus.h"

int	check_sol_tube(t_object *cyld, t_vec3f *sol)
{
	t_vec3f	origin_diff;
	t_vec3f	top_diff;
	double	x;
	double	y;

	origin_diff = vec3_diff(sol, &cyld->origin);
	top_diff = vec3_diff(sol, &cyld->top);
	x = scalar_product(&origin_diff, &cyld->orientation);
	y = scalar_product(&top_diff, &cyld->orientation);
	if ((x > 0) && (y < 0))
		return (1);
	return (0);
}

void	get_tube_intersec(t_object *cyld, t_ray *ray, t_vec3f *v_a, t_vec3f *v_o)
{
	double	a;
	double	b;
	double	c;
	double	t;
	t_vec3f	temp;

	a = scalar_product(v_a, v_a);
	b = 2 * scalar_product(v_a, v_o);
	c = scalar_product(v_o, v_o) - cyld->radius * cyld->radius;
	if (quadra_solver(a, b, c, &t) && t > ray->t_min && t < ray->t)
	{
		temp = get_inter_point(ray, t);
		if (!check_sol_tube(cyld, &temp))
			return ;
		ray->t = t;
		ray->inter = temp;
		temp = vec3_diff(&ray->inter, &cyld->origin);
		temp = vector_product(&temp, &cyld->orientation);
		temp = vector_product(&cyld->orientation, &temp);
		normalize_vec(&temp);
		ray->normal = temp;
		if (ray->t_min > -1.f)
			ray->inter_obj = cyld;
	}
}

void	tube_intersec(t_object *cyld, t_ray *ray)
{
	t_vec3f	v_a;
	t_vec3f	v_o;
	t_vec3f	origins;

	origins = vec3_diff(&ray->origin, &cyld->origin);
	v_a = vector_product(&ray->dir, &cyld->orientation);
	v_a = vector_product(&cyld->orientation, &v_a);
	v_o = vector_product(&origins, &cyld->orientation);
	v_o = vector_product(&cyld->orientation, &v_o);
	get_tube_intersec(cyld, ray, &v_a, &v_o);
}

void	cylinder_intersec(t_object *cylinder, t_ray *ray)
{
	double	t_cap;

	if (bot_cap_intersec(cylinder, ray, &t_cap) && t_cap < ray->t && t_cap > ray->t_min)
	{
		ray->t = t_cap;
		ray->normal = vec3_scale(&cylinder->orientation, -1);
		if (ray->t_min > 0.f)
			ray->inter_obj = cylinder;
		normalize_vec(&ray->normal);
	}
	if (top_cap_intersec(cylinder, ray, &t_cap) && t_cap < ray->t && t_cap > ray->t_min)
	{
		ray->t = t_cap;
		ray->normal = cylinder->orientation;
		if (ray->t_min > 0.f)
			ray->inter_obj = cylinder;
		normalize_vec(&ray->normal);
	}
	tube_intersec(cylinder, ray);
}
