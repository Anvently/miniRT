/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:50:01 by npirard           #+#    #+#             */
/*   Updated: 2024/02/19 18:27:12 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/calculus.h>
#include <libft.h>

static void	tranform_objects(t_data *data, t_matrix3f *matrix)
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

void	transform_scene(t_data *data, t_matrix3f *matrix)
{
	tranform_objects(data, matrix);
	transform_lights(data, matrix);
}
