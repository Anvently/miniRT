/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:44:10 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 16:26:31 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include <minirt/minirt.h>

typedef struct s_segment2 {
	t_coord2	a;
	t_coord2	b;
}			t_segment2;

typedef struct s_segment3 {
	t_coord3	a;
	t_coord3	b;
}			t_segment3;

typedef struct s_line {
	t_coord2	a;
	t_coord2	b;
	t_coord2	it;
	t_coord2	dir;
	int			color;
}				t_line;

/* -------------------------------------------------------------------------- */
/*                                  DRAW                                      */
/* -------------------------------------------------------------------------- */

void	draw_pxl(t_data *data, t_coord2 coord, int color);
void	draw_line(t_data *data, t_coord2 a, t_coord2 b, int color);
void	draw_segment(t_data *data, t_segment2 seg, int color);
void	draw_rect(t_data *data, t_coord2 a, t_coord2 b, int color);

/* -------------------------------------------------------------------------- */
/*                                    UTIL                                    */
/* -------------------------------------------------------------------------- */

bool	is_inside(int pos, int size);
int		get_sign(int n);

#endif