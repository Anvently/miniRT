/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:58:07 by npirard           #+#    #+#             */
/*   Updated: 2024/02/15 18:43:28 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
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
	printf("x=%d,y=%d\n", data->dnd.x, data->dnd.y);
	data->scene.camera.dir.y -= (double) data->dnd.y / 100.f;
	data->scene.camera.dir.x -= (double) data->dnd.x / 100.f;
	img_update_camera(data);
	return (0);
}
