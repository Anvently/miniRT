/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:28:36 by npirard           #+#    #+#             */
/*   Updated: 2024/02/15 17:07:16 by npirard          ###   ########.fr       */
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
	t_data	*data;

	data = (t_data *)data_ptr;
	//printf("screen_w=%f,screen_h=%f\n", data->scene.camera._u.x * (double) data->img_size.x,
	//	data->scene.camera._v.y * (double) data->img_size.y);
	if (render_threads(data))
		handle_close(data);
	if (img_put(data))
		handle_close(data);
	if (PFPS)
		pfps();
	return (0);
}
