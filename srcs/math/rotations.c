/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:35:19 by npirard           #+#    #+#             */
/*   Updated: 2024/02/19 12:44:27 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>
#include <math.h>

t_matrix4f	matrix_rotate(double x, double y, double z)
{
	t_matrix4f	matrix;

	ft_memset(&matrix, 0, sizeof(t_matrix4f));
	matrix.m0[0] = cos(y) * cos(z);
	matrix.m0[1] = sin(x) * sin(y) * cos(z) - cos(x) * sin(z);
	matrix.m0[2] = cos(x) * sin(y) * cos(z) + sin(x) * sin(z);
	matrix.m1[0] = cos(y) * sin(z);
	matrix.m1[1] = sin(x) * sin(y) * sin(z) + cos(x) * cos(z);
	matrix.m1[2] = cos(x) * sin(y) * sin(z) - sin(x) * cos(z);
	matrix.m2[0] = -sin(y);
	matrix.m2[1] = sin(x) * cos(y);
	matrix.m2[2] = cos(x) * cos(y);
	matrix.m3[3] = 1;
	return (matrix);
}

t_vec3f	vec3f_rotate(t_vec3f *vec, double x, double y, double z)
{
	t_matrix4f	matrix;

	matrix = matrix_rotate(x, y, z);
	return (vec3f_matrix(vec, &matrix));
}


