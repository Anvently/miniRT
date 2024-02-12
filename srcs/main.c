/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:10:44 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 13:38:40 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <libft.h>

static int	window_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->img = mlx_new_image(data->mlx, data->size.x, data->size.y);
	data->win = mlx_new_window(data->mlx, data->size.x,
			data->size.y, "MiniRT");
	data->addr = mlx_get_data_addr(data->img, &data->bbp,
			&data->len_line, &data->endian);
	if (!data->img || !data->win || !data->addr)
	{
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (1);
	}
	return (0);
}

static void	data_init(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->size.x = DFT_SIZE_X;
	data->size.y = DFT_SIZE_Y;
}

static void	hook_init(t_data *data)
{
	mlx_hook(data->win, ButtonPress, ButtonPressMask,
		event_button_press, data);
	mlx_hook(data->win, ButtonRelease, ButtonReleaseMask,
		event_button_release, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, event_key_release, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask,
		event_mouse_move, data);
	mlx_hook(data->win, DestroyNotify, ButtonPressMask, handle_close, data);
	mlx_loop_hook(data->mlx, render, data);
}

int	main(void)
{
	t_data	data;

	data_init(&data);
	if (window_init(&data))
		return (1);
	hook_init(&data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, data.img);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
