/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:28:36 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 13:30:49 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/raytracing.h>

int	render(void	*data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	generate_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	if (PFPS)
		pfps();
	return (0);
}