/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:50:01 by npirard           #+#    #+#             */
/*   Updated: 2024/02/26 13:28:11 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>

void	transform_objects(t_data *data, t_matrix3f *matrix,
			double angle, int target)
{
	t_list		*node;
	t_object	*obj;

	node = data->scene.objects;
	while (node)
	{
		obj = (t_object *)node->content;
		if (target == 0 || target == obj->id)
		{
			if (matrix)
			{
				obj->orientation = vec3f_matrix3f(&obj->orientation, matrix);
				obj->origin = vec3f_matrix3f(&obj->origin, matrix);
				obj->top = vec3f_matrix3f(&obj->top, matrix);
				obj->loc_x = vec3f_matrix3f(&obj->loc_x, matrix);
				obj->loc_y = vec3f_matrix3f(&obj->loc_y, matrix);
				obj->loc_z = vec3f_matrix3f(&obj->loc_z, matrix);
			}
			obj->angle += angle;
		}
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

static void	tranform_moves(t_data *data, t_matrix3f *matrix)
{
	t_list	*node;
	t_move	*move;

	node = data->scene.moves;
	while (node)
	{
		move = (t_move *)node->content;
		move->value = vec3f_matrix3f(&move->value, matrix);
		node = node->next;
	}
}

void	translate_scene(t_data *data, t_vec3f *dir)
{
	t_list		*node;
	t_object	*obj;
	t_light		*light;

	node = data->scene.objects;
	while (node)
	{
		obj = (t_object *)node->content;
		obj->origin = vec3_diff(&obj->origin, dir);
		obj->top = vec3_diff(&obj->top, dir);
		node = node->next;
	}
	node = data->scene.lights;
	while (node)
	{
		light = (t_light *)node->content;
		light->origin = vec3_diff(&light->origin, dir);
		node = node->next;
	}
	data->scene.camera.origin.x = 0;
	data->scene.camera.origin.y = 0;
	data->scene.camera.origin.z = 0;
}

void	transform_scene(t_data *data, t_matrix3f *matrix, double angle)
{
	transform_objects(data, matrix, angle, 0);
	transform_lights(data, matrix);
	tranform_moves(data, matrix);
}
