/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:08:26 by npirard           #+#    #+#             */
/*   Updated: 2024/02/15 13:10:30 by lmahe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt/minirt.h>
#include <minirt/parsing.h>
#include <minirt/objects.h>
#include <minirt/calculus.h>

int	scene_parse_sphere(t_object *object, int nbr, char **ptr, char *line)
{
	if (scene_parse_origin(ptr, &object->origin))
		return (error_parsing("sphere origin", nbr, line), 1);
	if (scene_parse_double(ptr, &object->radius))
		return (error_parsing("sphere diameter", nbr, line), 1);
	object->radius /= 2;
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
	t_vec3f	temp;

	if (scene_parse_origin(ptr, &object->origin))
		return (error_parsing("cylinder origin", nbr, line), 1);
	if (scene_parse_orientation(ptr, &object->orientation))
		return (error_parsing("cylinder orientation", nbr, line), 1);
	if (scene_parse_double(ptr, &object->radius))
		return (error_parsing("cylinder diameter", nbr, line), 1);
	object->radius /= 2;
	if (scene_parse_double(ptr, &object->height))
		return (error_parsing("cylinder height", nbr, line), 1);
	temp = vec3_scale(&object->orientation, object->height / 2);
	object->top = vec3_sum(&object->origin, &temp);
	object->origin = vec3_diff(&object->origin, &temp);
	if (scene_parse_color(ptr, &object->color))
		return (error_parsing("cylinder color", nbr, line), 1);
	return (0);
}
