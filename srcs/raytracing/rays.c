/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:27:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/15 13:27:04 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/draw.h>
#include <minirt/calculus.h>
#include <libft.h>

t_ray	generate_ray(t_coord2 *pxl, t_data *data)
{
	t_ray	ray;

	ft_memset(&ray, 0, sizeof(t_ray));
	ray.origin = data->scene.camera.origin;
	ray.dir = vec3_sum(&data->scene.camera.dir, &data->scene.camera._r);
	ray.dir.x += (double) pxl->x * data->scene.camera._u.x;
	ray.dir.y += (double) pxl->y * data->scene.camera._v.y;
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