/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:58:07 by npirard           #+#    #+#             */
/*   Updated: 2024/02/13 16:30:53 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <X11/keysym.h>

int	handle_close(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free(data->mlx);
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
