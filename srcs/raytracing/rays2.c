/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:27:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/26 13:41:11 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/draw.h>
#include <minirt/calculus.h>
#include <minirt/types.h>
#include <minirt/raytracing.h>
#include <libft.h>

t_color3f	get_reflect_color(t_data *data, t_ray *previous_ray)
{
	t_ray	reflect;

	ft_memset(&reflect, 0, sizeof(t_ray));
	reflect.type = REFLECT_RAY;
	previous_ray->theta = scalar_product(&previous_ray->dir,
			&previous_ray->normal);
	previous_ray->theta *= -1.f;
	reflect.dir.x = previous_ray->dir.x + 2.f * (previous_ray->theta)
		* previous_ray->normal.x;
	reflect.dir.y = previous_ray->dir.y + 2.f * (previous_ray->theta)
		* previous_ray->normal.y;
	reflect.dir.z = previous_ray->dir.z + 2.f * (previous_ray->theta)
		* previous_ray->normal.z;
	reflect.origin = previous_ray->inter;
	normalize_vec(&reflect.dir);
	reflect.nbr_bounce = previous_ray->nbr_bounce + 1;
	reflect.t_min = 0.000001;
	reflect.t = INFINITY;
	launch_ray(data, &reflect);
	return (reflect.l_final);
}

static t_vec3f	compute_refract_dir(t_ray *previous_ray)
{
	t_vec3f	dir;
	double	theta_r;
	double	k_i;
	double	k_r;

	k_i = 1.0;
	k_r = previous_ray->inter_obj->i_refraction;
	if (previous_ray->inside_obj)
		k_i = previous_ray->inside_obj->i_refraction;
	if (previous_ray->inside_obj == previous_ray->inter_obj)
		k_r = 1.0;
	k_r = k_i / k_r;
	theta_r = 1.f - (k_r * k_r) * \
		(1 - (previous_ray->theta * previous_ray->theta));
	if (theta_r < 0.f)
		return ((t_vec3f){0, 0, 0});
	theta_r = sqrt(theta_r);
	dir.x = (k_r * previous_ray->theta - theta_r) \
		* previous_ray->normal.x - k_r * -previous_ray->dir.x;
	dir.y = (k_r * previous_ray->theta - theta_r) \
		* previous_ray->normal.y - k_r * -previous_ray->dir.y;
	dir.z = (k_r * previous_ray->theta - theta_r) \
		* previous_ray->normal.z - k_r * -previous_ray->dir.z;
	return (dir);
}

t_color3f	get_refract_color(t_data *data, t_ray *previous_ray)
{
	t_ray	refract;

	ft_memset(&refract, 0, sizeof(t_ray));
	refract.type = REFRACT_RAY;
	previous_ray->theta = -scalar_product(&previous_ray->dir,
			&previous_ray->normal);
	refract.dir = compute_refract_dir(previous_ray);
	if (refract.dir.x == 0.0 && refract.dir.y == 0.0 && refract.dir.z == 0)
		return ((t_color3f){0.0, 0.0, 0.0});
	if (previous_ray->inter_obj->type != PLAN)
		refract.inside_obj = previous_ray->inter_obj;
	refract.origin = previous_ray->inter;
	normalize_vec(&refract.dir);
	refract.nbr_bounce = previous_ray->nbr_bounce + 1;
	refract.t_min = 0.000001;
	refract.t = INFINITY;
	launch_ray(data, &refract);
	return (refract.l_final);
}
