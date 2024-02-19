/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:58:07 by npirard           #+#    #+#             */
/*   Updated: 2024/02/19 13:39:14 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <pthread.h>
#include <math.h>

int	handle_resize_click(t_data *data)
{
	data->mouse_pressed = true;
	printf("PING\n");
	return (0);
}

int	handle_rotation(t_data *data)
{
	t_matrix4f	matrix;

	matrix = matrix_rotate(0.0, -data->dnd.y / 250.f, 0.0);
	data->scene.camera._cx = vec3f_matrix(&data->scene.camera._cx, &matrix);
	data->scene.camera._cz = vec3f_matrix(&data->scene.camera._cz, &matrix);
	matrix = matrix_rotate(0.0, 0.0, data->dnd.x / 250.f);
	data->scene.camera._cx = vec3f_matrix(&data->scene.camera._cx, &matrix);
	data->scene.camera._cy = vec3f_matrix(&data->scene.camera._cy, &matrix);
	img_update_camera(data);
	return (0);
}

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
