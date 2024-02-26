/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:11:25 by lmahe             #+#    #+#             */
/*   Updated: 2024/02/26 13:38:23 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>
#include <math.h>

double	row_col_sum(double row[3], double col[3])
{
	double	sigma;
	int		i;

	sigma = 0;
	i = 0;
	while (i < 3)
	{
		sigma += row[i] * col[i];
		i++;
	}
	return (sigma);
}

t_matrix3f	matrix_product(t_matrix3f *a, t_matrix3f *b)
{
	t_matrix3f	c;
	t_matrix3f	t_b;

	t_b = matrix_transpose(b);

	c.m0[0] = row_col_sum(a->m0, t_b.m0);
	c.m0[1] = row_col_sum(a->m0, t_b.m1);
	c.m0[2] = row_col_sum(a->m0, t_b.m2);
	c.m1[0] = row_col_sum(a->m1, t_b.m0);
	c.m1[1] = row_col_sum(a->m1, t_b.m1);
	c.m1[2] = row_col_sum(a->m1, t_b.m2);
	c.m2[0] = row_col_sum(a->m2, t_b.m0);
	c.m2[1] = row_col_sum(a->m2, t_b.m1);
	c.m2[2] = row_col_sum(a->m2, t_b.m2);
	return (c);
}
