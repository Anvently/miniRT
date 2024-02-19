/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rot_matrices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:32:09 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/19 13:39:52 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>
#include <math.h>

void	get_a(t_matrix3f *a, double theta)
{
	double	cos_t;

	ft_memset(a, 0, sizeof(t_matrix3f));
	cos_t = cos(theta);
	a->m0[0] = cos_t;
	a->m1[1] = cos_t;
	a->m2[2] = cos_t;
}

void	get_b(t_matrix3f *b, double theta, t_vec3f *axis)
{
	double	cos_t;

	ft_memset(b, 0, sizeof(t_matrix3f));
	cos_t = 1 - cos(theta);
	b->m0[0] = cos_t * axis->x * axis->x;
	b->m0[1] = cos_t * axis->x * axis->y;
	b->m0[2] = cos_t * axis->x * axis->z;
	b->m1[0] = b->m0[1];
	b->m1[1] = cos_t * axis->y * axis->y;
	b->m1[2] = cos_t * axis->y * axis->z;
	b->m2[0] = b->m0[2];
	b->m2[1] = b->m1[2];
	b->m2[2] = cos_t * axis->z * axis->z;
}

void	get_c(t_matrix3f *c, double theta, t_vec3f *axis)
{
	double	sin_t;

	sin_t = sin(theta);
	ft_memset(c, 0, sizeof(t_matrix3f));
	c->m0[1] = -sin_t * axis->z;
	c->m0[2] = sin_t * axis->y;
	c->m1[0] = sin_t * axis->z;
	c->m1[2] = -sin_t * axis->x;
	c->m2[0] = -sin_t * axis->y;
	c->m2[1] = sin_t * axis->x;
}
t_matrix3f	get_rotation_matrix(t_vec3f *axis, double theta)
{
	t_matrix3f	a;
	t_matrix3f	b;
	t_matrix3f	c;
	t_matrix3f	rot;

	ft_memset(&rot, 0, sizeof(t_matrix3f));
	get_a(&a, theta);
	get_b(&b, theta, axis);
	get_c(&c, theta, axis);
	rot = matrix_sum(&a, &b);
	rot = matrix_sum(&rot, &c);
	return (rot);
}

t_matrix3f	rotation_matrix(t_vec3f	*cam_dir)
{
	double	theta;
	double	cross_product;
	t_vec3f	axis;
	t_vec3f	u_x;

	u_x.x = 1;
	u_x.y = 0;
	u_x.z = 0;
	axis = vector_product(cam_dir, &u_x);
	normalize_vec(&axis);
	cross_product = scalar_product(cam_dir, &u_x);
	theta = acos(cross_product);
	return (get_rotation_matrix(&axis, theta));
}

int	main(void)
{
	t_vec3f	dir;
	t_matrix3f rot;
	t_vec3f	new;

	dir.x = 5;
	dir.y = 3;
	dir.z = 7;
	normalize_vec(&dir);
	rot = rotation_matrix(&dir);
	display_matrix(&rot);
	new = vec3f_mat3(&dir, &rot);
	display_vector(&new);


}
