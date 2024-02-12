/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:35:57 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 13:58:25 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/draw.h>

static bool	inter_abcd(t_coord2 a, t_coord2 b, t_coord2 c, t_coord2 d)
{
	long	det;
	long	t;

	det = (b.x - a.x) * (c.y - d.y) - (c.x - d.x) * (b.y - a.y);
	if (det == 0)
	{
		if ((a.x == c.x && a.y == c.y) || (a.x == d.x && a.y == d.y)
			|| (b.x == c.x && b.y == c.y) || (b.x == d.x && b.y == d.y))
			return (true);
		return (false);
	}
	t = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	if (t && (((t > 0) != (det > 0)) || ((t > 0) && (t > det))
			|| (t < 0 && t < det)))
		return (false);
	return (true);
}

static bool	inter_line(int x, int y, t_line *line)
{
	t_coord2	c;
	t_coord2	d;

	c.x = x;
	c.y = y;
	d.x = x + 1;
	d.y = y;
	if (inter_abcd(line->a, line->b, c, d))
		return (true);
	d.x = x;
	d.y = y + 1;
	if (inter_abcd(line->a, line->b, c, d))
		return (true);
	c = d;
	d.x = x + 1;
	if (inter_abcd(line->a, line->b, c, d))
		return (true);
	c.x = x + 1;
	c.y = y;
	if (inter_abcd(line->a, line->b, c, d))
		return (true);
	return (false);
}

static void	rec_draw_line(t_line *line, t_data *data)
{
	if (line->it.x == line->b.x && line->it.y == line->b.y)
		return ;
	draw_pxl(data, line->it, line->color);
	if (line->dir.x && is_inside(line->it.x + line->dir.x, data->size.x)
		&& inter_line(line->it.x + line->dir.x, line->it.y, line))
		line->it.x += line->dir.x;
	else if (line->dir.y
		&& is_inside(line->it.y + line->dir.y, data->size.y)
		&& inter_line(line->it.x, line->it.y + line->dir.y, line))
		line->it.y += line->dir.y;
	rec_draw_line(line, data);
}

void	draw_line(t_data *data, t_coord2 a, t_coord2 b, int color)
{
	t_line	line;

	line.dir.x = get_sign(b.x - a.x);
	line.dir.y = get_sign(b.y - a.y);
	if (!line.dir.x && !line.dir.y)
		return ;
	line.it.x = a.x;
	line.it.y = a.y;
	line.a = a;
	line.b = b;
	line.color = color;
	rec_draw_line(&line, data);
}