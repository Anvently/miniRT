/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:22:55 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 16:09:41 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <minirt/raytracing.h>

static double	get_spec_ratio(t_ray *ray)
{
	double	ratio;
	t_vec3f	reflect;

	reflect.x = -ray->dir.x + 2.f * (ray->theta) * ray->normal.x;
	reflect.y = -ray->dir.y + 2.f * (ray->theta) * ray->normal.y;
	reflect.z = -ray->dir.z + 2.f * (ray->theta) * ray->normal.z;
	normalize_vec(&reflect);
	ratio = scalar_product(&reflect, &(t_vec3f){-ray->old_dir.x,
			-ray->old_dir.y, -ray->old_dir.z});
	if (ratio < 0.0)
		return (0.0);
	ratio = pow(ratio, ray->inter_obj->k_roughness);
	return (ratio);
}

static t_color3f	compute_specular(t_ray *light_ray, t_light *light)
{
	t_color3f	l_specular;
	double		ratio;

	ratio = get_spec_ratio(light_ray);
	l_specular.r = light->color.r * ratio \
		* light_ray->inter_obj->color_specular.r;
	l_specular.g = light->color.g * ratio \
		* light_ray->inter_obj->color_specular.g;
	l_specular.b = light->color.b * ratio \
		* light_ray->inter_obj->color_specular.b;
	return (l_specular);
}

static t_color3f	compute_diffuse(t_ray *light_ray, t_light *light)
{
	t_color3f	l_diffuse;

	l_diffuse.r = light->color.r * light_ray->theta \
		* light_ray->inter_obj->color_diffuse.r;
	l_diffuse.g = light->color.g * light_ray->theta \
		* light_ray->inter_obj->color_diffuse.g;
	l_diffuse.b = light->color.b * light_ray->theta \
		* light_ray->inter_obj->color_diffuse.b;
	return (l_diffuse);
}

static t_color3f	compute_lights(t_data *data, t_ray *ray, t_light *light)
{
	ray->dir = vec3f_get_dir(&ray->origin, &light->origin);
	ray->theta = scalar_product(&ray->dir, &ray->normal);
	ray->t_max = sqrt(distance(&ray->origin, &light->origin)) -0.000001;
	ray->t = INFINITY;
	if (ray->theta >= 0)
	{
		check_inter(data, ray);
		if (ray->t >= ray->t_max || ray->t == 0)
		{
			color_add(&ray->l_final, compute_diffuse(ray, light));
			color_add(&ray->l_final, compute_specular(ray, light));
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
	ray_to_light.origin = ray->inter;
	ray_to_light.normal = ray->normal;
	ray_to_light.inter_obj = ray->inter_obj;
	ray_to_light.t_min = 0.0000000001;
	ray_to_light.old_dir = ray->dir;
	node = data->scene.lights;
	while (node)
	{
		light = (t_light *)node->content;
		color_add(&ray->l_final,
			compute_lights(data, &ray_to_light, light));
		node = node->next;
	}
}

// t_color	get_ray_color(t_ray *ray)
// {
// 	t_color	color;
// 	double	a;

// 	a = 0.5 * (ray->dir.y + 1.0);
// 	color.r = (1.0 - a) * 208 + a * 127;
// 	color.g = (1.0 - a) * 44 + a * 94;
// 	color.b = (1.0 - a) * 44 + a * 94;
// 	return (color);
// }

