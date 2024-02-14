/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:42:03 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 13:28:48 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct timeval	t_timeval;

static int	get_ms_diff(t_timeval *time, t_timeval *last_time)
{
	if (last_time->tv_sec == time->tv_sec)
		return ((time->tv_usec - last_time->tv_usec) / 1000);
	else if (time->tv_sec - last_time->tv_sec == 1)
		return ((1000000 - last_time->tv_usec + time->tv_usec) / 1000);
	else
		return ((time->tv_sec - last_time->tv_sec) * 1000 \
			+ (1000000 - last_time->tv_usec + time->tv_usec) / 1000);
}

void	pfps(void)
{
	static struct timeval	last_time;
	static int				fps;
	struct timeval			time;

	fps++;
	gettimeofday(&time, NULL);
	if (last_time.tv_sec == 0)
	{
		last_time = time;
		return ;
	}
	if (last_time.tv_sec != time.tv_sec)
	{
		printf("%lu FPS|%d ms\n", fps / (time.tv_sec - last_time.tv_sec),
			get_ms_diff(&time, &last_time) / fps);
		fps = 0;
		last_time = time;
	}
}
