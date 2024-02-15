/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:27:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/15 17:58:52 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/draw.h>
#include <minirt/calculus.h>
#include <libft.h>

void	launch_ray(t_data *data, t_ray *ray)
{
	t_object	*plane;
	t_object	*sphere;
	plane = (t_object *)data->scene.objects->content;
	sphere = (t_object *)data->scene.objects->next->content;
	plane_intersec(plane, ray);
	sphere_intersec(sphere, ray);
	//printf("t=%f\n", ray->t);
	// cyld = (t_object *)data->scene.objects->content;
	// cylinder_intersec(cyld, ray);
	if (ray->t == INFINITY)
		ray->color = color_getcolor(0);
}

t_ray	generate_ray(t_coord2f *pxl, t_data *data)
{
	t_ray	ray;

	ft_memset(&ray, 0, sizeof(t_ray));
	ray.origin = data->scene.camera.origin;
	ray.dir = vec3_sum(&data->scene.camera.dir, &data->scene.camera._r);
	ray.dir.x += pxl->x * data->scene.camera._u.x;
	ray.dir.y += pxl->y * data->scene.camera._v.y;
	ray.dir.z = 1.0;
	ray.t = INFINITY;
	ray.dir = vec3_sum(&ray.dir, &data->scene.camera.dir);
	normalize_vec(&ray.dir);
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

// /// @brief Compute ray properties of a given pixel
// /// @param ray
// /// @param x
// /// @param y
// /// @param camera
// void	generate_rays(t_data *data)
// {
// 	t_coord2	pxl;
// 	t_ray		ray;

// 	pxl.x = 0;
// 	while (pxl.x < data->img_size.x)
// 	{
// 		pxl.y = 0;
// 		while (pxl.y < data->img_size.y)
// 		{
// 			ray = generate_ray(&pxl, data);
// 			ray.color = get_ray_color(&ray);
// 			draw_pxl(data, pxl, color_getint(&ray.color));
// 			//printf("color = %d\n", color_getint(&ray.color));
// 			//printf("vx=%f, vy=%f, vz=%f\n", ray.dir.x, ray.dir.y, ray.dir.z);
// 			pxl.y++;
// 		}
// 		pxl.x++;
// 	}
// }