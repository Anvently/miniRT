/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:28:36 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 18:25:35 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/raytracing.h>
#include <minirt/draw.h>

void	render_chunk(t_data *data, t_coord2 *start);

/// @brief Check ppc
/// if ppc == 1
/// 	1 ray/pixel
/// if ppc > 1
///		1 ray = every pixel in the chunk
/// if ppc < 0
///		ppc ray = 1 pixel
/// @param data
/// @param start
/// @param dimension
void	render_thread_chunk(t_data *data, t_coord2 *start, t_coord2 *dimension)
{
	t_coord2	pxl;
	t_ray		ray;

	pxl.x = start->x;
	if (data->img_ppc > 1)
	{
		ray = generate_chunk_ray(&start, &dimension, data);
		ray.color = get_ray_color(&ray);
	}
	while (pxl.x < dimension->x - start->x)
	{
		pxl.y = start->y;
		while (pxl.y < dimension->y - start->y)
		{
			if (data->img_ppc == 1)
			{
				ray = generate_pxl_ray(&pxl, data);
				ray.color = get_ray_color(&ray);
			}
			draw_pxl(data, pxl, color_getint(&ray.color));
			pxl.y++;
		}
		pxl.x++;
	}
}

void	render_thread_chunk(t_data *data, t_coord2 *start, t_coord2 *dimension)
{
	if (data->img_ppc == 1)
	{

	}
}

/// @param data_ptr
/// @return
int	render(void	*data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	if (render_threads(data))
		handle_close(data);
	generate_rays(data);
	if (img_put(data))
		handle_close(data);
	if (PFPS)
		pfps();
	return (0);
}