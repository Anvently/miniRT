/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:44:43 by npirard           #+#    #+#             */
/*   Updated: 2024/02/15 18:19:30 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/draw.h>
#include <minirt/raytracing.h>
#include <minirt/calculus.h>
#include <math.h>

static void	chunk_draw(t_data *data, t_coord2f *start, int color)
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

static t_color	get_color(t_data *data, t_coord2f *start)
{
	t_ray		ray;

	ray = generate_ray(start, data);
	launch_ray(data, &ray);
	return (ray.color);
}

static void	render_low_res_chunk(t_data *data, int i)
{
	t_coord2f	start;
	t_color		color;

	start.x = (i % data->img_chunk_cell_w) * data->img_chunk_size
		+ data->img_chunk_size / 2;
	start.y = (i / data->img_chunk_cell_w) * data->img_chunk_size
		+ data->img_chunk_size / 2;
	color = get_color(data, &start);
	chunk_draw(data, &start, color_getint(&color));
}

static void	render_antialiasing_chunk(t_data *data, int i,
	t_color *antialisaing, int nbr_rays)
{
	t_coord2	chunk_start;
	t_coord2f	start;
	t_color		color;
	int			j;
	double		shift;

	shift = 1.f / -data->img_chunk_size;
	chunk_start.x = i % data->img_chunk_cell_w;
	chunk_start.y = i / data->img_chunk_cell_w;
	j = 0;
	while (j < nbr_rays)
	{
		start.x = chunk_start.x + (j % -data->img_chunk_size) * shift;
		start.y = chunk_start.y + (j / -data->img_chunk_size) * shift;
		antialisaing[j] = get_color(data, &start);
		j++;
	}
	color = color_average(antialisaing, nbr_rays);
	draw_pxl(data, &chunk_start, color_getint(&color));
}

void	render_chunk(t_data *data, int i, t_color *antialiasing)
{
	int			nbr_rays;

	if (data->img_chunk_size >= 0)
		render_low_res_chunk(data, i);
	else
	{
		nbr_rays = data->img_chunk_size * data->img_chunk_size;
		render_antialiasing_chunk(data, i, antialiasing, nbr_rays);
	}
}