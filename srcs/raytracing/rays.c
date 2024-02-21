/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:27:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 09:38:47 by npirard          ###   ########.fr       */
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
		// if (ray->inter_obj && ray->inter_obj == obj)
		// 	return ;
		if (obj->type == PLAN)
			plane_intersec(obj, ray);
		else if (obj->type == SPHERE)
			sphere_intersec(obj, ray);
		else if (obj->type == CYLINDER)
			cylinder_intersec(obj, ray);
		node = node->next;
		if (ray->t_min < 1.0 && ray->t != INFINITY)
			break ;
	}
}

t_color3f	get_ray_color(t_ray *ray)
{
	t_color		color;
	t_color3f	color3f;
	double		a;

	a = 0.5 * (ray->dir.y + 1.0);
	color.r = (1.0 - a) * 208 + a * 127;
	color.g = (1.0 - a) * 44 + a * 94;
	color.b = (1.0 - a) * 44 + a * 94;
	color3f = color_normalize(&color);
	return (color3f);
}

void	launch_ray(t_data *data, t_ray *ray)
{
	check_inter(data, ray);
	if (ray->inter_obj)
	{
		ray->inter = get_inter_point(ray, ray->t);
		ray->l_ambiant = color_product(&ray->inter_obj->color,
				&data->scene.ambiant_light._ambiant);
		check_lights(data, ray);
		ray->l_final.r = ray->l_diffuse.r + ray->l_ambiant.r + ray->l_spec.r;
		ray->l_final.g = ray->l_diffuse.g + ray->l_ambiant.g + ray->l_spec.g;
		ray->l_final.b = ray->l_diffuse.b + ray->l_ambiant.b + ray->l_spec.b;
	}
	color_unsature(&ray->l_final);
	// if (ray->t != INFINITY)
	// 	ray->l_final = ray->color_obj;

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

