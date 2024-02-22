/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:35:00 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/22 15:28:39 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>
#include <math.h>

static t_matrix3f	get_z_axis_rot(t_vec3f *dir)
{
	double	theta;
	t_vec3f	uz;

	uz.x = 0;
	uz.y = 0;
	uz.z = 1;
	if (dir->y == 0 && dir->x == 0)
		theta = 0;
	else
		theta = -atan2(dir->y, dir->x);
	return (get_rotation_matrix(&uz, theta));
}

t_matrix3f	get_z_align_rot(t_vec3f *dir)
{
	double	theta;
	t_vec3f	uy;

	uy.x = 0;
	uy.y = -1;
	uy.z = 0;
	theta = atan2(dir->x, dir->z);
	return (get_rotation_matrix(&uy, theta));
}

void	get_local_base(t_object *obj)
{
	t_matrix3f	m_z;
	t_matrix3f	m_y;
	t_matrix3f	m;
	t_vec3f		new_dir;

	if (obj->type == SPHERE)
		return ;
	m_z = get_z_axis_rot(&obj->orientation);
	new_dir = vec3f_matrix3f(&obj->orientation, &m_z);
	m_y = get_z_align_rot(&new_dir);
	new_dir = vec3f_matrix3f(&new_dir, &m_y);
	m = matrix_product(&m_y, &m_z);
	m = matrix_transpose(&m);
	new_dir.x = 1;
	new_dir.y = 0;
	new_dir.z = 0;
	obj->loc_x = vec3f_matrix3f(&new_dir, &m);
	new_dir.x = 0;
	new_dir.y = 1;
	new_dir.z = 0;
	obj->loc_y = vec3f_matrix3f(&new_dir, &m);
}


