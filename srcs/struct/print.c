/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:51:38 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 11:02:26 by lmahe            ###   ########.fr       */
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

void	t_object_print(void *object_ptr)
{
	t_object	*object;

	object = (t_object *)object_ptr;
	printf("Type: %s\n", (char *[3]){"sp", "pl", "cy"}[object->type - SPHERE]);
	printf("Origin: %.3f, %.3f, %.3f\n",
		object->origin.x, object->origin.y, object->origin.z);
	if (object->type == SPHERE || object->type == CYLINDER \
	|| object->type == CONE)
		printf("Radius: %.3f\n", object->radius);
	if (object->type == CYLINDER || object->type == CONE)
		printf("Height: %.3f\n", object->height);
	printf("Color: %f, %f, %f\n", object->color.r, object->color.g,
		object->color.b);
	if (object->type != SPHERE)
		printf("Orientation: %.3f, %.3f, %.3f\n",
			object->orientation.x, object->orientation.y,
			object->orientation.z);
}

void	t_scene_print(t_scene *scene)
{
	printf("------ Scene ------\nCamera\n");
	t_camera_print(&scene->camera);
	printf("Ambiant light\n");
	printf("Color: %f, %f, %f\nRatio: %.3f\n", scene->ambiant_light.color.r,
		scene->ambiant_light.color.g, scene->ambiant_light.color.b,
		scene->ambiant_light.ratio);
	printf("Lights\n");
	ft_lstprint(scene->lights, &t_light_print);
	printf("Objects\n");
	ft_lstprint(scene->objects, &t_object_print);
	printf("\n");
}

void	print_t_double3(t_double3 *vec)
{
	printf("X=%f | Y = %f | Z = %f\n", vec->x, vec->y, vec->z);
}

void	display_matrix(t_matrix3f *m)
{
	printf("| %f, %f, %f |\n", m->m0[0], m->m0[1], m->m0[2]);
	printf("| %f, %f, %f |\n", m->m1[0], m->m1[1], m->m1[2]);
	printf("| %f, %f, %f |\n", m->m2[0], m->m2[1], m->m2[2]);
}
