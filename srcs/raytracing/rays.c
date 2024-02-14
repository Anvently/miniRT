/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:27:51 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 11:32:02 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>



t_ray	generate_ray(t_coord2 *pxl, t_data *data)
{
	t_ray	ray;

	ray->origin = data->scene.camera.origin;
	ray->dir =
	//ray->dir = camera_dir + (pxl.x * data->scene.camera.u)
	//	+ (pxl.y * data->scene.camera.u)
	//	+ data->scene.camera.center

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