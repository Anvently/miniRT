/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:08:26 by npirard           #+#    #+#             */
/*   Updated: 2024/02/22 15:39:11 by npirard          ###   ########.fr       */
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
	return (0);
}

int	scene_parse_plan(t_object *object, int nbr, char **ptr, char *line)
{
	if (scene_parse_origin(ptr, &object->origin))
		return (error_parsing("plan origin", nbr, line), 1);
	if (scene_parse_orientation(ptr, &object->orientation))
		return (error_parsing("plan orientation", nbr, line), 1);
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
	return (0);
}

int	scene_parse_obj_properties(t_object *object, int nbr,
		char *ptr, char *line)
{
	if (*skip_space(&ptr) && scene_parse_texture(&ptr, object, nbr, line))
		return (1);
	if (*skip_space(&ptr) && scene_parse_ratio(&ptr, &object->k_ambiant))
		return (error_parsing("object ambiant light reflexion",
				nbr, line), 1);
	if (*skip_space(&ptr) && scene_parse_ratio(&ptr, &object->k_diffuse))
		return (error_parsing("object diffuse light reflexion",
				nbr, line), 1);
	if (*skip_space(&ptr) && scene_parse_ratio(&ptr, &object->k_specular))
		return (error_parsing("object specular light reflexion",
				nbr, line), 1);
	if (*skip_space(&ptr) && scene_parse_ratio(&ptr, &object->k_reflexion))
		return (error_parsing("object reflexion constant", nbr, line), 1);
	if (*skip_space(&ptr) && scene_parse_ratio(&ptr, &object->k_plastic))
		return (error_parsing("object plastic reflexion", nbr, line), 1);
	if (*skip_space(&ptr) && (scene_parse_double(&ptr, &object->k_roughness)
			|| object->k_roughness < 1.0))
		return (error_parsing("object roughness", nbr, line), 1);
	return (0);
}
