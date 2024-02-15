/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:28:36 by npirard           #+#    #+#             */
/*   Updated: 2024/02/15 13:12:03 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/raytracing.h>
#include <minirt/draw.h>

static void	chunk_draw(t_data *data, t_coord2 *start, int color)
{
	t_coord2	it;

	it.x = start->x;
	while (it.x < start->x + data->img_chunk_size)
	{
		it.y = start->y;
		while (it.y < start->y + data->img_chunk_size)
		{
			draw_pxl(data, &it, color);
			it.y++;
		}
		it.x++;
	}
}

void	render_chunk(t_data *data, int i)
{
	t_coord2	start;
	t_coord2	center;
	t_ray		ray;

	start.x = (i / data->img_chunk_cell) * data->img_chunk_size;
	start.y = (i % data->img_chunk_cell) * data->img_chunk_size;
	center.x = start.x + data->img_chunk_size / 2;
	center.y = start.y + data->img_chunk_size / 2;
	ray = generate_ray(&center, data);
	ray.color = get_ray_color(&ray);
	chunk_draw(data, &start, color_getint(&ray.color));
}

/// @param data_ptr
/// @return
int	render(void	*data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	if (render_threads(data))
		handle_close(data);
	if (img_put(data))
		handle_close(data);
	if (PFPS)
		pfps();
	return (0);
}