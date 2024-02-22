/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:20:48 by npirard           #+#    #+#             */
/*   Updated: 2024/02/22 12:12:57 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>

static	void	normalize_cone(t_object *obj)
{
	t_vec3f	temp;

	if (obj->type != CONE)
		return ;
	temp = vec3_scale(&obj->orientation, obj->height);
	obj->top = vec3_sum(&obj->origin, &temp);
}

static void	compute_color_constant(t_object *obj)
{
	obj->color_ambiant = color_ratio(&obj->color, obj->k_ambiant);
	obj->color_diffuse = color_ratio(&obj->color, obj->k_diffuse);
	obj->color_specular = color_ratio(&obj->color, (1.f - obj->k_plastic));
	color_add(&obj->color_specular,
		(t_color3f){obj->k_plastic, obj->k_plastic, obj->k_plastic});
	obj->color_specular = color_ratio(&obj->color_specular, obj->k_specular);
	// color_unsature(&obj->color_specular);
}

static void	normalize_objects(t_list *objects)
{
	t_list		*node;
	t_object	*obj;
	t_vec3f		temp;

	node = objects;
	while (node)
	{
		obj = (t_object *)node->content;
		normalize_vec(&obj->orientation);
		get_local_base(obj);
		if (obj->type == CYLINDER || obj->type == SPHERE)
			obj->radius /= 2;
		if (obj->type == CYLINDER)
		{
			temp = vec3_scale(&obj->orientation, obj->height / 2);
			obj->top = vec3_sum(&obj->origin, &temp);
			obj->origin = vec3_diff(&obj->origin, &temp);
		}
		normalize_cone(obj);
		compute_color_constant(obj);
		node = node->next;
	}
}

// void	normalize_lights(t_list *lights)
// {
// 	t_list		*node;
// 	t_light		*light;

// 	node = lights;
// 	while (node)
// 	{
// 		light = (t_light *)node->content;
// 		node = node->next;
// 	}
// }

void	normalize_scene(t_scene *scene)
{
	normalize_objects(scene->objects);
	scene->ambiant_light._ambiant = color_ratio(&scene->ambiant_light.color,
			scene->ambiant_light.ratio);
}
