/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmahe <lmahe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:08:26 by npirard           #+#    #+#             */
/*   Updated: 2024/02/21 09:57:33 by lmahe            ###   ########.fr       */
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
	if (scene_parse_double(ptr, &object->radius))
		return (error_parsing("cylinder diameter", nbr, line), 1);
	if (scene_parse_double(ptr, &object->height))
		return (error_parsing("cylinder height", nbr, line), 1);
	if (scene_parse_color(ptr, &object->color))
		return (error_parsing("cylinder color", nbr, line), 1);
	return (0);
}

int	scene_parse_cone(t_object *object, int nbr, char **ptr, char *line)
{
	if (scene_parse_origin(ptr, &object->origin))
		return (error_parsing("cone origin", nbr, line), 1);
	if (scene_parse_orientation(ptr, &object->orientation))
		return (error_parsing("cone orientation", nbr, line), 1);
	if (scene_parse_double(ptr, &object->radius))
		return (error_parsing("cone radius", nbr, line), 1);
	if (scene_parse_double(ptr, &object->height))
		return (error_parsing("cone height", nbr, line), 1);
	if (scene_parse_color(ptr, &object->color))
		return (error_parsing("disk color", nbr, line), 1);
	return (0);
}

int	scene_parse_obj_properties(t_object *object, int nbr,
		char *ptr, char *line)
{
	object->k_ambiant = 1.0;
	object->k_diffuse = 1.0;
	object->k_specular = 1.0;
	object->k_plastic = 1.0;
	while (ft_isspace(*ptr))
		ptr++;
	if (*ptr && scene_parse_ratio(&ptr, &object->k_ambiant))
		return (error_parsing("object ambiant light reflexion",
				nbr, line), 1);
	if (*ptr && scene_parse_ratio(&ptr, &object->k_diffuse))
		return (error_parsing("object diffuse light reflexion",
				nbr, line), 1);
	if (*ptr && scene_parse_ratio(&ptr, &object->k_specular))
		return (error_parsing("object specular light reflexion",
				nbr, line), 1);
	if (*ptr && scene_parse_ratio(&ptr, &object->k_plastic))
		return (error_parsing("object plastic reflexion reflexion",
				nbr, line), 1);
	return (0);
}
