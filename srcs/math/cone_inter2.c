/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_inter2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:32:04 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/26 17:32:17 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>
#include <math.h>

int	check_sol_body(t_object *cone, t_vec3f *sol)
{
	double	h;
	t_vec3f	temp;

	temp = vec3_diff(sol, &cone->origin);
	h = scalar_product(&temp, &cone->orientation);
	if ((h >= 0) && (h <= cone->height))
		return (1);
	return (0);
}

int	examine_sol(t_double3 *t, t_object *cone, t_ray *ray)
{
	t_vec3f	impact;

	if ((t->y > ray->t_min) && (t->y < ray->t))
	{
		impact = get_inter_point(ray, t->y);
		if (check_sol_body(cone, &impact))
		{
			t->z = t->y;
			return (1);
		}
	}
	if ((t->x > ray->t_min) && (t->x < ray->t))
	{
		impact = get_inter_point(ray, t->x);
		if (check_sol_body(cone, &impact))
		{
			t->z = t->x;
			return (1);
		}
	}
	return (0);
}
