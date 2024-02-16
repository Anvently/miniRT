/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:09:12 by npirard           #+#    #+#             */
/*   Updated: 2024/02/16 13:19:22 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>
#include <math.h>

t_vec3f	vec3f_matrix(t_vec3f *vec, t_matrix4f *matrix)
{
	t_vec3f	new_vec;

	new_vec.x = vec->x * matrix->m0[0] + vec->y * matrix->m0[1] \
		+ vec->z * matrix->m0[2] + matrix->m0[3];
	new_vec.y = vec->x * matrix->m1[0] + vec->y * matrix->m1[1] \
		+ vec->z * matrix->m1[2] + matrix->m1[3];
	new_vec.z = vec->x * matrix->m2[0] + vec->y * matrix->m2[1] \
		+ vec->z * matrix->m2[2] + matrix->m2[3];
	return (new_vec);
}
