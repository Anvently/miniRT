/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:28:36 by npirard           #+#    #+#             */
/*   Updated: 2024/02/26 13:42:28 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/raytracing.h>
#include <minirt/draw.h>
#include <minirt/calculus.h>

/// @param data_ptr
/// @return
int	render(void	*data_ptr)
{
	t_data			*data;
	double			render_time;

	data = (t_data *)data_ptr;
	if (render_threads(data))
		handle_close(data);
	if (img_put(data))
		handle_close(data);
	render_time = pfps();
	scene_move(&data->scene, render_time);
	return (0);
}
