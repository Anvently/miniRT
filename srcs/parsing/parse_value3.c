/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:32:20 by npirard           #+#    #+#             */
/*   Updated: 2024/02/25 15:09:26 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <libft.h>

int	scene_parse_light_obj(char **ptr, t_object *obj)
{
	t_list		*node;

	node = ft_lstnew(obj);
	if (!node)
		return (error("parsing object"), 1);
	ft_lstadd_back(&obj->data->scene.lights_obj, node);
	if (scene_parse_color(ptr, &obj->color_light))
		return (1);
	return (0);
}
