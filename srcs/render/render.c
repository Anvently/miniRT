/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:28:36 by npirard           #+#    #+#             */
/*   Updated: 2024/02/15 15:44:51 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/raytracing.h>
#include <minirt/draw.h>
#include <minirt/calculus.h>

static void	chunk_draw(t_data *data, t_coord2 *start, int color)
{
	t_coord2	it;

	it.x = start->x;
	//printf("number of chunks=%d\n",data->img_chunk_nbr);
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

void	launch_ray(t_data *data, t_ray *ray)
{
	t_object	*plane;
	t_object	*sphere;
	plane = (t_object *)data->scene.objects->content;
	sphere = (t_object *)data->scene.objects->next->content;
	plane_intersec(plane, ray);
	sphere_intersec(sphere, ray);
	//printf("t=%f\n", ray->t);
	// cyld = (t_object *)data->scene.objects->content;
	// cylinder_intersec(cyld, ray);
	if (ray->t == INFINITY)
		ray->color = color_getcolor(0);
}

void	render_chunk(t_data *data, int i)
{
	t_coord2	start;
	t_coord2	center;
	t_ray		ray;

	start.x = (i % data->img_chunk_cell_w) * data->img_chunk_size;
	start.y = (i / data->img_chunk_cell_w) * data->img_chunk_size;
	center.x = start.x + data->img_chunk_size / 2;
	center.y = start.y + data->img_chunk_size / 2;
	ray = generate_ray(&center, data);
	//ray.color = get_ray_color(&ray);
	launch_ray(data, &ray);
	chunk_draw(data, &start, color_getint(&ray.color));
}

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
