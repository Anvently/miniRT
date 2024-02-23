/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:42:03 by npirard           #+#    #+#             */
/*   Updated: 2024/02/23 18:07:04 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <minirt/minirt.h>

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

double	pfps(void)
{
	static struct timeval	last_time;
	static struct timeval	last_time_sec;
	static int				fps;
	struct timeval			time;
	double					render_time;

	fps++;
	gettimeofday(&time, NULL);
	if (last_time.tv_sec == 0)
	{
		last_time = time;
		last_time_sec = last_time;
		return (0.f);
	}
	render_time = get_ms_diff(&time, &last_time);
	last_time = time;
	if (last_time_sec.tv_sec != time.tv_sec)
	{
		if (PFPS)
			printf("%lu FPS|%d ms\n", fps / (time.tv_sec - last_time_sec.tv_sec),
				(int) render_time);
		fps = 0;
		last_time_sec = time;
	}
	return (render_time / 1000.f);
}
