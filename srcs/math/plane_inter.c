/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:56:02 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/21 17:18:21 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt/types.h"
#include "../../includes/minirt/calculus.h"


/// @brief check if a given ray intersect a given plane.
/// If so update the ray data.
/// @param plane
/// @param ray
void	plane_intersec(t_object *plane, t_ray *ray)
{
	double	a;
	double	b;
	double	c;

	if (plane->type != PLAN)
		return ;
	a = scalar_product(&ray->dir, &plane->orientation);
	c = scalar_product(&plane->orientation, &plane->origin);
	b = scalar_product(&plane->orientation, &ray->origin) - c;
	if (linear_solver(a, b, &c) && c < ray->t && c > ray->t_min)
	{
		ray->t = c;
		ray->normal = plane->orientation;
		if (ray->type != LIGHT_RAY)
			ray->inter_obj = plane;
		normalize_vec(&ray->normal);
		if (scalar_product(&ray->dir, &plane->orientation) >= 0)
			ray->normal = vec3_scale(&ray->normal, -1);
	}
}

