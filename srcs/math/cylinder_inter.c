/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:21:21 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/26 17:46:24 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>

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

void	get_tube_intersec(t_object *cyld, t_ray *ray,
			t_vec3f *v_a, t_vec3f *v_o)
{
	t_double3	coefficients;
	double		t;
	t_vec3f		temp;

	t = 0.0;
	coefficients.x = scalar_product(v_a, v_a);
	coefficients.y = 2 * scalar_product(v_a, v_o);
	coefficients.z = scalar_product(v_o, v_o) - cyld->radius * cyld->radius;
	if (quadra_solver(&coefficients, &t, ray->t_min)
		&& t > ray->t_min && t < ray->t)
	{
		temp = get_inter_point(ray, t);
		if (!check_sol_tube(cyld, &temp))
			return ;
		ray->t = t;
		ray->inter = temp;
		ray->normal = vec3_diff(&ray->inter, &cyld->origin);
		ray->normal = vector_product(&temp, &cyld->orientation);
		ray->normal = vector_product(&cyld->orientation, &temp);
		normalize_vec(&ray->normal);
		if (scalar_product(&ray->normal, &ray->dir) >= 0)
			ray->normal = vec3_scale(&ray->normal, -1);
		if (ray->type != LIGHT_RAY)
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

void	cylinder_top_cap(t_object *cylinder, t_ray *ray, double t_cap)
{
	if (top_cap_intersec(cylinder, ray, &t_cap)
		&& t_cap < ray->t && t_cap > ray->t_min)
	{
		ray->t = t_cap;
		ray->normal = cylinder->orientation;
		if (ray->type != LIGHT_RAY)
			ray->inter_obj = cylinder;
		normalize_vec(&ray->normal);
		if (scalar_product(&ray->normal, &ray->dir) > 0)
			ray->normal = vec3_scale(&ray->normal, -1);
	}
}

void	cylinder_intersec(t_object *cylinder, t_ray *ray)
{
	double	t_cap;

	t_cap = 0.0;
	if (bot_cap_intersec(cylinder, ray, &t_cap)
		&& t_cap < ray->t && t_cap > ray->t_min)
	{
		ray->t = t_cap;
		ray->normal = vec3_scale(&cylinder->orientation, -1);
		if (ray->type != LIGHT_RAY)
			ray->inter_obj = cylinder;
		normalize_vec(&ray->normal);
		if (scalar_product(&ray->normal, &ray->dir) > 0)
			ray->normal = vec3_scale(&ray->normal, -1);
	}
	cylinder_top_cap(cylinder, ray, t_cap);
	tube_intersec(cylinder, ray);
}
