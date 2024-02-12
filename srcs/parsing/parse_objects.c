/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:08:26 by npirard           #+#    #+#             */
/*   Updated: 2024/02/12 18:18:55 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <minirt/objects.h>

int	scene_parse_sphere(t_object *object, int nbr, char **ptr, char *line)
{
	if (scene_parse_origin(ptr, &object->origin))
		return (error_parsing("sphere origin", nbr, line), 1);
	if (scene_parse_float(ptr, &object->diameter))
		return (error_parsing("sphere diameter", nbr, line), 1);
	if (scene_parse_color(ptr, &object->color))
		return (error_parsing("sphere color", nbr, line), 1);
	return (0);
}

int	scene_parse_plan(t_object *object, int nbr, char **ptr, char *line)
{
	if (scene_parse_origin(ptr, &object->origin))
		return (error_parsing("plan origin", nbr, line), 1);
	if (scene_parse_orientation(ptr, &object->orientation))
		return (error_parsing("plan orientation", nbr, line), 1);
	if (scene_parse_color(ptr, &object->color))
		return (error_parsing("plan color", nbr, line), 1);
	return (0);
}

int	scene_parse_cylinder(t_object *object, int nbr, char **ptr, char *line)
{
	if (scene_parse_origin(ptr, &object->origin))
		return (error_parsing("cylinder origin", nbr, line), 1);
	if (scene_parse_orientation(ptr, &object->orientation))
		return (error_parsing("cylinder orientation", nbr, line), 1);
	if (scene_parse_float(ptr, &object->diameter))
		return (error_parsing("cylinder diameter", nbr, line), 1);
	if (scene_parse_float(ptr, &object->height))
		return (error_parsing("cylinder height", nbr, line), 1);
	if (scene_parse_color(ptr, &object->color))
		return (error_parsing("cylinder color", nbr, line), 1);
	return (0);
}
