/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:20:48 by npirard           #+#    #+#             */
/*   Updated: 2024/02/27 14:40:32 by npirard          ###   ########.fr       */
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

static void	normalize_triangle(t_object *obj)
{
	t_vec3f	u;
	t_vec3f	v;

	if (obj->type != TR)
		return ;
	u = vec3_diff(&obj->tr2, &obj->tr1);
	v = vec3_diff(&obj->tr3, &obj->tr1);
	obj->orientation = vector_product(&u, &v);
	obj->origin = u;
	obj->top = v;
	normalize_vec(&obj->orientation);
}

// normalize triangle will give orientation to
// triangle. Therefore it must happen first
static void	normalize_objects(t_list *objects)
{
	t_list		*node;
	t_object	*obj;
	t_vec3f		temp;

	node = objects;
	while (node)
	{
		obj = (t_object *)node->content;
		normalize_triangle(obj);
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
		obj->_light = color_ratio(&obj->color_light, obj->k_light);
		obj->_glow = color_ratio(&obj->color_glow, obj->k_glow);
		normalize_cone(obj);
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
		light->_color = color_ratio(&light->color, light->ratio);
		node = node->next;
	}
}

void	normalize_scene(t_scene *scene)
{
	normalize_objects(scene->objects);
	scene->ambiant_light._color = color_ratio(&scene->ambiant_light.color,
			scene->ambiant_light.ratio);
	normalize_lights(scene->lights);
}
