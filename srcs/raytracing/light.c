/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:22:55 by npirard           #+#    #+#             */
/*   Updated: 2024/02/20 17:37:56 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <minirt/raytracing.h>

static t_color3f	compute_diffusion(t_data *data, t_ray *ray, t_light *light)
{
	ray->dir = vec3f_get_dir(&ray->origin,
			&light->origin);
	ray->theta = scalar_product(&ray->dir,
			&ray->normal);
	// printf("type=%d, scal=%f\n", (int) ray->inter_obj->type, scalar_product(&ray->normal, &ray->inter_obj->orientation));
	// print_t_double3(&ray->normal);
	ray->t = INFINITY;
	if (ray->theta >= 0)
	{
		check_inter(data, ray);
		if (ray->t == INFINITY || ray->t == 0)
		{
			ray->l_diffuse.r = light->color.r * ray->theta \
				* ray->inter_obj->color_diffuse.r;
			ray->l_diffuse.g = light->color.g * ray->theta \
				* ray->inter_obj->color_diffuse.g;
			ray->l_diffuse.b = light->color.b * ray->theta \
				* ray->inter_obj->color_diffuse.b;
		}
	}
	// if (ray->t != INFINITY)
	// 	printf("t=%f\n", ray->t);
	// if (ray->theta >= 0)
	// {

	// }
	// else if (ray->theta < 0)
	// {
	// 	// printf()
	// 	ray->theta = 0.0;
	// }
	// color_filter(&ray->l_diffuse, &ray->inter_obj->color);
	return (ray->l_diffuse);
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
		ray->l_diffuse = compute_diffusion(data, &ray_to_light, light);
		//color_filter(&ray->color, &ray_to_light.color);
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

