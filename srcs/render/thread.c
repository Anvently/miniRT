/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:10:01 by npirard           #+#    #+#             */
/*   Updated: 2024/02/27 15:05:23 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <pthread.h>
#include <libft.h>
#include <math.h>

static void	*render_routine(void *data_ptr)
{
	t_data		*data;
	t_color3f	*colors;
	int			thread_i;
	int			i;
	int			max;

	data = (t_data *)data_ptr;
	pthread_mutex_lock(&data->thread_mutex);
	thread_i = data->thread_i;
	data->thread_i = -1;
	pthread_mutex_unlock(&data->thread_mutex);
	colors = NULL;
	if (data->img_chunk_size < 0)
	{
		colors = ft_calloc(data->img_chunk_size * data->img_chunk_size,
				sizeof(t_color3f));
		if (!colors)
			return (NULL);
	}
	i = thread_i * data->thread_chunk_nbr;
	max = i + data->thread_chunk_nbr;
	while (i < max && data->img)
		render_chunk(data, i++, colors);
	free(colors);
	return (NULL);
}

static int	start_threads(t_data *data)
{
	int	i;

	data->threads_id = ft_calloc(data->threads_nbr, sizeof(pthread_t));
	if (!data->threads_id && data->threads_nbr > 0)
		return (1);
	i = 0;
	while (i < data->threads_nbr)
	{
		data->thread_i = (int) i;
		if (pthread_create(&data->threads_id[i++], NULL, render_routine, data))
			return (1);
		while (1)
		{
			usleep(1);
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
	if (data->threads_nbr <= 0)
		render_routine(data);
	if (data->threads_nbr == 0)
		handle_close(data);
	start_threads(data);
	i = 0;
	while (i < data->threads_nbr && data->threads_id[i])
		pthread_join(data->threads_id[i++], NULL);
	if (data->threads_id)
		free(data->threads_id);
	data->threads_id = NULL;
	return (0);
}
