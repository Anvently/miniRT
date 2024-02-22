/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:22:55 by npirard           #+#    #+#             */
/*   Updated: 2024/02/22 14:36:51 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <minirt/raytracing.h>

void	check_lights(t_data *data, t_ray *ray)
{
	t_ray		ray_to_light;
	t_list		*node;
	t_light		*light;

	compute_ambiant(ray, &data->scene.ambiant_light.color);
	ft_memset(&ray_to_light, 0, sizeof(t_ray));
	ray_to_light.origin = ray->inter;
	ray_to_light.normal = ray->normal;
	ray_to_light.inter_obj = ray->inter_obj;
	ray_to_light.t_min = 0.0000000001;
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

