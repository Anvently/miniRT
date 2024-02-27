/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:27:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/27 09:15:37 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/draw.h>
#include <minirt/calculus.h>
#include <minirt/types.h>
#include <minirt/raytracing.h>
#include <libft.h>

void	check_inter(t_data *data, t_ray *ray)
{
	t_list		*node;
	t_object	*obj;

	node = data->scene.objects;
	while (node)
	{
		obj = (t_object *)node->content;
		if (obj->type == PLAN)
			plane_intersec(obj, ray);
		else if (obj->type == SPHERE)
			sphere_intersec(obj, ray);
		else if (obj->type == CYLINDER)
			cylinder_intersec(obj, ray);
		else if (obj->type == CONE)
			cone_intersec(obj, ray);
		else if (obj->type == TR)
			triangle_inter(obj, ray);
		node = node->next;
		if (ray->type == LIGHT_RAY && ray->t != INFINITY)
			break ;
	}
}

void	launch_ray(t_data *data, t_ray *ray)
{
	t_color3f	l_reflect;
	t_color3f	l_refract;

	check_inter(data, ray);
	if (ray->inter_obj == NULL)
		return ;
	ray->inter = get_inter_point(ray, ray->t);
	ray->l_surface = (*ray->inter_obj->texture.get_color) \
		(ray->inter_obj, &ray->inter);
	check_luminosity(data, ray);
	if (ray->inter_obj->k_reflexion > 0.01 && ray->nbr_bounce < 3)
	{
		l_reflect = get_reflect_color(data, ray);
		color_add(&ray->l_final,
			color_ratio(&l_reflect, ray->inter_obj->k_reflexion));
	}
	if (ray->inter_obj->k_reflexion > 0.f
		&& ray->inter_obj->k_reflexion < 0.99 && ray->nbr_bounce < 3)
	{
		l_refract = get_refract_color(data, ray);
		color_add(&ray->l_final, color_ratio(&l_refract,
				1.f - ray->inter_obj->k_reflexion));
	}
	color_unsature(&ray->l_final);
}

t_ray	generate_ray(t_coord2f *pxl, t_data *data)
{
	t_ray	ray;
	t_vec3f	upxl;
	t_vec3f	vpxl;

	ft_memset(&ray, 0, sizeof(t_ray));
	ray.origin = data->scene.camera.origin;
	ray.dir = vec3_sum(&data->scene.camera._cx, &data->scene.camera._r);
	upxl = vec3_scale(&data->scene.camera._u, (double) pxl->x);
	vpxl = vec3_scale(&data->scene.camera._v, (double) pxl->y);
	ray.dir = vec3_sum(&ray.dir, &upxl);
	ray.dir = vec3_sum(&ray.dir, &vpxl);
	ray.t = INFINITY;
	ray.t_min = 1.0;
	ray.type = CAMERA_RAY;
	normalize_vec(&ray.dir);
	return (ray);
}
