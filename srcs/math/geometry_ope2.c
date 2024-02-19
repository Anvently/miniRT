/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_ope2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:04:58 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/19 13:50:37 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt/calculus.h"
#include "../../includes/minirt/types.h"

t_vec3f	vec3_scale(t_vec3f *vector, double scale)
{
	t_vec3f	new;

	new.x = vector->x * scale;
	new.y = vector->y * scale;
	new.z = vector->z * scale;
	return (new);
}

double	distance(t_vec3f *a, t_vec3f *b)
{
	double	dist;
	t_vec3f	vec_diff;

	vec_diff = vec3_diff(a, b);
	dist = scalar_product(&vec_diff, &vec_diff);
	return (dist);
}
