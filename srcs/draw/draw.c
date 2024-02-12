/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:05:12 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 13:57:59 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/draw.h>
#include <math.h>
#include <libft.h>

void	draw_pxl(t_data *data, t_coord2 coord, int color)
{
	*(int *)(data->addr + (coord.y * data->len_line
				+ coord.x * (data->bbp / 8))) = color;
}

void	draw_segment(t_data *data, t_segment2 seg, int color)
{
	t_coord2	dir;

	if ((seg.a.x < 0 && seg.b.x < 0) || (seg.a.y < 0 && seg.b.y < 0)
		|| (seg.a.x > data->size.x && seg.b.x > data->size.x)
		|| (seg.a.y > data->size.y && seg.b.y > data->size.y)
		|| ((seg.a.x != seg.b.x) && (seg.a.y != seg.b.y)))
		return ;
	dir.x = get_sign(seg.b.x - seg.a.x);
	dir.y = get_sign(seg.b.y - seg.a.y);
	while (seg.a.x != seg.b.x || seg.a.y != seg.b.y)
	{
		if (is_inside(seg.a.x, data->size.x)
			&& is_inside(seg.a.y, data->size.y))
			draw_pxl(data, seg.a, color);
		seg.a.y += dir.y;
		seg.a.x += dir.x;
	}
}

void	draw_rect(t_data *data, t_coord2 a, t_coord2 b, int color)
{
	t_coord2	pxl;

	pxl.x = a.x;
	while (pxl.x < b.x)
	{
		pxl.y = a.y;
		while (pxl.y < b.y)
		{
			draw_pxl(data, pxl, color);
			pxl.y++;
		}
		pxl.x++;
	}
}
