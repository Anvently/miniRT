/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:49:00 by npirard           #+#    #+#             */
/*   Updated: 2024/02/15 16:15:01 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <mlx_int.h>
# include <stdbool.h>
# include <minirt/types.h>
# include <pthread.h>

# define DFT_SIZE_X 800
# define DFT_SIZE_Y 800
# define PFPS 1
# define DFT_NBR_THREADS 16
# define DFT_IMG_CHUNK_SIZE 4

typedef struct s_data {

	//Window
	t_int2			win_size;
	void			*img;
	void			*mlx;
	void			*win;
	char			*addr;
	int				bbp;
	int				len_line;
	int				endian;

	//Threads
	int				threads_nbr;
	int				thread_i;
	pthread_t		*threads_id;
	pthread_mutex_t	thread_mutex;
	int				thread_chunk_nbr;

	//Image
	t_int2			img_size;
	double			img_ratio;
	int				img_chunk_nbr;
	int				img_chunk_size;
	int				img_chunk_cell_w;
	int				img_chunk_cell_h;

	//User-inputs
	bool			mouse_pressed;
	t_int2			dnd;
	double			zoom;

	//Scene
	t_scene			scene;

}				t_data;

/* -------------------------------------------------------------------------- */
/*                                  RENDERING                                 */
/* -------------------------------------------------------------------------- */

int		render(void	*data);
int		render_threads(t_data *data);
void	render_chunk(t_data *data, int i);
void	img_update(t_data *data);
int		img_put(t_data *data);
void	img_update_camera(t_data *data);
int		img_update_chunk(t_data *data);

/* -------------------------------------------------------------------------- */
/*                                   EVENTS                                   */
/* -------------------------------------------------------------------------- */

int		event_button_press(int keycode, int x, int y, t_data *data);
int		event_button_release(int keycode, int x, int y, t_data *data);
int		event_mouse_move(int x, int y, t_data *data);
int		event_key_release(int keycode, t_data *data);
int		handle_close(t_data *data);
int		handle_resize(t_data *data);
int		handle_resize_click(t_data *data);
int		handle_pan(t_data *data);
int		handle_threads_nbr(int keycode, t_data *data);
int		handle_chunk_size(int keycode, t_data *data);

/* -------------------------------------------------------------------------- */
/*                                   COLORS                                   */
/* -------------------------------------------------------------------------- */

int		color_getint(t_color *color);
t_color	color_getcolor(int color);
int		color_get_r(int color);
int		color_get_g(int color);
int		color_get_b(int color);
int		color_get_t(int color);

/* -------------------------------------------------------------------------- */
/*                                   ERRORS                                   */
/* -------------------------------------------------------------------------- */

void	error(char *context);

void	pfps(void);

#endif