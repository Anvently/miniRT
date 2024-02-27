/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:51:38 by npirard           #+#    #+#             */
/*   Updated: 2024/02/27 11:23:38 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/types.h>
#include <minirt/objects.h>
#include <stdio.h>
#include <stdbool.h>
#include <libft.h>

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
	printf("Glow color: %f, %f, %f\n", obj->color_glow.r, obj->color_glow.g,
		obj->color_glow.b);
	printf("Glow color constant = %f\n", obj->k_glow);
	printf("Emissive light color: %f, %f, %f\n", obj->color_light.r,
		obj->color_light.g, obj->color_light.b);
	printf("Glow color constant = %f\n", obj->k_light);
}

void	t_object_print(void *object_ptr)
{
	t_object	*object;

	object = (t_object *)object_ptr;
	printf("Id: %d\n", object->id);
	printf("Type: %s\n", (char *[5]){"sp", "pl", "cy", "co", "tr"} \
		[object->type - SPHERE]);
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
	if (object->type == TR)
	{
		printf("Vertex 1: %.3f, %.3f, %.3f\n",
			object->tr1.x, object->tr1.y,
			object->tr1.z);
		printf("Vertex 2: %.3f, %.3f, %.3f\n",
			object->tr2.x, object->tr2.y,
			object->tr2.z);
		printf("Vertex 3: %.3f, %.3f, %.3f\n",
			object->tr3.x, object->tr3.y,
			object->tr3.z);
	}
	t_object_properties_print(object);
	printf("\n");
}

void	t_move_print(void *move_ptr)
{
	t_move	*move;

	move = (t_move *)move_ptr;
	printf("type=%d\n", (int)move->type);
	printf("Type: %s\n", \
		(char *[4]){"rotation", "self rotation", "translation", "scale"} \
		[(int)move->type]);
	printf("Target: %d\n", move->target);
	printf("Value: %.3f, %.3f, %.3f\n",
		move->value.x, move->value.y,
		move->value.z);
	printf("Speed: %f\n", move->speed);
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
	printf("Moves\n\n");
	ft_lstprint(scene->moves, &t_move_print);
	printf("\n");
}
