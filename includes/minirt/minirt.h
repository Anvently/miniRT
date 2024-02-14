/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:49:00 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 10:30:32 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <mlx_int.h>
# include <stdbool.h>
# include <minirt/types.h>

# define DFT_SIZE_X 800
# define DFT_SIZE_Y 800

typedef struct s_data {

	//Window
	t_int2			size;
	float			size_ratio;
	void			*img;
	void			*mlx;
	void			*win;
	char			*addr;
	int				bbp;
	int				len_line;
	int				endian;

	//User-inputs
	bool			mouse_pressed;
	t_int2			dnd;
	float			zoom;

	//Scene
	t_scene			scene;

}				t_data;

/* -------------------------------------------------------------------------- */
/*                                  RENDERING                                 */
/* -------------------------------------------------------------------------- */

int		render(void	*data);

/* -------------------------------------------------------------------------- */
/*                                   EVENTS                                   */
/* -------------------------------------------------------------------------- */

int		event_button_press(int keycode, int x, int y, t_data *data);
int		event_button_release(int keycode, int x, int y, t_data *data);
int		event_mouse_move(int x, int y, t_data *data);
int		event_key_release(int keycode, t_data *data);
int		handle_close(t_data *data);
int		handle_pan(t_data *data);

/* -------------------------------------------------------------------------- */
/*                                   COLORS                                   */
/* -------------------------------------------------------------------------- */

int		color_getint(t_color *color);
void	color_getcolor(int color, t_color *dest);
int		color_get_r(int color);
int		color_get_g(int color);
int		color_get_b(int color);
int		color_get_t(int color);

/* -------------------------------------------------------------------------- */
/*                                   ERRORS                                   */
/* -------------------------------------------------------------------------- */

void	error(char *context);

#endif