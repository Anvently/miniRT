/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:20:48 by npirard           #+#    #+#             */
/*   Updated: 2024/02/20 15:19:09 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>

static void	normalize_objects(t_list *objects)
{
	t_list		*node;
	t_object	*obj;
	t_vec3f		temp;

	node = objects;
	while (node)
	{
		obj = (t_object *)node->content;
		if (obj->type == CYLINDER || obj->type == SPHERE)
			obj->radius /= 2;
		if (obj->type == CYLINDER)
		{
			temp = vec3_scale(&obj->orientation, obj->height / 2);
			obj->top = vec3_sum(&obj->origin, &temp);
			obj->origin = vec3_diff(&obj->origin, &temp);
		}
		obj->color_ambiant = color_ratio(&obj->color, obj->k_ambiant);
		obj->color_diffuse = color_ratio(&obj->color, obj->k_diffuse);
		obj->color_specular = color_ratio(&obj->color, obj->k_specular);
		// obj->color = color_normalize(&obj->color);
		node = node->next;
	}
}

void	normalize_lights(t_list *lights)
{
	t_list		*node;
	t_light		*light;

	node = lights;
	while (node)
	{
		light = (t_light *)node->content;
		// light->color = color_normalize(&light->color);
		node = node->next;
	}
}

void	normalize_scene(t_scene *scene)
{
	normalize_objects(scene->objects);
	// normalize_lights(scene->lights);
	// scene->ambiant_light.color = color_normalize(&scene->ambiant_light.color);
	scene->ambiant_light._ambiant = color_ratio(&scene->ambiant_light.color,
			scene->ambiant_light.ratio);
}
