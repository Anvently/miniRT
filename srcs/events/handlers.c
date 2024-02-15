/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:58:07 by npirard           #+#    #+#             */
/*   Updated: 2024/02/15 12:21:56 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <pthread.h>
#include <math.h>

int	handle_close(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		mlx_loop_end(data->mlx);
		free(data->mlx);
	}
	if (data->threads_id)
		free(data->threads_id);
	pthread_mutex_destroy(&data->thread_mutex);
	data->img = NULL;
	data->mlx = NULL;
	data->win = NULL;
	ft_lstclear(&data->scene.lights, &free);
	ft_lstclear(&data->scene.objects, &free);
	exit(0);
}

int	handle_pan(t_data *data)
{
	(void)data;

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
	printf("Window size: x = %d, y = %d\n", attr.width, attr.height);
	return (0);
}

int	handle_threads_nbr(int keycode, t_data *data)
{
	if (keycode == 33 || keycode == XK_bracketright)
	{
		if (data->threads_nbr == 0)
			data->threads_nbr = 1;
		else if (data->threads_nbr != 1024)
			data->threads_nbr *= 2;
	}
	else if (keycode == 58 || keycode == XK_bracketleft)
		data->threads_nbr /= 2;
	img_update_chunk(data);
	printf("%d threads\n", data->threads_nbr);
	return (0);
}

int	handle_ppc(int keycode, t_data *data)
{
	if (keycode == 61)
	{
		if (data->img_ppc == -4)
			data->img_ppc = 1;
		else if (data->img_ppc > 0 && data->img_ppc != 1024)
			data->img_ppc *= 4;
		else if (data->img_ppc < 0)
			data->img_ppc /= 4;
	}
	else if (keycode == XK_minus)
	{
		if (data->img_ppc == 1)
			data->img_ppc = -4;
		else if (data->img_ppc < 0 && data->img_ppc != -1024)
			data->img_ppc *= 4;
		else if (data->img_ppc > 0)
			data->img_ppc /= 4;
	}
	printf("%d ppc\n", data->img_ppc);
	img_update(data);
	img_update_chunk(data);
	return (0);
}
