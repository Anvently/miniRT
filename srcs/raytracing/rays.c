/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:27:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 11:55:16 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>



t_ray	generate_ray(t_coord2 *pxl, t_data *data)
{
	t_ray	ray;

	ray.origin = data->scene.camera.origin;
	ray.dir = vec3_sum(&data->scene.camera.dir, &data->scene.camera._r);
	ray.dir.x += (float) pxl->x * data->scene.camera._u.x;
	ray.dir.y += (float) pxl->y * data->scene.camera._v.y;
	ray.dir.z = 0.0;
	ray.dir = vec3_sum(&ray.dir, &data->scene.camera.dir);
	return (ray);
}

/// @brief Compute ray properties of a given pixel
/// @param ray
/// @param x
/// @param y
/// @param camera
void	generate_rays(t_data *data)
{
	t_coord2	pxl;
	t_ray		ray;

	pxl.x = 0;
	while (pxl.x < data->size.x)
	{
		pxl.y = 0;
		while (pxl.y < data->size.y)
		{
			ray = generate_ray(&pxl, data);
			pxl.y++;
		}
		pxl.x++;
	}
}