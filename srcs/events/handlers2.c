/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:58:07 by npirard           #+#    #+#             */
/*   Updated: 2024/02/16 19:12:54 by npirard          ###   ########.fr       */
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
	t_vec3f	dir;
	double	angle_x;
	double	angle_y;

	angle_x = -data->dnd.y / 250.f;
	angle_y = data->dnd.x / 250.f;
	dir = vec3f_rotate(&data->scene.camera.dir, angle_x, angle_y, 0.0);
	//print_t_double3(&dir);
	// data->scene.camera.dir = dir;
	// normalize_vec(&data->scene.camera.dir);
	//print_t_double3(&dir);
	data->scene.camera.dir = dir;
	img_update_camera(data);
	return (0);
}
