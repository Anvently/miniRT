/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:51:38 by npirard           #+#    #+#             */
/*   Updated: 2024/02/26 13:44:57 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/types.h>
#include <stdio.h>
#include <stdbool.h>
#include <libft.h>

void	t_camera_print(void *camera_ptr)
{
	t_camera	*camera;

	camera = (t_camera *)camera_ptr;
	printf("Origin: %.3f, %.3f, %.3f\nDirection: %.3f, %.3f, %.3f\n" \
		"Fov: %d\n", camera->origin.x, camera->origin.y, camera->origin.z,
		camera->dir.x, camera->dir.y, camera->dir.z, camera->fov);
}

void	t_light_print(void *light_ptr)
{
	t_light	*light;

	light = (t_light *)light_ptr;
	printf("Origin: %.3f, %.3f, %.3f\n",
		light->origin.x, light->origin.y, light->origin.z);
	printf("Color: %f, %f, %f\nRatio: %.3f\n", light->color.r, light->color.g,
		light->color.b, light->ratio);
}

void	print_t_double3(t_double3 *vec)
{
	printf("X=%f | Y = %f | Z = %f\n", vec->x, vec->y, vec->z);
}

void	print_t_color3f(t_color3f *color)
{
	printf("R=%f | G = %f | B = %f\n", color->r, color->g, color->b);
}

void	display_matrix(t_matrix3f *m)
{
	printf("| %f, %f, %f |\n", m->m0[0], m->m0[1], m->m0[2]);
	printf("| %f, %f, %f |\n", m->m1[0], m->m1[1], m->m1[2]);
	printf("| %f, %f, %f |\n", m->m2[0], m->m2[1], m->m2[2]);
}
