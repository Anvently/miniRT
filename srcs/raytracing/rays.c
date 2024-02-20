/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:27:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/20 11:13:37 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/draw.h>
#include <minirt/calculus.h>
#include <minirt/types.h>
#include <libft.h>

static void	check_inter(t_data *data, t_ray *ray)
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
		node = node->next;
	}
}

void	check_lights(t_data *data, t_ray *ray)
{
	t_ray	ray_to_light;
	t_list	*node;
	t_light	*light;

	ft_memset(&ray_to_light, 0, sizeof(t_ray));
	ray_to_light.origin = ray->inter;
	node = data->scene.lights;
	while (node)
	{
		light = (t_light *)node->content;
		ray_to_light.dir = vec3f_get_dir(&ray_to_light.origin,
				&light->origin);
		ray_to_light.theta = scalar_product(&ray_to_light.dir,
				&ray_to_light.normal);
		ray_to_light.t = INFINITY;
		if (ray_to_light.theta > 0)
			check_inter(data, &ray_to_light);
		// if (ray_to_light.t != INFINITY)
		// 	// ray->color = ;
		node = node->next;
	}
}

void	launch_ray(t_data *data, t_ray *ray)
{
	check_inter(data, ray);
	if (ray->t == INFINITY)
		ray->color = (t_color3f){0.0, 0.0, 0.0};
	else
		color_filter(&ray->color, &data->scene.ambiant_light._ambiant);
	// printf("r=%f, g=%f, b=%f\n", ray->color.r, ray->color.g, ray->color.b);
	// check_lights(data, ray);
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
	normalize_vec(&ray.dir);
	// if (((int) pxl->x == 0 && (int) pxl->y == data->img_size.y - 1) || ((int) pxl->x == 0 && (int) pxl->y == 0)
	// 	|| ((int) pxl->x == data->img_size.x - 1 && (int) pxl->y == data->img_size.y - 1)
	// 	|| ((int) pxl->x == data->img_size.x - 1 && (int) pxl->y == 0))
	// {
	// 	printf("x=%f, y=%f\n", pxl->x, pxl->y);
	// 	print_t_double3(&ray.dir);
	// }
	return (ray);
}

t_color	get_ray_color(t_ray *ray)
{
	t_color	color;
	double	a;

	a = 0.5 * (ray->dir.y + 1.0);
	color.r = (1.0 - a) * 208 + a * 127;
	color.g = (1.0 - a) * 44 + a * 94;
	color.b = (1.0 - a) * 44 + a * 94;
	return (color);
}
