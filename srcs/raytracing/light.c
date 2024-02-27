/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:22:55 by npirard           #+#    #+#             */
/*   Updated: 2024/02/27 16:40:00 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <minirt/raytracing.h>

static t_color3f	compute_lights_obj(t_data *data, t_ray *ray,
						t_object *obj)
{
	t_object	*inter_obj;

	ray->dir = vec3f_get_dir(&ray->origin, &obj->origin);
	ray->theta = scalar_product(&ray->dir, &ray->normal);
	ray->t_max = sqrt(distance(&ray->origin, &obj->origin)) - T_MIN;
	ray->t = INFINITY;
	if (ray->theta >= 0)
	{
		inter_obj = ray->inter_obj;
		check_inter(data, ray);
		if (ray->inter_obj == obj)
		{
			ray->inter_obj = inter_obj;
			color_add(&ray->l_final, compute_diffuse(ray, &obj->_light));
			color_add(&ray->l_final, compute_specular(ray, &obj->_light));
		}
		ray->inter_obj = inter_obj;
	}
	return (ray->l_final);
}

void	check_light_obj(t_data *data, t_ray *ray)
{
	t_ray		ray_to_obj;
	t_list		*node;
	t_object	*obj;

	ft_memset(&ray_to_obj, 0, sizeof(t_ray));
	ray_to_obj.l_surface = ray->l_surface;
	ray_to_obj.origin = ray->inter;
	ray_to_obj.normal = ray->normal;
	ray_to_obj.inter_obj = ray->inter_obj;
	ray_to_obj.t_min = T_MIN;
	ray_to_obj.old_dir = ray->dir;
	ray_to_obj.type = CAMERA_RAY;
	node = data->scene.lights_obj;
	while (node)
	{
		obj = (t_object *)node->content;
		if (obj != ray->inter_obj)
			color_add(&ray->l_final,
				compute_lights_obj(data, &ray_to_obj, obj));
		node = node->next;
	}
}

t_color3f	compute_lights(t_data *data, t_ray *ray, t_light *light)
{
	ray->dir = vec3f_get_dir(&ray->origin, &light->origin);
	ray->theta = scalar_product(&ray->dir, &ray->normal);
	ray->t_max = sqrt(distance(&ray->origin, &light->origin)) - T_MIN;
	ray->t = INFINITY;
	if (ray->theta >= 0)
	{
		// if (ray->inter_obj == CYLINDER)
		// 	printf("theta=%f, normal=%f\n", ray->theta, ray->normal);
		check_inter(data, ray);
		if (ray->t >= ray->t_max || ray->t == 0)
		{
			color_add(&ray->l_final, compute_diffuse(ray, &light->_color));
			color_add(&ray->l_final, compute_specular(ray, &light->_color));
		}
	}
	return (ray->l_final);
}

void	check_lights(t_data *data, t_ray *ray)
{
	t_ray		ray_to_light;
	t_list		*node;
	t_light		*light;

	ft_memset(&ray_to_light, 0, sizeof(t_ray));
	ray_to_light.l_surface = ray->l_surface;
	ray_to_light.origin = ray->inter;
	ray_to_light.normal = ray->normal;
	ray_to_light.inter_obj = ray->inter_obj;
	ray_to_light.t_min = T_MIN;
	ray_to_light.old_dir = ray->dir;
	ray_to_light.type = LIGHT_RAY;
	node = data->scene.lights;
	while (node)
	{
		light = (t_light *)node->content;
		color_add(&ray->l_final,
			compute_lights(data, &ray_to_light, light));
		node = node->next;
	}
}

void	check_luminosity(t_data *data, t_ray *ray)
{
	compute_ambiant(ray, &data->scene.ambiant_light._color);
	if (ray->inter_obj->k_glow > 0)
		color_add(&ray->l_final,
			color_product(&ray->inter_obj->_glow, &ray->l_surface));
	check_lights(data, ray);
	check_light_obj(data, ray);
}
