/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:10:01 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 17:50:45 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <pthread.h>
#include <libft.h>
#include <math.h>

static void	*render_routine(void *data_ptr)
{
	t_data		*data;
	int			i;
	int			cells;
	t_coord2	start;
	t_coord2	dimensions;

	data = (t_data *)data_ptr;
	pthread_mutex_lock(&data->thread_mutex);
	i = data->thread_i;
	data->thread_i = -1;
	pthread_mutex_unlock(&data->thread_mutex);
	cells = (int) sqrt(data->nbr_threads);
	if (cells == 0)
		cells = 1;
	dimensions.x = data->img_size.x / cells;
	dimensions.y = data->img_size.y / cells;
	start.x = (i % cells) * dimensions.x;
	start.y = (i / cells) * dimensions.y;
	render_thread_chunk(data, &start, &dimensions);
	return (NULL);
}

static int	start_threads(t_data *data)
{
	int	i;

	data->threads_id = ft_calloc(data->nbr_threads, sizeof(pthread_t));
	if (!data->threads_id && data->nbr_threads > 0)
		return (1);
	i = 0;
	while (i < data->nbr_threads)
	{
		data->thread_i = (int) i;
		if (pthread_create(&data->threads_id[i++], NULL, render_routine, data))
			return (1);
		while (1)
		{
			usleep(10);
			pthread_mutex_lock(&data->thread_mutex);
			if (data->thread_i < 0)
			{
				pthread_mutex_unlock(&data->thread_mutex);
				break ;
			}
			pthread_mutex_unlock(&data->thread_mutex);
		}
	}
	return (0);
}

///Number of threads must be 1 or a multiple of 4.
int	render_threads(t_data *data)
{
	int	i;

	data->thread_i = 0;
	if (data->nbr_threads <= 0)
		render_routine(data);
	if (data->nbr_threads > 1024
		|| (data->nbr_threads > 1 && data->nbr_threads % 4))
		handle_close(data);
	start_threads(data);
	i = 0;
	while (i < data->nbr_threads && data->threads_id[i])
		pthread_join(data->threads_id[i++], NULL);
	if (data->threads_id)
		free(data->threads_id);
	data->threads_id = NULL;
	return (0);
}
