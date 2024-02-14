/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:43:56 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 15:01:43 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/raytracing.h>
#include <math.h>

void	img_update_camera(t_data *data)
{
	double	screen_w;
	double	screen_h;

	screen_w = 2.0 * tan((double) data->scene.camera.fov / 2.0);
	screen_h = screen_w * data->img_ratio;
	data->scene.camera._u.x = screen_w / (double) data->img_size.x;
	data->scene.camera._u.y = 0.0;
	data->scene.camera._u.z = 0.0;
	data->scene.camera._v.x = 0.0;
	data->scene.camera._v.y = screen_h / (double) data->img_size.y;
	data->scene.camera._v.z = 0.0;
	data->scene.camera._r.x = -screen_w / 2.0;
	data->scene.camera._r.y = -screen_h / 2.0;
	data->scene.camera._r.z = 0.0;
	// printf("ux=%f, uy=%f, uz=%f\n", data->scene.camera._u.x, data->scene.camera._u.y,
	// 	data->scene.camera._u.z);
	// printf("vx=%f, vy=%f, vz=%f\n", data->scene.camera._v.x, data->scene.camera._v.y,
	// 	data->scene.camera._v.z);
	// printf("cx=%f, cy=%f, cz=%f\n", data->scene.camera._r.x, data->scene.camera._r.y,
	// 	data->scene.camera._r.z);
}
