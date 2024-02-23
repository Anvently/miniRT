/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:27:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/23 18:47:50 by npirard          ###   ########.fr       */
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
	// printf("refract dir :\n");
	// print_t_double3(&refract.dir);
	// print_t_double3(&previous_ray->dir);
	launch_ray(data, &refract);
	return (refract.l_final);
}

void	launch_ray(t_data *data, t_ray *ray)
{
	t_color3f	l_reflect;
	t_color3f	l_refract;

	check_inter(data, ray);
	if (ray->inter_obj)
	{
		ray->inter = get_inter_point(ray, ray->t);
		ray->l_surface = (*ray->inter_obj->texture.get_color) \
			(ray->inter_obj, &ray->inter);
		check_lights(data, ray);
		if (ray->inter_obj->k_reflexion > 0.0 && ray->nbr_bounce < 3)
		{
			// if (ray->inter_obj->id == 1)
			// 	printf("PING\n");
			l_reflect = get_reflect_color(data, ray);
			l_refract = get_refract_color(data, ray);
			l_reflect = color_ratio(&l_reflect, ray->inter_obj->k_reflexion);
			l_refract = color_ratio(&l_refract,
					1.f - ray->inter_obj->k_reflexion);
			color_add(&ray->l_final, l_reflect);
			color_add(&ray->l_final, l_refract);
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
	ray.type = CAMERA_RAY;
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

