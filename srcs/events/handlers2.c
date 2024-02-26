/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:58:07 by npirard           #+#    #+#             */
/*   Updated: 2024/02/26 13:33:53 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <pthread.h>
#include <math.h>

int	handle_zoom(t_data *data, int keycode)
{
	if (keycode == Button4)
		data->scene.camera.origin = vec3_sum(&data->scene.camera.origin,
				&data->scene.camera._cx);
	else if (keycode == Button5)
		data->scene.camera.origin = vec3_diff(&data->scene.camera.origin,
				&data->scene.camera._cx);
	return (0);
}

int	handle_rotation(t_data *data)
{
	t_matrix3f	matrix_y;
	t_matrix3f	matrix_z;

	matrix_y = matrix_rotate(0.0, -data->dnd.y / 250.f, 0.0);
	matrix_z = matrix_rotate(0.0, 0.0, -data->dnd.x / 250.f);
	data->scene.camera._cx = vec3f_matrix3f(&data->scene.camera._cx, &matrix_y);
	data->scene.camera._cy = vec3f_matrix3f(&data->scene.camera._cy, &matrix_y);
	data->scene.camera._cz = vec3f_matrix3f(&data->scene.camera._cz, &matrix_y);
	transform_scene(data, &matrix_z, -data->dnd.x / 250.f);
	img_update_camera(data);
	return (0);
}
