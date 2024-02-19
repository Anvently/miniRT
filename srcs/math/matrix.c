/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:09:12 by npirard           #+#    #+#             */
/*   Updated: 2024/02/19 15:16:22 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>
#include <math.h>

t_vec3f	vec3f_matrix4f(t_vec3f *vec, t_matrix4f *matrix)
{
	t_vec3f	new_vec;

	new_vec.x = vec->x * matrix->m0[0] + vec->y * matrix->m0[1] \
		+ vec->z * matrix->m0[2] + matrix->m3[0];
	new_vec.y = vec->x * matrix->m1[0] + vec->y * matrix->m1[1] \
		+ vec->z * matrix->m1[2] + matrix->m3[1];
	new_vec.z = vec->x * matrix->m2[0] + vec->y * matrix->m2[1] \
		+ vec->z * matrix->m2[2] + matrix->m3[2];
	return (new_vec);
}

t_vec3f	vec3f_matrix3f(t_vec3f *vec, t_matrix3f *matrix)
{
	t_vec3f	new;

	new.x = vec->x * matrix->m0[0] + vec->y * matrix->m0[1] \
		+ vec->z * matrix->m0[2];
	new.y = vec->x * matrix->m1[0] + vec->y * matrix->m1[1] \
		+ vec->z * matrix->m1[2];
	new.z = vec->x * matrix->m2[0] + vec->y * matrix->m2[1] \
		+ vec->z * matrix->m2[2];
	return (new);
}

t_matrix3f	matrix_sum(t_matrix3f *a, t_matrix3f *b)
{
	t_matrix3f	c;

	c.m0[0] = a->m0[0] + b->m0[0];
	c.m0[1] = a->m0[1] + b->m0[1];
	c.m0[2] = a->m0[2] + b->m0[2];
	c.m1[0] = a->m1[0] + b->m1[0];
	c.m1[1] = a->m1[1] + b->m1[1];
	c.m1[2] = a->m1[2] + b->m1[2];
	c.m2[0] = a->m2[0] + b->m2[0];
	c.m2[1] = a->m2[1] + b->m2[1];
	c.m2[2] = a->m2[2] + b->m2[2];
	return (c);
}

t_matrix3f	matrix_scale(t_matrix3f *a, double k)
{
	t_matrix3f	b;

	b.m0[0] = a->m0[0] * k;
	b.m0[1] = a->m0[1] * k;
	b.m0[2] = a->m0[2] * k;
	b.m1[0] = a->m1[0] * k;
	b.m1[1] = a->m1[1] * k;
	b.m1[2] = a->m1[2] * k;
	b.m2[0] = a->m2[0] * k;
	b.m2[1] = a->m2[1] * k;
	b.m2[2] = a->m2[2] * k;
	return (b);
}

t_matrix3f	matrix_transpose(t_matrix3f *m)
{
	t_matrix3f	matrix;

	ft_memset(&matrix, 0, sizeof(t_matrix3f));
	matrix.m0[0] = m->m0[0];
	matrix.m0[1] = m->m1[0];
	matrix.m0[2] = m->m2[0];
	matrix.m1[0] = m->m0[1];
	matrix.m1[1] = m->m1[1];
	matrix.m1[2] = m->m2[1];
	matrix.m2[0] = m->m0[2];
	matrix.m2[1] = m->m1[2];
	matrix.m2[2] = m->m2[2];
	return (matrix);
}
