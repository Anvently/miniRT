/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:27:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 16:09:53 by npirard          ###   ########.fr       */
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
		//if (ray->inter_obj && ray->inter_obj == obj)
		//	return ;
		if (obj->type == PLAN)
			plane_intersec(obj, ray);
		else if (obj->type == SPHERE)
			sphere_intersec(obj, ray);
		else if (obj->type == CYLINDER)
			cylinder_intersec(obj, ray);
		else if (obj->type == CONE)
			cone_intersec(obj, ray);
		node = node->next;
		if (ray->t_min < 1.0 && ray->t != INFINITY)
			break ;
	}
}

t_color3f	get_reflect_color(t_data *data, t_ray *previous_ray)
{
	t_ray	reflect;

	ft_memset(&reflect, 0, sizeof(t_ray));
	// printf("previous ray dir\n");
	// print_t_double3(&previous_ray->dir);
	// printf("previous ray normal\n");
	// print_t_double3(&previous_ray->normal);
	previous_ray->theta = scalar_product(&previous_ray->dir, &previous_ray->normal);
	previous_ray->theta *= -1.f;
	reflect.dir.x = previous_ray->dir.x + 2.f * (previous_ray->theta)
			* previous_ray->normal.x;
	reflect.dir.y = previous_ray->dir.y + 2.f * (previous_ray->theta)
			* previous_ray->normal.y;
	reflect.dir.z = previous_ray->dir.z + 2.f * (previous_ray->theta)
			* previous_ray->normal.z;
	reflect.origin = previous_ray->inter;
	normalize_vec(&reflect.dir);
	// printf("reflect ray dir\n");
	// print_t_double3(&reflect.dir);
	reflect.nbr_bounce = previous_ray->nbr_bounce + 1;
	reflect.t_min = 0.01;
	reflect.t = INFINITY;
	launch_ray(data, &reflect);
	return (reflect.l_final);
}

void	launch_ray(t_data *data, t_ray *ray)
{
	t_color3f	l_reflect;

	check_inter(data, ray);
	if (ray->inter_obj)
	{
		ray->inter = get_inter_point(ray, ray->t);
		ray->l_final = color_product(&ray->inter_obj->color,
				&data->scene.ambiant_light._ambiant);
		check_lights(data, ray);
		if (ray->inter_obj->k_reflexion > 0.0 && ray->nbr_bounce < 3)
		{
			l_reflect = get_reflect_color(data, ray);
			l_reflect = color_ratio(&l_reflect, ray->inter_obj->k_reflexion);
			ray->l_final = color_ratio(&ray->l_final,
					1.f - ray->inter_obj->k_reflexion);
			color_add(&ray->l_final, l_reflect);
		}
		color_unsature(&ray->l_final);
	}
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

