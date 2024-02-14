/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:37:48 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 17:05:01 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>


static bool	check_new_img(t_data *data)
{
	t_int2	new_size;

	new_size.x = data->win_size.x - data->win_size.x % data->img_ppc;
	new_size.y = data->win_size.y - data->win_size.y % data->img_ppc;
	if (new_size.x < data->img_ppc || new_size.y < data->img_ppc)
		return (false);
	if (data->img == NULL)
	{
		data->img_size = new_size;
		return (true);
	}
	else if (new_size.x != data->img_size.x || new_size.y != data->img_size.y)
	{
		data->img_size = new_size;
		return (true);
	}
	return (false);
}

void	img_update(t_data *data)
{
	if (check_new_img(data) == false)
		return ;
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_clear_window(data->mlx, data->win);
	}
	data->img = mlx_new_image(data->mlx, data->img_size.x, data->img_size.y);
	if (!data->img)
		handle_close(data);
	data->addr = mlx_get_data_addr(data->img, &data->bbp,
			&data->len_line, &data->endian);
	if (!data->addr)
		handle_close(data);
	data->img_ratio = (double) data->img_size.y / (double) data->img_size.x;
	img_update_camera(data);
}

int	img_put(t_data *data)
{
	int	x;
	int	y;

	if (data->img == NULL)
		return (0);
	x = (data->win_size.x - data->img_size.x) / 2;
	y = (data->win_size.y - data->img_size.y) / 2;
	if (mlx_put_image_to_window(data->mlx, data->win, data->img, x, y))
		return (1);
	return (0);
}