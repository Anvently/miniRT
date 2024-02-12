/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:19:17 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 14:01:25 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
#include <minirt/minirt.h>

int	event_button_press(int keycode, int x, int y, t_data *data)
{
	if (keycode == Button1)
	{
		data->mouse_pressed = true;
		data->dnd.x = x;
		data->dnd.y = y;
	}
	else if (keycode == Button4) //molette avant
	{
		data->zoom *= 1.5;
	}
	else if (keycode == Button5) //molette arriere
	{

		data->zoom /= 1.5;
	}
	return (0);
}

int	event_button_release(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == Button1) //Left click
		data->mouse_pressed = false;
	else if (keycode == Button3) //Right click
		return (0);
	return (0);
}

int	event_mouse_move(int x, int y, t_data *data)
{
	if (data->mouse_pressed)
	{
		// data->move_x -= ((double)(x - data->dnd.x)
		// 		/ data->size_x / 2.f) / data->zoom;
		// data->move_y -= ((double)(y - data->dnd.y)
		// 		/ data->size_y / 2.f) / data->zoom;
		data->dnd.x = x;
		data->dnd.y = y;
	}
	return (0);
}

int	event_key_release(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		handle_close(data);
	else if (keycode == XK_Right || keycode == XK_Left
		|| keycode == XK_Up || keycode == XK_Down)
		handle_pan(data);
	return (0);
}
