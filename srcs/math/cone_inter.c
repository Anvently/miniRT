/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:41:22 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/22 16:36:52 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>
#include <math.h>


int	check_sol_body(t_object *cone, t_vec3f *sol)
{
	t_vec3f	origin_diff;
	t_vec3f	top_diff;
	double	x;
	double	y;

	origin_diff = vec3_diff(sol, &cone->origin);
	top_diff = vec3_diff(sol, &cone->top);
	x = scalar_product(&origin_diff, &cone->orientation);
	y = scalar_product(&top_diff, &cone->orientation);
	if ((x > 0) && (y < 0))
		return (1);
	return (0);
}

static void	get_body_intersec(t_object *cone, t_ray *ray, t_double3 *coeff)
{
	double	t;
	t_vec3f	temp;

	t = 0.0;
	if (quadra_solver(coeff, &t, ray->t_min) && t < ray->t && t > ray->t_min)
	{
		temp = get_inter_point(ray, t);
		if (!check_sol_body(cone, &temp))
			return ;
		ray->t = t;
		ray->inter = temp;
		temp = vec3_diff(&ray->inter, &cone->origin);
		temp = vector_product(&temp, &cone->orientation);
		temp = vector_product(&cone->orientation, &temp);
		normalize_vec(&temp);
		ray->normal = temp;
		if (scalar_product(&ray->normal, &ray->dir) >= 0)
			ray->normal = vec3_scale(&ray->normal, -1);
		if (ray->type != LIGHT_RAY)
			ray->inter_obj = cone;
	}
}

void	main_body_intersec(t_object *cone, t_ray *ray)
{
	t_vec3f		v_a;
	t_vec3f		r_ao;
	t_vec3f		h_o;
	t_double3	temp;
	t_double3	coeff;

	temp.x = scalar_product(&ray->dir, &cone->orientation);
	temp.y = cone->radius / cone->height;
	v_a = vector_product(&cone->orientation, &ray->dir);
	v_a = vector_product(&v_a, &cone->orientation);
	r_ao = vec3_diff(&ray->origin, &cone->origin);
	r_ao = vector_product(&cone->orientation, &r_ao);
	r_ao = vector_product(&r_ao, &cone->orientation);
	h_o = vec3_diff(&ray->origin, &cone->origin);
	temp.z = cone->height - scalar_product(&h_o, &cone->orientation);
	coeff.x = scalar_product(&v_a, &v_a);
	coeff.y = 2 * scalar_product(&r_ao, &v_a);
	coeff.z = scalar_product(&r_ao, &r_ao);
	coeff.x -= temp.x * temp.x * temp.y * temp.y;
	coeff.y += 2 * temp.x * temp.z * temp.y * temp.y;
	coeff.z -= temp.y * temp.y * temp.z * temp.z;
	get_body_intersec(cone, ray, &coeff);
}

int	base_intersect(t_object *cone, t_ray *ray, double *t)
{
	double	a;
	double	b;
	t_vec3f	impact;

	a = scalar_product(&ray->dir, &cone->orientation);
	b = (-1) * scalar_product(&cone->origin, &cone->orientation);
	b += scalar_product(&cone->orientation, &ray->origin);
	if (!linear_solver(a, b, t))
		return (0);
	impact = get_inter_point(ray, *t);
	if (distance(&impact, &cone->origin) > cone->radius * cone->radius)
		return (0);
	return (1);
}

void	cone_intersec(t_object *cone, t_ray *ray)
{
	double	t_cap;

	t_cap = 0.0;
	if (base_intersect(cone, ray, &t_cap) && t_cap > ray->t_min && t_cap < ray->t)
	{
		ray->t = t_cap;
		ray->normal = vec3_scale(&cone->orientation, -1);
		normalize_vec(&ray->normal);
		if (ray->type != LIGHT_RAY)
			ray->inter_obj = cone;
	}
	main_body_intersec(cone, ray);
}
