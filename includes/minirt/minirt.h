/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:49:00 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 14:01:58 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <mlx_int.h>
# include <stdbool.h>

# define DFT_SIZE_X 800
# define DFT_SIZE_Y 800

typedef struct s_size2 {
	int		x;
	int		y;
}			t_size2;

typedef struct s_data {

	//Window
	t_size2		size;
	void		*img;
	void		*mlx;
	void		*win;
	char		*addr;
	int			bbp;
	int			len_line;
	int			endian;

	//User-inputs
	bool		mouse_pressed;
	t_size2		dnd;
	float		zoom;

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

#endif