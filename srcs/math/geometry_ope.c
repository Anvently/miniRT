/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_ope.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:53:31 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/26 13:37:48 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>

double	scalar_product(t_vec3f *t_u, t_vec3f *t_v)
{
	double	res;

	res = t_u->x * t_v->x + t_u->y * t_v->y + t_u->z * t_v->z;
	return (res);
}

void	normalize_vec(t_vec3f *t_u)
{
	double	norm;

	if (t_u->x == 0 && t_u->y == 0 && t_u->z == 0)
		return ;

	norm = sqrt(scalar_product(t_u, t_u));
	t_u->x /= norm;
	t_u->y /= norm;
	t_u->z /= norm;
}


t_vec3f	vector_product(t_vec3f *t_u, t_vec3f *t_v)
{
	t_vec3f	t_n;

	t_n.x = t_u->y * t_v->z - t_u->z * t_v->y;
	t_n.y = t_u->z * t_v->x - t_u->x * t_v->z;
	t_n.z = t_u->x * t_v->y - t_u->y * t_v->x;
	return (t_n);
}

t_vec3f	vec3_sum(t_vec3f *t_u, t_vec3f *t_v)
{
	t_vec3f	t_w;

	t_w.x = t_u->x + t_v->x;
	t_w.y = t_u->y + t_v->y;
	t_w.z = t_u->z + t_v->z;
	return (t_w);
}

t_vec3f	vec3_diff(t_vec3f *t_u, t_vec3f *t_v)
{
	t_vec3f	t_w;

	t_w.x = t_u->x - t_v->x;
	t_w.y = t_u->y - t_v->y;
	t_w.z = t_u->z - t_v->z;
	return (t_w);
}





