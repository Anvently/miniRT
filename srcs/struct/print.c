/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:51:38 by npirard           #+#    #+#             */
/*   Updated: 2024/02/23 15:11:55 by npirard          ###   ########.fr       */
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

void	t_texture_print(t_texture *texture)
{
	printf("Texture type: %s\n",
		(char *[3]){"S", "D", "I"}[(int)texture->type]);
	if (texture->type == TEX_IMG)
		printf("Image path: %s\n", texture->file_path);
	if (texture->type != TEX_IMG)
		printf("Color1: %f, %f, %f\n", texture->color1.r, texture->color1.g,
			texture->color1.b);
	if (texture->type == TEX_DAM)
	{
		printf("Color2: %f, %f, %f\n", texture->color2.r, texture->color2.g,
			texture->color2.b);
		printf("Resolution: %d\n", texture->resolution);
	}
}

void	t_object_properties_print(t_object *obj)
{
	printf("Ambiant light constant = %f\n", obj->k_ambiant);
	printf("Diffuse light constant = %f\n", obj->k_diffuse);
	printf("Specular light constant = %f\n", obj->k_specular);
	printf("Reflexion constant = %f\n", obj->k_reflexion);
	printf("Refractive index = %f\n", obj->i_refraction);
	printf("Portion of plastic reflexion = %f\n", obj->k_plastic);
	printf("Roughness constant = %f\n", obj->k_roughness);
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
	t_texture_print(&object->texture);
	if (object->type != SPHERE)
		printf("Orientation: %.3f, %.3f, %.3f\n",
			object->orientation.x, object->orientation.y,
			object->orientation.z);
	t_object_properties_print(object);
	printf("\n");
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
	printf("Objects\n\n");
	ft_lstprint(scene->objects, &t_object_print);
	printf("\n");
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
