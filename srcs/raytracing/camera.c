/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:43:56 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 11:22:57 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/raytracing.h>
#include <math.h>

void	rt_update_camera(t_data *data)
{
	float	screen_w;
	float	screen_h;

	screen_w = 2.0 * tan((float) data->scene.camera.fov / 2.0);
	screen_h = screen_w * data->size_ratio;
	data->scene.camera._u.x = screen_w / (float) data->size.x;
	data->scene.camera._r.x = (-screen_w / 2.0) * data->scene.camera._u.x;
	data->scene.camera._u.y = 0.0;
	data->scene.camera._v.x = 0.0;
	data->scene.camera._v.y = screen_h / (float) data->size.y;
	data->scene.camera._r.y = (-screen_h / 2.0) * data->scene.camera._v.y;
}
