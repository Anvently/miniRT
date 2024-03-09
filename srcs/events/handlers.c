/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:58:07 by npirard           #+#    #+#             */
/*   Updated: 2024/03/09 16:21:42 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <minirt/objects.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <pthread.h>
#include <math.h>

int	handle_close(t_data *data)
{
	ft_lstclear(&data->textures_img, &t_texture_free);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	data->img = NULL;
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	data->mlx = NULL;
	if (data->threads_id)
		free(data->threads_id);
	pthread_mutex_destroy(&data->thread_mutex);
	ft_lstclear(&data->scene.lights, &free);
	ft_lstclear(&data->scene.moves, &free);
	ft_lstclear(&data->scene.objects, &free);
	ft_lstclear(&data->scene.lights_obj, NULL);
	exit(0);
}

int	handle_pan(t_data *data, int keycode)
{
	if (keycode == KEY_UP)
		data->scene.camera.origin = vec3_sum(&data->scene.camera.origin,
				&data->scene.camera._cz);
	else if (keycode == KEY_DOWN)
		data->scene.camera.origin = vec3_diff(&data->scene.camera.origin,
				&data->scene.camera._cz);
	else if (keycode == KEY_RIGHT)
		data->scene.camera.origin = vec3_diff(&data->scene.camera.origin,
				&data->scene.camera._cy);
	else if (keycode == KEY_LEFT)
		data->scene.camera.origin = vec3_sum(&data->scene.camera.origin,
				&data->scene.camera._cy);
	img_update_camera(data);
	return (0);
}

int	handle_resize(t_data *data)
{
	XWindowAttributes	attr;
	Display				*display;
	Window				win;

	win = ((t_xvar *) data->mlx)->win_list->window;
	display = (((t_xvar *) data->mlx))->display;
	XGetWindowAttributes(display, win, &attr);
	data->win_size.x = attr.width;
	data->win_size.y = attr.height;
	img_update(data);
	img_update_chunk(data);
	return (0);
}

int	handle_threads_nbr(int keycode, t_data *data)
{
	int	max;

	max = data->img_chunk_nbr;
	if (keycode == 33 || keycode == KEY_THREAD_INCR)
	{
		if (max > 1024)
			max = 1024;
		data->threads_nbr = get_sup_multiple(data->img_chunk_nbr,
				data->threads_nbr, max);
	}
	else if (keycode == 58 || keycode == KEY_THREAD_DECR)
		data->threads_nbr = get_inf_multiple(data->img_chunk_nbr,
				data->threads_nbr);
	img_update_chunk(data);
	printf("%d threads\n", data->threads_nbr);
	return (0);
}

int	handle_chunk_size(int keycode, t_data *data)
{
	if (keycode == KEY_CHUNK_INCR)
	{
		if (data->img_chunk_size == -2)
			data->img_chunk_size = 1;
		else if (data->img_chunk_size > 0 && data->img_chunk_size != 32)
			data->img_chunk_size *= 2;
		else if (data->img_chunk_size < 0)
			data->img_chunk_size++;
	}
	else if (keycode == KEY_CHUNK_DECR)
	{
		if (data->img_chunk_size == 1)
			data->img_chunk_size = -2;
		else if (data->img_chunk_size < 0 && data->img_chunk_size != -8)
			data->img_chunk_size--;
		else if (data->img_chunk_size > 0)
			data->img_chunk_size /= 2;
	}
	img_update(data);
	img_update_chunk(data);
	printf("chunk size = %d\n%d threads\n",
		data->img_chunk_size, data->threads_nbr);
	return (0);
}
