/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:22:55 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 11:00:26 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <minirt/raytracing.h>

static t_color3f	compute_specular(t_ray *light_ray, t_light *light)
{
	t_color3f	l_specular;

	l_specular.r = light->color.r * light_ray->theta \
		* light_ray->inter_obj->color_specular.r;
	l_specular.g = light->color.g * light_ray->theta \
		* light_ray->inter_obj->color_specular.g;
	l_specular.b = light->color.b * light_ray->theta \
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
	ray->dir = vec3f_get_dir(&ray->origin,
			&light->origin);
	ray->theta = scalar_product(&ray->dir,
			&ray->normal);
	ray->t = INFINITY;
	if (ray->theta >= 0)
	{
		check_inter(data, ray);
		if (ray->t == INFINITY || ray->t == 0)
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

