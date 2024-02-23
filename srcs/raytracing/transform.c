/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:50:01 by npirard           #+#    #+#             */
/*   Updated: 2024/02/23 13:53:11 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>

static void	transform_objects(t_data *data, t_matrix3f *matrix, double angle)
{
	t_list		*node;
	t_object	*obj;

	node = data->scene.objects;
	while (node)
	{
		obj = (t_object *)node->content;
		obj->orientation = vec3f_matrix3f(&obj->orientation, matrix);
		obj->origin = vec3f_matrix3f(&obj->origin, matrix);
		obj->top = vec3f_matrix3f(&obj->top, matrix);
		obj->loc_x = vec3f_matrix3f(&obj->loc_x, matrix);
		obj->loc_y = vec3f_matrix3f(&obj->loc_y, matrix);
		obj->loc_z = vec3f_matrix3f(&obj->loc_z, matrix);
		obj->angle += angle;
		node = node->next;
	}
}

void	transform_angle(t_data *data, double angle)
{
	t_list		*node;
	t_object	*obj;

	node = data->scene.objects;
	while (node)
	{
		obj = (t_object *)node->content;
		if (obj->type == SPHERE)
			obj->angle += angle;
		node = node->next;
	}
}

static void	transform_lights(t_data *data, t_matrix3f *matrix)
{
	t_list		*node;
	t_light		*light;

	node = data->scene.lights;
	while (node)
	{
		light = (t_light *)node->content;
		light->origin = vec3f_matrix3f(&light->origin, matrix);
		node = node->next;
	}
}

void	transform_scene(t_data *data, t_matrix3f *matrix, double angle)
{
	transform_objects(data, matrix, angle);
	transform_lights(data, matrix);
}
