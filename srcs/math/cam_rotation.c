/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:10:46 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/26 12:26:00 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>
#include <math.h>

double	sign(double x)
{
	if (x >= 0)
		return (1);
	else
		return (-1);
}

t_matrix3f	get_x_axis_rot(t_vec3f *dir)
{
	double	theta;
	t_vec3f	ux;

	ux.x = 1;
	ux.y = 0;
	ux.z = 0;
	if (dir->y == 0)
		theta = 0;
	else
	{
		theta = sign(dir->y) * dir->z / sqrt(dir->y * dir->y + dir->z * dir->z);
		theta = acos(theta);
	}
	return (get_rotation_matrix(&ux, theta));
}

t_matrix3f	get_y_axis_rot(t_vec3f *dir)
{
	double	theta;
	t_vec3f	uy;

	uy.x = 0;
	uy.y = -1;
	uy.z = 0;
	if (dir->z == 0 && dir->x >= 0)
		theta = 0;
	else if (dir->z == 0 && dir->x < 0)
		theta = M_PI;
	else
	{
		theta = sign(dir->x) * dir->x / sqrt(dir->x * dir->x + dir->z * dir->z);
		if (dir->x >= 0 && dir->z >= 0)
			theta = -acos(theta);
		else if (dir->x >= 0 && dir->z < 0)
			theta = acos(theta);
		else if (dir->x < 0 && dir->z >= 0)
			theta = -(M_PI - acos(theta));
		else
			theta = M_PI - acos(theta);
	}
	return (get_rotation_matrix(&uy, theta));
}

t_matrix3f	cam_rotation(t_vec3f *dir)
{
	t_matrix3f	m_x;
	t_matrix3f	m_y;
	t_matrix3f	m;
	t_vec3f		new_dir;

	m_x = get_x_axis_rot(dir);
	new_dir = vec3f_matrix3f(dir, &m_x);
	m_y = get_y_axis_rot(&new_dir);
	new_dir = vec3f_matrix3f(&new_dir, &m_y);
	m = matrix_product(&m_y, &m_x);
	return (m);
}


